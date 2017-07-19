#include "SkiaWindow.h"
#include "SkiaCanvas.h"

#include <gl/GrGLInterface.h>
#include <gl/GrGLDefines.h>
#include <gl/GrGLUtil.h>
#include <GrContext.h>
#include <GrBackendSurface.h>
#include <GrContextOptions.h>
#include <SkRefCnt.h>
#include <SkSurface.h>
#include <SkSurfaceProps.h>
#include <SkCanvas.h>

#include <iostream>
#include <atomic>

SkiaWindow::MainLoop::MainLoop(Nan::Callback *cb,
                               EGLNativeBackend* backend,
                               SkiaWindow *window,
                               int width, int height)
  : AsyncWorker(cb),
    backend_(backend),
    window_(window),
    width_(width),
    height_(height) {
}

SkiaWindow::MainLoop::~MainLoop() {
  std::cout << "SkiaWindow::MainLoop::~MainLoop" << std::endl;
}

void SkiaWindow::MainLoop::Execute() {
  sk_sp<const GrGLInterface> interface;
  GrContext* context;
  GrGLFramebufferInfo fbInfo;
  GrGLint buffer;
  GrPixelConfig config = kRGBA_8888_GrPixelConfig;
  sk_sp<SkSurface> surface;
  sk_sp<SkColorSpace> color_space = nullptr;
  SkSurfaceProps surface_props = SkSurfaceProps::kLegacyFontHost_InitType;

  if (!backend_) {
    Nan::ThrowError("No backend for window !");
    return;
  }

  if (!backend_->Initialise()) {
    Nan::ThrowError("EGL initialisation failed !");
    return;
  }

  backend_->Reset();

  interface.reset(GrGLCreateNativeInterface());
  if (!interface.get()) {
    Nan::ThrowError("SKIA interface initialisation failed !");
    return;
  }

  context = GrContext::Create(kOpenGL_GrBackend,
                              (GrBackendContext)interface.get());

  if (!context) {
    Nan::ThrowError("SKIA context initialisation failed !");
    return;
  }

  GR_GL_GetIntegerv(interface.get(), GR_GL_FRAMEBUFFER_BINDING, &buffer);
  fbInfo.fFBOID = buffer;

  GrBackendRenderTarget backendRT(width_,
                                  height_,
                                  backend_->SampleCount(),
                                  backend_->StencilBits(),
                                  config,
                                  fbInfo);

  surface= SkSurface::MakeFromBackendRenderTarget(context,
                                                  backendRT,
                                                  kBottomLeft_GrSurfaceOrigin,
                                                  color_space,
                                                  &surface_props);

  if (!surface.get()) {
    Nan::ThrowError("SKIA surface initialisation failed !");
    return;
  }

  while (window_->Running()) {
    SkCanvas *canvas = surface->getCanvas();
    window_->Draw(canvas);
    canvas->flush();
    context->flush();
    backend_->SwapBuffers();
    usleep(40000);
  }

  std::cout << "Loop done" << std::endl;
}

NAN_MODULE_INIT(SkiaWindow::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(SkiaWindow::New);
  tpl->SetClassName(Nan::New("Window").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "start", SkiaWindow::Start);
  Nan::SetPrototypeMethod(tpl, "stop", SkiaWindow::Stop);
  Nan::SetPrototypeMethod(tpl, "release", SkiaWindow::Release);
  Nan::SetPrototypeMethod(tpl, "setDrawHandler", SkiaWindow::SetDrawHandler);

  constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("Window").ToLocalChecked(),
           Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(SkiaWindow::New) {
  if (info.Length() != 2) {
    Nan::ThrowError("Invalid number of argument for window constructor !");
    return;
  }

  if (info.IsConstructCall()) {
    if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
      Nan::ThrowError("Invalid argument for window constructor !");
      return;
    }

    SkiaWindow *window = new SkiaWindow(static_cast<int>(info[0]->Uint32Value()),
                                        static_cast<int>(info[1]->Uint32Value()));

    window->Wrap(info.This());

    info.GetReturnValue().Set(info.This());
  } else {
    const int argc = 2;
    v8::Local<v8::Value> argv[argc] = { info[0], info[1] };
    v8::Local<v8::Function> cons = Nan::New(SkiaWindow::constructor());

    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

NAN_METHOD(SkiaWindow::Start) {
  SkiaWindow* window = Nan::ObjectWrap::Unwrap<SkiaWindow>(info.Holder());
  window->Start();
}

NAN_METHOD(SkiaWindow::Stop) {
  SkiaWindow* window = Nan::ObjectWrap::Unwrap<SkiaWindow>(info.Holder());
  window->Stop();
}

NAN_METHOD(SkiaWindow::Release) {
  SkiaWindow* window = Nan::ObjectWrap::Unwrap<SkiaWindow>(info.Holder());
  window->Release();
}

NAN_METHOD(SkiaWindow::SetDrawHandler) {
  SkiaWindow* window = Nan::ObjectWrap::Unwrap<SkiaWindow>(info.Holder());

  if (info.Length() != 1) {
    Nan::ThrowError("Invalid number of argument for setDrawHandler !");
    return;
  }

  if (!info[0]->IsFunction()) {
    Nan::ThrowError("Invalid argument for setDrawHandler !");
    return;
  }

  window->SetDrawHandler(info[0].As<v8::Function>());
}

typedef struct {
    SkiaWindow *window;
    SkCanvas *canvas;
} AsyncData;

void SkiaWindow::ThreadJumper(uv_async_t* handle) {
  if (handle && handle->data && ((AsyncData*)handle->data)->canvas) {
    ((AsyncData*)handle->data)->window->CallDrawHandler(((AsyncData*)handle->data)->canvas);
  }
}

SkiaWindow::SkiaWindow(int width, int height)
  : backend_(EGLNativeBackend::CreateBackend(width, height)),
    loop_(NULL),
    has_draw_handler_(false),
    has_view_(false),
    width_(width),
    height_(height),
    running_(false) {

  async_.data = new AsyncData();
  ((AsyncData*)async_.data)->window = this;
  ((AsyncData*)async_.data)->canvas = NULL;

  uv_cond_init(&cond_);
  uv_mutex_init(&mutex_);
  uv_async_init(uv_default_loop(), &async_, &SkiaWindow::ThreadJumper);
}

SkiaWindow::~SkiaWindow() {
  Release();
}

NAN_METHOD(SkiaWindow::onMainLoopEnd) {
  std::cout << "SkiaWindow::onMainLoopEnd" << std::endl;
}

void SkiaWindow::Start() {
  if (!backend_) {
    Nan::ThrowError("No backend for window !");
    return;
  }

  v8::Local<v8::Function> fn = Nan::New<v8::FunctionTemplate>(SkiaWindow::onMainLoopEnd)->GetFunction();

  running_ = true;
  loop_ = new MainLoop(new Nan::Callback(fn), backend_, this, width_, height_);
  Nan::AsyncQueueWorker(loop_);
}

void SkiaWindow::Stop() {
  if (!loop_) {
    Nan::ThrowError("Window is not started !");
    return;
  }

  running_ = false;
}

void SkiaWindow::Release() {
  if (backend_) {
    delete backend_;
    backend_ = NULL;
  }

  AsyncData* data = (AsyncData*)async_.data;
  delete data;

  uv_close((uv_handle_t*)&async_, NULL);
}

void SkiaWindow::SetDrawHandler(v8::Local<v8::Function> handler) {
  draw_handler_.SetFunction(handler);
  has_draw_handler_ = true;
}

void SkiaWindow::Draw(SkCanvas *canvas) {
  if (has_draw_handler_) {
    ((AsyncData*)async_.data)->canvas = canvas;
    uv_async_send(&async_);
    uv_cond_wait(&cond_, &mutex_);
  }
  if (has_view_) {
    // view_->Draw(canvas);
  }
}

void SkiaWindow::CallDrawHandler(SkCanvas *canvas) {
  if (has_draw_handler_) {
    Nan::HandleScope scope;
    v8::Local<v8::Value> argv[] = { SkiaCanvas::CreateObject(canvas) };
    draw_handler_.Call(1, argv);
    // usleep(1000);
    uv_cond_signal(&cond_);
  }
}

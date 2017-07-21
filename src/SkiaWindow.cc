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
                               EGLNativeInterface* backend,
                               SkiaWindow *window,
                               uv_mutex_t *mutex,
                               int width, int height)
  : AsyncWorker(cb),
    egl_interface_(backend),
    window_(window),
    mutex_(mutex),
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

  if (!egl_interface_) {
    Nan::ThrowError("No backend for window !");
    return;
  }

  if (!egl_interface_->Initialise()) {
    Nan::ThrowError("EGL initialisation failed !");
    return;
  }

  egl_interface_->Reset();

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
                                  egl_interface_->SampleCount(),
                                  egl_interface_->StencilBits(),
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

  egl_interface_->SetupEvents();

  while (window_->Running()) {
    SkCanvas *canvas = surface->getCanvas();
    uv_mutex_lock(mutex_);
    window_->Draw(canvas);
    canvas->flush();
    uv_mutex_unlock(mutex_);
    context->flush();
    egl_interface_->SwapBuffers();
    egl_interface_->ProcessEvents();
    usleep(40000);
  }
}

NAN_MODULE_INIT(SkiaWindow::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(SkiaWindow::New);
  tpl->SetClassName(Nan::New("Window").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "start", SkiaWindow::Start);
  Nan::SetPrototypeMethod(tpl, "stop", SkiaWindow::Stop);
  Nan::SetPrototypeMethod(tpl, "release", SkiaWindow::Release);
  Nan::SetPrototypeMethod(tpl, "setDrawHandler", SkiaWindow::SetDrawHandler);
  Nan::SetPrototypeMethod(tpl, "setView", SkiaWindow::SetView);
  Nan::SetPrototypeMethod(tpl, "on", SkiaWindow::On);

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

NAN_METHOD(SkiaWindow::SetView) {
  SkiaWindow* window = Nan::ObjectWrap::Unwrap<SkiaWindow>(info.Holder());

  if (info.Length() != 1) {
    Nan::ThrowError("Invalid number of argument for setDrawHandler !");
    return;
  }

  if (!info[0]->IsObject()) {
    Nan::ThrowError("Invalid argument for setDrawHandler !");
    return;
  }

  window->SetView(info[0].As<v8::Object>());
}

NAN_METHOD(SkiaWindow::On) {
  SkiaWindow* window = Nan::ObjectWrap::Unwrap<SkiaWindow>(info.Holder());

  if (info.Length() != 2) {
    Nan::ThrowError("Invalid number of argument for Window.On !");
    return;
  }

  if (!info[0]->IsString() || !info[1]->IsFunction()) {
    Nan::ThrowError("Invalid argument for Window.On !");
    return;
  }

  Nan::Utf8String val(info[0]);

  window->AddEventHandler(std::string(*val), info[1].As<v8::Function>());
}

typedef struct {
    SkiaWindow *window;
    SkCanvas *canvas;
} DrawAsyncData;

void SkiaWindow::DrawThreadJumper(uv_async_t* handle) {
  if (handle && handle->data && ((DrawAsyncData*)handle->data)->canvas) {
    ((DrawAsyncData*)handle->data)->window->CallDrawHandlerOnNodeThread(((DrawAsyncData*)handle->data)->canvas);
  }
}

typedef struct {
    SkiaWindow *window;
    EGLNativeInterface::Event* event;
} EventAsyncData;

void SkiaWindow::EventThreadJumper(uv_async_t* handle) {
  if (handle && handle->data) {
    ((EventAsyncData*)handle->data)->window->CallEventHandlersOnNodeThread(
      ((EventAsyncData*)handle->data)->event);
  }
}

SkiaWindow::SkiaWindow(int width, int height)
  : egl_interface_(EGLNativeInterface::CreateBackend(width, height, this)),
    loop_(NULL),
    has_draw_handler_(false),
    view_(NULL),
    width_(width),
    height_(height),
    running_(false) {

  draw_async_.data = new DrawAsyncData();
  ((DrawAsyncData*)draw_async_.data)->window = this;
  ((DrawAsyncData*)draw_async_.data)->canvas = NULL;

  event_async_.data = new EventAsyncData();
  ((EventAsyncData*)event_async_.data)->window = this;
  ((EventAsyncData*)event_async_.data)->event = NULL;

  uv_mutex_init(&event_mutex_);
  uv_cond_init(&draw_cond_);
  uv_mutex_init(&draw_cond_mutex_);
  uv_mutex_init(&draw_mutex_);
  uv_async_init(uv_default_loop(), &draw_async_, &SkiaWindow::DrawThreadJumper);
  uv_async_init(uv_default_loop(), &event_async_, &SkiaWindow::EventThreadJumper);
}

SkiaWindow::~SkiaWindow() {
  Release();
}

NAN_METHOD(SkiaWindow::onMainLoopEnd) {
}

void SkiaWindow::Start() {
  if (!egl_interface_) {
    Nan::ThrowError("No backend for window !");
    return;
  }

  v8::Local<v8::Function> fn = Nan::New<v8::FunctionTemplate>(SkiaWindow::onMainLoopEnd)->GetFunction();

  running_ = true;
  loop_ = new MainLoop(new Nan::Callback(fn), egl_interface_, this,
                       &draw_mutex_, width_, height_);
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
  if (egl_interface_) {
    delete egl_interface_;
    egl_interface_ = NULL;
  }

  delete ((DrawAsyncData*)draw_async_.data);
  delete ((EventAsyncData*)event_async_.data);

  uv_close((uv_handle_t*)&draw_async_, NULL);
  uv_close((uv_handle_t*)&event_async_, NULL);
}

void SkiaWindow::SetDrawHandler(v8::Local<v8::Function> handler) {
  draw_handler_.SetFunction(handler);
  has_draw_handler_ = true;
}

void SkiaWindow::Draw(SkCanvas *canvas) {
  if (has_draw_handler_) {
    ((DrawAsyncData*)draw_async_.data)->canvas = canvas;
    uv_async_send(&draw_async_);
    uv_cond_wait(&draw_cond_, &draw_cond_mutex_);
  }

  if (view_)
    view_->Draw(canvas);
}

void SkiaWindow::CallDrawHandlerOnNodeThread(SkCanvas *canvas) {
  uv_mutex_lock(&draw_mutex_);
  if (has_draw_handler_) {
    Nan::HandleScope scope;
    v8::Local<v8::Value> argv[] = { SkiaCanvas::CreateObject(canvas) };
    draw_handler_.Call(1, argv);
  }

  uv_cond_signal(&draw_cond_);
  uv_mutex_unlock(&draw_mutex_);
}

void SkiaWindow::SetView(v8::Local<v8::Object> view) {
  view_ = Nan::ObjectWrap::Unwrap<SkiaView>(view);
}

void SkiaWindow::AddEventHandler(std::string name, v8::Local<v8::Function> handler) {
  uv_mutex_lock(&event_mutex_);
  event_handlers_[name].push_back(new Nan::Callback(handler));
  uv_mutex_unlock(&event_mutex_);
}

void SkiaWindow::RemoveEventHandler(std::string name, v8::Local<v8::Function> handler) {
  uv_mutex_lock(&event_mutex_);

  if (event_handlers_.find(name) == event_handlers_.end()) {
    uv_mutex_unlock(&event_mutex_);
    return;
  }

  for (EventHandlerVector::iterator it = event_handlers_[name].begin();
       it != event_handlers_[name].end(); ++it) {
    if (*(*(*it)) == handler) {
      event_handlers_[name].erase(it);
      delete (*it);
      break;
    }
  }

  uv_mutex_unlock(&event_mutex_);
}

void SkiaWindow::EmitEvent(EGLNativeInterface::Event* event) {
    ((EventAsyncData*)event_async_.data)->event = event;
    uv_async_send(&event_async_);
}

void SkiaWindow::CallEventHandlersOnNodeThread(EGLNativeInterface::Event* event) {
  if (!event)
    return;

  const std::string name = event->GetName();

  uv_mutex_lock(&event_mutex_);

  if (event_handlers_.find(name) != event_handlers_.end()) {
    Nan::HandleScope scope;
    v8::Local<v8::Value> argv[] = { event->GetData() };

    for (EventHandlerVector::iterator it = event_handlers_[name].begin();
       it != event_handlers_[name].end(); ++it) {
      (*it)->Call(1, argv);
    }
  }

  uv_mutex_unlock(&event_mutex_);

  delete event;
}

void SkiaWindow::ClearEventHandlers() {
  uv_mutex_lock(&event_mutex_);
  for (std::map<std::string, EventHandlerVector>::iterator it = event_handlers_.begin();
       it != event_handlers_.end(); ++it) {
    for (EventHandlerVector::iterator jt= it->second.begin();
         jt != it->second.end(); ++jt) {
      delete (*jt);
    }
    it->second.clear();
  }
  uv_mutex_unlock(&event_mutex_);
}

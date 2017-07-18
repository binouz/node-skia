#include "SkiaWindow.h"
#include "SkiaCanvas.h"

#include <gl/GrGLDefines.h>
#include <gl/GrGLUtil.h>
#include <GrBackendSurface.h>
#include <GrContextOptions.h>

#include <SkCanvas.h>

#include <iostream>

NAN_MODULE_INIT(SkiaWindow::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(SkiaWindow::New);
  tpl->SetClassName(Nan::New("Window").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "initialise", SkiaWindow::Initialise);
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

NAN_METHOD(SkiaWindow::Initialise) {
  SkiaWindow* window = Nan::ObjectWrap::Unwrap<SkiaWindow>(info.Holder());
  window->Initialise();
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

SkiaWindow::SkiaWindow(int width, int height)
  : backend_(EGLNativeBackend::CreateBackend(width, height)),
    surface_props_(SkSurfaceProps::kLegacyFontHost_InitType),
    has_draw_handler_(false),
    width_(width),
    height_(height) {
}

SkiaWindow::~SkiaWindow() {
  Release();
}

void SkiaWindow::Initialise() {
  if (!backend_) {
    Nan::ThrowError("No backend for window !");
    return;
  }

  if (!backend_->Initialise()) {
    Nan::ThrowError("EGL initialisation failed !");
    return;
  }

  backend_->Reset();

  interface_.reset(GrGLCreateNativeInterface());
  if (!interface_.get()) {
    Nan::ThrowError("SKIA interface initialisation failed !");
    return;
  }

  context_ = GrContext::Create(kOpenGL_GrBackend,
                               (GrBackendContext)interface_.get());

  if (!context_) {
    Nan::ThrowError("SKIA context initialisation failed !");
    return;
  }

  GrPixelConfig config = kRGBA_8888_GrPixelConfig;
  GrGLFramebufferInfo fbInfo;
  GrGLint buffer;

  GR_GL_GetIntegerv(interface_.get(), GR_GL_FRAMEBUFFER_BINDING, &buffer);
  fbInfo.fFBOID = buffer;

  GrBackendRenderTarget backendRT(width_,
                                  height_,
                                  backend_->SampleCount(),
                                  backend_->StencilBits(),
                                  config,
                                  fbInfo);
  sk_sp<SkColorSpace> color_space = nullptr;

  surface_= SkSurface::MakeFromBackendRenderTarget(context_,
                                                   backendRT,
                                                   kBottomLeft_GrSurfaceOrigin,
                                                   color_space,
                                                   &surface_props_);

  if (!surface_.get()) {
    Nan::ThrowError("SKIA surface initialisation failed !");
  }
}

void SkiaWindow::Start() {
  if (!backend_) {
    Nan::ThrowError("No backend for window !");
    return;
  }

  while (1) {
    SkCanvas *canvas = surface_->getCanvas();

    if (has_draw_handler_) {
      v8::Local<v8::Value> argv[] = { SkiaCanvas::CreateObject(canvas) };
      draw_handler_.Call(1, argv);
    }

    canvas->flush();
    backend_->SwapBuffers();
    usleep(40000);
  }
}

void SkiaWindow::Stop() {
  if (!backend_) {
    Nan::ThrowError("No backend for window !");
    return;
  }
}

void SkiaWindow::Release() {
  if (backend_)
    delete backend_;
}

void SkiaWindow::SetDrawHandler(v8::Local<v8::Function> handler) {
  draw_handler_.SetFunction(handler);
  has_draw_handler_ = true;
}

#include "EGLNativeInterface.h"

#include <iostream>

#define USE_FBDEV_INTERFACE 0
#define USE_X11_INTERFACE 1

static const EGLint configAttribs[] = {
  EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
  EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
  EGL_RED_SIZE, 8,
  EGL_GREEN_SIZE, 8,
  EGL_BLUE_SIZE, 8,
  EGL_ALPHA_SIZE, 8,
  EGL_DEPTH_SIZE, 8,
  EGL_STENCIL_SIZE, 8,
  EGL_NONE
};

static const EGLint contextAttribs[] = {
  EGL_CONTEXT_CLIENT_VERSION, 2,
  EGL_NONE
};

#if USE_FBDEV_INTERFACE
#include "EGLNativeInterfaceFbdev.cc"
#elif USE_X11_INTERFACE
#include "EGLNativeInterfaceX11.cc"
#else
#error "No native interface available..."
#endif

EGLNativeInterface *EGLNativeInterface::CreateBackend(int width, int height, EGLNativeInterface::EventClient *client) {
  return new EGLNativeInterfaceX11(width, height, client);
}

EGLNativeInterface::EGLNativeInterface(int width, int height)
  : display_(EGL_NO_DISPLAY),
    surface_(EGL_NO_SURFACE),
    context_(EGL_NO_CONTEXT),
    width_(width),
    height_(height) {
}

EGLNativeInterface::~EGLNativeInterface() {
  Release();
}

bool EGLNativeInterface::Initialise() {
  if (display_ == EGL_NO_DISPLAY) {
    display_ = GetDisplay();

    if (display_ == EGL_NO_DISPLAY)
      return false;

    if (!eglBindAPI(EGL_OPENGL_ES_API))
      return false;

    if (!eglInitialize(display_, NULL, NULL))
      return false;
  }

  EGLint numConfigs;
  eglChooseConfig(display_, configAttribs, &config_, 1, &numConfigs);

  if (context_ == EGL_NO_CONTEXT) {
    context_ = eglCreateContext(display_, config_, EGL_NO_CONTEXT, contextAttribs);

    if (context_ == EGL_NO_CONTEXT) {
      std::cout << "EGLNativeInterface::Initialise: eglCreateContext failed" << std::endl;
      return false;
    }
  }

  if (surface_ == EGL_NO_SURFACE) {
    surface_ = CreateWindowSurface(display_, config_);

    if (surface_ == EGL_NO_SURFACE)
      return false;
  }

  if (!eglMakeCurrent(display_, surface_, surface_, context_)) {
    std::cout << "EGLNativeInterface::Initialise: eglMakeCurrent failed" << std::endl;
    return false;
  }

  // eglSwapInterval(display_, 1);

  return true;
}

void EGLNativeInterface::Reset() {
  glViewport(0, 0, width_, height_);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClearStencil(0);
  glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  eglSwapBuffers(display_, surface_);
}

void EGLNativeInterface::SwapBuffers() {
  eglSwapBuffers(display_, surface_);
}

void EGLNativeInterface::Release() {
  if (display_ != EGL_NO_DISPLAY) {
    if (context_ != EGL_NO_CONTEXT)
      eglDestroyContext(display_, context_);
    if (surface_ != EGL_NO_SURFACE)
      eglDestroySurface(display_, surface_);
    eglTerminate(display_);
  }
}

int EGLNativeInterface::StencilBits() {
  int res;
  eglGetConfigAttrib(display_, config_, EGL_STENCIL_SIZE, &res);
  return res;
}

int EGLNativeInterface::SampleCount() {
  int res;
  eglGetConfigAttrib(display_, config_, EGL_SAMPLES, &res);
  return res;
}

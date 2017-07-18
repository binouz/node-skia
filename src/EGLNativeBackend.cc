#include "EGLNativeBackend.h"

#include <iostream>

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

#if 0
#include <EGL/fbdev_window.h>

class EGLNativeBackendHisilicon : public EGLNativeBackend {

  protected:

    EGLDisplay GetDisplay() {
      return eglGetDisplay(EGL_DEFAULT_DISPLAY);
    }

    EGLSurface CreateWindowSurface(EGLDisplay display, EGLConfig config) {
      return eglCreateWindowSurface(display, config, &native_, NULL);
    }

    ~EGLNativeBackendX11() override {
    }

  private:

    EGLNativeBackendX11()
      : EGLNativeBackend() {
    }

    fbdev_window native_;

    friend EGLNativeBackend;
};
#endif

#if 1
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class EGLNativeBackendX11 : public EGLNativeBackend {

  public:

  protected:

    EGLDisplay GetDisplay() {
      display_ = XOpenDisplay(NULL);

      if (!display_) {
        std::cout << "EGLNativeBackendX11::GetDisplay : XOpenDisplay failed" << std::endl;
        return EGL_NO_DISPLAY;
      }

      return eglGetDisplay(display_);
    }

    EGLSurface CreateWindowSurface(EGLDisplay display, EGLConfig config) {
      EGLSurface res;
      EGLint vid;
      XVisualInfo *visInfo, visTemplate;
      XSetWindowAttributes attr;
      unsigned long mask;
      int num_visuals;
      int scrnum = DefaultScreen(display_);
      Window root = RootWindow(display_, scrnum);

      if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &vid)) {
        std::cout << "EGLNativeBackendX11::CreateWindowSurface : eglGetConfigAttrib failed" << std::endl;
        return EGL_NO_SURFACE;
      }

      visTemplate.visualid = vid;
      visInfo = XGetVisualInfo(display_, VisualIDMask, &visTemplate, &num_visuals);

      if (!visInfo) {
        std::cout << "EGLNativeBackendX11::CreateWindowSurface : XGetVisualInfo failed" << std::endl;
        return EGL_NO_SURFACE;
      }

      attr.background_pixel = 0;
      attr.border_pixel = 0;

      attr.colormap = XCreateColormap(display_, root, visInfo->visual, AllocNone);
      attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask;
      mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

      window_ = XCreateWindow(display_, root, 0, 0, width(), height(),
                              0, visInfo->depth, InputOutput,
                              visInfo->visual, mask, &attr);

      res = eglCreateWindowSurface(display, config, window_, NULL);

      XFree(visInfo);

      XMapWindow(display_, window_);

      return res;
    }

    ~EGLNativeBackendX11() override {
      if (display_) {
        XDestroyWindow(display_, window_);
        XCloseDisplay(display_);
      }
    }

  private:

    EGLNativeBackendX11(int width, int height)
      : EGLNativeBackend(width, height),
        display_(NULL) {
    }

    Display *display_;
    Window window_;

    friend EGLNativeBackend;
};
#endif

EGLNativeBackend *EGLNativeBackend::CreateBackend(int width, int height) {
  return new EGLNativeBackendX11(width, height);
}

EGLNativeBackend::EGLNativeBackend(int width, int height)
  : display_(EGL_NO_DISPLAY),
    surface_(EGL_NO_SURFACE),
    context_(EGL_NO_CONTEXT),
    width_(width),
    height_(height) {
}

EGLNativeBackend::~EGLNativeBackend() {
  Release();
}

bool EGLNativeBackend::Initialise() {
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
      std::cout << "EGLNativeBackend::Initialise: eglCreateContext failed" << std::endl;
      return false;
    }
  }

  if (surface_ == EGL_NO_SURFACE) {
    surface_ = CreateWindowSurface(display_, config_);

    if (surface_ == EGL_NO_SURFACE)
      return false;
  }

  if (!eglMakeCurrent(display_, surface_, surface_, context_)) {
    std::cout << "EGLNativeBackend::Initialise: eglMakeCurrent failed" << std::endl;
    return false;
  }

  // eglSwapInterval(display_, 1);

  return true;
}

void EGLNativeBackend::Reset() {
  glViewport(0, 0, width_, height_);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClearStencil(0);
  glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  eglSwapBuffers(display_, surface_);
}

void EGLNativeBackend::SwapBuffers() {
  eglSwapBuffers(display_, surface_);
}

void EGLNativeBackend::Release() {
  if (display_ != EGL_NO_DISPLAY) {
    if (context_ != EGL_NO_CONTEXT)
      eglDestroyContext(display_, context_);
    if (surface_ != EGL_NO_SURFACE)
      eglDestroySurface(display_, surface_);
    eglTerminate(display_);
  }
}

int EGLNativeBackend::StencilBits() {
  int res;
  eglGetConfigAttrib(display_, config_, EGL_STENCIL_SIZE, &res);
  return res;
}

int EGLNativeBackend::SampleCount() {
  int res;
  eglGetConfigAttrib(display_, config_, EGL_SAMPLES, &res);
  return res;
}

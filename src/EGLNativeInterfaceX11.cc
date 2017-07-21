#include <X11/Xlib.h>
#include <X11/Xutil.h>

class EGLNativeInterfaceX11 : public EGLNativeInterface {

  public:

  protected:

    EGLDisplay GetDisplay() {
      display_ = XOpenDisplay(NULL);

      if (!display_) {
        std::cout << "EGLNativeInterfaceX11::GetDisplay : XOpenDisplay failed" << std::endl;
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
        std::cout << "EGLNativeInterfaceX11::CreateWindowSurface : eglGetConfigAttrib failed" << std::endl;
        return EGL_NO_SURFACE;
      }

      visTemplate.visualid = vid;
      visInfo = XGetVisualInfo(display_, VisualIDMask, &visTemplate, &num_visuals);

      if (!visInfo) {
        std::cout << "EGLNativeInterfaceX11::CreateWindowSurface : XGetVisualInfo failed" << std::endl;
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

    void SetupEvents() {
      XSelectInput(display_, window_, KeyPressMask|ButtonPressMask);

      WM_DELETE_WINDOW_ = XInternAtom(display_, "WM_DELETE_WINDOW", False);
      XSetWMProtocols(display_, window_, &WM_DELETE_WINDOW_, 1);
    }

    void ProcessEvents() {
      XEvent event;

      if (!client_)
        return;

      while (XPending(display_) > 0) {
        XNextEvent(display_, &event);

        if (event.type == ClientMessage) {
          if (((Atom)event.xclient.data.l[0]) == WM_DELETE_WINDOW_) {
            client_->EmitEvent(new EGLNativeInterface::CloseEvent());
          }
        } else if (event.type == KeyPress) {
          client_->EmitEvent(new EGLNativeInterface::KeyEvent(event.xkey.keycode));
        } else if (event.type == ButtonPress) {
            client_->EmitEvent(
              new EGLNativeInterface::ClickEvent(event.xbutton.x, event.xbutton.y));
        }
      }
    }

    ~EGLNativeInterfaceX11() override {
      if (display_) {
        XDestroyWindow(display_, window_);
        XCloseDisplay(display_);
      }
    }

  private:

    EGLNativeInterfaceX11(int width, int height, EGLNativeInterface::EventClient* client)
      : EGLNativeInterface(width, height),
        display_(NULL),
        client_(client) {
    }

    Display *display_;
    Window window_;
    Atom WM_DELETE_WINDOW_;

    EGLNativeInterface::EventClient* client_;

    friend EGLNativeInterface;
};

#include <EGL/fbdev_window.h>

class EGLNativeInterfaceFbdev : public EGLNativeInterface {

  protected:

    EGLDisplay GetDisplay() {
      return eglGetDisplay(EGL_DEFAULT_DISPLAY);
    }

    EGLSurface CreateWindowSurface(EGLDisplay display, EGLConfig config) {
      return eglCreateWindowSurface(display, config, &native_, NULL);
    }

    void SetupEvents() {
    }

    void ProcessEvents() {
      // TODO : evdev
    }

    ~EGLNativeInterfaceFbdev() override {
    }

  private:


    EGLNativeInterfaceFbdev(int width, int height, EGLNativeInterface::EventClient* client)
      : EGLNativeInterface(width, height),
        client_(client) {
      native_.width = width;
      native_.height = height;
    }

    fbdev_window native_;

    friend EGLNativeInterface;
};

#ifndef EGLNATIVEINTERFACEFBDEV_H_
# define EGLNATIVEINTERFACEFBDEV_H_

#include <EGL/fbdev_window.h>

#include "../EGLNativeInterface.h"

class EGLNativeInterfaceFbdev : public EGLNativeInterface {

  protected:

    EGLDisplay GetDisplay();
    EGLSurface CreateWindowSurface(EGLDisplay display, EGLConfig config);

    void SetupEvents();
    void ProcessEvents();

    ~EGLNativeInterfaceFbdev() override;

  private:

    EGLNativeInterfaceFbdev(int width, int height, EGLNativeInterface::EventClient* client);

    fbdev_window native_;

    friend EGLNativeInterface;
};


#endif /* !EGLNATIVEINTERFACEFBDEV.H */

#ifndef EGLNATIVEINTERFACEX11_H_
# define EGLNATIVEINTERFACEX11_H_

#include "../EGLNativeInterface.h"

class EGLNativeInterfaceX11 : public EGLNativeInterface {

  public:

  protected:

    EGLDisplay GetDisplay() override;
    EGLSurface CreateWindowSurface(EGLDisplay display, EGLConfig config) override;

    void SetupEvents() override;
    void ProcessEvents() override;

    ~EGLNativeInterfaceX11() override;

  private:

    EGLNativeInterfaceX11(int width, int height, EGLNativeInterface::EventClient* client);

    Display *display_;
    Window window_;
    Atom WM_DELETE_WINDOW_;

    EGLNativeInterface::EventClient* client_;

    friend EGLNativeInterface;
};

#endif /* !EGLNATIVEINTERFACEX11.H */

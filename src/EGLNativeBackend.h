#ifndef EGLNATIVEBACKEND_H_
# define EGLNATIVEBACKEND_H_

#include <string>

#include <EGL/egl.h>
#include <GLES2/gl2.h>

class EGLNativeBackend {

  public:

    static EGLNativeBackend *CreateBackend(int width, int height);

    bool Initialise();
    void Reset();
    void SwapBuffers();
    void Release();
    int StencilBits();
    int SampleCount();

    virtual ~EGLNativeBackend() = 0;

  protected:

    EGLNativeBackend(int width, int height);

    int width() { return width_; }
    int height() { return height_; }

    virtual EGLDisplay GetDisplay() = 0;
    virtual EGLSurface CreateWindowSurface(EGLDisplay display, EGLConfig config) = 0;

  private:

    EGLDisplay display_;
    EGLConfig config_;
    EGLSurface surface_;
    EGLContext context_;

    int width_;
    int height_;
};

#endif /* !EGLNATIVEBACKEND.H */

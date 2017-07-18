#ifndef SKIAWINDOW_H_
# define SKIAWINDOW_H_

#include <nan.h>

#include <gl/GrGLInterface.h>
#include <GrContext.h>
#include <SkRefCnt.h>
#include <SkSurface.h>
#include <SkSurfaceProps.h>

#include "EGLNativeBackend.h"

class SkiaWindow : public Nan::ObjectWrap
{
  public:

    static NAN_MODULE_INIT(Init);

  private:

    static NAN_METHOD(New);
    static NAN_METHOD(Initialise);
    static NAN_METHOD(Start);
    static NAN_METHOD(Stop);
    static NAN_METHOD(Release);
    static NAN_METHOD(SetDrawHandler);

    static inline Nan::Persistent<v8::Function>& constructor() {
      static Nan::Persistent<v8::Function> my_constructor;
      return my_constructor;
    }

    explicit SkiaWindow(int width, int height);
    ~SkiaWindow();

    void Initialise();
    void Start();
    void Stop();
    void Release();
    void SetDrawHandler(v8::Local<v8::Function> handler);

    EGLNativeBackend* backend_;

    sk_sp<const GrGLInterface> interface_;
    sk_sp<SkSurface>           surface_;
    GrContext*                 context_;
    SkSurfaceProps             surface_props_;

    Nan::Callback draw_handler_;
    bool has_draw_handler_;

    int width_;
    int height_;
};

#endif /* !SKIAWINDOW.H */

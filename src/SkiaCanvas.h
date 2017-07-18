#ifndef SKIACANVAS_H_
# define SKIACANVAS_H_

#include <nan.h>

class SkCanvas;

class SkiaCanvas : public Nan::ObjectWrap {
  public:

    static NAN_MODULE_INIT(Init);

    static NAN_METHOD(New);
    static NAN_METHOD(DrawColor);
    static NAN_METHOD(DrawRect);

    static v8::Local<v8::Object> CreateObject(SkCanvas* wrapped);

    static inline Nan::Persistent<v8::Function>& constructor() {
      static Nan::Persistent<v8::Function> my_constructor;
      return my_constructor;
    }

    SkiaCanvas() : wrapped_(NULL) {}
    ~SkiaCanvas() {}

    inline void Set(SkCanvas* wrapped) {
      wrapped_ = wrapped;
    }

    inline SkCanvas* Get() {
      return wrapped_;
    }

  private:

    SkCanvas* wrapped_;
};

#endif /* !SKIACANVAS.H */

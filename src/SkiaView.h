#ifndef SKIAVIEW_H_
# define SKIAVIEW_H_

#include <nan.h>

#include <SkCanvas.h>

class SkiaView : public Nan::ObjectWrap {

  public:

    static NAN_MODULE_INIT(Init);

    void Draw(SkCanvas *canvas);

    ~SkiaView();

  private:

    static inline Nan::Persistent<v8::Function>& constructor() {
      static Nan::Persistent<v8::Function> my_constructor;
      return my_constructor;
    }

    SkiaView(SkColor background_color);

    static NAN_METHOD(New);
    static NAN_METHOD(Update);

    class Tree {
      public:
        virtual void Draw(SkCanvas *canvas) = 0;
        virtual void Update(v8::Local<v8::Object> tree) = 0;

        virtual ~Tree() = 0;
    };

    class SkiaViewTreeImpl;

    Tree *tree_;

};

#endif /* !SKIAVIEW.H */

#ifndef SKIAVIEW_H_
# define SKIAVIEW_H_

#include <nan.h>

#include <SkCanvas.h>

class SkiaViewNode;

class SkiaView : public Nan::ObjectWrap {

  public:

    static NAN_MODULE_INIT(Init);

    void Draw(SkCanvas *canvas);

    ~SkiaView();

  private:

    static NAN_METHOD(New);
    static NAN_METHOD(SetRoot);

    static inline Nan::Persistent<v8::Function>& constructor() {
      static Nan::Persistent<v8::Function> my_constructor;
      return my_constructor;
    }

    SkiaView(SkColor color);

    class Tree {
      public:
        virtual void Draw(SkCanvas *canvas) = 0;
        virtual void Update(SkiaViewNode *node) = 0;

        Tree() {}
        virtual ~Tree() {}
    };

    class SkiaViewTreeImpl;

    Tree *tree_;
};

#endif /* !SKIAVIEW.H */

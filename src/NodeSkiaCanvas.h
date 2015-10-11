#ifndef NODESKIACANVAS_H_
# define NODESKIACANVAS_H_

#include <nan.h>

#include <SkCanvas.h>

class NodeSkiaCanvas : public Nan::ObjectWrap {
  public:
    static void Initialise(v8::Local<v8::Object> exports);
    static v8::Local<v8::Value> NewJSObject(SkCanvas *canvas);

    SkCanvas *toSkCanvas() {
      return canvas_;
    };

    NodeSkiaCanvas();
    ~NodeSkiaCanvas();

  private:

    void setCanvas(SkCanvas *canvas);

    static void New(const Nan::FunctionCallbackInfo<v8::Value>& args);

    static void drawColor(const Nan::FunctionCallbackInfo<v8::Value>& args);
    static void drawRect(const Nan::FunctionCallbackInfo<v8::Value>& args);
    static void drawCircle(const Nan::FunctionCallbackInfo<v8::Value>& args);

    static Nan::Persistent<v8::Function> constructor;

    SkCanvas *canvas_;
    bool owner_;
};

#endif /* !NODESKIACANVAS.H */

#ifndef NODESKIAPAINT_H_
# define NODESKIAPAINT_H_

#include <nan.h>

#include <SkPaint.h>

class NodeSkiaPaint : public Nan::ObjectWrap {
  public:
    static void Initialise(v8::Local<v8::Object> exports);

    SkPaint *toSkPaint() {
      return paint_;
    };

    NodeSkiaPaint();
    ~NodeSkiaPaint();

  private:

    static void New(const Nan::FunctionCallbackInfo<v8::Value>& args);

    static void setColor(const Nan::FunctionCallbackInfo<v8::Value>& args);

    static Nan::Persistent<v8::Function> constructor;

    SkPaint *paint_;
};

#endif /* !NODESKIAPAINT.H */

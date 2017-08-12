#ifndef SKIAPAINT_H_
# define SKIAPAINT_H_

#include <nan.h>

#include <SkPaint.h>

/* TODO : Shader... */

class SkiaPaint : public Nan::ObjectWrap {
  public:

    static NAN_MODULE_INIT(Init);

    static NAN_METHOD(New);

    static NAN_GETTER(GetFlags);
    static NAN_SETTER(SetFlags);

    static NAN_GETTER(GetAntiAlias);
    static NAN_SETTER(SetAntiAlias);

    static NAN_GETTER(GetDither);
    static NAN_SETTER(SetDither);

    static NAN_GETTER(GetLinearText);
    static NAN_SETTER(SetLinearText);

    static NAN_GETTER(GetSubpixelText);
    static NAN_SETTER(SetSubpixelText);

    static NAN_GETTER(GetLCDRenderText);
    static NAN_SETTER(SetLCDRenderText);

    static NAN_GETTER(GetEmbeddedBitmapText);
    static NAN_SETTER(SetEmbeddedBitmapText);

    static NAN_GETTER(GetAutohinted);
    static NAN_SETTER(SetAutohinted);

    static NAN_GETTER(GetVerticalText);
    static NAN_SETTER(SetVerticalText);

    static NAN_GETTER(GetFakeBoldText);
    static NAN_SETTER(SetFakeBoldText);

    static NAN_GETTER(GetDevKernText);
    static NAN_SETTER(SetDevKernText);

    static NAN_GETTER(GetFilterQuality);
    static NAN_SETTER(SetFilterQuality);

    static NAN_GETTER(GetStyle);
    static NAN_SETTER(SetStyle);

    static NAN_GETTER(GetColor);
    static NAN_SETTER(SetColor);

    static NAN_GETTER(GetStrokeWidth);
    static NAN_SETTER(SetStrokeWidth);

    static NAN_GETTER(GetStrokeMiter);
    static NAN_SETTER(SetStrokeMiter);

    static NAN_GETTER(GetStrokeCap);
    static NAN_SETTER(SetStrokeCap);

    static NAN_GETTER(GetStrokeJoin);
    static NAN_SETTER(SetStrokeJoin);

    static NAN_GETTER(GetTextAlign);
    static NAN_SETTER(SetTextAlign);

    static NAN_GETTER(GetTextSize);
    static NAN_SETTER(SetTextSize);

    static NAN_METHOD(MeasureText);

    static inline Nan::Persistent<v8::Function>& constructor() {
      static Nan::Persistent<v8::Function> my_constructor;
      return my_constructor;
    }

    SkiaPaint();
    ~SkiaPaint();

    SkPaint Get() {
      return paint_;
    }

  private:

    void FromObject(v8::Local<v8::Object> obj);

    SkPaint paint_;
};

#endif /* !SKIAPAINT.H */

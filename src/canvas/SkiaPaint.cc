#include "SkiaPaint.h"

NAN_MODULE_INIT(SkiaPaint::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
      tpl->InstanceTemplate()->SetInternalFieldCount(1);
  v8::Local<v8::ObjectTemplate> obj = tpl->InstanceTemplate();
  Nan::SetAccessor(obj, Nan::New("flags").ToLocalChecked(),
                   SkiaPaint::GetFlags, SkiaPaint::SetFlags);
  Nan::SetAccessor(obj, Nan::New("antiAlias").ToLocalChecked(),
                   SkiaPaint::GetAntiAlias, SkiaPaint::SetAntiAlias);
  Nan::SetAccessor(obj, Nan::New("dither").ToLocalChecked(),
                   SkiaPaint::GetDither, SkiaPaint::SetDither);
  Nan::SetAccessor(obj, Nan::New("linearText").ToLocalChecked(),
                   SkiaPaint::GetLinearText, SkiaPaint::SetLinearText);
  Nan::SetAccessor(obj, Nan::New("subpixelText").ToLocalChecked(),
                   SkiaPaint::GetSubpixelText, SkiaPaint::SetSubpixelText);
  Nan::SetAccessor(obj, Nan::New("LCDRenderText").ToLocalChecked(),
                   SkiaPaint::GetLCDRenderText, SkiaPaint::SetLCDRenderText);
  Nan::SetAccessor(obj, Nan::New("embeddedBitmapText").ToLocalChecked(),
                   SkiaPaint::GetEmbeddedBitmapText, SkiaPaint::SetEmbeddedBitmapText);
  Nan::SetAccessor(obj, Nan::New("autohinted").ToLocalChecked(),
                   SkiaPaint::GetAutohinted, SkiaPaint::SetAutohinted);
  Nan::SetAccessor(obj, Nan::New("verticalText").ToLocalChecked(),
                   SkiaPaint::GetVerticalText, SkiaPaint::SetVerticalText);
  Nan::SetAccessor(obj, Nan::New("fakeBoldText").ToLocalChecked(),
                   SkiaPaint::GetFakeBoldText, SkiaPaint::SetFakeBoldText);
  Nan::SetAccessor(obj, Nan::New("devKernText").ToLocalChecked(),
                   SkiaPaint::GetDevKernText, SkiaPaint::SetDevKernText);
  Nan::SetAccessor(obj, Nan::New("style").ToLocalChecked(),
                   SkiaPaint::GetStyle, SkiaPaint::SetStyle);
  Nan::SetAccessor(obj, Nan::New("color").ToLocalChecked(),
                   SkiaPaint::GetColor, SkiaPaint::SetColor);
  Nan::SetAccessor(obj, Nan::New("strokeWidth").ToLocalChecked(),
                   SkiaPaint::GetStrokeWidth, SkiaPaint::SetStrokeWidth);
  Nan::SetAccessor(obj, Nan::New("strokeMiter").ToLocalChecked(),
                   SkiaPaint::GetStrokeMiter, SkiaPaint::SetStrokeMiter);
  Nan::SetAccessor(obj, Nan::New("strokeCap").ToLocalChecked(),
                   SkiaPaint::GetStrokeCap, SkiaPaint::SetStrokeCap);
  Nan::SetAccessor(obj, Nan::New("strokeJoin").ToLocalChecked(),
                   SkiaPaint::GetStrokeJoin, SkiaPaint::SetStrokeJoin);
  Nan::SetAccessor(obj, Nan::New("textAlign").ToLocalChecked(),
                   SkiaPaint::GetTextAlign, SkiaPaint::SetTextAlign);
  Nan::SetAccessor(obj, Nan::New("textSize").ToLocalChecked(),
                   SkiaPaint::GetTextSize, SkiaPaint::SetTextSize);
  Nan::SetPrototypeMethod(tpl, "measureText", SkiaPaint::MeasureText);
  constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("Canvas").ToLocalChecked(),
           Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(SkiaPaint::New) {
  if (info.IsConstructCall()) {
    SkiaPaint *paint = new SkiaPaint();

    if (info.Length() > 0 && info[0]->IsObject())
      paint->FromObject(info[0].As<v8::Object>());

    paint->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    v8::Local<v8::Value> argv[1];
    v8::Local<v8::Function> cons = Nan::New(constructor());

    if (info.Length() > 0)
      argv[0] = info[0];

    info.GetReturnValue().Set(cons->NewInstance(info.Length(), argv));
  }
}

NAN_GETTER(SkiaPaint::GetFlags) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.getFlags()));
}

NAN_SETTER(SkiaPaint::SetFlags) {
  if (!value->IsNumber()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setFlags(value->Uint32Value());
}

NAN_GETTER(SkiaPaint::GetAntiAlias) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.isAntiAlias()));
}

NAN_SETTER(SkiaPaint::SetAntiAlias) {
  if (!value->IsBoolean()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setFlags(value->ToBoolean()->Value());
}

NAN_GETTER(SkiaPaint::GetDither) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.isDither()));
}

NAN_SETTER(SkiaPaint::SetDither) {
  if (!value->IsBoolean()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setDither(value->ToBoolean()->Value());
}

NAN_GETTER(SkiaPaint::GetLinearText) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.isLinearText()));
}

NAN_SETTER(SkiaPaint::SetLinearText) {
  if (!value->IsBoolean()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setLinearText(value->ToBoolean()->Value());
}

NAN_GETTER(SkiaPaint::GetSubpixelText) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.isSubpixelText()));
}

NAN_SETTER(SkiaPaint::SetSubpixelText) {
  if (!value->IsBoolean()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setSubpixelText(value->ToBoolean()->Value());
}

NAN_GETTER(SkiaPaint::GetLCDRenderText) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.isLCDRenderText()));
}

NAN_SETTER(SkiaPaint::SetLCDRenderText) {
  if (!value->IsBoolean()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setLCDRenderText(value->ToBoolean()->Value());
}

NAN_GETTER(SkiaPaint::GetEmbeddedBitmapText) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.isEmbeddedBitmapText()));
}

NAN_SETTER(SkiaPaint::SetEmbeddedBitmapText) {
  if (!value->IsBoolean()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setEmbeddedBitmapText(value->ToBoolean()->Value());
}

NAN_GETTER(SkiaPaint::GetAutohinted) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.isAutohinted()));
}

NAN_SETTER(SkiaPaint::SetAutohinted) {
  if (!value->IsBoolean()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setAutohinted(value->ToBoolean()->Value());
}

NAN_GETTER(SkiaPaint::GetVerticalText) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.isVerticalText()));
}

NAN_SETTER(SkiaPaint::SetVerticalText) {
  if (!value->IsBoolean()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setVerticalText(value->ToBoolean()->Value());
}

NAN_GETTER(SkiaPaint::GetFakeBoldText) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.isFakeBoldText()));
}

NAN_SETTER(SkiaPaint::SetFakeBoldText) {
  if (!value->IsBoolean()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setFakeBoldText(value->ToBoolean()->Value());
}

NAN_GETTER(SkiaPaint::GetDevKernText) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.isDevKernText()));
}

NAN_SETTER(SkiaPaint::SetDevKernText) {
  if (!value->IsBoolean()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setDevKernText(value->ToBoolean()->Value());
}

NAN_GETTER(SkiaPaint::GetFilterQuality)  {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.getFilterQuality()));
}

NAN_SETTER(SkiaPaint::SetFilterQuality) {
  if (!value->IsNumber()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setFilterQuality(static_cast<SkFilterQuality>(value->Uint32Value()));
}

NAN_GETTER(SkiaPaint::GetStyle) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.getStyle()));
}

NAN_SETTER(SkiaPaint::SetStyle) {
  if (!value->IsNumber()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setStyle(static_cast<SkPaint::Style>(value->Uint32Value()));
}

NAN_GETTER(SkiaPaint::GetColor) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.getColor()));
}

NAN_SETTER(SkiaPaint::SetColor) {
  if (!value->IsNumber()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setColor(static_cast<SkColor>(value->Uint32Value()));
}

NAN_GETTER(SkiaPaint::GetStrokeWidth)  {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.getStrokeWidth()));
}

NAN_SETTER(SkiaPaint::SetStrokeWidth) {
  if (!value->IsNumber()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setStrokeWidth(value->Uint32Value());
}

NAN_GETTER(SkiaPaint::GetStrokeMiter)  {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.getStrokeMiter()));
}

NAN_SETTER(SkiaPaint::SetStrokeMiter) {
  if (!value->IsNumber()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setStrokeMiter(value->Uint32Value());
}

NAN_GETTER(SkiaPaint::GetStrokeCap)  {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.getStrokeCap()));
}

NAN_SETTER(SkiaPaint::SetStrokeCap) {
  if (!value->IsNumber()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setStrokeCap(static_cast<SkPaint::Cap>(value->Uint32Value()));
}

NAN_GETTER(SkiaPaint::GetStrokeJoin) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.getStrokeJoin()));
}

NAN_SETTER(SkiaPaint::SetStrokeJoin) {
  if (!value->IsNumber()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setStrokeJoin(static_cast<SkPaint::Join>(value->Uint32Value()));
}

NAN_GETTER(SkiaPaint::GetTextAlign) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.getTextAlign()));
}

NAN_SETTER(SkiaPaint::SetTextAlign) {
  if (!value->IsNumber()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setTextAlign(static_cast<SkPaint::Align>(value->Uint32Value()));
}

NAN_GETTER(SkiaPaint::GetTextSize) {
  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  info.GetReturnValue().Set(Nan::New(paint->paint_.getTextSize()));
}

NAN_SETTER(SkiaPaint::SetTextSize) {
  if (!value->IsNumber()) {
    Nan::ThrowError("Invalid type");
    return;
  }

  SkiaPaint *paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());
  paint->paint_.setTextSize(value->ToNumber()->Value());
}

NAN_METHOD(SkiaPaint::MeasureText) {
  SkiaPaint* paint = Nan::ObjectWrap::Unwrap<SkiaPaint>(info.Holder());

  if (info.Length() < 1) {
    Nan::ThrowError("Not enough arguments");
    return;
  }

  if (!info[0]->IsString()) {
    Nan::ThrowError("Invalid arguments");
    return;
  }

  Nan::Utf8String val(info[0]);
  std::string text(*val);

  info.GetReturnValue().Set(
    Nan::New(paint->paint_.measureText(text.c_str(), text.size())));
}

SkiaPaint::SkiaPaint() {
}

SkiaPaint::~SkiaPaint() {
}

#define SET_INT_PROPERTY(o, n, e)                                       \
  if (Nan::Has(o, Nan::New(n).ToLocalChecked()).FromJust()) {           \
    v8::Local<v8::Value> prop =                                         \
      Nan::Get(o, Nan::New(n).ToLocalChecked()).ToLocalChecked();       \
    if (prop->IsNumber())                                               \
      e;                                                                \
  }

#define SET_FLOAT_PROPERTY(o, n, m)                                     \
  if (Nan::Has(o, Nan::New(n).ToLocalChecked()).FromJust()) {           \
    v8::Local<v8::Value> prop =                                         \
      Nan::Get(o, Nan::New(n).ToLocalChecked()).ToLocalChecked();       \
    if (prop->IsNumber())                                               \
      paint_.m(prop->ToNumber()->Value());                              \
  }

#define SET_BOOL_PROPERTY(o, n, m)                                      \
  if (Nan::Has(o, Nan::New(n).ToLocalChecked()).FromJust()) {           \
    v8::Local<v8::Value> prop =                                         \
      Nan::Get(o, Nan::New(n).ToLocalChecked()).ToLocalChecked();       \
    if (prop->IsBoolean())                                              \
      paint_.m(prop->ToBoolean()->Value());                             \
  }

void SkiaPaint::FromObject(v8::Local<v8::Object> obj) {
  SET_INT_PROPERTY(obj, "flags", paint_.setFlags(prop->Uint32Value()));
  SET_BOOL_PROPERTY(obj, "antiAlias", setAntiAlias);
  SET_BOOL_PROPERTY(obj, "dither", setDither);
  SET_BOOL_PROPERTY(obj, "linearText", setLinearText);
  SET_BOOL_PROPERTY(obj, "subpixelText", setSubpixelText);
  SET_BOOL_PROPERTY(obj, "LCDRenderText", setLCDRenderText);
  SET_BOOL_PROPERTY(obj, "embeddedBitmapText", setEmbeddedBitmapText);
  SET_BOOL_PROPERTY(obj, "autohinted", setAutohinted);
  SET_BOOL_PROPERTY(obj, "verticalText", setVerticalText);
  SET_BOOL_PROPERTY(obj, "fakeBoldText", setFakeBoldText);
  SET_BOOL_PROPERTY(obj, "devKernText", setDevKernText);
  SET_INT_PROPERTY(obj, "filterQuality",
                   paint_.setFilterQuality(static_cast<SkFilterQuality>(prop->Uint32Value())));
  SET_INT_PROPERTY(obj, "style",
                   paint_.setStyle(static_cast<SkPaint::Style>(prop->Uint32Value())));
  SET_INT_PROPERTY(obj, "color",
                   paint_.setColor(static_cast<SkColor>(prop->Uint32Value())));
  SET_INT_PROPERTY(obj, "strokeWidth", paint_.setStrokeWidth(prop->Uint32Value()));
  SET_INT_PROPERTY(obj, "strokeMiter", paint_.setStrokeMiter(prop->Uint32Value()));
  SET_INT_PROPERTY(obj, "strokeCap",
                   paint_.setStrokeCap(static_cast<SkPaint::Cap>(prop->Uint32Value())));
  SET_INT_PROPERTY(obj, "strokeJoin",
                   paint_.setStrokeJoin(static_cast<SkPaint::Join>(prop->Uint32Value())));
  SET_INT_PROPERTY(obj, "textAlign",
                   paint_.setTextAlign(static_cast<SkPaint::Align>(prop->Uint32Value())));
  SET_FLOAT_PROPERTY(obj, "textSize", setTextSize);
}

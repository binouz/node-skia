#include "SkiaCanvas.h"

#include <SkCanvas.h>

NAN_MODULE_INIT(SkiaCanvas::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  Nan::SetPrototypeMethod(tpl, "drawColor", SkiaCanvas::DrawColor);
  Nan::SetPrototypeMethod(tpl, "drawRect", SkiaCanvas::DrawRect);
  constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("SkiaCanvas").ToLocalChecked(),
           Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(SkiaCanvas::New) {
  if (info.Length() != 0) {
    Nan::ThrowError("Invalid number of argument for SkiaCanvas constructor !");
    return;
  }

  if (info.IsConstructCall()) {
    SkiaCanvas *wrapper = new SkiaCanvas();
    wrapper->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    v8::Local<v8::Function> cons = Nan::New(constructor());
    info.GetReturnValue().Set(cons->NewInstance(0, NULL));
  }
}

NAN_METHOD(SkiaCanvas::DrawColor) {
  SkiaCanvas* wrapper = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (!wrapper->Get()) {
    Nan::ThrowError("Drawing on null canvas !");
    return;
  }

  if (info.Length() != 1) {
    Nan::ThrowError("Invalid number of argument for canvas.drawColor !");
    return;
  }

  if (!info[0]->IsNumber()) {
    Nan::ThrowError("Invalid argument for canvas.drawColor !");
    return;
  }

  wrapper->Get()->drawColor(static_cast<SkColor>(info[0]->Uint32Value()));
}

NAN_METHOD(::SkiaCanvas::DrawRect) {
  SkiaCanvas* wrapper = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (!wrapper->Get()) {
    Nan::ThrowError("Drawing on null canvas !");
    return;
  }

  if (info.Length() != 5) {
    Nan::ThrowError("Invalid number of argument for canvas.drawColor !");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber() ||
      !info[3]->IsNumber() || !info[4]->IsNumber()) {
    Nan::ThrowError("Invalid argument for canvas.drawColor !");
    return;
  }

  SkPaint paint;
  SkRect rect;

  paint.setColor(static_cast<SkColor>(info[0]->Uint32Value()));

  rect.fLeft = static_cast<SkScalar>(info[1]->ToNumber()->Value());
  rect.fTop = static_cast<SkScalar>(info[2]->ToNumber()->Value());
  rect.fRight = rect.fLeft + static_cast<SkScalar>(info[3]->ToNumber()->Value());
  rect.fBottom = rect.fTop + static_cast<SkScalar>(info[4]->ToNumber()->Value());

  wrapper->Get()->drawRect(rect, paint);
}

v8::Local<v8::Object> SkiaCanvas::CreateObject(SkCanvas* wrapped)  {
  v8::Local<v8::Function> cons = Nan::New(SkiaCanvas::constructor());
  v8::Local<v8::Object> obj = Nan::NewInstance(cons, 0, NULL).ToLocalChecked();

  SkiaCanvas* wrapper = Nan::ObjectWrap::Unwrap<SkiaCanvas>(obj);
  wrapper->Set(wrapped);

  return obj;
}

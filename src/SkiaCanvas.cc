#include "SkiaCanvas.h"

#include <SkCanvas.h>

NAN_MODULE_INIT(SkiaCanvas::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  Nan::SetPrototypeMethod(tpl, "drawColor", SkiaCanvas::DrawColor);
  Nan::SetPrototypeMethod(tpl, "drawRect", SkiaCanvas::DrawRect);
  Nan::SetPrototypeMethod(tpl, "drawPoint", SkiaCanvas::DrawPoint);
  Nan::SetPrototypeMethod(tpl, "drawLine", SkiaCanvas::DrawLine);
  Nan::SetPrototypeMethod(tpl, "drawText", SkiaCanvas::DrawText);
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

NAN_METHOD(SkiaCanvas::DrawRect) {
  SkiaCanvas* wrapper = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (!wrapper->Get()) {
    Nan::ThrowError("Drawing on null canvas !");
    return;
  }

  if (info.Length() != 5) {
    Nan::ThrowError("Invalid number of argument for canvas.drawRect !");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber() ||
      !info[3]->IsNumber() || !info[4]->IsNumber()) {
    Nan::ThrowError("Invalid argument for canvas.drawRect !");
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

NAN_METHOD(SkiaCanvas::DrawPoint) {
  SkiaCanvas* wrapper = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (!wrapper->Get()) {
    Nan::ThrowError("Drawing on null canvas !");
    return;
  }

  if (info.Length() != 3) {
    Nan::ThrowError("Invalid number of argument for canvas.drawColor !");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
    Nan::ThrowError("Invalid argument for canvas.drawPoint !");
    return;
  }

  SkPaint paint;

  paint.setColor(static_cast<SkColor>(info[0]->Uint32Value()));

  wrapper->Get()->drawPoint(static_cast<SkScalar>(info[1]->ToNumber()->Value()),
                            static_cast<SkScalar>(info[2]->ToNumber()->Value()),
                            paint);
}

NAN_METHOD(SkiaCanvas::DrawLine) {
  SkiaCanvas* wrapper = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (!wrapper->Get()) {
    Nan::ThrowError("Drawing on null canvas !");
    return;
  }

  if (info.Length() != 5) {
    Nan::ThrowError("Invalid number of argument for canvas.drawLine !");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber() ||
      !info[3]->IsNumber() || !info[4]->IsNumber()) {
    Nan::ThrowError("Invalid argument for canvas.drawLine !");
    return;
  }

  SkPaint paint;
  SkPoint p1, p2;

  paint.setColor(static_cast<SkColor>(info[0]->Uint32Value()));

  p1.fX = static_cast<SkScalar>(info[1]->ToNumber()->Value());
  p1.fY = static_cast<SkScalar>(info[2]->ToNumber()->Value());
  p2.fX = static_cast<SkScalar>(info[3]->ToNumber()->Value());
  p2.fY = static_cast<SkScalar>(info[4]->ToNumber()->Value());

  wrapper->Get()->drawLine(p1, p2, paint);
}

NAN_METHOD(SkiaCanvas::DrawText) {
  SkiaCanvas* wrapper = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (!wrapper->Get()) {
    Nan::ThrowError("Drawing on null canvas !");
    return;
  }

  if (info.Length() != 4) {
    Nan::ThrowError("Invalid number of argument for canvas.drawLine !");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber() ||
      !info[3]->IsString()) {
    Nan::ThrowError("Invalid argument for canvas.drawLine !");
    return;
  }

  SkPaint paint;
  paint.setColor(static_cast<SkColor>(info[0]->Uint32Value()));

  Nan::Utf8String val(info[3]);
  std::string str(*val);

  wrapper->Get()->drawText(str.c_str(), str.size(),
                           static_cast<SkColor>(info[1]->ToNumber()->Value()),
                           static_cast<SkColor>(info[2]->ToNumber()->Value()),
                           paint);
}

v8::Local<v8::Object> SkiaCanvas::CreateObject(SkCanvas* wrapped)  {
  v8::Local<v8::Function> cons = Nan::New(SkiaCanvas::constructor());
  v8::Local<v8::Object> obj = Nan::NewInstance(cons, 0, NULL).ToLocalChecked();

  SkiaCanvas* wrapper = Nan::ObjectWrap::Unwrap<SkiaCanvas>(obj);
  wrapper->Set(wrapped);

  return obj;
}

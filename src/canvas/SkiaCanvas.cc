#include "SkiaCanvas.h"
#include "SkiaPaint.h"
#include "../V8Utils.h"

/*
  - flush()
  - save()
  - restore()
  - setPaint(SkPaint paint)

  - translate(SkScalar dx, SkScalar dy)
  - scale(SkScalar sx, SkScalar sy)
  - rotate(SkScalar deg)
  - skew(SkScalar sx, SkScalar sy)
  - concat(SkMatrix matrix)
  - setMatrix(SkMatrix matrix)

  - drawColor(SkColor color)
  - drawPoint(SkColor color)
  - drawRect(object rect)
  - drawOval(object rect)
  - drawCircle(x, y, radius)
  - drawArc(object rect, SkScalar start, SkScalar sweep, bool useCenter)
  - drawRoundRect(object rect, SkScalar rx, SkScalar ry)
  - drawPath(SkPath, path)
  - drawImage(SkImage img, SkScalar x, SkScalar y)
  - drawBitmap(SkBitmap bitmap, SkScalar x, SkScalar y)
  - drawText(string text, SkScalar x, SkScalar y);

*/

NAN_MODULE_INIT(SkiaCanvas::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  Nan::SetPrototypeMethod(tpl, "flush", SkiaCanvas::Flush);
  Nan::SetPrototypeMethod(tpl, "save", SkiaCanvas::Save);
  Nan::SetPrototypeMethod(tpl, "restore", SkiaCanvas::Restore);
  Nan::SetPrototypeMethod(tpl, "setPaint", SkiaCanvas::SetPaint);

  Nan::SetPrototypeMethod(tpl, "translate", SkiaCanvas::Translate);
  Nan::SetPrototypeMethod(tpl, "scale", SkiaCanvas::Scale);
  Nan::SetPrototypeMethod(tpl, "rotate", SkiaCanvas::Rotate);
  Nan::SetPrototypeMethod(tpl, "skew", SkiaCanvas::Skew);
  // Nan::SetPrototypeMethod(tpl, "concat", SkiaCanvas::Concat);
  // Nan::SetPrototypeMethod(tpl, "setMatrix", SkiaCanvas::SetMatrix);

  Nan::SetPrototypeMethod(tpl, "drawColor", SkiaCanvas::DrawColor);
  Nan::SetPrototypeMethod(tpl, "drawPoint", SkiaCanvas::DrawPoint);
  Nan::SetPrototypeMethod(tpl, "drawRect", SkiaCanvas::DrawRect);
  Nan::SetPrototypeMethod(tpl, "drawOval", SkiaCanvas::DrawOval);
  Nan::SetPrototypeMethod(tpl, "drawCircle", SkiaCanvas::DrawCircle);
  Nan::SetPrototypeMethod(tpl, "drawArc", SkiaCanvas::DrawArc);
  Nan::SetPrototypeMethod(tpl, "drawRoundRect", SkiaCanvas::DrawRoundRect);
  // Nan::SetPrototypeMethod(tpl, "drawPath", SkiaCanvas::DrawPath);
  // Nan::SetPrototypeMethod(tpl, "drawBitmap", SkiaCanvas::DrawBitmap);
  // Nan::SetPrototypeMethod(tpl, "drawText", SkiaCanvas::DrawText);
  constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("Canvas").ToLocalChecked(),
           Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(SkiaCanvas::New) {
  if (info.IsConstructCall()) {
    SkiaCanvas *canvas = new SkiaCanvas();
    canvas->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    v8::Local<v8::Function> cons = Nan::New(constructor());
    info.GetReturnValue().Set(cons->NewInstance(0, NULL));
  }
}

NAN_METHOD(SkiaCanvas::Flush) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  canvas->canvas_->flush();
}

NAN_METHOD(SkiaCanvas::Save) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  canvas->canvas_->save();
}

NAN_METHOD(SkiaCanvas::Restore) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  canvas->canvas_->restore();
}

NAN_METHOD(SkiaCanvas::SetPaint) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  if (info.Length() < 1) {
    Nan::ThrowError("Not enough arguments");
    return;
  }

  if (!info[0]->IsObject()) {
    Nan::ThrowError("Invalid argument");
    return;
  }

  canvas->paint_ = Nan::ObjectWrap::Unwrap<SkiaPaint>(
    v8::Local<v8::Object>::Cast(info[0]))->Get();
}

NAN_METHOD(SkiaCanvas::Translate) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  if (info.Length() < 2) {
    Nan::ThrowError("Not enough arguments");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
    Nan::ThrowError("Invalid arguments");
    return;
  }

  canvas->canvas_->translate(static_cast<SkScalar>(info[0]->ToNumber()->Value()),
                             static_cast<SkScalar>(info[1]->ToNumber()->Value()));
}

NAN_METHOD(SkiaCanvas::Scale) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  if (info.Length() < 2) {
    Nan::ThrowError("Not enough arguments");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
    Nan::ThrowError("Invalid arguments");
    return;
  }

  canvas->canvas_->scale(static_cast<SkScalar>(info[0]->ToNumber()->Value()),
                         static_cast<SkScalar>(info[1]->ToNumber()->Value()));
}

NAN_METHOD(SkiaCanvas::Rotate) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  if (info.Length() < 1) {
    Nan::ThrowError("Not enough arguments");
    return;
  }

  if (!info[0]->IsNumber()) {
    Nan::ThrowError("Invalid arguments");
    return;
  }

  canvas->canvas_->rotate(static_cast<SkScalar>(info[0]->ToNumber()->Value()));
}

NAN_METHOD(SkiaCanvas::Skew) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  if (info.Length() < 2) {
    Nan::ThrowError("Not enough arguments");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber()) {
    Nan::ThrowError("Invalid arguments");
    return;
  }

  canvas->canvas_->skew(static_cast<SkScalar>(info[0]->ToNumber()->Value()),
                        static_cast<SkScalar>(info[1]->ToNumber()->Value()));
}

// NAN_METHOD(SkiaCanvas::Concat) {
//   SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

//   if (canvas->canvas_ == NULL) {
//     Nan::ThrowError("Canvas is null");
//     return;
//   }

//   if (info.Length() < 1) {
//     Nan::ThrowError("Not enough arguments");
//     return;
//   }

//   if (!info[0]->IsObject()) {
//     Nan::ThrowError("Invalid argument");
//     return;
//   }

//   SkiaMatrix *matrix = Nan::ObjectWrap::Unwrap<SkiaMatrix>(
//     v8::Local<v8::Object>::Cast(info[0]));

//   canvas->canvas_->concat(matrix->Get());
// }

// NAN_METHOD(SkiaCanvas::SetMatrix) {
//   SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

//   if (canvas->canvas_ == NULL) {
//     Nan::ThrowError("Canvas is null");
//     return;
//   }

//   if (info.Length() < 1) {
//     Nan::ThrowError("Not enough arguments");
//     return;
//   }

//   if (!info[0]->IsObject()) {
//     Nan::ThrowError("Invalid argument");
//     return;
//   }

//   SkiaMatrix *matrix = Nan::ObjectWrap::Unwrap<SkiaMatrix>(
//     v8::Local<v8::Object>::Cast(info[0]));

//   canvas->canvas_->setMatrix(matrix->Get());
// }

NAN_METHOD(SkiaCanvas::DrawColor) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  if (info.Length() < 1) {
    Nan::ThrowError("Not enough arguments");
    return;
  }

  if (!info[0]->IsNumber()) {
    Nan::ThrowError("Invalid arguments");
    return;
  }

  canvas->canvas_->drawColor(info[0]->Uint32Value());
}

NAN_METHOD(SkiaCanvas::DrawPoint) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  if (info.Length() < 1) {
    Nan::ThrowError("Not enough arguments");
    return;
  }

  if (!info[0]->IsNumber()) {
    Nan::ThrowError("Invalid arguments");
    return;
  }

  canvas->canvas_->drawPoint(info[0]->ToNumber()->Value(),
                             info[1]->ToNumber()->Value(),
                             canvas->paint_);
}

NAN_METHOD(SkiaCanvas::DrawRect) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  if (info.Length() < 1) {
    Nan::ThrowError("Not enough arguments");
    return;
  }

  if (!info[0]->IsObject()) {
    Nan::ThrowError("Invalid arguments");
    return;
  }

  SkRect rect;
  v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(info[0]);

  rect.fTop = V8Utils::GetSkScalar(obj, "x");
  rect.fLeft = V8Utils::GetSkScalar(obj, "y");
  rect.fBottom = rect.fTop + V8Utils::GetSkScalar(obj, "width");
  rect.fRight = rect.fLeft + V8Utils::GetSkScalar(obj, "height");

  canvas->canvas_->drawRect(rect, canvas->paint_);
}

NAN_METHOD(SkiaCanvas::DrawOval) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  if (info.Length() < 1) {
    Nan::ThrowError("Not enough arguments");
    return;
  }

  if (!info[0]->IsObject()) {
    Nan::ThrowError("Invalid arguments");
    return;
  }

  SkRect rect;
  v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(info[0]);

  rect.fTop = V8Utils::GetSkScalar(obj, "x");
  rect.fLeft = V8Utils::GetSkScalar(obj, "y");
  rect.fBottom = rect.fTop + V8Utils::GetSkScalar(obj, "width");
  rect.fRight = rect.fLeft + V8Utils::GetSkScalar(obj, "height");

  canvas->canvas_->drawOval(rect, canvas->paint_);
}

NAN_METHOD(SkiaCanvas::DrawCircle) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  if (info.Length() < 3) {
    Nan::ThrowError("Not enough arguments");
    return;
  }

  if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
    Nan::ThrowError("Invalid arguments");
    return;
  }

  canvas->canvas_->drawCircle(info[0]->ToNumber()->Value(),
                              info[1]->ToNumber()->Value(),
                              info[2]->ToNumber()->Value(),
                              canvas->paint_);
}

NAN_METHOD(SkiaCanvas::DrawArc) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  if (info.Length() < 4) {
    Nan::ThrowError("Not enough arguments");
    return;
  }

  if (!info[0]->IsObject() || !info[1]->IsNumber() || !info[2]->IsNumber() ||
      !info[3]->IsBoolean()) {
    Nan::ThrowError("Invalid arguments");
    return;
  }

  SkRect rect;
  v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(info[0]);

  rect.fTop = V8Utils::GetSkScalar(obj, "x");
  rect.fLeft = V8Utils::GetSkScalar(obj, "y");
  rect.fBottom = rect.fTop + V8Utils::GetSkScalar(obj, "width");
  rect.fRight = rect.fLeft + V8Utils::GetSkScalar(obj, "height");

  canvas->canvas_->drawArc(rect,
                           info[1]->ToNumber()->Value(),
                           info[2]->ToNumber()->Value(),
                           info[3]->ToBoolean()->Value(),
                           canvas->paint_);
}

NAN_METHOD(SkiaCanvas::DrawRoundRect) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  if (info.Length() < 3) {
    Nan::ThrowError("Not enough arguments");
    return;
  }

  if (!info[0]->IsObject() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
    Nan::ThrowError("Invalid arguments");
    return;
  }

  SkRect rect;
  v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(info[0]);

  rect.fTop = V8Utils::GetSkScalar(obj, "x");
  rect.fLeft = V8Utils::GetSkScalar(obj, "y");
  rect.fBottom = rect.fTop + V8Utils::GetSkScalar(obj, "width");
  rect.fRight = rect.fLeft + V8Utils::GetSkScalar(obj, "height");

  canvas->canvas_->drawRoundRect(rect,
                                 info[1]->ToNumber()->Value(),
                                 info[2]->ToNumber()->Value(),
                                 canvas->paint_);
}

// NAN_METHOD(SkiaCanvas::DrawPath) {
//   SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

//   if (canvas->canvas_ == NULL) {
//     Nan::ThrowError("Canvas is null");
//     return;
//   }

//   if (info.Length() < 1) {
//     Nan::ThrowError("Not enough arguments");
//     return;
//   }

//   if (!info[0]->IsObject()) {
//     Nan::ThrowError("Invalid arguments");
//     return;
//   }

//   SkiaPath *path = Nan::ObjectWrap::Unwrap<SkiaPath>(
//     v8::Local<v8::Object>::Cast(info[0]));

//   canvas->canvas_->drawRoundRect(path->Get(),
//                                 canvas->paint_);
// }

// NAN_METHOD(SkiaCanvas::DrawImage) {
//   SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

//   if (canvas->canvas_ == NULL) {
//     Nan::ThrowError("Canvas is null");
//     return;
//   }

//   if (info.Length() < 3) {
//     Nan::ThrowError("Not enough arguments");
//     return;
//   }

//   if (!info[0]->IsObject() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
//     Nan::ThrowError("Invalid arguments");
//     return;
//   }

//   SkiaImage *path = Nan::ObjectWrap::Unwrap<SkiaImage>(
//     v8::Local<v8::Object>::Cast(info[0]));

//   canvas->canvas_->drawImage(image->Get(),
//                             info[1]->ToNumber()->Value(),
//                             info[2]->ToNumber()->Value());
// }

// NAN_METHOD(SkiaCanvas::DrawBitmap) {
//   SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

//   if (canvas->canvas_ == NULL) {
//     Nan::ThrowError("Canvas is null");
//     return;
//   }

//   if (info.Length() < 3) {
//     Nan::ThrowError("Not enough arguments");
//     return;
//   }

//   if (!info[0]->IsObject() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
//     Nan::ThrowError("Invalid arguments");
//     return;
//   }

//   SkiaBitmap *bitmap = Nan::ObjectWrap::Unwrap<SkiaBitmap>(
//     v8::Local<v8::Object>::Cast(info[0]));

//   canvas->canvas_->drawBitmap(bitmap->Get(),
//                             info[1]->ToNumber()->Value(),
//                             info[2]->ToNumber()->Value());
// }

NAN_METHOD(SkiaCanvas::DrawText) {
  SkiaCanvas* canvas = Nan::ObjectWrap::Unwrap<SkiaCanvas>(info.Holder());

  if (canvas->canvas_ == NULL) {
    Nan::ThrowError("Canvas is null");
    return;
  }

  if (info.Length() < 3) {
    Nan::ThrowError("Not enough arguments");
    return;
  }

  if (!info[0]->IsObject() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
    Nan::ThrowError("Invalid arguments");
    return;
  }

  Nan::Utf8String val(info[0]);
  std::string text(*val);

  canvas->canvas_->drawText(text.c_str(),
                            text.size(),
                            info[1]->ToNumber()->Value(),
                            info[2]->ToNumber()->Value(),
                            canvas->paint_);
}

v8::Local<v8::Object> SkiaCanvas::CreateObject(SkCanvas* canvas)  {
  v8::Local<v8::Function> cons = Nan::New(SkiaCanvas::constructor());
  v8::Local<v8::Object> obj = Nan::NewInstance(cons, 0, NULL).ToLocalChecked();

  SkiaCanvas* wrapped = Nan::ObjectWrap::Unwrap<SkiaCanvas>(obj);
  wrapped->Set(canvas);

  return obj;
}

SkiaCanvas::SkiaCanvas()
  : canvas_(NULL) {
}

SkiaCanvas::~SkiaCanvas() {
}

void SkiaCanvas::Set(SkCanvas *canvas) {
  canvas_ = canvas;
}

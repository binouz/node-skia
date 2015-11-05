#include "NodeSkiaOval.h"

NodeSkiaOval::NodeSkiaOval()
  : color_(0x00000000)
{
}

NodeSkiaOval::~NodeSkiaOval()
{
}

void NodeSkiaOval::parseElement(v8::Local<v8::Object> obj)
{
  color_ = GetSkColor(obj, "color");
}

void NodeSkiaOval::renderElement(SkCanvas *canvas)
{
  SkPaint paint;
  SkRect rect;

  paint.setColor(color_);

  rect.fLeft = left_;
  rect.fTop = top_;
  rect.fRight = left_ + width_;
  rect.fBottom = top_ + height_;

  canvas->drawOval(rect, paint);
}

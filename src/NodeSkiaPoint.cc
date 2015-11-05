#include "NodeSkiaPoint.h"

NodeSkiaPoint::NodeSkiaPoint()
  : color_(0x00000000)
{
}

NodeSkiaPoint::~NodeSkiaPoint()
{
}

void NodeSkiaPoint::parseElement(v8::Local<v8::Object> obj)
{
  color_ = GetSkColor(obj, "color");
}

void NodeSkiaPoint::renderElement(SkCanvas *canvas)
{
  SkPaint paint;

  paint.setColor(color_);
  canvas->drawPoint(left_, top_, paint);
}

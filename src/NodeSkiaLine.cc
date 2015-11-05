#include "NodeSkiaLine.h"

NodeSkiaLine::NodeSkiaLine()
  : color_(0x00000000)
{
}

NodeSkiaLine::~NodeSkiaLine()
{
}

void NodeSkiaLine::parseElement(v8::Local<v8::Object> obj)
{
  color_ = GetSkColor(obj, "color");
}

void NodeSkiaLine::renderElement(SkCanvas *canvas)
{
  SkPaint paint;

  paint.setColor(color_);
  canvas->drawLine(left_, top_, right_, bottom_, paint);
}

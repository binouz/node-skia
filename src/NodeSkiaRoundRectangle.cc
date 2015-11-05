#include "NodeSkiaRoundRectangle.h"

NodeSkiaRoundRectangle::NodeSkiaRoundRectangle()
  : color_(0x00000000),
    x_radius_(0),
    y_radius_(0)
{
}

NodeSkiaRoundRectangle::~NodeSkiaRoundRectangle()
{
}

void NodeSkiaRoundRectangle::parseElement(v8::Local<v8::Object> obj)
{
  color_ = GetSkColor(obj, "color");
  x_radius_ = GetSkColor(obj, "x_radius");
  y_radius_ = GetSkColor(obj, "y_radius");
}

void NodeSkiaRoundRectangle::renderElement(SkCanvas *canvas)
{
  SkPaint paint;
  SkRect rect;

  paint.setColor(color_);

  rect.fLeft = left_;
  rect.fTop = top_;
  rect.fRight = right_;
  rect.fBottom = bottom_;

  canvas->drawRoundRect(rect, x_radius_, y_radius_, paint);
}

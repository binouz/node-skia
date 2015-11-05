#include "NodeSkiaCircle.h"

#include <iostream>

NodeSkiaCircle::NodeSkiaCircle()
  : color_(0x00000000)
{
}

NodeSkiaCircle::~NodeSkiaCircle()
{
}

void NodeSkiaCircle::parseElement(v8::Local<v8::Object> obj)
{
  color_ = GetSkColor(obj, "color");
}

void NodeSkiaCircle::renderElement(SkCanvas *canvas)
{
  SkPaint paint;
  SkScalar radius = (width_) / 2;
  SkScalar cx = left_ + radius;
  SkScalar cy = top_ + radius;

  paint.setColor(color_);

  std::cout << "NodeSkiaCircle::renderElement: cx=" << cx << " cy=" << cy << " radius=" << radius << std::endl;

  canvas->drawCircle(cx, cy, radius, paint);
}

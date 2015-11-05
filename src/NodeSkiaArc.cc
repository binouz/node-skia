#include "NodeSkiaArc.h"

NodeSkiaArc::NodeSkiaArc()
  : color_(0x00000000),
    start_(0),
    sweep_(0),
    use_center_(false)
{
}

NodeSkiaArc::~NodeSkiaArc()
{
}

void NodeSkiaArc::parseElement(v8::Local<v8::Object> obj)
{
  color_ = GetSkColor(obj, "color");
  start_ = GetSkScalar(obj, "start");
  sweep_ = GetSkScalar(obj, "sweep");
  use_center_ = GetSkScalar(obj, "use_center");
}

void NodeSkiaArc::renderElement(SkCanvas *canvas)
{
  SkPaint paint;
  SkRect rect;

  paint.setColor(color_);

  rect.fLeft = left_;
  rect.fTop = top_;
  rect.fRight = right_;
  rect.fBottom = bottom_;

  canvas->drawArc(rect, start_, sweep_, use_center_, paint);
}

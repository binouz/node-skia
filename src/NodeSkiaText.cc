#include "NodeSkiaText.h"

NodeSkiaText::NodeSkiaText()
  : color_(0x00000000)
{
}

NodeSkiaText::~NodeSkiaText()
{
}

void NodeSkiaText::parseElement(v8::Local<v8::Object> obj)
{
  color_ = GetSkColor(obj, "color");
  text_ = GetString(obj, "text");
}

void NodeSkiaText::renderElement(SkCanvas *canvas)
{
  SkPaint paint;

  paint.setColor(color_);

  canvas->drawText(text_.c_str(), text_.size(), left_, top_, paint);
}

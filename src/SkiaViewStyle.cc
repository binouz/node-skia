#include "SkiaViewStyle.h"
#include "V8Utils.h"

SkiaViewStyle::SkiaViewStyle()
  : color_(0x0),
    background_color_(0x0),
    x_(0),
    y_(0),
    width_(0),
    height_(0),
    font_size_(0) {
}

SkiaViewStyle::~SkiaViewStyle() {
}

void SkiaViewStyle::Transform(SkCanvas *canvas) {
}

void SkiaViewStyle::Update(v8::Local<v8::Object> object) {
  color_ = V8Utils::GetSkColor(object, "color");
  background_color_ = V8Utils::GetSkColor(object, "backgroundColor");
  x_ = V8Utils::GetSkScalar(object, "x");
  y_ = V8Utils::GetSkScalar(object, "y");
  width_ = V8Utils::GetSkScalar(object, "width");
  height_ = V8Utils::GetSkScalar(object, "height");
  font_size_ = V8Utils::GetSkScalar(object, "fontSize");
}

SkColor SkiaViewStyle::Color() {
  return color_;
}

SkColor SkiaViewStyle::BackgroundColor() {
  return background_color_;
}

SkScalar SkiaViewStyle::X() {
  return x_;
}

SkScalar SkiaViewStyle::Y() {
  return y_;
}

SkScalar SkiaViewStyle::Width() {
  return width_;
}

SkScalar SkiaViewStyle::Height() {
  return height_;
}

SkScalar SkiaViewStyle::FontSize() {
  return font_size_;
}

void SkiaViewStyle::DrawText(SkCanvas *canvas, std::string& text) {
  SkPaint paint;

  paint.setColor(color_);
  paint.setAntiAlias(true);
  paint.setTextSize(font_size_);

  canvas->drawText(text.c_str(), text.size(), x_, y_, paint);
}

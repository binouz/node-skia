#include "SkiaViewStyle.h"
#include "../V8Utils.h"

SkiaViewStyle::SkiaViewStyle()
  : color_(0x0),
    background_color_(0x0),
    font_size_(0),
    width_(0),
    height_(0),
    top_(0),
    left_(0),
    right_(0),
    bottom_(0) {
}

SkiaViewStyle::~SkiaViewStyle() {
}

void SkiaViewStyle::Transform(SkCanvas *canvas) {
}

void SkiaViewStyle::Update(v8::Local<v8::Object> object) {
  color_ = V8Utils::GetSkColor(object, "color");
  background_color_ = V8Utils::GetSkColor(object, "backgroundColor");
  font_size_ = V8Utils::GetSkScalar(object, "fontSize");
  width_ = V8Utils::GetSkScalar(object, "width");
  height_ = V8Utils::GetSkScalar(object, "height");
  top_ = V8Utils::GetSkScalar(object, "top");
  left_ = V8Utils::GetSkScalar(object, "left");
  right_ = V8Utils::GetSkScalar(object, "right");
  bottom_ = V8Utils::GetSkScalar(object, "bottom");
  direction_ = V8Utils::GetString(object, "direction");
  margin_top_ = V8Utils::GetSkScalar(object, "marginTop");
  margin_left_ = V8Utils::GetSkScalar(object, "marginLeft");
  margin_right_ = V8Utils::GetSkScalar(object, "marginRight");
  margin_bottom_ = V8Utils::GetSkScalar(object, "marginBottom");
  padding_top_ = V8Utils::GetSkScalar(object, "paddingTop");
  padding_left_ = V8Utils::GetSkScalar(object, "paddingLeft");
  padding_right_ = V8Utils::GetSkScalar(object, "paddingRight");
  padding_bottom_ = V8Utils::GetSkScalar(object, "paddingBottom");
  border_ = V8Utils::GetSkScalar(object, "border");
}

SkColor SkiaViewStyle::Color() {
  return color_;
}

SkColor SkiaViewStyle::BackgroundColor() {
  return background_color_;
}

SkScalar SkiaViewStyle::FontSize() {
  return font_size_;
}

SkScalar SkiaViewStyle::Width() {
  return width_;
}

SkScalar SkiaViewStyle::Height() {
  return height_;
}

SkScalar SkiaViewStyle::Top() {
  return top_;
}

SkScalar SkiaViewStyle::Left() {
  return left_;
}

SkScalar SkiaViewStyle::Right() {
  return right_;
}

SkScalar SkiaViewStyle::Bottom()  {
  return bottom_;
}

std::string SkiaViewStyle::Direction()  {
  return direction_;
}

v8::Local<v8::Object> SkiaViewStyle::GetObject() {
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();

  Nan::ForceSet(obj, Nan::New("color").ToLocalChecked(), Nan::New(color_));
  Nan::ForceSet(obj, Nan::New("backgroundColor").ToLocalChecked(), Nan::New(background_color_));

  Nan::ForceSet(obj, Nan::New("fontSize").ToLocalChecked(), Nan::New(font_size_));

  Nan::ForceSet(obj, Nan::New("width").ToLocalChecked(), Nan::New(width_));
  Nan::ForceSet(obj, Nan::New("height").ToLocalChecked(), Nan::New(height_));

  Nan::ForceSet(obj, Nan::New("top").ToLocalChecked(), Nan::New(top_));
  Nan::ForceSet(obj, Nan::New("left").ToLocalChecked(), Nan::New(left_));
  Nan::ForceSet(obj, Nan::New("right").ToLocalChecked(), Nan::New(right_));
  Nan::ForceSet(obj, Nan::New("bottom").ToLocalChecked(), Nan::New(bottom_));

  Nan::ForceSet(obj, Nan::New("direction").ToLocalChecked(), Nan::New(direction_).ToLocalChecked());

  Nan::ForceSet(obj, Nan::New("marginTop").ToLocalChecked(), Nan::New(margin_top_));
  Nan::ForceSet(obj, Nan::New("marginLeft").ToLocalChecked(), Nan::New(margin_left_));
  Nan::ForceSet(obj, Nan::New("marginRight").ToLocalChecked(), Nan::New(margin_right_));
  Nan::ForceSet(obj, Nan::New("marginBottom").ToLocalChecked(), Nan::New(margin_bottom_));

  Nan::ForceSet(obj, Nan::New("paddingTop").ToLocalChecked(), Nan::New(padding_top_));
  Nan::ForceSet(obj, Nan::New("paddingLeft").ToLocalChecked(), Nan::New(padding_left_));
  Nan::ForceSet(obj, Nan::New("paddingRight").ToLocalChecked(), Nan::New(padding_right_));
  Nan::ForceSet(obj, Nan::New("paddingBottom").ToLocalChecked(), Nan::New(padding_bottom_));
  Nan::ForceSet(obj, Nan::New("border").ToLocalChecked(), Nan::New(border_));

  return obj;
}

void SkiaViewStyle::DrawText(SkCanvas *canvas, std::string& text) {
  SkPaint paint;

  paint.setColor(color_);
  paint.setAntiAlias(true);
  paint.setTextSize(font_size_);

  SkScalar text_size = paint.measureText(text.c_str(), text.size());
  SkScalar height = (height_ > 0 ? height_ : font_size_);
  SkScalar width = width_ > 0 ? width_ : text_size;
  SkScalar top = top_ + (height + font_size_) / 2 + padding_top_ + margin_top_;
  SkScalar left = left_ + (width - text_size) / 2 + padding_left_ + margin_left_;

  canvas->drawText(text.c_str(), text.size(), left, top, paint);
}

void SkiaViewStyle::DrawBorders(SkCanvas *canvas) {
  SkPaint paint;

  if (border_ <= 0)
    return;

  paint.setColor(color_);

  canvas->drawLine(left_ + margin_left_,
                   top_ + margin_top_,
                   left_ + width_ - margin_right_,
                   top_ + margin_top_,
                   paint);

  canvas->drawLine(left_ + width_ - margin_right_,
                   top_ + margin_top_,
                   left_ + width_ - margin_right_,
                   top_ + height_ - margin_bottom_,
                   paint);

  canvas->drawLine(left_ + width_ - margin_right_,
                   top_ + height_ - margin_bottom_,
                   left_ + margin_left_,
                   top_ + height_ - margin_bottom_,
                   paint);

  canvas->drawLine(left_ + margin_left_,
                   top_ + height_ - margin_bottom_,
                   left_ + margin_left_,
                   top_ + margin_top_,
                   paint);
}

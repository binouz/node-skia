#include "SkiaViewElement.h"
#include "V8Utils.h"

// #include "SkiaElements.cc"

SkiaViewElement *SkiaViewElement::CreateElement(v8::Local<v8::Object> obj) {
  return new SkiaViewElement();
}

SkiaViewElement::SkiaViewElement() {
}

SkiaViewElement::~SkiaViewElement() {
}

void SkiaViewElement::Draw(SkCanvas *canvas) {
  canvas->save();

  DrawElement(canvas);

  for (std::vector<SkiaViewElement *>::iterator it = children_.begin();
       it != children_.end(); ++it) {
    (*it)->Draw(canvas);
  }

  style_.Transform(canvas);

  canvas->restore();
}

void SkiaViewElement::Update(v8::Local<v8::Object> object) {
  UpdateElement(object);
  style_.Update(V8Utils::GetObject(object, "style"));
  UpdateChildren(V8Utils::GetArray(object, "children"));
}

SkiaViewStyle *SkiaViewElement::GetStyle() {
  return &style_;
}

void SkiaViewElement::UpdateChildren(v8::Local<v8::Array> children) {
  ClearChildren();

  uint32_t size = children->Length();

  for (uint32_t i = 0; i < size; i++)
  {
    v8::Local<v8::Object> obj = children->CloneElementAt(i);
    SkiaViewElement *elm = CreateElement(obj);
    if (elm)
      children_.push_back(elm);
  }
}

void SkiaViewElement::ClearChildren() {
  for (std::vector<SkiaViewElement *>::iterator it = children_.begin();
       it != children_.end(); ++it) {
    delete (*it);
  }

  children_.clear();
}

void SkiaViewElement::DrawElement(SkCanvas *canvas) {
  {
    SkPaint paint;
    SkRect rect;

    paint.setColor(style_.BackgroundColor());

    rect.fLeft = style_.X();
    rect.fTop = style_.Y();
    rect.fRight = rect.fLeft + style_.Width();
    rect.fBottom = rect.fTop + style_.Height();

    canvas->save();
    canvas->drawRect(rect, paint);
    canvas->restore();
  }

  {
    canvas->save();
    style_.DrawText(canvas, content_);
    canvas->restore();
  }
}

void SkiaViewElement::UpdateElement(v8::Local<v8::Object> object) {
  content_ = V8Utils::GetString(object, "content");
}

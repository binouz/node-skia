#include "NodeSkiaTree.h"

#include <iostream>

static SkScalar GetSkScalar(v8::Local<v8::Object> obj, const char *str)
{
  if (!Nan::Has(obj, Nan::New(str).ToLocalChecked()).FromJust())
    return 0;

  v8::Local<v8::Value> prop = Nan::Get(obj, Nan::New(str).ToLocalChecked()).ToLocalChecked();
  if (!prop->IsNumber())
    return 0;

  return static_cast<SkScalar>(prop->ToNumber()->Value());
}

static SkColor GetSkColor(v8::Local<v8::Object> obj, const char *str)
{
  if (!Nan::Has(obj, Nan::New(str).ToLocalChecked()).FromJust())
    return 0;

  v8::Local<v8::Value> prop = Nan::Get(obj, Nan::New(str).ToLocalChecked()).ToLocalChecked();
  if (!prop->IsNumber())
    return 0;

  return static_cast<SkColor>(prop->Uint32Value());
}

static bool GetBool(v8::Local<v8::Object> obj, const char *str)
{
  if (!Nan::Has(obj, Nan::New(str).ToLocalChecked()).FromJust())
    return false;

  v8::Local<v8::Value> prop = Nan::Get(obj, Nan::New(str).ToLocalChecked()).ToLocalChecked();
  if (!prop->IsBoolean())
    return false;

  return prop->ToBoolean()->Value();
}

NodeSkiaRectangle *NodeSkiaElement::CreateNodeSkiaRectangle(v8::Local<v8::Object> obj)
{
  NodeSkiaRectangle * res = new NodeSkiaRectangle();
  res->parse(obj);
  return res;
}

NodeSkiaElement *NodeSkiaElement::CreateElement(v8::Local<v8::Object> obj)
{
  if (!Nan::Has(obj, Nan::New("type").ToLocalChecked()).FromJust())
    return NULL;

  v8::Local<v8::Value> value = Nan::Get(obj, Nan::New("type").ToLocalChecked()).ToLocalChecked();
  if (!value->IsString())
      return NULL;

  v8::String::Utf8Value str(value->ToString());
  if (std::string(*str) == "rectangle")
    return NodeSkiaElement::CreateNodeSkiaRectangle(obj);

  return NULL;
}

NodeSkiaElement::NodeSkiaElement() {}

NodeSkiaElement::~NodeSkiaElement() {}

void NodeSkiaElement::parseChildren(v8::Local<v8::Object> obj)
{
  clearChildren();

  if (!Nan::Has(obj, Nan::New("children").ToLocalChecked()).FromJust())
    return;

  v8::Local<v8::Value> children = Nan::Get(obj, Nan::New("children").ToLocalChecked()).ToLocalChecked();
  if (!children->IsArray())
    return;

  v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(children);
  uint32_t size = array->Length();

  for (uint32_t i = 0; i < size; i++)
  {
    v8::Local<v8::Object> obj = array->CloneElementAt(i);
    NodeSkiaElement *elm = NodeSkiaElement::CreateElement(obj);
    if (elm)
      children_.push_back(elm);
  }
}

void NodeSkiaElement::renderChildren(SkCanvas *canvas)
{
  for (std::vector<NodeSkiaElement *>::const_iterator it = children_.begin();
       it != children_.end();
       it++)
    (*it)->render(canvas);
}

void NodeSkiaElement::clearChildren()
{
  while (children_.size() > 0)
  {
    delete children_.back();
    children_.pop_back();
  }
}

NodeSkiaRectangle::NodeSkiaRectangle()
  : x_(0),
    y_(0),
    width_(0),
    height_(0),
    color_(0x00000000),
    angle_(0)
{
}

NodeSkiaRectangle::~NodeSkiaRectangle()
{
}

void NodeSkiaRectangle::parse(v8::Local<v8::Object> obj)
{
  x_ = GetSkScalar(obj, "x");
  y_= GetSkScalar(obj, "y");
  width_ = GetSkScalar(obj, "width");
  height_ = GetSkScalar(obj, "height");
  color_ = GetSkColor(obj, "color");
  rotate_ = GetBool(obj, "rotate");
  angle_ = GetSkScalar(obj, "angle");

  this->parseChildren(obj);
}

void NodeSkiaRectangle::render(SkCanvas *canvas)
{
  SkPaint paint;
  SkRect rect;

  paint.setColor(color_);

  if (rotate_)
  {
    canvas->save();
    canvas->translate(x_ + width_ / 2, y_ + height_ / 2);
    canvas->rotate(angle_);
    rect.fLeft = -width_ / 2;
    rect.fTop = -height_ / 2;
    rect.fRight = width_ / 2;
    rect.fBottom = height_ / 2;
    canvas->drawRect(rect, paint);
    canvas->restore();
  }
  else
  {
    rect.fLeft = x_;
    rect.fTop = y_;
    rect.fRight = x_ + width_;
    rect.fBottom = y_ + height_;
    canvas->drawRect(rect, paint);
  }

  this->renderChildren(canvas);
}

NodeSkiaTree::NodeSkiaTree()
  : color_(0x00000000)
{
}

NodeSkiaTree::~NodeSkiaTree()
{
}

void NodeSkiaTree::parse(v8::Local<v8::Object> obj)
{
  color_ = GetSkColor(obj, "background");

  this->parseChildren(obj);
}

void NodeSkiaTree::render(SkCanvas *canvas)
{
  canvas->drawColor(color_);

  this->renderChildren(canvas);
}

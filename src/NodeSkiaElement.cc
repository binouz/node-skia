#include "NodeSkiaElement.h"
#include "NodeSkiaPoint.h"
#include "NodeSkiaLine.h"
#include "NodeSkiaRectangle.h"
#include "NodeSkiaOval.h"
#include "NodeSkiaCircle.h"
#include "NodeSkiaArc.h"
#include "NodeSkiaRoundRectangle.h"
#include "NodeSkiaText.h"

SkScalar GetSkScalar(v8::Local<v8::Object> obj, const char *str)
{
  if (!Nan::Has(obj, Nan::New(str).ToLocalChecked()).FromJust())
    return 0;

  v8::Local<v8::Value> prop = Nan::Get(obj, Nan::New(str).ToLocalChecked()).ToLocalChecked();
  if (!prop->IsNumber())
    return 0;

  return static_cast<SkScalar>(prop->ToNumber()->Value());
}

SkColor GetSkColor(v8::Local<v8::Object> obj, const char *str)
{
  if (!Nan::Has(obj, Nan::New(str).ToLocalChecked()).FromJust())
    return 0;

  v8::Local<v8::Value> prop = Nan::Get(obj, Nan::New(str).ToLocalChecked()).ToLocalChecked();
  if (!prop->IsNumber())
    return 0;

  return static_cast<SkColor>(prop->Uint32Value());
}

bool GetBool(v8::Local<v8::Object> obj, const char *str)
{
  if (!Nan::Has(obj, Nan::New(str).ToLocalChecked()).FromJust())
    return false;

  v8::Local<v8::Value> prop = Nan::Get(obj, Nan::New(str).ToLocalChecked()).ToLocalChecked();
  if (!prop->IsBoolean())
    return false;

  return prop->ToBoolean()->Value();
}

std::string GetString(v8::Local<v8::Object> obj, const char *str)
{
  if (!Nan::Has(obj, Nan::New(str).ToLocalChecked()).FromJust())
    return "";

  v8::Local<v8::Value> prop = Nan::Get(obj, Nan::New(str).ToLocalChecked()).ToLocalChecked();
  if (!prop->IsString())
    return "";

  Nan::Utf8String val(prop);

  return std::string(*val);
}

static NodeSkiaElement *CreateElement(v8::Local<v8::Object> obj)
{
  if (!Nan::Has(obj, Nan::New("type").ToLocalChecked()).FromJust())
    return NULL;

  v8::Local<v8::Value> value = Nan::Get(obj, Nan::New("type").ToLocalChecked()).ToLocalChecked();
  if (!value->IsString())
      return NULL;

  NodeSkiaElement *res = NULL;
  v8::String::Utf8Value str(value->ToString());
  if (std::string(*str) == "point")
    res = new NodeSkiaPoint(); /**/
  else if (std::string(*str) == "line")
    res = new NodeSkiaLine(); /**/
  else if (std::string(*str) == "rectangle")
    res = new NodeSkiaRectangle(); /**/
  else if (std::string(*str) == "oval")
    res = new NodeSkiaOval(); /**/
  else if (std::string(*str) == "circle")
    res = new NodeSkiaCircle(); /**/
  else if (std::string(*str) == "arc")
    res = new NodeSkiaArc(); /**/
  else if (std::string(*str) == "round-rectangle")
    res = new NodeSkiaRoundRectangle(); /**/
  else if (std::string(*str) == "text")
    res = new NodeSkiaText(); /**/
  else
    return NULL;

  res->parse(obj);

  return res;
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
    NodeSkiaElement *elm = CreateElement(obj);
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

void NodeSkiaElement::render(SkCanvas *canvas)
{
  canvas->save();
  renderElement(canvas);
  renderChildren(canvas);
  canvas->restore();
}

void NodeSkiaElement::parse(v8::Local<v8::Object> obj)
{
  top_ = 0;
  left_ = 0;
  right_ = 0;
  bottom_ = 0;
  width_ = 0;
  height_ = 0;

  if (Nan::Has(obj, Nan::New("layout").ToLocalChecked()).FromJust())
  {
    v8::Local<v8::Value> prop = Nan::Get(obj, Nan::New("layout").ToLocalChecked()).ToLocalChecked();
    if (prop->IsObject())
    {
      v8::Local<v8::Object> layout = prop->ToObject();
      top_ = GetSkScalar(layout, "top");
      left_ = GetSkScalar(layout, "left");
      right_ = GetSkScalar(layout, "right");
      bottom_ = GetSkScalar(layout, "bottom");
      width_ = GetSkScalar(layout, "width");
      height_ = GetSkScalar(layout, "height");
    }
  }

  parseElement(obj);
  parseChildren(obj);
}

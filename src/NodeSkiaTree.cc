#include "NodeSkiaTree.h"

NodeSkiaTree::NodeSkiaTree()
  : color_(0x00000000)
{
}

NodeSkiaTree::~NodeSkiaTree()
{
}

void NodeSkiaTree::parseElement(v8::Local<v8::Object> obj)
{
  color_ = GetSkColor(obj, "color");
}

void NodeSkiaTree::renderElement(SkCanvas *canvas)
{
  canvas->drawColor(color_);
}

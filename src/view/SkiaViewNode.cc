// Copyright 2017 Aubin REBILLAT <rebillat.aubin@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include "SkiaViewNode.h"

NAN_MODULE_INIT(SkiaViewNode::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(SkiaViewNode::New);
  v8::Local<v8::ObjectTemplate> obj_tpl = tpl->InstanceTemplate();
  tpl->SetClassName(Nan::New("ViewNode").ToLocalChecked());
  obj_tpl->SetInternalFieldCount(1);
  Nan::SetAccessor(obj_tpl, Nan::New("children").ToLocalChecked(),
                   SkiaViewNode::GetChildren, SkiaViewNode::SetChildren);
  Nan::SetAccessor(obj_tpl, Nan::New("style").ToLocalChecked(),
                   SkiaViewNode::GetStyle, SkiaViewNode::SetStyle);
  Nan::SetAccessor(obj_tpl, Nan::New("properties").ToLocalChecked(),
                   SkiaViewNode::GetProperties, SkiaViewNode::SetProperties);
  Nan::SetAccessor(obj_tpl, Nan::New("text").ToLocalChecked(),
                   SkiaViewNode::GetText, SkiaViewNode::SetText);
  constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("ViewNode").ToLocalChecked(),
           Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(SkiaViewNode::New) {
  if (info.IsConstructCall()) {
    SkiaViewNode *view = new SkiaViewNode();
    view->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    v8::Local<v8::Function> cons = Nan::New(SkiaViewNode::constructor());
    info.GetReturnValue().Set(cons->NewInstance(0, NULL));
  }
}

NAN_GETTER(SkiaViewNode::GetChildren) {
  SkiaViewNode *node = Nan::ObjectWrap::Unwrap<SkiaViewNode>(info.Holder());
  v8::Local<v8::Array> res = Nan::New<v8::Array>(node->children_.size());
  std::vector<SkiaViewNode *>::iterator it = node->children_.begin();

  for (int i = 0; it != node->children_.end(); ++it)
    Nan::Set(res, i++, (*it)->handle());

  info.GetReturnValue().Set(res);
}

NAN_GETTER(SkiaViewNode::GetStyle) {
  SkiaViewNode *node = Nan::ObjectWrap::Unwrap<SkiaViewNode>(info.Holder());
  info.GetReturnValue().Set(node->style_.GetObject());
}

NAN_GETTER(SkiaViewNode::GetText) {
  SkiaViewNode *node = Nan::ObjectWrap::Unwrap<SkiaViewNode>(info.Holder());
  info.GetReturnValue().Set(Nan::New(node->text_).ToLocalChecked());
}

NAN_GETTER(SkiaViewNode::GetProperties) {
  SkiaViewNode *node = Nan::ObjectWrap::Unwrap<SkiaViewNode>(info.Holder());
  info.GetReturnValue().Set(node->GetNodeProperties());
}

NAN_SETTER(SkiaViewNode::SetChildren) {
  if (!value->IsArray()) {
    Nan::ThrowError("Invalid type for children setter");
    return;
  }

  SkiaViewNode *node = Nan::ObjectWrap::Unwrap<SkiaViewNode>(info.Holder());
  v8::Local<v8::Array> children = value.As<v8::Array>();
  uint32_t size = children->Length();

  node->children_.clear();

  for (uint32_t i = 0; i < size; i++)
  {
    v8::Local<v8::Object> obj = v8::Local<v8::Object>::Cast(children->Get(i));
    node->children_.push_back(Nan::ObjectWrap::Unwrap<SkiaViewNode>(obj));
  }
}

NAN_SETTER(SkiaViewNode::SetStyle) {
  if (!value->IsObject()) {
    Nan::ThrowError("Invalid type for style setter");
    return;
  }

  SkiaViewNode *node = Nan::ObjectWrap::Unwrap<SkiaViewNode>(info.Holder());
  node->style_.Update(value.As<v8::Object>());
}

NAN_SETTER(SkiaViewNode::SetProperties) {
  if (!value->IsObject()) {
    Nan::ThrowError("Invalid type for properties setter");
    return;
  }

  SkiaViewNode *node = Nan::ObjectWrap::Unwrap<SkiaViewNode>(info.Holder());
  node->SetNodeProperties(value.As<v8::Object>());
}

NAN_SETTER(SkiaViewNode::SetText) {
  if (!value->IsString()) {
    Nan::ThrowError("Invalid type for text setter");
    return;
  }

  SkiaViewNode *node = Nan::ObjectWrap::Unwrap<SkiaViewNode>(info.Holder());
  Nan::Utf8String val(value);
  node->text_ = *val;
}

SkiaViewNode::SkiaViewNode() {
}

SkiaViewNode::~SkiaViewNode() {
}

void SkiaViewNode::Draw(SkCanvas *canvas) {
  canvas->save();

  DrawNode(canvas);

  for (std::vector<SkiaViewNode *>::iterator it = children_.begin();
       it != children_.end(); ++it) {
    (*it)->Draw(canvas);
  }

  style_.Transform(canvas);

  canvas->restore();
}

SkiaViewStyle *SkiaViewNode::GetStyle() {
  return &style_;
}

void SkiaViewNode::DrawNode(SkCanvas *canvas) {
  {
    SkPaint paint;
    SkRect rect;

    paint.setColor(style_.BackgroundColor());

    rect.fLeft = style_.Top();
    rect.fTop = style_.Left();
    rect.fRight = style_.Right();
    rect.fBottom = style_.Bottom();

    canvas->save();
    canvas->drawRoundRect(rect, 0, 0, paint);
    canvas->restore();
  }

  {
    canvas->save();
    style_.DrawBorders(canvas);
    canvas->restore();
  }

  {
    canvas->save();
    style_.DrawText(canvas, text_);
    canvas->restore();
  }
}

v8::Local<v8::Object> SkiaViewNode::GetNodeProperties() {
  return Nan::New<v8::Object>();
}

void SkiaViewNode::SetNodeProperties(v8::Local<v8::Object> props) {
}

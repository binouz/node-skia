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

#include "SkiaView.h"
#include "SkiaViewStyle.h"
#include "SkiaViewNode.h"

class SkiaView::SkiaViewTreeImpl : public SkiaView::Tree {
  public:

    SkiaViewTreeImpl(SkColor color)
      : node_(NULL), color_(color) {
      uv_mutex_init(&mutex_);
    }
    ~SkiaViewTreeImpl() {}

    void Draw(SkCanvas *canvas) {
      uv_mutex_lock(&mutex_);
      canvas->drawColor(color_);
      if (node_)
        node_->Draw(canvas);
      uv_mutex_unlock(&mutex_);
    }

    void Update(SkiaViewNode *node) {
      node_ = node;
    }

  private:

    SkiaViewNode *node_;

    SkColor color_;

    uv_mutex_t mutex_;
};

NAN_MODULE_INIT(SkiaView::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(SkiaView::New);
  tpl->SetClassName(Nan::New("View").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  Nan::SetPrototypeMethod(tpl, "setRoot", SkiaView::SetRoot);
  constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("View").ToLocalChecked(),
           Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(SkiaView::New) {
  if (info.Length() != 1) {
    Nan::ThrowError("Invalid number of argument for SkiaView constructor !");
    return;
  }

  if (info.IsConstructCall()) {
    SkiaView *view = new SkiaView(static_cast<SkColor>(info[0]->Uint32Value()));
    view->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    v8::Local<v8::Value> argv[] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New(SkiaView::constructor());
    info.GetReturnValue().Set(cons->NewInstance(1, argv));
  }
}

NAN_METHOD(SkiaView::SetRoot) {
  SkiaView* view = Nan::ObjectWrap::Unwrap<SkiaView>(info.Holder());

  if (info.Length() != 1) {
    Nan::ThrowError("Invalid number of argument for SkiaView.update !");
    return;
  }

  if (!info[0]->IsObject()) {
    Nan::ThrowError("Invalid argument for SkiaView.update !");
    return;
  }

  view->tree_->Update(Nan::ObjectWrap::Unwrap<SkiaViewNode>(
                        v8::Local<v8::Object>::Cast(info[0])));
}

SkiaView::SkiaView(SkColor color)
  : tree_(new SkiaViewTreeImpl(color)) {
}

SkiaView::~SkiaView() {
  delete tree_;
}

void SkiaView::Draw(SkCanvas *canvas) {
  tree_->Draw(canvas);
}

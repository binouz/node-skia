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

#ifndef SKIAVIEWELEMENT_H_
# define SKIAVIEWELEMENT_H_

#include <nan.h>

#include <SkCanvas.h>

#include "SkiaViewStyle.h"

class SkiaViewNode : public Nan::ObjectWrap {

  public:

    static NAN_MODULE_INIT(Init);

    SkiaViewNode();
    virtual ~SkiaViewNode();

    void Draw(SkCanvas *canvas);

  protected:

    SkiaViewStyle *GetStyle();

  private:

    static NAN_METHOD(New);

    static NAN_GETTER(GetChildren);
    static NAN_GETTER(GetStyle);
    static NAN_GETTER(GetProperties);
    static NAN_GETTER(GetText);

    static NAN_SETTER(SetChildren);
    static NAN_SETTER(SetStyle);
    static NAN_SETTER(SetProperties);
    static NAN_SETTER(SetText);

    static inline Nan::Persistent<v8::Function>& constructor() {
      static Nan::Persistent<v8::Function> my_constructor;
      return my_constructor;
    }

    virtual void DrawNode(SkCanvas *canvas);
    virtual v8::Local<v8::Object> GetNodeProperties();
    virtual void SetNodeProperties(v8::Local<v8::Object> props);

    SkiaViewStyle style_;

    std::string text_;

    std::vector<SkiaViewNode *> children_;
};

#endif /* !SKIAVIEWELEMENT.H */

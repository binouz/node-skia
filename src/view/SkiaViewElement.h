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

class SkiaViewElement {

  public:

    static SkiaViewElement *CreateElement(v8::Local<v8::Object> obj);

    SkiaViewElement();
    virtual ~SkiaViewElement();

    void Draw(SkCanvas *canvas);
    void Update(v8::Local<v8::Object> object);

  protected:

    SkiaViewStyle *GetStyle();

  private:

    SkiaViewElement(v8::Local<v8::Object> obj);

    virtual void DrawElement(SkCanvas *canvas);
    virtual void UpdateElement(v8::Local<v8::Object> obj);

    void UpdateChildren(v8::Local<v8::Array> children);
    void ClearChildren();

    SkiaViewStyle style_;

    std::string content_;

    std::vector<SkiaViewElement *> children_;

};

#endif /* !SKIAVIEWELEMENT.H */

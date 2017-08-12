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

#ifndef SKIAVIEW_H_
# define SKIAVIEW_H_

#include <nan.h>

#include <SkCanvas.h>

class SkiaViewNode;

class SkiaView : public Nan::ObjectWrap {

  public:

    static NAN_MODULE_INIT(Init);

    void Draw(SkCanvas *canvas);

    ~SkiaView();

  private:

    static NAN_METHOD(New);
    static NAN_METHOD(SetRoot);

    static inline Nan::Persistent<v8::Function>& constructor() {
      static Nan::Persistent<v8::Function> my_constructor;
      return my_constructor;
    }

    SkiaView(SkColor color);

    class Tree {
      public:
        virtual void Draw(SkCanvas *canvas) = 0;
        virtual void Update(SkiaViewNode *node) = 0;

        Tree() {}
        virtual ~Tree() {}
    };

    class SkiaViewTreeImpl;

    Tree *tree_;
};

#endif /* !SKIAVIEW.H */

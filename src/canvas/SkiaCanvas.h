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

#ifndef SKIACANVAS_H_
# define SKIACANVAS_H_

#include <nan.h>

#include <SkCanvas.h>

class SkiaCanvas  : public Nan::ObjectWrap {
  public:

    static NAN_MODULE_INIT(Init);

    static NAN_METHOD(New);

    static NAN_METHOD(Flush);
    static NAN_METHOD(Save);
    static NAN_METHOD(Restore);
    static NAN_METHOD(SetPaint);

    static NAN_METHOD(Translate);
    static NAN_METHOD(Scale);
    static NAN_METHOD(Rotate);
    static NAN_METHOD(Skew);
    // static NAN_METHOD(Concat);
    // static NAN_METHOD(SetMatrix);

    static NAN_METHOD(DrawColor);
    static NAN_METHOD(DrawPoint);
    static NAN_METHOD(DrawRect);
    static NAN_METHOD(DrawOval);
    static NAN_METHOD(DrawCircle);
    static NAN_METHOD(DrawArc);
    static NAN_METHOD(DrawRoundRect);
    // static NAN_METHOD(DrawPath);
    // static NAN_METHOD(DrawImage);
    // static NAN_METHOD(DrawBitmap);
    static NAN_METHOD(DrawText);

    static inline Nan::Persistent<v8::Function>& constructor() {
      static Nan::Persistent<v8::Function> my_constructor;
      return my_constructor;
    }

    static v8::Local<v8::Object> CreateObject(SkCanvas* canvas);

    SkiaCanvas();
    ~SkiaCanvas();

  private:

    void Set(SkCanvas *canvas);

    SkCanvas *canvas_;
    SkPaint paint_;
};

#endif /* !SKIACANVAS.H */

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

#ifndef SKIAVIEWSTYLE_H_
# define SKIAVIEWSTYLE_H_

#include <nan.h>

#include <SkCanvas.h>

// class SkiaViewTransform {
// };

class SkiaViewStyle {

  public:

    SkiaViewStyle();
    ~SkiaViewStyle();

    void Transform(SkCanvas *canvas);
    void Update(v8::Local<v8::Object> object);

    void DrawText(SkCanvas *canvas, std::string& text);
    void DrawBorders(SkCanvas *canvas);

    SkColor Color();
    SkColor BackgroundColor();
    SkScalar FontSize();
    SkScalar Width();
    SkScalar Height();
    SkScalar Top();
    SkScalar Left();
    SkScalar Right();
    SkScalar Bottom();
    std::string Direction();

    v8::Local<v8::Object> GetObject();

  private:

    SkColor color_;
    SkColor background_color_;
    SkScalar font_size_;
    SkScalar width_;
    SkScalar height_;
    SkScalar top_;
    SkScalar left_;
    SkScalar right_;
    SkScalar bottom_;
    std::string direction_;
    SkScalar margin_top_;
    SkScalar margin_left_;
    SkScalar margin_right_;
    SkScalar margin_bottom_;
    SkScalar padding_top_;
    SkScalar padding_left_;
    SkScalar padding_right_;
    SkScalar padding_bottom_;
    SkScalar border_;

    // TODO : Transforms, Advanced Background, Border
};

#endif /* !SKIAVIEWSTYLE.H */

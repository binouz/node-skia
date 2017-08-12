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

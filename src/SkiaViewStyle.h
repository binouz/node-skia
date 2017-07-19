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

    SkColor Color();
    SkColor BackgroundColor();
    SkScalar X();
    SkScalar Y();
    SkScalar Width();
    SkScalar Height();
    SkScalar FontSize();

  private:

    SkColor color_;
    SkColor background_color_;
    SkScalar x_;
    SkScalar y_;
    SkScalar width_;
    SkScalar height_;
    SkScalar font_size_;

    //std::vector<SkiaViewTransform> transforms_;
};

#endif /* !SKIAVIEWSTYLE.H */

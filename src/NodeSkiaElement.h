#ifndef NODESKIAELEMENT_H_
# define NODESKIAELEMENT_H_

#include <nan.h>
#include <SkCanvas.h>

class NodeSkiaElement {
  public:
    NodeSkiaElement();
    virtual ~NodeSkiaElement();

    void parse(v8::Local<v8::Object> obj);
    void render(SkCanvas *canvas);

  protected:

    virtual void renderElement(SkCanvas *canvas) = 0;
    virtual void parseElement(v8::Local<v8::Object> obj) = 0;

    SkScalar top_;
    SkScalar left_;
    SkScalar right_;
    SkScalar bottom_;
    SkScalar width_;
    SkScalar height_;

  private:

    void parseChildren(v8::Local<v8::Object> obj);
    void renderChildren(SkCanvas *canvas);
    void clearChildren();

    std::vector<NodeSkiaElement *> children_;
};

SkScalar GetSkScalar(v8::Local<v8::Object> obj, const char *str);
SkColor GetSkColor(v8::Local<v8::Object> obj, const char *str);
bool GetBool(v8::Local<v8::Object> obj, const char *str);
std::string GetString(v8::Local<v8::Object> obj, const char *str);

#endif /* !NODESKIAELEMENT.H */

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

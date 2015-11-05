#ifndef NODESKIAARC_H_
# define NODESKIAARC_H_

#include "NodeSkiaElement.h"

class NodeSkiaArc : public NodeSkiaElement {
  public:

    NodeSkiaArc();
    ~NodeSkiaArc();

  protected:

    void parseElement(v8::Local<v8::Object> obj);
    void renderElement(SkCanvas *canvas);

  private:
    SkColor color_;
    SkScalar start_;
    SkScalar sweep_;
    bool use_center_;
};

#endif /* !NODESKIAARC.H */

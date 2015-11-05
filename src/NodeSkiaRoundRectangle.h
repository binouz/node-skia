#ifndef NODESKIAROUNDRECTANGLE_H_
# define NODESKIAROUNDRECTANGLE_H_

#include "NodeSkiaElement.h"

class NodeSkiaRoundRectangle : public NodeSkiaElement {
  public:

    NodeSkiaRoundRectangle();
    ~NodeSkiaRoundRectangle();

  protected:

    void parseElement(v8::Local<v8::Object> obj);
    void renderElement(SkCanvas *canvas);

  private:

    SkColor color_;
    SkScalar x_radius_;
    SkScalar y_radius_;
};

#endif /* !NODESKIAROUNDRECTANGLE.H */

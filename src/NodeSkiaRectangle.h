#ifndef NODESKIARECTANGLE_H_
# define NODESKIARECTANGLE_H_

#include "NodeSkiaElement.h"

class NodeSkiaRectangle : public NodeSkiaElement {
  public:

    NodeSkiaRectangle();
    ~NodeSkiaRectangle();

  protected:

    void parseElement(v8::Local<v8::Object> obj);
    void renderElement(SkCanvas *canvas);

  private:
    SkColor color_;
};

#endif /* !NODESKIARECTANGLE.H */

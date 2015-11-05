#ifndef NODESKIACIRCLE_H_
# define NODESKIACIRCLE_H_

#include "NodeSkiaElement.h"

class NodeSkiaCircle : public NodeSkiaElement {
  public:

    NodeSkiaCircle();
    ~NodeSkiaCircle();

  protected:

    void parseElement(v8::Local<v8::Object> obj);
    void renderElement(SkCanvas *canvas);

  private:
    SkColor color_;
};

#endif /* !NODESKIACIRCLE.H */

#ifndef NODESKIAOVAL_H_
# define NODESKIAOVAL_H_

#include "NodeSkiaElement.h"

class NodeSkiaOval : public NodeSkiaElement {
  public:

    NodeSkiaOval();
    ~NodeSkiaOval();

  protected:

    void parseElement(v8::Local<v8::Object> obj);
    void renderElement(SkCanvas *canvas);

  private:
    SkColor color_;
};

#endif /* !NODESKIAOVAL.H */

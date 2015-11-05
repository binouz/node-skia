#ifndef NODESKIAPOINT_H_
# define NODESKIAPOINT_H_

#include "NodeSkiaElement.h"

class NodeSkiaPoint : public NodeSkiaElement {
  public:

    NodeSkiaPoint();
    ~NodeSkiaPoint();

  protected:

    void parseElement(v8::Local<v8::Object> obj);
    void renderElement(SkCanvas *canvas);

  private:
    SkColor color_;
};

#endif /* !NODESKIAPOINT.H */

#ifndef NODESKIALINE_H_
# define NODESKIALINE_H_

#include "NodeSkiaElement.h"

class NodeSkiaLine : public NodeSkiaElement {
  public:

    NodeSkiaLine();
    ~NodeSkiaLine();

  protected:

    void parseElement(v8::Local<v8::Object> obj);
    void renderElement(SkCanvas *canvas);

  private:
    SkColor color_;
};

#endif /* !NODESKIALINE.H */

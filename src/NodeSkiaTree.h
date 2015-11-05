#ifndef NODESKIATREE_H_
# define NODESKIATREE_H_

#include "NodeSkiaElement.h"

class NodeSkiaTree : public NodeSkiaElement {
  public:

    NodeSkiaTree();
    ~NodeSkiaTree();

  protected:

    void renderElement(SkCanvas *canvas);
    void parseElement(v8::Local<v8::Object> elements);

  private:
    SkColor color_;
};

#endif /* !NODESKIATREE.H */

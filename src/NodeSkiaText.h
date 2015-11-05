#ifndef NODESKIATEXT_H_
# define NODESKIATEXT_H_

#include "NodeSkiaElement.h"

class NodeSkiaText : public NodeSkiaElement {
  public:

    NodeSkiaText();
    ~NodeSkiaText();

  protected:

    void parseElement(v8::Local<v8::Object> obj);
    void renderElement(SkCanvas *canvas);

  private:
    SkColor color_;
    std::string text_;
};

#endif /* !NODESKIATEXT.H */

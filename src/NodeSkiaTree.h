#ifndef NODESKIATREE_H_
# define NODESKIATREE_H_

#include <nan.h>
#include <SkCanvas.h>

class NodeSkiaRectangle;

class NodeSkiaElement {
  public:
    NodeSkiaElement();
    virtual ~NodeSkiaElement();

    void parse(v8::Local<v8::Object> obj);
    void render(SkCanvas *canvas);

  protected:

    static NodeSkiaElement *CreateElement(v8::Local<v8::Object> element);
    virtual void renderElement(SkCanvas *canvas) = 0;
    virtual void parseElement(v8::Local<v8::Object> obj) = 0;

    SkScalar top_;
    SkScalar left_;
    SkScalar right_;
    SkScalar bottom_;
    SkScalar width_;
    SkScalar height_;

  private:

    void parseChildren(v8::Local<v8::Object> obj);
    void renderChildren(SkCanvas *canvas);
    void clearChildren();

    static NodeSkiaRectangle *CreateNodeSkiaRectangle(v8::Local<v8::Object> value);

    std::vector<NodeSkiaElement *> children_;
};

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

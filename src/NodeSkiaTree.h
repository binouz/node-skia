#ifndef NODESKIATREE_H_
# define NODESKIATREE_H_

#include <nan.h>
#include <SkCanvas.h>

class NodeSkiaRectangle;

class NodeSkiaElement {
  public:
    NodeSkiaElement();
    virtual ~NodeSkiaElement();

    virtual void parse(v8::Local<v8::Object> obj) = 0;
    virtual void render(SkCanvas *canvas ) = 0;

  protected:

    static NodeSkiaElement *CreateElement(v8::Local<v8::Object> element);
    void parseChildren(v8::Local<v8::Object> obj);
    void renderChildren(SkCanvas *canvas);

  private:

    void clearChildren();

    static NodeSkiaRectangle *CreateNodeSkiaRectangle(v8::Local<v8::Object> value);

    std::vector<NodeSkiaElement *> children_;
};

class NodeSkiaRectangle : public NodeSkiaElement {
  public:

    NodeSkiaRectangle();
    ~NodeSkiaRectangle();

    void parse(v8::Local<v8::Object> obj);
    void render(SkCanvas *canvas);

  private:
    SkScalar x_;
    SkScalar y_;
    SkScalar width_;
    SkScalar height_;
    SkColor color_;
    bool rotate_;
    SkScalar speed_;
    SkScalar angle_;
};

class NodeSkiaTree : public NodeSkiaElement {
  public:

    NodeSkiaTree();
    ~NodeSkiaTree();

    void render(SkCanvas *canvas);
    void parse(v8::Local<v8::Object> elements);

  private:
    SkColor color_;

};

#endif /* !NODESKIATREE.H */

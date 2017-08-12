#include "SkiaWindow.h"
#include "canvas/SkiaCanvas.h"
#include "view/SkiaView.h"
#include "view/SkiaViewNode.h"

void Init(v8::Local<v8::Object> exports)
{
  SkiaWindow::Init(exports);
  SkiaCanvas::Init(exports);
  SkiaView::Init(exports);
  SkiaViewNode::Init(exports);
}

NODE_MODULE(skia, Init)

#include "SkiaWindow.h"
#include "SkiaCanvas.h"
#include "SkiaView.h"

void Init(v8::Local<v8::Object> exports)
{
  SkiaWindow::Init(exports);
  SkiaCanvas::Init(exports);
  SkiaView::Init(exports);
}

NODE_MODULE(skia, Init)

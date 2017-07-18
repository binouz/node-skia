#include "SkiaWindow.h"
#include "SkiaCanvas.h"

void Init(v8::Local<v8::Object> exports)
{
  SkiaWindow::Init(exports);
  SkiaCanvas::Init(exports);
}

NODE_MODULE(skia, Init)

#include "NodeOSWindow.h"

#include "NodeSkiaCanvas.h"
#include "NodeSkiaPaint.h"

void Start(const Nan::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() != 1) {
    Nan::ThrowError("Wrong number of arguments");
    return;
  }

  if (!args[0]->IsFunction()) {
    Nan::ThrowTypeError("Wrong argument type");
    return;
  }

  NodeOSWindow *window = NodeOSWindow::GetInstance();

  if (!window)
    return;

  window->SetCallback(args[0].As<v8::Function>());

  while (SkEvent::ProcessEvent())
    ;

  window->start();
}

void Stop(const Nan::FunctionCallbackInfo<v8::Value>& args)
{
  NodeOSWindow *window = NodeOSWindow::GetInstance();

  if (window)
    window->stop();
}

void Draw(const Nan::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() != 1) {
    Nan::ThrowError("Wrong number of arguments");
    return;
  }

  if (!args[0]->IsObject()) {
    Nan::ThrowTypeError("Wrong argument type");
    return;
  }

  NodeOSWindow *window = NodeOSWindow::GetInstance();

  if (!window)
    return;

  window->drawTree(args[0]->ToObject());
}

void Init(v8::Local<v8::Object> exports)
{
  //NodeSkiaCanvas::Initialise(exports);
  //NodeSkiaPaint::Initialise(exports);
  exports->Set(Nan::New("Start").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Start)->GetFunction());
  exports->Set(Nan::New("Stop").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Stop)->GetFunction());
  exports->Set(Nan::New("Draw").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Draw)->GetFunction());
}

NODE_MODULE(skia, Init)

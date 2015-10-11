#include "NodeSkiaCanvas.h"
#include "NodeSkiaPaint.h"

Nan::Persistent<v8::Function> NodeSkiaCanvas::constructor;

NodeSkiaCanvas::NodeSkiaCanvas()
{
  owner_ = true;
  canvas_ = new SkCanvas();
}

NodeSkiaCanvas::~NodeSkiaCanvas()
{
  if (owner_)
    delete canvas_;
}

void NodeSkiaCanvas::setCanvas(SkCanvas *canvas)
{
  delete canvas_;
  owner_ = false;
  canvas_ = canvas;
}

void NodeSkiaCanvas::Initialise(v8::Local<v8::Object> exports)
{
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("SkCanvas").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "drawColor", drawColor);
  Nan::SetPrototypeMethod(tpl, "drawRect", drawRect);
  Nan::SetPrototypeMethod(tpl, "drawCircle", drawCircle);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("SkCanvas").ToLocalChecked(), tpl->GetFunction());
}

void NodeSkiaCanvas::New(const Nan::FunctionCallbackInfo<v8::Value>& args)
{
  if (args.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    NodeSkiaCanvas* obj = new NodeSkiaCanvas();
    obj->Wrap(args.This());
    args.GetReturnValue().Set(args.This());
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 0;
    v8::Local<v8::Value> argv[argc] = {};
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    args.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void NodeSkiaCanvas::drawColor(const Nan::FunctionCallbackInfo<v8::Value>& args)
{
  if (args.Length() != 1)
  {
    Nan::ThrowError("Wrong number of arguments");
    return;
  }

  if (!args[0]->IsNumber())
  {
    Nan::ThrowTypeError("Wrong argument type");
    return;
  }

  NodeSkiaCanvas *obj = ObjectWrap::Unwrap<NodeSkiaCanvas>(args.Holder());

  obj->toSkCanvas()->drawColor(static_cast<SkColor>(args[0]->Uint32Value()));

  args.GetReturnValue().Set(Nan::Undefined());
}

void NodeSkiaCanvas::drawRect(const Nan::FunctionCallbackInfo<v8::Value>& args)
{
  if (args.Length() != 5)
  {
    Nan::ThrowError("Wrong number of arguments");
    return;
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber() || !args[3]->IsNumber() || !args[4]->IsObject())
  {
    Nan::ThrowTypeError("Wrong argument type");
    return;
  }

  NodeSkiaCanvas *obj = ObjectWrap::Unwrap<NodeSkiaCanvas>(args.Holder());
  NodeSkiaPaint *paint = ObjectWrap::Unwrap<NodeSkiaPaint>(args[4]->ToObject());

  SkRect rect;
  rect.fLeft = args[0]->NumberValue();
  rect.fTop = args[1]->NumberValue();
  rect.fRight = rect.fLeft + args[2]->NumberValue();
  rect.fBottom = rect.fTop + args[3]->NumberValue();

  obj->toSkCanvas()->drawRect(rect, *(paint->toSkPaint()));

  args.GetReturnValue().Set(Nan::Undefined());
}

void NodeSkiaCanvas::drawCircle(const Nan::FunctionCallbackInfo<v8::Value>& args)
{
  if (args.Length() != 4)
  {
    Nan::ThrowError("Wrong number of arguments");
    return;
  }

  if (!args[0]->IsNumber() || !args[1]->IsNumber() || !args[2]->IsNumber() || !args[3]->IsObject())
  {
    Nan::ThrowTypeError("Wrong argument type");
    return;
  }

  NodeSkiaCanvas *obj = ObjectWrap::Unwrap<NodeSkiaCanvas>(args.Holder());
  NodeSkiaPaint *paint = ObjectWrap::Unwrap<NodeSkiaPaint>(args[4]->ToObject());

  obj->toSkCanvas()->drawCircle(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), *(paint->toSkPaint()));

  args.GetReturnValue().Set(Nan::Undefined());
}

v8::Local<v8::Value> NodeSkiaCanvas::NewJSObject(SkCanvas *canvas)
{
  Nan::EscapableHandleScope scope;
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance();
  ObjectWrap::Unwrap<NodeSkiaCanvas>(instance)->setCanvas(canvas);
  return scope.Escape(instance);
}

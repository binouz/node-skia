#include "NodeSkiaPaint.h"

Nan::Persistent<v8::Function> NodeSkiaPaint::constructor;

NodeSkiaPaint::NodeSkiaPaint()
{
  paint_ = new SkPaint();
}


NodeSkiaPaint::~NodeSkiaPaint()
{
  delete paint_;
}

void NodeSkiaPaint::Initialise(v8::Local<v8::Object> exports)
{
  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);;
  tpl->SetClassName(Nan::New("SkPaint").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "setColor", setColor);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("SkPaint").ToLocalChecked(), tpl->GetFunction());
}

void NodeSkiaPaint::New(const Nan::FunctionCallbackInfo<v8::Value>& args)
{
  if (args.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    NodeSkiaPaint* obj = new NodeSkiaPaint();
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

void NodeSkiaPaint::setColor(const Nan::FunctionCallbackInfo<v8::Value>& args)
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

  NodeSkiaPaint *obj = ObjectWrap::Unwrap<NodeSkiaPaint>(args.Holder());
  obj->toSkPaint()->setColor(static_cast<SkColor>(args[0]->Uint32Value()));
  args.GetReturnValue().Set(Nan::Undefined());
}

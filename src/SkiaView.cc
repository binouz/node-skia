#include "SkiaView.h"
#include "SkiaViewStyle.h"
#include "SkiaViewElement.h"

class SkiaView::SkiaViewTreeImpl : public SkiaView::Tree,
                                   public SkiaViewElement {
  public:

    SkiaViewTreeImpl(SkColor background_color)
      : background_color_(background_color) {
      uv_mutex_init(&mutex_);
    }
    ~SkiaViewTreeImpl() {}

    void Draw(SkCanvas *canvas) {
      uv_mutex_lock(&mutex_);
      canvas->drawColor(background_color_);
      SkiaViewElement::Draw(canvas);
      uv_mutex_unlock(&mutex_);
    }

    void Update(v8::Local<v8::Object> tree) {
      uv_mutex_lock(&mutex_);
      SkiaViewElement::Update(tree);
      uv_mutex_unlock(&mutex_);
    }

  private:

    SkColor background_color_;

    uv_mutex_t mutex_;
};

NAN_MODULE_INIT(SkiaView::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(SkiaView::New);
  tpl->SetClassName(Nan::New("View").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  Nan::SetPrototypeMethod(tpl, "update", SkiaView::Update);
  constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("View").ToLocalChecked(),
           Nan::GetFunction(tpl).ToLocalChecked());
}

NAN_METHOD(SkiaView::New) {
  if (info.Length() != 1) {
    Nan::ThrowError("Invalid number of argument for SkiaView constructor !");
    return;
  }

  if (info.IsConstructCall()) {
    SkiaView *view = new SkiaView(static_cast<SkColor>(info[0]->Uint32Value()));
    view->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    v8::Local<v8::Value> argv[] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New(SkiaView::constructor());
    info.GetReturnValue().Set(cons->NewInstance(1, argv));
  }
}

NAN_METHOD(SkiaView::Update) {
  SkiaView* view = Nan::ObjectWrap::Unwrap<SkiaView>(info.Holder());

  if (info.Length() != 1) {
    Nan::ThrowError("Invalid number of argument for SkiaView.update !");
    return;
  }

  if (!info[0]->IsObject()) {
    Nan::ThrowError("Invalid argument for SkiaView.update !");
    return;
  }

  view->tree_->Update(info[0].As<v8::Object>());
}

SkiaView::SkiaView(SkColor background_color)
  : tree_(new SkiaViewTreeImpl(background_color)) {
}

SkiaView::~SkiaView() {
  delete tree_;
}

void SkiaView::Draw(SkCanvas *canvas) {
  tree_->Draw(canvas);
}

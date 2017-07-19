#ifndef V8UTILS_H_
# define V8UTILS_H_

namespace V8Utils {

  static inline SkScalar GetSkScalar(v8::Local<v8::Object> obj, const char *str)
  {
    if (!Nan::Has(obj, Nan::New(str).ToLocalChecked()).FromJust())
      return 0;

    v8::Local<v8::Value> prop = Nan::Get(obj, Nan::New(str).ToLocalChecked()).ToLocalChecked();
    if (!prop->IsNumber())
      return 0;

    return static_cast<SkScalar>(prop->ToNumber()->Value());
  }

  static inline SkColor GetSkColor(v8::Local<v8::Object> obj, const char *str)
  {
    if (!Nan::Has(obj, Nan::New(str).ToLocalChecked()).FromJust())
      return 0;

    v8::Local<v8::Value> prop = Nan::Get(obj, Nan::New(str).ToLocalChecked()).ToLocalChecked();
    if (!prop->IsNumber())
      return 0;

    return static_cast<SkColor>(prop->Uint32Value());
  }

  static inline bool GetBool(v8::Local<v8::Object> obj, const char *str)
  {
    if (!Nan::Has(obj, Nan::New(str).ToLocalChecked()).FromJust())
      return false;

    v8::Local<v8::Value> prop = Nan::Get(obj, Nan::New(str).ToLocalChecked()).ToLocalChecked();
    if (!prop->IsBoolean())
      return false;

    return prop->ToBoolean()->Value();
  }

  static inline std::string GetString(v8::Local<v8::Object> obj, const char *str)
  {
    if (!Nan::Has(obj, Nan::New(str).ToLocalChecked()).FromJust())
      return "";

    v8::Local<v8::Value> prop = Nan::Get(obj, Nan::New(str).ToLocalChecked()).ToLocalChecked();
    if (!prop->IsString())
      return "";

    Nan::Utf8String val(prop);

    return std::string(*val);
  }

  static inline v8::Local<v8::Object> GetObject(v8::Local<v8::Object> obj, const char *str)
  {
    if (!Nan::Has(obj, Nan::New(str).ToLocalChecked()).FromJust())
      return Nan::New<v8::Object>();

    v8::Local<v8::Value> prop = Nan::Get(obj, Nan::New(str).ToLocalChecked()).ToLocalChecked();
    if (!prop->IsObject())
      return Nan::New<v8::Object>();

    return prop.As<v8::Object>();
  }

  static inline v8::Local<v8::Array> GetArray(v8::Local<v8::Object> obj, const char *str)
  {
    if (!Nan::Has(obj, Nan::New(str).ToLocalChecked()).FromJust())
      return Nan::New<v8::Array>();

    v8::Local<v8::Value> prop = Nan::Get(obj, Nan::New(str).ToLocalChecked()).ToLocalChecked();
    if (!prop->IsArray())
      return Nan::New<v8::Array>();

    return v8::Local<v8::Array>::Cast(prop);
  }

}

#endif /* !V8UTILS.H */

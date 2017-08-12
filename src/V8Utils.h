// Copyright 2017 Aubin REBILLAT <rebillat.aubin@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

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

#ifndef EGLNATIVEINTERFACE_H_
# define EGLNATIVEINTERFACE_H_

#include <string>

#include <nan.h>

#include <EGL/egl.h>
#include <GLES2/gl2.h>

class EGLNativeInterface {

  public:

    class Event {
      public:

        Event() {}
        virtual ~Event() {}

        virtual const std::string GetName() = 0;
        virtual v8::Local<v8::Object> GetData() = 0;
    };

    class EventClient {
      public:
        virtual void EmitEvent(Event* event) = 0;
    };

    static EGLNativeInterface *CreateBackend(int width, int height, EventClient* client);

    bool Initialise();
    void Reset();
    void SwapBuffers();
    void Release();
    int StencilBits();
    int SampleCount();

    virtual void SetupEvents() = 0;
    virtual void ProcessEvents() = 0;

    virtual ~EGLNativeInterface() = 0;

  protected:

    class CloseEvent : public Event {
      public:
        CloseEvent() {}
        ~CloseEvent() {}

        const std::string GetName() override {
          return "close";
        }

        v8::Local<v8::Object> GetData() {
          return Nan::New<v8::Object>();
        }
    };

    class KeyEvent : public Event {
      public:
        KeyEvent(int key_code) : key_code_(key_code) {}
        ~KeyEvent() {}

        const std::string GetName() override {
          return "key";
        }

        v8::Local<v8::Object> GetData() override {
          v8::Local<v8::Object> data = Nan::New<v8::Object>();
          Nan::ForceSet(data, Nan::New("keycode").ToLocalChecked(), Nan::New(key_code_));
          return data;
        }

      private:

        int key_code_;
    };

    class ClickEvent : public Event {
      public:
        ClickEvent(int x, int y) : x_(x), y_(y) {}
        ~ClickEvent() {}

        const std::string GetName() override {
          return "click";
        }

        v8::Local<v8::Object> GetData() override {
          v8::Local<v8::Object> data = Nan::New<v8::Object>();
          Nan::ForceSet(data, Nan::New("x").ToLocalChecked(), Nan::New(x_));
          Nan::ForceSet(data, Nan::New("y").ToLocalChecked(), Nan::New(y_));
          return data;
        }

      private:

        int x_;
        int y_;
    };

    EGLNativeInterface(int width, int height);

    int width() { return width_; }
    int height() { return height_; }

    virtual EGLDisplay GetDisplay() = 0;
    virtual EGLSurface CreateWindowSurface(EGLDisplay display, EGLConfig config) = 0;

  private:

    EGLDisplay display_;
    EGLConfig config_;
    EGLSurface surface_;
    EGLContext context_;

    int width_;
    int height_;
};

#endif /* !EGLNATIVEINTERFACE.H */

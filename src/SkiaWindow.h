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

#ifndef SKIAWINDOW_H_
# define SKIAWINDOW_H_

#include <atomic>
#include <map>
#include <vector>

#include <nan.h>

#include "view/SkiaView.h"
#include "interface/EGLNativeInterface.h"

class SkCanvas;

class SkiaWindow : public EGLNativeInterface::EventClient,
                   public Nan::ObjectWrap
{
  public:

    static NAN_MODULE_INIT(Init);

    void Draw(SkCanvas *canvas);
    void EmitEvent(EGLNativeInterface::Event* event);

  protected:

    bool Running() {
      return running_;
    }

  private:

    class MainLoop : public Nan::AsyncWorker {
      public :

        MainLoop(Nan::Callback *cb,
                 EGLNativeInterface* backend,
                 SkiaWindow *window,
                 uv_mutex_t *mutex,
                 int width, int height);
        ~MainLoop();

        void Execute() override;

      private:

        EGLNativeInterface* egl_interface_;
        SkiaWindow* window_;

        uv_mutex_t *mutex_;

        int width_;
        int height_;

        friend SkiaWindow;
    };

    static NAN_METHOD(New);
    static NAN_METHOD(Start);
    static NAN_METHOD(Stop);
    static NAN_METHOD(Release);
    static NAN_METHOD(SetDrawHandler);
    static NAN_METHOD(SetView);
    static NAN_METHOD(onMainLoopEnd);
    static NAN_METHOD(On);

    static inline Nan::Persistent<v8::Function>& constructor() {
      static Nan::Persistent<v8::Function> my_constructor;
      return my_constructor;
    }

    static void DrawThreadJumper(uv_async_t* handle);
    static void EventThreadJumper(uv_async_t* handle);

    explicit SkiaWindow(int width, int height);
    ~SkiaWindow();

    void Start();
    void Stop();
    void Release();
    void SetDrawHandler(v8::Local<v8::Function> handler);
    void CallDrawHandlerOnNodeThread(SkCanvas *canvas);
    void SetView(v8::Local<v8::Object> view);
    void AddEventHandler(std::string name, v8::Local<v8::Function> handler);
    void RemoveEventHandler(std::string name, v8::Local<v8::Function> handler);
    void CallEventHandlersOnNodeThread(EGLNativeInterface::Event* event);
    void ClearEventHandlers();

    EGLNativeInterface* egl_interface_;
    MainLoop *loop_;

    Nan::Callback draw_handler_;
    bool has_draw_handler_;

    SkiaView *view_;

    uv_async_t event_async_;
    uv_mutex_t event_mutex_;
    uv_async_t draw_async_;
    uv_cond_t draw_cond_;
    uv_mutex_t draw_cond_mutex_;
    uv_mutex_t draw_mutex_;

    int width_;
    int height_;

    typedef std::vector<Nan::Callback*> EventHandlerVector;
    std::map<std::string, EventHandlerVector> event_handlers_;

    std::atomic<bool> running_;
};

#endif /* !SKIAWINDOW.H */

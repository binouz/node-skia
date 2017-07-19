#ifndef SKIAWINDOW_H_
# define SKIAWINDOW_H_

#include <atomic>

#include <nan.h>

#include "EGLNativeBackend.h"

class SkCanvas;

class SkiaWindow : public Nan::ObjectWrap
{
  public:

    static NAN_MODULE_INIT(Init);

    void Draw(SkCanvas *canvas);

  protected:

    bool Running() {
      return running_;
    }

  private:

    class MainLoop : public Nan::AsyncWorker {
      public :

        MainLoop(Nan::Callback *cb,
                 EGLNativeBackend* backend,
                 SkiaWindow *window,
                 int width, int height);
        ~MainLoop();

        void Execute() override;

      private:

        EGLNativeBackend* backend_;
        SkiaWindow* window_;

        int width_;
        int height_;

        friend SkiaWindow;
    };

    static NAN_METHOD(New);
    static NAN_METHOD(Start);
    static NAN_METHOD(Stop);
    static NAN_METHOD(Release);
    static NAN_METHOD(SetDrawHandler);
    static NAN_METHOD(onMainLoopEnd);

    static inline Nan::Persistent<v8::Function>& constructor() {
      static Nan::Persistent<v8::Function> my_constructor;
      return my_constructor;
    }

    static void ThreadJumper(uv_async_t* handle);

    explicit SkiaWindow(int width, int height);
    ~SkiaWindow();

    void Start();
    void Stop();
    void Release();
    void SetDrawHandler(v8::Local<v8::Function> handler);
    void CallDrawHandler(SkCanvas *canvas);

    EGLNativeBackend* backend_;
    MainLoop *loop_;

    Nan::Callback draw_handler_;
    bool has_draw_handler_;

    bool has_view_;

    uv_async_t async_;
    uv_cond_t cond_;
    uv_mutex_t mutex_;

    int width_;
    int height_;

    std::atomic<bool> running_;
};

#endif /* !SKIAWINDOW.H */

#ifndef NODEOSWINDOW_H_
# define NODEOSWINDOW_H_

#include <nan.h>
#include <uv.h>

#include <SkWindow.h>
#include <SkEvent.h>
#include <gl/GrGLInterface.h>
#include <SkApplication.h>
#include <SkGradientShader.h>
#include <SkGraphics.h>
#include <SkGr.h>
#include <SkSurface.h>

#include "NodeSkiaTree.h"

class NodeOSWindow : public SkOSWindow {

  public:

    static NodeOSWindow *GetInstance();

    ~NodeOSWindow();

    void tearDownBackend();
    bool setUpBackend();
    void setUpRenderTarget();

    void draw(SkCanvas* canvas);

    void SetCallback(v8::Local<v8::Function> callback);
    void CallJSCallback();

    void start();
    void stop();

    void drawTree(v8::Local<v8::Object> obj);

  protected:

    SkSurface* createSurface() override;

  private:

    NodeOSWindow(void* hwnd);
    void renderTree(SkCanvas *canvas);

    static NodeOSWindow *instance_;

    GrContext* context_;
    GrRenderTarget* render_target_;
    AttachmentInfo attachment_info_;
    const GrGLInterface* interface_;

    NodeSkiaTree tree_;

    Nan::Callback callback_;
    bool has_callback_;

    uv_async_t async_;
    uv_cond_t cond_;
    uv_mutex_t mutex_;

    typedef SkOSWindow INHERITED;
};

#endif /* !NODEOSWINDOW.H */

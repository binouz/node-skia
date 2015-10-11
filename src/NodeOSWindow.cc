#include "NodeOSWindow.h"

#include <unistd.h>
#include <iostream>

class MainLoop : public Nan::AsyncWorker {
  public :

    MainLoop(Nan::Callback *cb, NodeOSWindow *window)
      : AsyncWorker(cb), window_(window) {}
    ~MainLoop() {}

    void Execute() {
      SkGraphics::Init();
      SkEvent::Init();
      window_->setUpBackend();
      window_->loop();
    }

  private:
    NodeOSWindow *window_;
};

static void trampolined_draw(uv_async_t* handle, int)
{
  NodeOSWindow::GetInstance()->CallJSCallback();
}

NodeOSWindow *NodeOSWindow::instance_ = NULL;

NodeOSWindow *NodeOSWindow::GetInstance()
{
  if (!NodeOSWindow::instance_)
    NodeOSWindow::instance_ = new NodeOSWindow(NULL);
  return NodeOSWindow::instance_;
}

NodeOSWindow::NodeOSWindow(void* hwnd)
  : INHERITED(hwnd)
{
  render_target_ = NULL;
  has_callback_ = false;
  uv_cond_init(&cond_);
  uv_mutex_init(&mutex_);
  uv_async_init(uv_default_loop(), &async_, &trampolined_draw);
}

NodeOSWindow::~NodeOSWindow()
{
  this->tearDownBackend();
}

SkSurface* NodeOSWindow::createSurface() {
  SkSurfaceProps props(INHERITED::getSurfaceProps());
  return SkSurface::NewRenderTargetDirect(render_target_, &props);
}

void NodeOSWindow::tearDownBackend()
{
  SkSafeUnref(context_);
  context_ = NULL;

  SkSafeUnref(interface_);
  interface_ = NULL;

  SkSafeUnref(render_target_);
  render_target_ = NULL;

  INHERITED::detach();
}

bool NodeOSWindow::setUpBackend()
{
  this->setColorType(kRGBA_8888_SkColorType);
  this->setVisibleP(true);
  this->setClipToBounds(false);

  if (!attach(kNativeGL_BackEndType, 0, &attachment_info_))
  {
    detach();
    return false;
  }

  interface_ = GrGLCreateNativeInterface();
  context_ = GrContext::Create(kOpenGL_GrBackend, (GrBackendContext)interface_);

  this->setUpRenderTarget();

  return true;
}

void NodeOSWindow::setUpRenderTarget()
{
  SkSafeUnref(render_target_);
  render_target_ = this->renderTarget(attachment_info_, interface_, context_);
};

void NodeOSWindow::CallJSCallback()
{
  Nan::HandleScope scope;
  callback_.Call(0, NULL);
  usleep(1000);
  uv_cond_signal(&cond_);
}

void NodeOSWindow::draw(SkCanvas* canvas)
{
  if (has_callback_)
  {
    uv_async_send(&async_);
    uv_cond_wait(&cond_, &mutex_);
    renderTree(canvas);
    context_->flush();
    this->inval(NULL);
    INHERITED::present();
  }
}

void NodeOSWindow::drawTree(v8::Local<v8::Object> obj)
{
  tree_.parse(obj);
}

void NodeOSWindow::renderTree(SkCanvas *canvas)
{
  tree_.render(canvas);
}

void NodeOSWindow::SetCallback(v8::Local<v8::Function> callback)
{
  has_callback_ = true;
  callback_.SetFunction(callback);
}

void NodeOSWindow::start()
{
  Nan::AsyncQueueWorker(new MainLoop(NULL, this));
}

void NodeOSWindow::stop()
{
}

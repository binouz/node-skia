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

#include "EGLNativeInterfaceX11.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>

EGLNativeInterface *EGLNativeInterface::CreateInterface(int width, int height, EGLNativeInterface::EventClient *client) {
  return new EGLNativeInterfaceX11(width, height, client);
}

EGLNativeInterfaceX11::~EGLNativeInterfaceX11() {
  if (display_) {
    XDestroyWindow(display_, window_);
    XCloseDisplay(display_);
  }
}

EGLNativeInterfaceX11::EGLNativeInterfaceX11(int width, int height, EGLNativeInterface::EventClient* client)
  : EGLNativeInterface(width, height),
    display_(NULL),
    client_(client) {}

EGLDisplay EGLNativeInterfaceX11::GetDisplay() {
  display_ = XOpenDisplay(NULL);

  if (!display_)
    return EGL_NO_DISPLAY;

  return eglGetDisplay(display_);
}

EGLSurface EGLNativeInterfaceX11::CreateWindowSurface(EGLDisplay display, EGLConfig config) {
  EGLSurface res;
  EGLint vid;
  XVisualInfo *visInfo, visTemplate;
  XSetWindowAttributes attr;
  unsigned long mask;
  int num_visuals;
  int scrnum = DefaultScreen(display_);
  Window root = RootWindow(display_, scrnum);

  if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &vid))
    return EGL_NO_SURFACE;

  visTemplate.visualid = vid;
  visInfo = XGetVisualInfo(display_, VisualIDMask, &visTemplate, &num_visuals);

  if (!visInfo)
    return EGL_NO_SURFACE;

  attr.background_pixel = 0;
  attr.border_pixel = 0;

  attr.colormap = XCreateColormap(display_, root, visInfo->visual, AllocNone);
  attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask;
  mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

  window_ = XCreateWindow(display_, root, 0, 0, width(), height(),
                          0, visInfo->depth, InputOutput,
                          visInfo->visual, mask, &attr);

  res = eglCreateWindowSurface(display, config, window_, NULL);

  XFree(visInfo);

  XMapWindow(display_, window_);

  return res;
}

void EGLNativeInterfaceX11::SetupEvents() {
  XSelectInput(display_, window_, KeyPressMask|ButtonPressMask);

  WM_DELETE_WINDOW_ = XInternAtom(display_, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(display_, window_, &WM_DELETE_WINDOW_, 1);
}

void EGLNativeInterfaceX11::ProcessEvents() {
  XEvent event;

  if (!client_)
    return;

  while (XPending(display_) > 0) {
    XNextEvent(display_, &event);

    if (event.type == ClientMessage) {
      if (((Atom)event.xclient.data.l[0]) == WM_DELETE_WINDOW_) {
        client_->EmitEvent(new EGLNativeInterface::CloseEvent());
      }
    } else if (event.type == KeyPress) {
      client_->EmitEvent(new EGLNativeInterface::KeyEvent(event.xkey.keycode));
    } else if (event.type == ButtonPress) {
      client_->EmitEvent(
        new EGLNativeInterface::ClickEvent(event.xbutton.x, event.xbutton.y));
    }
  }
}

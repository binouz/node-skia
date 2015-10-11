/*
 * Copyright 2006 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkOSWindow_egl_DEFINED
#define SkOSWindow_egl_DEFINED

#include <EGL/egl.h>
#include <EGL/fbdev_window.h>

#include "SkWindow.h"

class SkEvent;

struct SkEGLWindow {
  EGLDisplay fDisplay;
  EGLSurface fSurface;
  EGLContext fContext;
  EGLConfig fConfig;
  fbdev_window fNative;
};

class SkOSWindow : public SkWindow {
public:
    SkOSWindow(void*);
    ~SkOSWindow();

    virtual void loop();

    enum SkBackEndTypes {
        kNone_BackEndType,
        kNativeGL_BackEndType,
#if SK_ANGLE
        kANGLE_BackEndType,
#endif // SK_ANGLE
#if SK_COMMAND_BUFFER
        kCommandBuffer_BackEndType,
#endif // SK_COMMAND_BUFFER
    };

    bool attach(SkBackEndTypes attachType, int msaaSampleCount, AttachmentInfo*);
    void detach();
    void present();

    bool makeFullscreen();
    void setVsync(bool);
    void closeWindow();

protected:

private:

    SkEGLWindow fWindow;

    typedef SkWindow INHERITED;
};

#endif

#include "EGLNativeInterfaceFbdev.h"

EGLNativeInterface *EGLNativeInterface::CreateInterface(int width, int height, EGLNativeInterface::EventClient *client) {
  return new EGLNativeInterfaceFbdev(width, height, client);
}

EGLNativeInterfaceFbdev::EGLNativeInterfaceFbdev(int width, int height, EGLNativeInterface::EventClient* client)
  : EGLNativeInterface(width, height),
    client_(client) {
  native_.width = width;
  native_.height = height;
}

EGLNativeInterfaceFbdev::~EGLNativeInterfaceFbdev() override {
}

EGLDisplay EGLNativeInterfaceFbdev::GetDisplay() {
  return eglGetDisplay(EGL_DEFAULT_DISPLAY);
}

EGLSurface EGLNativeInterfaceFbdev::CreateWindowSurface(EGLDisplay display, EGLConfig config) {
  return eglCreateWindowSurface(display, config, &native_, NULL);
}

void EGLNativeInterfaceFbdev::SetupEvents() {
}

void EGLNativeInterfaceFbdev::ProcessEvents() {
  // TODO : evdev
}

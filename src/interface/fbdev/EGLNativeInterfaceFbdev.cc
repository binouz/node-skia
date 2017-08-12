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

#include "EGLNativeInterfaceFbdev.h"

#error "Not implemented yet !"

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

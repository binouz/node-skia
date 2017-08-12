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

#ifndef EGLNATIVEINTERFACEFBDEV_H_
# define EGLNATIVEINTERFACEFBDEV_H_

#include <EGL/fbdev_window.h>

#include "../EGLNativeInterface.h"

class EGLNativeInterfaceFbdev : public EGLNativeInterface {

  protected:

    EGLDisplay GetDisplay();
    EGLSurface CreateWindowSurface(EGLDisplay display, EGLConfig config);

    void SetupEvents();
    void ProcessEvents();

    ~EGLNativeInterfaceFbdev() override;

  private:

    EGLNativeInterfaceFbdev(int width, int height, EGLNativeInterface::EventClient* client);

    fbdev_window native_;

    friend EGLNativeInterface;
};


#endif /* !EGLNATIVEINTERFACEFBDEV.H */

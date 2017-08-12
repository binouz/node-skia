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

#ifndef EGLNATIVEINTERFACEX11_H_
# define EGLNATIVEINTERFACEX11_H_

#include "../EGLNativeInterface.h"

class EGLNativeInterfaceX11 : public EGLNativeInterface {

  public:

  protected:

    EGLDisplay GetDisplay() override;
    EGLSurface CreateWindowSurface(EGLDisplay display, EGLConfig config) override;

    void SetupEvents() override;
    void ProcessEvents() override;

    ~EGLNativeInterfaceX11() override;

  private:

    EGLNativeInterfaceX11(int width, int height, EGLNativeInterface::EventClient* client);

    Display *display_;
    Window window_;
    Atom WM_DELETE_WINDOW_;

    EGLNativeInterface::EventClient* client_;

    friend EGLNativeInterface;
};

#endif /* !EGLNATIVEINTERFACEX11.H */

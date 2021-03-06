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

var Skia = require("../build/Release/skia");

var Window = Skia.Window;
var win = new Window(1280, 720);

win.setDrawHandler(function(canvas) {
    canvas.drawColor(0xFFFFFFFF);
    canvas.drawText(0xFF000000, 100, 100, "Hello World !");
});

win.start();
win.on("close", function() {
    win.stop();
    win.release();
});

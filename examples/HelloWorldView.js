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
var View = Skia.View;
var Node = Skia.ViewNode;

var win = new Window(1280, 720);
var view = new View(0xFFFFFFFF);
var root = new Node();
var header = new Node();
var body = new Node();
var footer = new Node();

header.text = "header";
header.style = {
    color : 0xFF000000,
    fontSize : 30,
    width : 1280,
    height : 200,
    marginTop : 10,
    marginLeft : 10,
    marginRight : 10,
    marginBottom : 10,
    border : 2
};
body.text = "body";
body.style = {
    color : 0xFF000000,
    fontSize : 30,
    width : 1280,
    height : 320,
    top : 200,
    marginTop : 10,
    marginLeft : 10,
    marginRight : 10,
    marginBottom : 10
};
footer.text = "footer";
footer.style = {
    color : 0xFF000000,
    fontSize : 30,
    width : 1280,
    height : 200,
    top : 520,
    marginTop : 10,
    marginLeft : 10,
    marginRight : 10,
    marginBottom : 10,
    border : 2
};

root.text = "ROOT";
root.style = {
    backgroundColor: 0x6600FF00,
    width : 1280,
    height : 720
};
root.children = [ header, body, footer ];

view.setRoot(root);

win.setView(view);
win.start();
win.on("close", function() {
    win.stop();
    win.release();
});

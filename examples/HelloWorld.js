var Skia = require("../build/Release/skia");

var Window = Skia.Window;
var View = Skia.View;

var view = new View(0xFFFFFFFF);
var win = new Window(1280, 720);
win.setView(view);
win.start();
view.update({
    style : {
        color : 0xFF000000,
        x: 100,
        y: 100,
        fontSize : 30
    },
    children : [],
    content: "Hello World !"
});
// window.stop();
// window.release();

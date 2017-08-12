var Skia = require("../build/Release/skia");

var Window = Skia.Window;
var paint = new Skia.Canvas.Paint({
});

var win = new Window(1280, 720);

win.setDrawHandler(function(canvas) {
    canvas.
});

win.start();
win.on("close", function() {
    win.stop();
    win.release();
});

var Skia = require("../build/Release/skia");

var window = new Skia.Window(1280, 720);
window.initialise();
window.setDrawHandler(function(canvas) {
    canvas.drawRect(0xFFFFFFFF, 10, 10, 500, 500);
});
window.start();
// window.stop();
// window.release();

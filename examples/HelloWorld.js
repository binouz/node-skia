var Skia = require("../build/Release/skia");

var window = new Skia.Window(1280, 720);
window.initialise();
window.setDrawHandler(function(canvas) {
    canvas.drawColor(0xFF000000);
    canvas.drawRect(0xFFFFFFFF, 10, 10, 500, 500);
    canvas.drawPoint(0xFF0000FF, 500, 500);
    canvas.drawLine(0xFFFF0000, 10, 200, 800, 200);
    canvas.drawText(0xFF00FF00, 600, 600, "Hello World !");
});
window.start();
// window.stop();
// window.release();

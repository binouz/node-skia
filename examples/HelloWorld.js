var Skia = require("../build/Release/skia");
var x = 0;
var window = new Skia.Window(1280, 720);
window.setDrawHandler(function(canvas) {
    canvas.drawColor(0xFF000000);
    canvas.drawText(0xFFFFFFFF, x, 200, "Hello World !");
    x = (x + 10) % (1280 - 50);
});
window.start();
// window.stop();
// window.release();

setTimeout(function() {
    console.log("Stop !")
    window.stop();
    window.release();
}, 10000);

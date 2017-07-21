var Skia = require("../build/Release/skia");

var Window = Skia.Window;
var View = Skia.View;

var view = new View(0xFFFFFFFF);
var win = new Window(1280, 720);

var content = { style : {}, content : "", children : [] };
var latest;

function createElement() {
    return {
        style : {
            color : 0xFF000000,
            x: 0,
            y: 0,
            fontSize : 30
        },
        content: "Hello World !",
        children : []
    }
}

win.setView(view);
win.start();

view.update(content);

win.on("close", function() {
    console.log("CLOSE");
    win.stop();
    win.release();
});

win.on("key", function(data) {
    console.log("KEY :", data);

    if (latest) {
        if (data.keycode == 114) {
            latest.style.x += 10;
        } else if (data.keycode == 113) {
            latest.style.x -= 10;
        } else if (data.keycode == 111) {
            latest.style.y -= 10;
        } else if (data.keycode == 116) {
            latest.style.y += 10;
        }
    }

    console.log(content);

    view.update(content);
});

win.on("click", function(data) {
    console.log("CLICK :", data);

    var elm = createElement();

    elm.style.x = data.x;
    elm.style.y = data.y;

    latest = elm;

    content.children.push(elm);
    view.update(content);
});

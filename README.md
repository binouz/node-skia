# node-skia

This node module allows you to draw with skia on a native EGL window.

## Build

### Linux


```shell
# make
```

## API

- Spawn a native EGL window to draw on

```javascript
var skia = require("skia");
var Window = skia.Window;

var win = new Window(1280, 720);
win.start();
win.stop();
win.release();
```

- Draw at each frame directly on canvas :

```javascript
var skia = require("skia");
var Window = skia.Window;

var win = new Window(1280, 720);
win.setDrawHandler(function(canvas) {
    canvas.drawColor(0xFFFFFFFF);
    canvas.drawText(0xFF000000, 100, 100, "Hello World !");
});
win.start();
win.stop();
win.release();
```

- Use asynchronous view system :

```javascript
var skia = require("skia");
var Window = skia.Window;
var View = skia.View;

var View = new View(0xFFFFFFFF);
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
win.stop();
win.release();
```

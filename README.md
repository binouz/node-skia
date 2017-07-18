# node-skia

This node module allows you to draw with skia on a native window.

## Build

### Linux


Prerequisites : npm, node and node-gyp installed

```shell
# npm install
# ./configure.sh --platform=$PLATFORM
# ./build.sh
```

$PLATFORM can have the following values :
- egl : Cross compile for arm and egl
- sdl : Host build with SDL

## API

For now, it looks like this :

```javascript
var skia = require("skia");

skia.Start(function () {
  skia.Draw({
    background : 0xFFFFFFFF,
    children : [
      {
        type : "rectangle",
        x : 10,
        y : 10,
        width : 100,
        height : 100,
        color : 0xFFFF0000
      },
      {
        type : "rectangle",
        x : 200,
        y : 200,
        width : 150,
        height : 150,
        color : 0xFF00FF00,
        children : [
          {
            type : "rectangle",
            x : 225,
            y : 225,
            width : 100,
            height : 100,
            color : 0xFF0000FF
          },
        ]
      }
    ]
  });
});
```

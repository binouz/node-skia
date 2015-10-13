# node-skia

This node module allows you to draw with skia on a native window.

## Buils

### Linux

Install node/npm and build skia following [this tutorial](https://skia.org/user/quick/linux).
At step 4, when building, use these commands :
```shell
/home/user/skia/# GYP_DEFINES="skia_shared_lib=1" bin/sync-and-gyp && ninja -C out/Debug
/home/user/skia/# mkdir ../node-skia/deps/skia/libs ../node-skia/deps/skia/include
/home/user/skia/# cp -r include/* ../node-skia/deps/skia/include
/home/user/skia/# cp out/Debug/lib/libskia.so out/Debug/libskia_views.a ../node-skia/deps/skia/libs
/home/user/skia/# cd ../node-skia
/home/user/node-skia# npm install
```

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

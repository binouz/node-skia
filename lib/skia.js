var skia = require('../build/Debug/skia');

var COLORS = {
  BLACK : 0xFF000000,
  WHITE : 0xFFFFFFFF,
  RED : 0xFFFF0000,
  GREEN : 0xFF00FF00,
  BLUE : 0xFF0000FF,
  rgba : function (r, g, b, a) {
    return ((a & 0xFF) << 24) +
      ((r & 0xFF) << 16) +
      ((g & 0xFF) << 8) +
      (b & 0xFF);
  },
  rgb : function (r, g, b) {
    return 0xFF000000 +
      ((r & 0xFF) << 16) +
      ((g & 0xFF) << 8) +
      (b & 0xFF);
  }
};

var TYPES = {
  POINT : "point",
  LINE : "line",
  RECTANGLE : "rectangle",
  OVAL : "oval",
  CIRCLE : "circle",
  ARC : "arc",
  ROUND_RECTANGLE : "round-rectangle",
  // PATH : "path",
  // IMAGE : "image",
  TEXT : "text",
};

/*var TRANSFORMS = {
  TRANSLATE,
  SCALE,
  ROTATE,
  SKEW,
  CONCAT,
  MATRIX
};*/

module.exports = {
  color : COLORS,
  type : TYPES,
  //transform : TRANSFORMS,
  Draw : skia.Draw,
  Start : skia.Start,
  Stop : skia.Stop
};

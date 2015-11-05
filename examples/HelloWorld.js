var skia = require('../lib/skia');
var cssLayout = require("css-layout");

var tree = {
  style : {
    width : 500,
    height : 500
  },
  color : skia.color.WHITE,
  children : [
    {
      type : skia.type.RECTANGLE,
      color : skia.color.RED,
      style : {
        padding : 20,
        flex: 1,
      },
      children : [
        {
          type : skia.type.OVAL,
          color : skia.color.GREEN,
          style : {
            flex: 1,
          },
          children : [
          ]
        },
        {
          type : skia.type.RECTANGLE,
          color : skia.color.BLUE,
          style : {
            flex: 1,
            padding : 50,
          },
          children : [
            {
              type : skia.type.TEXT,
              color : skia.color.BLACK,
              text : "Hi boy !",
              style : {
              }
            },
            {
              type : skia.type.CIRCLE,
              color : skia.color.WHITE,
              style : {
                flex: 1,
              },
              children : [
              ]
            },
          ]
        }
      ]
    }
  ]
}

cssLayout(tree);

console.log(JSON.stringify(tree, null, 4));

skia.Start(function() {
  skia.Draw(tree);
});

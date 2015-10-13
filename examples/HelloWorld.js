var skia = require('../build/Debug/skia');
var cssLayout = require("css-layout");

var tree = {
    children : [
        {
            type : "rectangle",
            color : 0xFFFF0000,
            style : {
                width : 100,
                padding : 20,
            },
            children : [
                {
                    type : "rectangle",
                    color : 0xFF00FF00,
                    style : {
                        width : 100,
                        padding : 30,
                    },
                    children : [
                        {
                            type : "rectangle",
                            color : 0xFF0000FF,
                            style : {
                                width : 100,
                            }
                        }
                    ]
                }
            ]
        }
    ],
    style : {
        padding : 10,
        width : 500,
        height : 500
    },
    color : 0xFFFFFFFF
}

cssLayout(tree);

console.log(JSON.stringify(tree, null, 4));

skia.Start(function() {
    skia.Draw(tree);
});

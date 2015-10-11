var skia = require('../build/Debug/skia');

var elm1 = {
    type : "rectangle",
    x : 225,
    y : 225,
    width : 100,
    height : 100,
    color : 0xFF0000FF,
    rotate : true,
    angle  : 0
};

var elm2 = {
    type : "rectangle",
    x : 200,
    y : 200,
    width : 150,
    height : 150,
    color : 0xFF00FF00,
    rotate : true,
    angle : 0,
    children : [
        elm1
    ]
};

var tree = {
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
            elm2
        ]
    }

skia.Start(function() {
    elm1.angle += 0.2;
    elm2.angle -= 0.2;
    skia.Draw(tree);

});

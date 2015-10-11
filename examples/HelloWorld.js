var skia = require('../build/Debug/skia');

skia.Start(function() {

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

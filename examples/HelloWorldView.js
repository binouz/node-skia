var Skia = require("../build/Release/skia");

var Window = Skia.Window;
var View = Skia.View;
var Node = Skia.ViewNode;

var win = new Window(1280, 720);
var view = new View(0xFFFFFFFF);
var root = new Node();
var header = new Node();
var body = new Node();
var footer = new Node();

header.text = "header";
header.style = {
    color : 0xFF000000,
    fontSize : 30,
    width : 1280,
    height : 200,
    marginTop : 10,
    marginLeft : 10,
    marginRight : 10,
    marginBottom : 10,
    border : 2
};
body.text = "body";
body.style = {
    color : 0xFF000000,
    fontSize : 30,
    width : 1280,
    height : 320,
    top : 200,
    marginTop : 10,
    marginLeft : 10,
    marginRight : 10,
    marginBottom : 10
};
footer.text = "footer";
footer.style = {
    color : 0xFF000000,
    fontSize : 30,
    width : 1280,
    height : 200,
    top : 520,
    marginTop : 10,
    marginLeft : 10,
    marginRight : 10,
    marginBottom : 10,
    border : 2
};

root.text = "ROOT";
root.style = {
    backgroundColor: 0x6600FF00,
    width : 1280,
    height : 720
};
root.children = [ header, body, footer ];

view.setRoot(root);

win.setView(view);
win.start();
win.on("close", function() {
    win.stop();
    win.release();
});

# QTMyPaint

QTMyPaint is an interface to help integrate the libmypaint brush engine library within your QT based applications. (The example's GUI is based on a demo application made by Sebastien Leon)

The main code of this interface is stored in the sub-folder "src"

This lib is at a very early stage and only implements very basic features. Please feel free to fork and modify this project.

License: GPL v3, see [LICENSE](./LICENSE) for details


Prerequisites
---------------

Build dependencies:
* [json-c](https://github.com/json-c/json-c/wiki) A copy of json-c is included in this project
* [libmypaint](https://github.com/mypaint/libmypaint) A copy of libmypaint is included in this project. It has been modified to be built in a C++ environment. It may not be the best approach. "libmypaint.c" has to be included so we can't use the headers of a pre-built version of the C lib.



Usage
---------

A global object is used for the communication with libmypaint

    MPHandler *mypaint = MPHandler::handler();

Set the size of your drawing surface :

    mypaint->setSurfaceSize(QSize(640, 480));

Set a brush color :

    mypaint->setBrushColor(QColor(0, 0, 0));

Draw a stroke :

    // Call this once on press event
    mypaint->startStroke();

    // Call this on each move event
    mypaint->strokeTo(x, y); // Basic call
    mypaint->strokeTo(x, y, pressure, xTilt,  yTilt); // Call with tablet handling


A signal/slot mecanism is used to handle stroke events :

* newTile(MPSurface*, MPTile*) is called when a tile is added to the surface (the brush is drawing on a blank area)
* updateTile(MPSurface*, MPTile*) is called when a tile is visually updated.

MPTile inherits from QGraphicsItem and can be used with a QGraphicsScene object.


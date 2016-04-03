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

**A global object is used for the communication with libmypaint**


    MPHandler *mypaint = MPHandler::handler();


**Set the size of your drawing surface :**

    QSize size = ...;
    mypaint->setSurfaceSize(size);


**Set a brush color :**

    QColor color = ...;
    mypaint->setBrushColor(color);


**Get and set a brush specific setting value :**

    float value = ...;
    mypaint->setBrushValue(MYPAINT_BRUSH_SETTING_RADIUS_LOGARITHMIC, value);

    value = mypaint->getBrushValue(MYPAINT_BRUSH_SETTING_RADIUS_LOGARITHMIC)

_Note that the setting type is defined by libmypaint's MyPaintBrushSetting enum._


**Draw a stroke :**

    // Call this once on press event
    mypaint->startStroke();

    // Call this on each move event
    mypaint->strokeTo(x, y); // Basic call
    mypaint->strokeTo(x, y, pressure, xTilt,  yTilt); // Call with tablet handling

A signal/slot mecanism is used to handle stroke events :

* newTile(MPSurface*, MPTile*) is called when a tile is added to the surface (the brush is drawing on a blank area)
* updateTile(MPSurface*, MPTile*) is called when a tile is visually updated.

MPTile inherits from QGraphicsItem and should be added to a QGraphicsScene object on the newTile() event.


**Render the surface as an image :**

    QImage image = mypaint->renderImage();


**Clear the surface :**

    mypaint->clearSurface();

* clearedSurface(MPSurface*) is called when the surface has been cleared.

_Note that in order to optimize the output of the final UI, when a surface is cleared, all the MPtiles (QGraphicsItem) that represent this surface are automatically removed from their QGraphicsScene._
_You don't need to worry about that._


**Load the surface with an existing image :**

    QImage image = ...;
    mypaint->loadImage(image);

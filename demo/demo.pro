#-------------------------------------------------
#
# Project created by QtCreator 2015-04-02T23:12:23
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo 
TEMPLATE = app

SOURCES += \
    $$PWD/main.cpp\
    $$PWD/mainwindow.cpp \
    $$PWD/mypaintview.cpp \
    $$PWD/PuMPBrushes.cpp \
    demoapp.cpp

HEADERS  += \
    $$PWD/mainwindow.h \
    $$PWD/mypaintview.h \
    $$PWD/PuMPBrushes.h \
    demoapp.h

FORMS    += \
    $$PWD/mainwindow.ui


# --- libjson ---

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../json-c/release/ -ljson-c
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../json-c/debug/ -ljson-c
else:unix: LIBS += -L$$OUT_PWD/../json-c/ -ljson-c

INCLUDEPATH += $$PWD/../json-c
DEPENDPATH += $$PWD/../json-c

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../json-c/release/libjson-c.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../json-c/debug/libjson-c.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../json-c/release/json-c.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../json-c/debug/json-c.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../json-c/libjson-c.a


# --- liblibmypaint ---

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libmypaint/release/ -llibmypaint
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libmypaint/debug/ -llibmypaint
else:unix: LIBS += -L$$OUT_PWD/../libmypaint/ -llibmypaint

INCLUDEPATH += $$PWD/../libmypaint
DEPENDPATH += $$PWD/../libmypaint

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libmypaint/release/liblibmypaint.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libmypaint/debug/liblibmypaint.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libmypaint/release/libmypaint.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../libmypaint/debug/libmypaint.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../libmypaint/liblibmypaint.a

# --- QTMyPaint ---

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/release/ -lQTMyPaint
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug/ -lQTMyPaint
else:unix: LIBS += -L$$OUT_PWD/../src/ -lQTMyPaint

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/release/libQTMyPaint.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/debug/libQTMyPaint.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/release/QTMyPaint.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/debug/QTMyPaint.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/libQTMyPaint.a

RESOURCES += resources.qrc



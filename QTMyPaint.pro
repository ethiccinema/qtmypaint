#-------------------------------------------------
#
# Project created by QtCreator 2015-04-09T11:14:52
#
#-------------------------------------------------

win32:OS=win32
unix:mac:OS=macosx
unix:!mac:OS=linux

TEMPLATE = app

TARGET = demo

DEPENDPATH   += .
INCLUDEPATH  += demo json-c libmypaint src

CONFIG       += qt
QT           += core gui widgets


SOURCES = \
    demo/main.cpp\
    demo/mainwindow.cpp \
    demo/mypaintview.cpp \
    demo/demoapp.cpp \
    demo//mpbrushselector.cpp \
    src/mpbrushlib.cpp

HEADERS  = \
    demo/mainwindow.h \
    demo/mypaintview.h \
    demo/demoapp.h \
    demo//mpbrushselector.h \
    src/mpbrushlib.h

FORMS    += \
    demo/mainwindow.ui

RESOURCES += \
    demo/resources.qrc


SOURCES += \
    json-c/arraylist.c \
    json-c/debug.c \
    json-c/json_c_version.c \
    json-c/json_object.c \
    json-c/json_object_iterator.c \
    json-c/json_tokener.c \
    json-c/json_util.c \
    json-c/libjson.c \
    json-c/linkhash.c \
    json-c/printbuf.c \
    json-c/random_seed.c

HEADERS += \
    json-c/arraylist.h \
    json-c/bits.h \
    json-c/debug.h \
    json-c/json.h \
    json-c/json_c_version.h \
    json-c/json_inttypes.h \
    json-c/json_object.h \
    json-c/json_object_iterator.h \
    json-c/json_object_private.h \
    json-c/json_tokener.h \
    json-c/json_util.h \
    json-c/linkhash.h \
    json-c/math_compat.h \
    json-c/printbuf.h \
    json-c/random_seed.h \
    json-c/config.h \
    json-c/json_config.h


SOURCES += \
    libmypaint/brushmodes.c \
    libmypaint/fifo.c \
    libmypaint/helpers.c \
    libmypaint/libmypaint.c \
    libmypaint/mapping.c \
    libmypaint/mypaint.c \
    libmypaint/mypaint-brush.c \
    libmypaint/mypaint-brush-settings.c \
    libmypaint/mypaint-fixed-tiled-surface.c \
    libmypaint/mypaint-rectangle.c \
    libmypaint/mypaint-surface.c \
    libmypaint/mypaint-tiled-surface.c \
    libmypaint/operationqueue.c \
    libmypaint/rng-double.c \
    libmypaint/tilemap.c \
    libmypaint/utils.c

HEADERS += \
    libmypaint/brushmodes.h \
    libmypaint/brushsettings-gen.h \
    libmypaint/fifo.h \
    libmypaint/helpers.h \
    libmypaint/mapping.h \
    libmypaint/mypaint.h \
    libmypaint/mypaint-brush.h \
    libmypaint/mypaint-brush-settings.h \
    libmypaint/mypaint-brush-settings-gen.h \
    libmypaint/mypaint-config.h \
    libmypaint/mypaint-config.h.in \
    libmypaint/mypaint-fixed-tiled-surface.h \
    libmypaint/mypaint-glib-compat.h \
    libmypaint/mypaint-rectangle.h \
    libmypaint/mypaint-surface.h \
    libmypaint/mypaint-tiled-surface.h \
    libmypaint/operationqueue.h \
    libmypaint/rng-double.h \
    libmypaint/tiled-surface-private.h \
    libmypaint/tilemap.h \
    libmypaint/utils.h


SOURCES += \
    src/mpbrush.cpp \
    src/mphandler.cpp \
    src/mpsurface.cpp \
    src/mptile.cpp


HEADERS += \
    src/mpbrush.h \
    src/mphandler.h \
    src/mpsurface.h \
    src/mptile.h

QMAKE_CFLAGS += -std=c99
QMAKE_CFLAGS += -D_XOPEN_SOURCE=600

unix: CONFIG += link_pkgconfig
#unix: PKGCONFIG += json-c

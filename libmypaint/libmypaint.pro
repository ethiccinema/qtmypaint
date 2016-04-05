QT += core gui widgets

TARGET = libmypaint
TEMPLATE = lib
CONFIG += staticlib

HEADERS += brushmodes.h \
           brushsettings-gen.h \
           fifo.h \
           helpers.h \
           mapping.h \
           mypaint.h \
           mypaint-brush.h \
           mypaint-brush-settings.h \
           mypaint-brush-settings-gen.h \
           mypaint-config.h \
           mypaint-config.h.in \
           mypaint-fixed-tiled-surface.h \
           mypaint-glib-compat.h \
           mypaint-rectangle.h \
           mypaint-surface.h \
           mypaint-tiled-surface.h \
           operationqueue.h \
           rng-double.h \
           tiled-surface-private.h \
           tilemap.h \
           utils.h

SOURCES += brushmodes.c \
           fifo.c \
           helpers.c \
           libmypaint.c \
           mapping.c \
           mypaint.c \
           mypaint-brush.c \
           mypaint-brush-settings.c \
           mypaint-fixed-tiled-surface.c \
           mypaint-rectangle.c \
           mypaint-surface.c \
           mypaint-tiled-surface.c \
           operationqueue.c \
           rng-double.c \
           tilemap.c \
           utils.c

INCLUDEPATH += ../json-c
LIBS += -L../json-c -ljson-c

# for C files, we need to allow C99 mode.
QMAKE_CFLAGS += -std=c99

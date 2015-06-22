#-------------------------------------------------
#
# Project created by QtCreator 2015-03-31T23:25:53
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = libmypaint
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    $$PWD/brushmodes.c \
    $$PWD/fifo.c \
    $$PWD/helpers.c \
    $$PWD/libmypaint.c \
    $$PWD/mapping.c \
    $$PWD/mypaint.c \
    $$PWD/mypaint-brush.c \
    $$PWD/mypaint-brush-settings.c \
    $$PWD/mypaint-fixed-tiled-surface.c \
    $$PWD/mypaint-rectangle.c \
    $$PWD/mypaint-surface.c \
    $$PWD/mypaint-tiled-surface.c \
    $$PWD/operationqueue.c \
    $$PWD/rng-double.c \
    $$PWD/tilemap.c \
    $$PWD/utils.c

HEADERS += \
    $$PWD/brushmodes.h \
    $$PWD/brushsettings-gen.h \
    $$PWD/fifo.h \
    $$PWD/helpers.h \
    $$PWD/mapping.h \
    $$PWD/mypaint.h \
    $$PWD/mypaint-brush.h \
    $$PWD/mypaint-brush-settings.h \
    $$PWD/mypaint-brush-settings-gen.h \
    $$PWD/mypaint-config.h \
    $$PWD/mypaint-config.h.in \
    $$PWD/mypaint-fixed-tiled-surface.h \
    $$PWD/mypaint-glib-compat.h \
    $$PWD/mypaint-rectangle.h \
    $$PWD/mypaint-surface.h \
    $$PWD/mypaint-tiled-surface.h \
    $$PWD/operationqueue.h \
    $$PWD/rng-double.h \
    $$PWD/tiled-surface-private.h \
    $$PWD/tilemap.h \
    $$PWD/utils.h

INCLUDEPATH += $$PWD

# for C files, we need to allow C99 mode.
#QMAKE_CFLAGS += -std=c99

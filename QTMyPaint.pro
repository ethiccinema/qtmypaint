#-------------------------------------------------
#
# Project created by QtCreator 2015-04-09T11:14:52
#
#-------------------------------------------------

TEMPLATE = subdirs


json-c.subdir = json-c

libmypaint.subdir = libmypaint
libmypaint.depends = json-c


SUBDIRS = json-c \
    libmypaint \
    QTMyPaint \
    Demo

#QT       += core gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = QTMyPaint
#TEMPLATE = app


#SOURCES += main.cpp\
#        mainwindow.cpp \
#    Example/mainwindow.cpp \
#    Example/mypaintview.cpp \
#    Example/PuMPBrushes.cpp \
#    QTMyPaint/mpbrush.cpp \
#    QTMyPaint/mphandler.cpp \
#    QTMyPaint/mpsurface.cpp \
#    QTMyPaint/mptile.cpp \
#    libmypaint/gegl/mypaint-gegl-surface.c \
#    libmypaint/glib/mypaint-brush.c \
#    libmypaint/glib/mypaint-gegl-glib.c \
#    libmypaint/json-c/tests/parse_flags.c \
#    libmypaint/json-c/tests/test1.c \
#    libmypaint/json-c/tests/test2.c \
#    libmypaint/json-c/tests/test4.c \
#    libmypaint/json-c/tests/test_cast.c \
#    libmypaint/json-c/tests/test_charcase.c \
#    libmypaint/json-c/tests/test_locale.c \
#    libmypaint/json-c/tests/test_null.c \
#    libmypaint/json-c/tests/test_parse.c \
#    libmypaint/json-c/tests/test_parse_int64.c \
#    libmypaint/json-c/tests/test_printbuf.c \
#    libmypaint/json-c/tests/test_set_serializer.c \
#    libmypaint/json-c/tests/testReplaceExisting.c \
#    libmypaint/json-c/arraylist.c \
#    libmypaint/json-c/debug.c \
#    libmypaint/json-c/json_c_version.c \
#    libmypaint/json-c/json_object.c \
#    libmypaint/json-c/json_object_iterator.c \
#    libmypaint/json-c/json_tokener.c \
#    libmypaint/json-c/json_util.c \
#    libmypaint/json-c/libjson.c \
#    libmypaint/json-c/linkhash.c \
#    libmypaint/json-c/printbuf.c \
#    libmypaint/json-c/random_seed.c \
#    libmypaint/brushmodes.c \
#    libmypaint/fifo.c \
#    libmypaint/helpers.c \
#    libmypaint/libmypaint.c \
#    libmypaint/mapping.c \
#    libmypaint/mypaint-brush-settings.c \
#    libmypaint/mypaint-brush.c \
#    libmypaint/mypaint-fixed-tiled-surface.c \
#    libmypaint/mypaint-rectangle.c \
#    libmypaint/mypaint-surface.c \
#    libmypaint/mypaint-tiled-surface.c \
#    libmypaint/mypaint.c \
#    libmypaint/operationqueue.c \
#    libmypaint/rng-double.c \
#    libmypaint/tilemap.c \
#    libmypaint/utils.c

#HEADERS  += mainwindow.h \
#    Example/mainwindow.h \
#    Example/mypaintview.h \
#    Example/PuMPBrushes.h \
#    libmypaint/gegl/mypaint-gegl-surface.h \
#    libmypaint/glib/mypaint-brush.h \
#    libmypaint/glib/mypaint-gegl-glib.h \
#    libmypaint/json-c/tests/parse_flags.h \
#    libmypaint/json-c/arraylist.h \
#    libmypaint/json-c/bits.h \
#    libmypaint/json-c/debug.h \
#    libmypaint/json-c/json.h \
#    libmypaint/json-c/json_c_version.h \
#    libmypaint/json-c/json_inttypes.h \
#    libmypaint/json-c/json_object.h \
#    libmypaint/json-c/json_object_iterator.h \
#    libmypaint/json-c/json_object_private.h \
#    libmypaint/json-c/json_tokener.h \
#    libmypaint/json-c/json_util.h \
#    libmypaint/json-c/linkhash.h \
#    libmypaint/json-c/math_compat.h \
#    libmypaint/json-c/printbuf.h \
#    libmypaint/json-c/random_seed.h \
#    libmypaint/brushmodes.h \
#    libmypaint/brushsettings-gen.h \
#    libmypaint/fifo.h \
#    libmypaint/helpers.h \
#    libmypaint/mapping.h \
#    libmypaint/mypaint-brush-settings-gen.h \
#    libmypaint/mypaint-brush-settings.h \
#    libmypaint/mypaint-brush.h \
#    libmypaint/mypaint-config.h \
#    libmypaint/mypaint-fixed-tiled-surface.h \
#    libmypaint/mypaint-glib-compat.h \
#    libmypaint/mypaint-rectangle.h \
#    libmypaint/mypaint-surface.h \
#    libmypaint/mypaint-tiled-surface.h \
#    libmypaint/mypaint.h \
#    libmypaint/operationqueue.h \
#    libmypaint/rng-double.h \
#    libmypaint/tiled-surface-private.h \
#    libmypaint/tilemap.h \
#    libmypaint/utils.h \
#    QTMyPaint/mpbrush.h \
#    QTMyPaint/mphandler.h \
#    QTMyPaint/mpsurface.h \
#    QTMyPaint/mptile.h

#FORMS    += mainwindow.ui

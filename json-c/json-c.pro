#-------------------------------------------------
#
# Project created by QtCreator 2015-03-31T21:52:35
#
#-------------------------------------------------

QT       -= gui

TARGET = json-c
TEMPLATE = lib
CONFIG += staticlib

SOURCES += $$PWD/arraylist.c \
    $$PWD/debug.c \
    $$PWD/json_c_version.c \
    $$PWD/json_object.c \
    $$PWD/json_object_iterator.c \
    $$PWD/json_tokener.c \
    $$PWD/json_util.c \
    $$PWD/libjson.c \
    $$PWD/linkhash.c \
    $$PWD/printbuf.c \
    $$PWD/random_seed.c

HEADERS += $$PWD/arraylist.h \
    $$PWD/bits.h \
    $$PWD/debug.h \
    $$PWD/json.h \
    $$PWD/json_c_version.h \
    $$PWD/json_inttypes.h \
    $$PWD/json_object.h \
    $$PWD/json_object_iterator.h \
    $$PWD/json_object_private.h \
    $$PWD/json_tokener.h \
    $$PWD/json_util.h \
    $$PWD/linkhash.h \
    $$PWD/math_compat.h \
    $$PWD/printbuf.h \
    $$PWD/random_seed.h \
    $$PWD/config.h \
    $$PWD/json_config.h
#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}

# for C files, we need to allow C99 mode.
QMAKE_CFLAGS += -std=c99
QMAKE_CFLAGS += -D_XOPEN_SOURCE=600

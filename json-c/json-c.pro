#-------------------------------------------------
#
# Project created by QtCreator 2015-03-31T21:52:35
#
#-------------------------------------------------

QT       -= gui

TARGET = json-c
TEMPLATE = lib
CONFIG += staticlib

SOURCES += arraylist.c \
    debug.c \
    json_c_version.c \
    json_object.c \
    json_object_iterator.c \
    json_tokener.c \
    json_util.c \
    libjson.c \
    linkhash.c \
    printbuf.c \
    random_seed.c

HEADERS += arraylist.h \
    bits.h \
    debug.h \
    json.h \
    json_c_version.h \
    json_inttypes.h \
    json_object.h \
    json_object_iterator.h \
    json_object_private.h \
    json_tokener.h \
    json_util.h \
    linkhash.h \
    math_compat.h \
    printbuf.h \
    random_seed.h \
    config.h \
    json_config.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}



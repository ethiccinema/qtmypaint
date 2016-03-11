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
          src \
          demo

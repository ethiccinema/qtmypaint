#-------------------------------------------------
#
# Project created by QtCreator 2015-03-31T23:25:53
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTMyPaint
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    $$PWD/mpbrush.cpp \
    $$PWD/mphandler.cpp \
    $$PWD/mpsurface.cpp \
    $$PWD/mptile.cpp \


HEADERS += \
    $$PWD/mpbrush.h \
    $$PWD/mphandler.h \
    $$PWD/mpsurface.h \
    $$PWD/mptile.h \

# --- json-c ---
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

# --- libmypaint ---
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

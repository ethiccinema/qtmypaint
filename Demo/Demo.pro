#-------------------------------------------------
#
# Project created by QtCreator 2015-04-02T23:12:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mypaint_test
TEMPLATE = app


SOURCES += \
    $$PWD/main.cpp\
    $$PWD/mainwindow.cpp \
    $$PWD/mypaintview.cpp \
    $$PWD/PuMPBrushes.cpp \


HEADERS  += \
    $$PWD/mainwindow.h \
    $$PWD/mypaintview.h \
    $$PWD/PuMPBrushes.h \

FORMS    += \
    $$PWD/mainwindow.ui






# --- QTMyPaint ---
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../QTMyPaint/release/ -lQTMyPaint
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../QTMyPaint/debug/ -lQTMyPaint
else:unix: LIBS += -L$$OUT_PWD/../QTMyPaint/ -lQTMyPaint

INCLUDEPATH += $$PWD/../QTMyPaint
DEPENDPATH += $$PWD/../QTMyPaint

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QTMyPaint/release/libQTMyPaint.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QTMyPaint/debug/libQTMyPaint.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QTMyPaint/release/QTMyPaint.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../QTMyPaint/debug/QTMyPaint.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../QTMyPaint/libQTMyPaint.a

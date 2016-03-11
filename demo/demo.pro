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

HEADERS  += \
    $$PWD/mainwindow.h \
    $$PWD/mypaintview.h \
    $$PWD/PuMPBrushes.h \

FORMS    += \
    $$PWD/mainwindow.ui

INCLUDEPATH += \
    $$PWD/../libmypaint

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

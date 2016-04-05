QT += core gui widgets
CONFIG += qt

TARGET = demo 
TEMPLATE = app

SOURCES = main.cpp \
          mainwindow.cpp \
          mypaintview.cpp \
          demoapp.cpp \
          mpbrushselector.cpp

HEADERS = mainwindow.h \
          mypaintview.h \
          demoapp.h \
          mpbrushselector.h

FORMS += mainwindow.ui

# --- QTMyPaint ---
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/release/ -lQTMyPaint
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/debug/ -lQTMyPaint
else:unix: LIBS += -L$$OUT_PWD/../src/ -lQTMyPaint

INCLUDEPATH += ../libmypaint
INCLUDEPATH += ../src
DEPENDPATH += ../src

LIBS += -L../json-c -ljson-c

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/release/libQTMyPaint.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/debug/libQTMyPaint.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/release/QTMyPaint.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/debug/QTMyPaint.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/libQTMyPaint.a

RESOURCES += resources.qrc

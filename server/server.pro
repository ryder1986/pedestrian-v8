QT += core
QT -= gui
QT += network
TARGET = server
CONFIG += console
CONFIG -= app_bundle
CONFIG += c++11
TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    serverinforeporter.cpp \
    camera.cpp

HEADERS += \
    server.h \
    common.h \
    serverinforeporter.h \
    videosrc.h \
    videohandler.h \
    camera.h \
    config.h \
    protocol.h
INCLUDEPATH+=/root/sources/opencv-2.4.9/build/__install/include
#LIBS += -L/root/sources/opencv-2.4.9/build/__install/lib  -lopencv_core  -lopencv_highgui  -lopencv_objdetect -lopencv_imgproc -lopencv_ml -lopencv_video
LIBS += -L/root/sources/opencv-2.4.9/build/__install/lib/  -lopencv_core  -lopencv_highgui  -lopencv_objdetect -lopencv_imgproc -lopencv_ml -lopencv_video
DEFINES+=SERVER
#LIBS += -L/root/sources/opencv-2-4-9-1/build/__install/lib/  -lopencv_core  -lopencv_highgui  -lopencv_objdetect -lopencv_imgproc -lopencv_ml -lopencv_video
#QMAKE_LFLAGS+="-Wl,--rpath=/root/sources/opencv-2-4-9-1/build/__install/lib/"
RESOURCES += \
    hog-res.qrc
QMAKE_LFLAGS+="-Wl,--rpath=/root/sources/opencv-2.4.9/build/__install/lib"
QMAKE_CFLAGS+="-w"

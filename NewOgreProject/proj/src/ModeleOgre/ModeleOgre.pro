#-------------------------------------------------
#
# Project created by QtCreator 2013-04-24T08:05:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ModeleOgre
TEMPLATE = app
unix {
    INCLUDEPATH += /usr/include/OGRE
    INCLUDEPATH += /usr/include/OIS
    CONFIG += link_pkgconfig
    PKGCONFIG += OGRE
    PKGCONFIG += OIS
}

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    Volume.cpp \
    Scene.cpp \
    Piece.cpp \
    OrbitCamera.cpp \
    LoaderXML.cpp \
    InputListener.cpp \
    GravityCenter.cpp \
    Fuselage.cpp \
    DisplayObject.cpp \
    Base.cpp \
    appwidget.cpp \
    TinyXML/tinyxml2.cpp

HEADERS  += mainwindow.h \
    Volume.h \
    Scene.h \
    OrbitCamera.h \
    LoaderXML.h \
    DisplayObject.h \
    ColourConstant.h \
    appwidget.h \
    Fuselage.h \
    GravityCenter.h \
    InputListener.h \
    Base.h \
    Piece.h \
    TinyXML/tinyxml2.h \
    TinyXML/FunctionXML.h

FORMS    += mainwindow.ui

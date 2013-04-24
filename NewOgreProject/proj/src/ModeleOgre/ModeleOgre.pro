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
    CONFIG += link_pkgconfig
    PKGCONFIG += OGRE
}


SOURCES += main.cpp\
        mainwindow.cpp \
    ogrewidget.cpp

HEADERS  += mainwindow.h \
    ogrewidget.h

FORMS    += mainwindow.ui

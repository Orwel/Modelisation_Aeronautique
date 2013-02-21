# -------------------------------------------------
# Project created by QtCreator 2009-11-13T05:18:26
# -------------------------------------------------
QT += svg
TARGET = recastOgre
TEMPLATE = app
unix { 
    # You may need to change this include directory
    INCLUDEPATH += /usr/include/OGRE
    CONFIG += link_pkgconfig
    PKGCONFIG += OGRE
}
win32 { 
    # You may need to change this include directory
    OGREHOME = C:\OgreSDK_mingw_v1-7-2
    LIBS += -L$$OGREHOME\boost_1_44\lib
    release:LIBS += -L$$OGREHOME\lib\release
    debug:LIBS += -L$$OGREHOME\lib\debug
    INCLUDEPATH += $$OGREHOME\include\OGRE
    INCLUDEPATH += $$OGREHOME\boost_1_44
}
CONFIG(debug, debug|release) { 
    TARGET = $$join(TARGET,,,d)
    LIBS *= -lOgreMain_d
}
CONFIG(release, debug|release):LIBS *= -lOgreMain
SOURCES += main.cpp \
    mainwindow.cpp \
    ogrewidget.cpp
HEADERS += mainwindow.h \
    ogrewidget.h
FORMS += mainwindow.ui

# -------------------------------------------------
# Project created by QtCreator 2009-11-13T05:18:26
# -------------------------------------------------
QT += svg
TARGET = recastOgre
TEMPLATE = app
unix {
    # You may need to change this include directory
    INCLUDEPATH += /usr/include/OGRE
    INCLUDEPATH += /usr/include/boost/typeof/std
    CONFIG += link_pkgconfig
    PKGCONFIG += OGRE 
}
win32 {
    # You may need to change this include directory
    OGREHOME = D:\ogrehead\sdk
    LIBS += -LC:\boost\boost_1_40\lib
    Release:LIBS += -L$$OGREHOME\lib\release
    Debug:LIBS += -L$$OGREHOME\lib\debug
    INCLUDEPATH += $$OGREHOME\include\OGRE
    INCLUDEPATH += C:\boost\boost_1_40

    CONFIG(debug, debug|release) {
        TARGET = $$join(TARGET,,,d)
        LIBS += -lOgreMain_d
    }
    CONFIG(release, debug|release):LIBS *= -lOgreMain
}

FORMS += mainwindow.ui \
    piecedialog.ui
SOURCES += main.cpp \
    mainwindow.cpp \
    ogrewidget.cpp \
    piecedialog.cpp \
    Base.cpp \
    Volume.cpp \
    Scene.cpp \
    Piece.cpp \
    OrbitCamera.cpp \
    LoaderXML.cpp \
    InputListener.cpp \
    GravityCenter.cpp \
    Fuselage.cpp \
    DisplayObject.cpp \
    appwidget.cpp \
    TinyXML/tinyxml2.cpp
HEADERS += mainwindow.h \
    ogrewidget.h \
    piecedialog.h \
    Base.h \
    Volume.h \
    Scene.h \
    Piece.h \
    OrbitCamera.h \
    LoaderXML.h \
    InputListener.h \
    GravityCenter.h \
    Fuselage.h \
    DisplayObject.h \
    ColourConstant.h \
    appwidget.h \
    TinyXML/tinyxml2.h \
    TinyXML/FunctionXML.h


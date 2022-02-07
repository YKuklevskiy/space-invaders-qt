QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alienmanager.cpp \
    alienship.cpp \
    bomb.cpp \
    collider.cpp \
    gamemanager.cpp \
    gameobject.cpp \
    gameui.cpp \
    linearprojectile.cpp \
    main.cpp \
    mainwindow.cpp \
    render.cpp \
    rocket.cpp \
    spaceship.cpp \
    textureholder.cpp \
    transform.cpp

HEADERS += \
    alienmanager.h \
    alienship.h \
    bomb.h \
    collider.h \
    gameconsts.h \
    gamemanager.h \
    gameobject.h \
    gameui.h \
    linearprojectile.h \
    mainwindow.h \
    render.h \
    rocket.h \
    spaceship.h \
    textureholder.h \
    transform.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    textures.qrc

DISTFILES +=

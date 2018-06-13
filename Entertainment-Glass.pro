#-------------------------------------------------
#
# Project created by QtCreator 2018-04-12T20:39:43
#
#-------------------------------------------------

QT       += core gui bluetooth multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Entertainment-Glass
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    reader.cpp \
    xoxframe.cpp \
    menuframe.cpp \
    serverui.cpp \
    devicesframe.cpp \
    connectframe.cpp \
    messageframe.cpp \
    xoxlogic.cpp \
    connect4logic.cpp \
    connect4frame.cpp \
    pingbossframe.cpp \
    pingbosslogic.cpp

HEADERS += \
    common.h \
    reader.h \
    xoxframe.h \
    menuframe.h \
    serverui.h \
    devicesframe.h \
    connectframe.h \
    messageframe.h \
    xoxlogic.h \
    connect4logic.h \
    connect4frame.h \
    pingbossframe.h \
    pingbosslogic.h

FORMS += \
    xoxframe.ui \
    menuframe.ui \
    serverui.ui \
    devicesframe.ui \
    connectframe.ui \
    messageframe.ui \
    frame.ui \
    xoxdummy.ui \
    c4dummy.ui \
    connect4frame.ui \
    pingbossframe.ui

RESOURCES += \
    images.qrc

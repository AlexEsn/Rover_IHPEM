QT       += core gui
QT       += bluetooth
QT       += widgets

TARGET = joypad
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        blt.cpp \
        main.cpp \
        mainwindow.cpp \
        joypad.cpp

HEADERS += \
        blt.h \
        mainwindow.h \
        joypad.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resource.qrc

#-------------------------------------------------
#
# Project created by QtCreator 2019-02-10T13:15:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MySimpleBackup
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
        mainwindow.cpp \
    textfunktionen.cpp \
    text_zeilenweise.cpp \
    quellen.cpp \
    dialog_seichern_laden.cpp \
    config.cpp \
    backup.cpp \
    ordner.cpp \
    umwandeln.cpp

HEADERS += \
        mainwindow.h \
    mydef.h \
    todo.h \
    textfunktionen.h \
    text_zeilenweise.h \
    quellen.h \
    dialog_seichern_laden.h \
    config.h \
    backup.h \
    ordner.h \
    umwandeln.h

FORMS += \
        mainwindow.ui \
    dialog_seichern_laden.ui \
    config.ui


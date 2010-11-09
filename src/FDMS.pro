# -------------------------------------------------
# Project created by QtCreator 2010-06-09T21:56:58
# -------------------------------------------------
QT += sql
TARGET = FDMS
TEMPLATE = app
UI_DIR = ../src/
SOURCES += sources/main.cpp \
    sources/databasemanager.cpp \
    sources/wndnewfirefighter.cpp \
    sources/mainwindow.cpp \
    sources/wndsetup.cpp \
    sources/wndactivedrill.cpp \
    sources/wndsplash.cpp \
    sources/firefighter.cpp \
    sources/wndsearch.cpp \
    sources/wndeditfirefighter.cpp
HEADERS += headers/databasemanager.h \
    headers/wndnewfirefighter.h \
    headers/mainwindow.h \
    headers/wndsetup.h \
    headers/wndactivedrill.h \
    headers/wndsplash.h \
    headers/LogFunctions.h \
    headers/firefighter.h \
    headers/wndsearch.h \
    headers/wndeditfirefighter.h
FORMS += forms/wndNewFirefighter.ui \
	forms/mainwindow.ui \
    forms/wndsetup.ui \
    forms/wndactivedrill.ui \
    forms/wndsplash.ui \
    forms/wndsearch.ui \
    forms/wndeditfirefighter.ui

RESOURCES += \
    resources/icons.qrc

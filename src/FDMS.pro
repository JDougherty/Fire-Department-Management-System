# -------------------------------------------------
# Project created by QtCreator 2010-06-09T21:56:58
# -------------------------------------------------
QT += sql
TARGET = FDMS
TEMPLATE = app
UI_DIR = ../src/
SOURCES += sources/main.cpp \
    sources/databasemanager.cpp \
    sources/wndfirefighter.cpp \
    sources/mainwindow.cpp \
    sources/wndsetup.cpp \
    sources/firefighter.cpp \
    sources/wndsearch.cpp \
    sources/wndeditfirefighter.cpp \
    sources/wndinventorycontrol.cpp \
    sources/wndinventorycheck.cpp \
    sources/wndactivedrill.cpp \
    sources/wndactivecall.cpp \
    sources/settingsmanager.cpp
HEADERS += headers/databasemanager.h \
    headers/wndfirefighter.h \
    headers/mainwindow.h \
    headers/wndsetup.h \
    headers/LogFunctions.h \
    headers/firefighter.h \
    headers/wndsearch.h \
    headers/wndeditfirefighter.h \
    headers/wndinventorycontrol.h \
    headers/wndinventorycheck.h \
    headers/wndactivedrill.h \
    headers/wndactivecall.h \
    headers/settingsmanager.h
FORMS += forms/wndfirefighter.ui \
	forms/mainwindow.ui \
    forms/wndsetup.ui \
    forms/wndsearch.ui \
    forms/wndeditfirefighter.ui \
    forms/wndinventorycontrol.ui \
    forms/wndinventorycheck.ui \
    forms/wndactivedrill.ui \
    forms/wndactivecall.ui

RESOURCES += \
    resources/resources.qrc

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
    sources/wndsplash.cpp \
    sources/firefighter.cpp \
    sources/wndsearch.cpp \
    sources/wndeditfirefighter.cpp \
    sources/wndinventorycontrol.cpp \
    sources/wndinventorycheck.cpp \
    sources/wndactivedrill.cpp \
    sources/wndactivecall.cpp
HEADERS += headers/databasemanager.h \
    headers/wndnewfirefighter.h \
    headers/mainwindow.h \
    headers/wndsetup.h \
    headers/wndsplash.h \
    headers/LogFunctions.h \
    headers/firefighter.h \
    headers/wndsearch.h \
    headers/wndeditfirefighter.h \
    headers/wndinventorycontrol.h \
    headers/wndinventorycheck.h \
    headers/wndactivedrill.h \
    headers/wndactivecall.h
FORMS += forms/wndNewFirefighter.ui \
	forms/mainwindow.ui \
    forms/wndsetup.ui \
    forms/wndsplash.ui \
    forms/wndsearch.ui \
    forms/wndeditfirefighter.ui \
    forms/wndinventorycontrol.ui \
    forms/wndinventorycheck.ui \
    forms/wndactivedrill.ui \
    forms/wndactivecall.ui

RESOURCES += \
    resources/resources.qrc

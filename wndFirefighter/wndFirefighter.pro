TEMPLATE = lib

UI_DIR = ui/

CONFIG += plugin

INCLUDEPATH += ../FDMS/headers

HEADERS = wndFirefighter.h \
    wndFirefighterPlugin.h

SOURCES = wndFirefighter.cpp \
    wndFirefighterPlugin.cpp

TARGET = $$qtLibraryTarget($$TARGET)

DESTDIR = ../plugins

FORMS += \
    wndfirefighter.ui

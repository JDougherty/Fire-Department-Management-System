TEMPLATE = lib

UI_DIR = ui/

CONFIG += plugin

INCLUDEPATH += ../../FDMS/headers

HEADERS = wndFirefighter.h \
    wndFirefighterPlugin.h

SOURCES = wndFirefighter.cpp \
    wndFirefighterPlugin.cpp

TARGET = $$qtLibraryTarget($$TARGET)

DESTDIR = ../

FORMS += \
    wndFirefighter.ui

RESOURCES += \
    resources.qrc

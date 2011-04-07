TEMPLATE = lib

UI_DIR = ui/

CONFIG += plugin

INCLUDEPATH += ../../FDMS/headers

HEADERS = wndCall.h \
    wndCallPlugin.h

SOURCES = wndCall.cpp \
    wndCallPlugin.cpp

TARGET = $$qtLibraryTarget($$TARGET)

DESTDIR = ../

FORMS += \
    wndCall.ui

RESOURCES += \
    resources.qrc

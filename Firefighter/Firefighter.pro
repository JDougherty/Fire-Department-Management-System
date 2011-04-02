TEMPLATE = lib

CONFIG += plugin

INCLUDEPATH += ../FDMS/headers

HEADERS = FirefighterPlugin.h

SOURCES = FirefighterPlugin.cpp

TARGET = $$qtLibraryTarget($$TARGET)

DESTDIR = ../plugins

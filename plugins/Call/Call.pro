TEMPLATE = lib

CONFIG += plugin

INCLUDEPATH += ../../FDMS/headers

HEADERS = CallPlugin.h

SOURCES = CallPlugin.cpp

TARGET = $$qtLibraryTarget($$TARGET)

DESTDIR = ../

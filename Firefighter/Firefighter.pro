TEMPLATE = lib

CONFIG += plugin

INCLUDEPATH += ../FDMS/headers

HEADERS = Firefighter.h

SOURCES = Firefighter.cpp

TARGET = $$qtLibraryTarget($$TARGET)

DESTDIR = ../plugins

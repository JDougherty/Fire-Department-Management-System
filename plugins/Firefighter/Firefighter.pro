QT += sql

TEMPLATE = lib

CONFIG += plugin

INCLUDEPATH += ../../FDMS/headers

HEADERS = FirefighterPlugin.h \
    Firefighter.h

SOURCES = FirefighterPlugin.cpp \
    Firefighter.cpp

TARGET = $$qtLibraryTarget($$TARGET)

DESTDIR = ../

QT += sql

TEMPLATE = lib

CONFIG += plugin

INCLUDEPATH += ../../FDMS/headers

HEADERS = CallPlugin.h \
    Call.h

SOURCES = CallPlugin.cpp \
    Call.cpp

TARGET = $$qtLibraryTarget($$TARGET)

DESTDIR = ../

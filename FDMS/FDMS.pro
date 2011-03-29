QT += sql
TARGET = FDMS
TEMPLATE = app
UI_DIR = ui/

INCLUDEPATH += headers

SOURCES += sources/main.cpp \
    sources/MainWindow.cpp \
    sources/managers/PluginManager.cpp \
    sources/managers/SettingManager.cpp \
    sources/wndSetup.cpp \
    sources/managers/DatabaseManager.cpp
	
HEADERS += headers/MainWindow.h \
    headers/MDIWindow.h \
    headers/plugins/MDIWindowPlugin.h \
    headers/plugins/DatabasePlugin.h \
    headers/managers/PluginManager.h \
    headers/managers/SettingManager.h \
    headers/wndSetup.h \
    headers/managers/DatabaseManager.h

FORMS += forms/MainWindow.ui \
    forms/wndSetup.ui

RESOURCES += \
    resources/resources.qrc

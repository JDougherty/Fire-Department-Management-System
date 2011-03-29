QT += sql
TARGET = FDMS
TEMPLATE = app
UI_DIR = ui/

INCLUDEPATH += headers

SOURCES += sources/main.cpp \
    sources/MainWindow.cpp \
    sources/managers/PluginManager.cpp \
    sources/managers/SettingManager.cpp
	
HEADERS += headers/MainWindow.h \
    headers/MDIWindow.h \
    headers/plugins/MDIWindowPlugin.h \
    headers/plugins/DatabasePlugin.h \
    headers/managers/PluginManager.h \
    headers/managers/SettingManager.h

FORMS += forms/MainWindow.ui \

RESOURCES += \
    resources/resources.qrc

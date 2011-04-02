#ifndef BASEPLUGIN_H
#define BASEPLUGIN_H

#include <QList>
#include <QPair>
#include <QString>

#include "plugins/DependencyList.h"
#include "plugins/PluginInfo.h"

class BasePlugin
{
    public:
        virtual                     ~BasePlugin( void ) {}

        virtual PluginInfo          getPluginInfo( void ) = 0;
        virtual DependencyList      getDependencies( void ) = 0;
};

Q_DECLARE_INTERFACE( BasePlugin, "com.FDS.Plugin.Base/1.0" );

#endif // BASEPLUGIN_H

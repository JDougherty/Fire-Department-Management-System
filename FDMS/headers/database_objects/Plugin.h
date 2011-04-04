#ifndef PLUGIN_H
#define PLUGIN_H

#include <QList>
#include <QObject>
#include <QPair>
#include <QSqlTableModel>

#include "managers/DatabaseManager.h"
#include "plugins/PluginInfo.h"

class Plugin
{
    public:
        static bool                 createTable( void );
        static bool                 save( PluginInfo pluginInfo, QString sHash );
        static bool                 load( QList<QPair<PluginInfo, QString> > &lInstalledPlugins );
};

#endif // PLUGIN_H

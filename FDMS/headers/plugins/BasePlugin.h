#ifndef BASEPLUGIN_H
#define BASEPLUGIN_H

#include <QList>
#include <QObject>
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

        bool dependenciesMet( QList<BasePlugin*> plugins )
        {
            bool bMet;

            foreach ( PluginInfo dependency, getDependencies() )
            {
                bMet = false;

                foreach ( BasePlugin *pPlugin, plugins )
                {
                    if ( pPlugin->getPluginInfo() == dependency )
                    {
                        bMet = true;
                        break;
                    }
                }

                if ( !bMet )
                {
                    qDebug( "%s", qPrintable( QObject::tr( "BasePlugin: Need " ) + getDependencies().toString() + "." ) );
                    qDebug( "%s", qPrintable( QObject::tr( "BasePlugin: Dependencies NOT met for " ) + getPluginInfo().toString() + "." ) );
                    return false;
                }

            }

            qDebug( "%s", qPrintable( QObject::tr( "BasePlugin: Dependencies met for " ) + getPluginInfo().toString() + "." ) );
            return true;
        }
};

Q_DECLARE_INTERFACE( BasePlugin, "com.FDS.Plugin.Base/1.0" );

#endif // BASEPLUGIN_H

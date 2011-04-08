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
    protected:
        QList<BasePlugin*>          _Dependencies;

    public:
        virtual                     ~BasePlugin( void ) {}

        virtual PluginInfo          getInfo( void ) = 0;
        virtual DependencyList      getDependencies( void ) = 0;

        bool loadDependencies( QList<BasePlugin*> plugins )
        {
             _Dependencies.clear();

            foreach ( PluginInfo dependency, getDependencies() )
            {
                bool bMet = false;

                foreach ( BasePlugin *pPlugin, plugins )
                {
                    if ( pPlugin->getInfo() == dependency )
                    {
                        _Dependencies.push_back( pPlugin );
                        bMet = true;
                        break;
                    }
                }

                if ( !bMet )
                {
                    _Dependencies.clear();
                    qDebug( "%s", qPrintable( QObject::tr( "BasePlugin: Need " ) + getDependencies().toString() + "." ) );
                    qDebug( "%s", qPrintable( QObject::tr( "BasePlugin: Could not load all dependencies for " ) + getInfo().toString() + "." ) );
                    return false;
                }

            }

            qDebug( "%s", qPrintable( QObject::tr( "BasePlugin: Dependencies met for " ) + getInfo().toString() + "." ) );
            return true;
        }
};

Q_DECLARE_INTERFACE( BasePlugin, "com.FDS.Plugin.Base/1.0" );

#endif // BASEPLUGIN_H

#ifndef DEPENDENCYLIST_H
#define DEPENDENCYLIST_H

#include <QList>
#include <QString>

#include "plugins/PluginInfo.h"

class DependencyList : public QList<PluginInfo>
{
    public:
        DependencyList( void )
        {

        }

        void add( const PluginInfo &d )
        {
            push_back( d );
        }

        QString toString( void ) const
        {
            QString s;

            for ( QList<PluginInfo>::const_iterator itr = begin(); itr != end(); itr++ )
                s += itr->toString() + ", ";

            s.chop( 2 );

            return s;
        }
};

#endif // DEPENDENCYLIST_H

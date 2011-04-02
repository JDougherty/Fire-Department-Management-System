#ifndef DEPENDENCYLIST_H
#define DEPENDENCYLIST_H

#include <QList>
#include <QString>

#include "plugins/PluginInfo.h"

class DependencyList : public QList<PluginInfo>
{
    public:

                                    DependencyList( void );

        void                        add( const PluginInfo &d );
        bool                        contains( const PluginInfo &otherInfo ) const;
        QString                     toString( void ) const;
};

#endif // DEPENDENCYLIST_H

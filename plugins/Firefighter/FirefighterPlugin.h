/*
    Fire Department Management System
    Copyright (C) 2010  Joseph W. Dougherty

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef FIREFIGHTERPLUGIN_H
#define FIREFIGHTERPLUGIN_H

#include <QObject>
#include <QtCore/QtPlugin>

#include "database_objects/DatabaseObject.h"
#include "plugins/DatabaseObjectPlugin.h"
#include "plugins/DependencyList.h"
#include "plugins/PluginInfo.h"

class FirefighterPlugin : public QObject, DatabaseObjectPlugin
{
    Q_OBJECT
    Q_INTERFACES( DatabaseObjectPlugin )

    public:
        PluginInfo                  getInfo( void );
        DependencyList              getDependencies( void );

        DatabaseObject *            getInstance( void );
        DatabaseObject *            getInstance( int iID );
};

#endif // FIREFIGHTERPLUGIN_H

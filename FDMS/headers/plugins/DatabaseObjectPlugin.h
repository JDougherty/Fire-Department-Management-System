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

#ifndef DATABASEOBJECTPLUGIN_H
#define DATABASEOBJECTPLUGIN_H

#include <QString>

#include "BasePlugin.h"
#include "database_objects/DatabaseObject.h"

class DatabaseObjectPlugin : public BasePlugin
{
    public:
        virtual                     ~DatabaseObjectPlugin( void ) {}

        virtual DatabaseObject *    getInstance( void ) = 0;
        virtual DatabaseObject *    getInstance( int iID ) = 0;

        virtual QString             echo( const QString &message ) = 0;
};

Q_DECLARE_INTERFACE( DatabaseObjectPlugin, "com.FDS.Plugin.DatabaseObject/1.0" );

#endif // DATABASEOBJECTPLUGIN_H

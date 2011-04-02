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

#ifndef DATABASEPLUGIN_H
#define DATABASEPLUGIN_H

#include <QString>

#include "BasePlugin.h"

class DatabasePlugin : public BasePlugin
{
    public:
        virtual                     ~DatabasePlugin( void ) {}

        virtual QString             echo( const QString &message ) = 0;
};

Q_DECLARE_INTERFACE( DatabasePlugin, "com.FDS.Plugin.Database/1.0" );

#endif // DATABASEPLUGIN_H

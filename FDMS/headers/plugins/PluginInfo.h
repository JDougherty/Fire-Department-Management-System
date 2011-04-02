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

#ifndef PLUGININFO_H
#define PLUGININFO_H

#include <QString>

class PluginInfo
{
    private:
        QString                     _sName, _sVersion;

    public:
                                    PluginInfo( QString sName, QString sVersion );

        QString                     getName( void ) const;
        QString                     getVersion( void ) const;
        QString                     toString( void ) const;
        bool                        operator==( const PluginInfo &other ) const;
};

#endif // PLUGININFO_H

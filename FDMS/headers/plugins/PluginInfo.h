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
        QString _sName, _sVersion;

    public:
        PluginInfo( void )
        {
            _sName = "invalid";
            _sVersion = "invalid";
        }

        PluginInfo( QString sName, QString sVersion )
        {
            _sName = sName;
            _sVersion = sVersion;
        }

        QString getName( void ) const
        {
            return _sName;
        }

        QString getVersion( void ) const
        {
            return _sVersion;
        }

        QString toString( void ) const
        {
            return _sName + " v" + _sVersion;
        }

        bool operator==( const PluginInfo &other ) const
        {
            return ( other._sName.compare( _sName ) == 0 && other._sVersion.compare( _sVersion ) == 0 );
        }
};

#endif // PLUGININFO_H

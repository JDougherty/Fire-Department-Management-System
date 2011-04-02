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

#include "plugins/DependencyList.h"

DependencyList::DependencyList( void )
{
}

void DependencyList::add( const PluginInfo &d )
{
    push_back( d );
}

bool DependencyList::contains( const PluginInfo &otherInfo ) const
{
    return contains( otherInfo );
}

QString DependencyList::toString( void ) const
{
    QString s;

    for ( QList<PluginInfo>::const_iterator itr = begin(); itr != end(); itr++ )
        s += itr->toString() + ", ";

    s.chop( 2 );

    return s;
}

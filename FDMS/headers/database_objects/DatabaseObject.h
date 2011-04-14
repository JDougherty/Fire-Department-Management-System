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

#ifndef DATABASEOBJECT_H
#define DATABASEOBJECT_H

class DatabaseObject
{
    protected:
        int                         _iID;
        QMap<QString, QVariant>     _Entry;

    public:
        virtual                     ~DatabaseObject( void ) {}

        int                         ID( void ) { return _iID; }

        virtual bool                createTable( void ) = 0;

        bool                        setValue( QString sItemName, QVariant vData ) { _Entry[sItemName] = vData; return true; }
        QMap<QString, QVariant>     getValues( void ) { return _Entry; }
        virtual bool                saveValues( void ) = 0;
        virtual bool                loadValues( void ) = 0;
};

#endif // DATABASEOBJECT_H

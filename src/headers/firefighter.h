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

#ifndef FIREFIGHTER_H
#define FIREFIGHTER_H

#include "databasemanager.h"
#include <QVector>

//! Allows for loading, adding, and updating a firefighter.
class Firefighter
{
    private:
        QVector<QString>        _attributes;

        int                     _iID;

    public:
                                Firefighter( void );
                                Firefighter( QVector<QString> attributes );

        bool                    InsertToDatabase( DatabaseManager *pDB );
        bool                    LoadAttributes( int iID, DatabaseManager *pDB );
        bool                    UpdateAttributes( QVector<QString> attributes, DatabaseManager *pDB );

        // accessors
        int                     ID( void );
        QString                 FirstName( void );
        QString                 MiddleName( void );
        QString                 LastName( void );
        QString                 Dob( void );
        QString                 LocalID( void );
        QString                 StateID( void );
        QString                 Address( void );
        QString                 City( void );
        QString                 State( void );
        QString                 ZipCode( void );
        QString                 DateJoin( void );
        QString                 Status( void );
        QString                 Hphone( void );
        QString                 Wphone( void );
        QString                 Cphone( void );
        QString                 DrvLic( void );
        QString                 CDL( void );
};

#endif // FIREFIGHTER_H

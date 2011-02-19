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

        bool                    insert( DatabaseManager *pDB );
        bool                    update( DatabaseManager *pDB );

    public:
                                Firefighter( void );

        bool                    save( DatabaseManager *pDB );
        bool                    load( int iID, DatabaseManager *pDB );

        // accessors
        int                     id( void );
        QString                 firstName( void );
        QString                 middleName( void );
        QString                 lastName( void );
        QString                 dob( void );
        QString                 localID( void );
        QString                 stateID( void );
        QString                 address( void );
        QString                 city( void );
        QString                 state( void );
        QString                 zipCode( void );
        QString                 dateJoin( void );
        QString                 status( void );
        QString                 hphone( void );
        QString                 wphone( void );
        QString                 cphone( void );
        QString                 drvLic( void );
        QString                 cdl( void );

        // setters
        void                     id( int iID );
        void                    firstName( QString s );
        void                    middleName( QString s );
        void                    lastName( QString s );
        void                    dob( QString s );
        void                    localID( QString s );
        void                    stateID( QString s );
        void                    address( QString s );
        void                    city( QString s );
        void                    state( QString s );
        void                    zipCode( QString s );
        void                    dateJoin( QString s );
        void                    status( QString s );
        void                    hphone( QString s );
        void                    wphone( QString s );
        void                    cphone( QString s );
        void                    drvLic( QString s );
        void                    cdl( QString s );
};

#endif // FIREFIGHTER_H

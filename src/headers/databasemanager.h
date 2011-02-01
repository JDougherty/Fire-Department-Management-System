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
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QSqlQuery>
#include <QVariant>
#include <QtDebug>
#include <QCryptographicHash>


class DatabaseManager : public QObject
{
    private:
        QSqlDatabase            _DB;

        QString                 _sPath,
                                _sDatabaseName;

        QString                 buildPath( QString sDatabaseName );

        bool                    buildStructure( void );
        bool                    verifyStructure( void );

    public:
                                DatabaseManager( QString sDatabaseName );
                                ~DatabaseManager( void );

        bool                    exists( void );
        bool                    open( void );
        bool                    isOpen( void );
        void                    close( void );

        bool                    build( void );
        bool                    verify( void );
        bool                    remove( void );

        bool                    query( QSqlQuery &qry );

        QSqlError               lastError( void );
};

#endif

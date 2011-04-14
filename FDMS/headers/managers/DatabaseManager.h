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

#include <QCheckBox>
#include <QComboBox>
#include <QCryptographicHash>
#include <QDateTimeEdit>
#include <QDir>
#include <QFile>
#include <QLineEdit>
#include <QMap>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QtDebug>
#include <QTextEdit>
#include <QVariant>
#include <QWidget>

#include "managers/SettingManager.h"

//! Handles a DB connection and verifies DB integrity.
/*!
  Basically a wrapper for QSqlDatabase.
*/
class DatabaseManager
{
    private:
                                    DatabaseManager( void );
                                    ~DatabaseManager( void );

        QSqlDatabase                _DB;

        QString                     _sFile; //!< DB file path.

    public:
        static DatabaseManager*     getInstance( void );

        bool                        setFile( QString sFile );
        bool                        getFile( void );
        bool                        deleteFile( void );
        bool                        existsFile( void );

        bool                        open( void );
        bool                        isOpen( void );
        void                        close( void );

        QSqlDatabase                getConnection( void );

        bool                        query( QSqlQuery &qry );

        QSqlError                   lastError( void );
};

#endif

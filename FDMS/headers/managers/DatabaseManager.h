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

        bool                        createTables( void );
        bool                        verifyTables( void );

        QSqlQuery                   bindValues( QWidget *pWidget, QString sQuery, QString sTabName = "" );
        QList<QWidget *>            getWidgets( QWidget *pWidget, QString sTabName );

        QSqlDatabase                _DB;

        QString                     _sFile; //!< DB file path.

    public:
        friend DatabaseManager*     getDatabaseManager( void );
        friend QSqlDatabase         getDatabaseManagerConnection( void );

        bool                        initialize( void );

        bool                        setFile( QString sFile );
        bool                        removeFile( void );

        bool                        exists( void );
        bool                        open( void );
        bool                        isOpen( void );
        void                        close( void );

        bool                        create( void );
        bool                        verify( void );

        QSqlDatabase                getConnection( void );

        void                        buildQueries( QWidget *pWidget, QString sTableName, QString sTabName = "" );

        bool                        query( QSqlQuery &qry );

        QSqlError                   lastError( void );
};

DatabaseManager* getDatabaseManager( void );
QSqlDatabase getDatabaseManagerConnection( void );

#endif

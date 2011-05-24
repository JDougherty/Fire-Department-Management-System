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
        DatabaseManager( void )
        {
            _sFile = QString::null;
            _DB = QSqlDatabase::addDatabase( "QSQLITE" );
        }

        ~DatabaseManager( void )
        {
            close();
            QSqlDatabase::removeDatabase( "QSQLITE" );
        }

        QSqlDatabase                _DB;

        QString                     _sFile; //!< DB file path.

    public:      
        static DatabaseManager* getInstance( void )
        {
            static DatabaseManager dbm;
            return &dbm;
        }

        //! Sets the DB file path.
        /*!
          \param sFile DB file path.
        */
        bool setFile( QString sFile )
        {
            if ( SettingManager::getInstance()->setValue( "database/file", sFile ) )
            {
                _sFile = sFile;
                return true;
            }

            return false;
        }

        bool getFile( void )
        {
            _sFile = SettingManager::getInstance()->getValue( "database/file" ).toString();
            return true;
        }

        //! Deletes the SQLite database file.
        /*!
          \return bool - Successfully deleted the db file.
        */
        bool deleteFile( void )
        {
            close(); // Close the database if it is already open
            bool bRemoved = QFile::remove( _sFile ); // Remove created database binary file

            if ( bRemoved )
                qDebug( qPrintable( QObject::tr( "DatabaseManager: Removed %s" ) ), qPrintable( _sFile ) );
            else
                qDebug( qPrintable( QObject::tr( "DatabaseManager: Failed to remove %s" ) ), qPrintable( _sFile ) );

            return bRemoved;
        }

        //! See if the SQL Lite file exists.
        /*!
          \return bool - DB file exists.
        */
        bool existsFile( void )
        {
            if ( _sFile == QString::null || !QFile::exists( _sFile ) )
            {
                qDebug( qPrintable( QObject::tr( "DatabaseManager: %s does not exist." ) ), qPrintable( _sFile ) );
                return false;
            }

            qDebug( qPrintable( QObject::tr( "DatabaseManager: %s exists." ) ), qPrintable( _sFile ) );
            return true;
        }

        //! Attempts to open the database (and creates the file if DNE).
        /*!
          \return bool - Successfully opened the database.
        */
        bool open( void )
        {
            _DB.setDatabaseName( _sFile );

            if ( !_DB.open() ) // If database name (file) DNE it creates it then tries to open it
            {
                qDebug( qPrintable( QObject::tr( "DatabaseManager: Error opening %s: %s" ) ), qPrintable( _sFile ), qPrintable( _DB.lastError().databaseText() ) );
                return false;
            }

            qDebug( qPrintable( QObject::tr( "DatabaseManager: Opened %s" ) ), qPrintable( _sFile ) );
            return true;
        }

        //! Checks if the database is open or not.
        /*!
          \return bool - DB opened.
        */
        bool isOpen( void )
        {
            return _DB.isOpen();
        }

        //! Closes the database.
        bool close( void )
        {
            qDebug( qPrintable( QObject::tr( "DatabaseManager: Closed %s" ) ), qPrintable( _sFile ) );
            _DB.close();
            return true;
        }

        QSqlDatabase getConnection( void )
        {
            return _DB;
        }

        //! Executes a query through the database.
        /*!
          \param query QSqlQuery which has been prepared and bound upon.
          \return bool - Query executed successfully.
        */
        bool query( QSqlQuery &query )
        {
           bool ret = query.exec();
           qDebug( qPrintable( QObject::tr( "DatabaseManager: Executing Query: %s" ) ), qPrintable( query.executedQuery() ) );
           return ret;
        }

        //! Wrapper to return the SQLite database last error.
        /*!
          \return QSqlError - Returned by the SQLite database.
        */
        QSqlError lastError( void )
        {
            return _DB.lastError();
        }
};

#endif

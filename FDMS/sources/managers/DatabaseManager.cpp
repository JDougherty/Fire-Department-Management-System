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

#include "managers/DatabaseManager.h"

DatabaseManager* DatabaseManager::getInstance( void )
{
    static DatabaseManager dbm;
    return &dbm;
}

DatabaseManager::DatabaseManager( void )
{
    _sFile = QString::null;
    _DB = QSqlDatabase::addDatabase( "QSQLITE" );
}

DatabaseManager::~DatabaseManager( void )
{
    close();
    QSqlDatabase::removeDatabase( "QSQLITE" );
}

//! Sets the DB file path.
/*!
  \param sFile DB file path.
*/
bool DatabaseManager::setFile( QString sFile )
{
    if ( SettingManager::getInstance()->setValue( "database/file", sFile ) )
    {
        _sFile = sFile;
        return true;
    }

    return false;
}

bool DatabaseManager::getFile( void )
{
    _sFile = SettingManager::getInstance()->getValue( "database/file" ).toString();
    return true;
}

//! Deletes the SQLite database file.
/*!
  \return bool - Successfully deleted the db file.
*/
bool DatabaseManager::deleteFile( void )
{
    close(); // Close the database if it is already open
    bool bRemoved = QFile::remove( _sFile ); // Remove created database binary file

    if ( bRemoved )
        qDebug( qPrintable( QObject::tr( "Database Manager: Removed %s" ) ), qPrintable( _sFile ) );
    else
        qDebug( qPrintable( QObject::tr( "Database Manager: Failed to remove %s" ) ), qPrintable( _sFile ) );

    return bRemoved;
}

//! See if the SQL Lite file exists.
/*!
  \return bool - DB file exists.
*/
bool DatabaseManager::existsFile( void )
{
    if ( _sFile == QString::null || !QFile::exists( _sFile ) )
    {
        qDebug( qPrintable( QObject::tr( "Database Manager: %s does not exist." ) ), qPrintable( _sFile ) );
        return false;
    }

    qDebug( qPrintable( QObject::tr( "Database Manager: %s exists." ) ), qPrintable( _sFile ) );
    return true;
}

//! Attempts to open the database (and creates the file if DNE).
/*!
  \return bool - Successfully opened the database.
*/
bool DatabaseManager::open( void )
{
    _DB.setDatabaseName( _sFile );

    if ( !_DB.open() ) // If database name (file) DNE it creates it then tries to open it
    {
        qDebug( qPrintable( QObject::tr( "Database Manager: Error opening %s: %s" ) ), qPrintable( _sFile ), qPrintable( _DB.lastError().databaseText() ) );
        return false;
    }

    qDebug( qPrintable( QObject::tr( "Database Manager: Opened %s" ) ), qPrintable( _sFile ) );
    return true;
}

//! Checks if the database is open or not.
/*!
  \return bool - DB opened.
*/
bool DatabaseManager::isOpen( void )
{
    return _DB.isOpen();
}

//! Closes the database.
void DatabaseManager::close( void )
{
    qDebug( qPrintable( QObject::tr( "Database Manager: Closed %s" ) ), qPrintable( _sFile ) );
    _DB.close();
}

QSqlDatabase DatabaseManager::getConnection( void )
{
    return _DB;
}

//! Executes a query through the database.
/*!
  \param query QSqlQuery which has been prepared and bound upon.
  \return bool - Query executed successfully.
*/
bool DatabaseManager::query( QSqlQuery &query )
{
   bool ret = query.exec();
   qDebug( qPrintable( QObject::tr( "Database Manager: Executing Query: %s" ) ), qPrintable( query.executedQuery() ) );
   return ret;
}

//! Wrapper to return the SQLite database last error.
/*!
  \return QSqlError - Returned by the SQLite database.
*/
QSqlError DatabaseManager::lastError( void )
{
    return _DB.lastError();
}

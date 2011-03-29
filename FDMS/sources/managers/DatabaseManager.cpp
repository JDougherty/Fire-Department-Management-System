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

DatabaseManager* getDatabaseManager( void )
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

bool DatabaseManager::initialize( void )
{
    SettingManager *sm = getSettingManager();
    _sFile = sm->get( "database/file" ).toString();

    if ( !exists() ) return false;

    _DB = QSqlDatabase::addDatabase( "QSQLITE" );
    _DB.setDatabaseName( _sFile );
    return true;
}

//! Sets the DB file path.
/*!
  \param sFile DB file path.
*/
bool DatabaseManager::setFile( QString sFile )
{
    SettingManager *sm = getSettingManager();
    sm->set( "database/file", sFile );

    return initialize();
}

//! Deletes the SQLite database file.
/*!
  \return bool - Successfully deleted the db file.
*/
bool DatabaseManager::removeFile( void )
{
    close(); // Close the database if it is already open
    bool bRemoved = QFile::remove( _sFile ); // Remove created database binary file

    if ( bRemoved )
        qDebug( "Database Manager: Removed %s", qPrintable( _sFile ) );
    else
        qDebug( "Database Manager: Failed to remove %s", qPrintable( _sFile ) );

    return bRemoved;
}

//! See if the SQL Lite file exists.
/*!
  \return bool - DB file exists.
*/
bool DatabaseManager::exists( void )
{
    if ( _sFile == QString::null || !QFile::exists( _sFile ) )
    {
        qDebug( "Database Manager: %s does not exist.", qPrintable( _sFile ) );
        return false;
    }

    qDebug( "Database Manager: %s exists.", qPrintable( _sFile ) );
    return true;
}

//! Attempts to open the database (and creates the file if DNE).
/*!
  \return bool - Successfully opened the database.
*/
bool DatabaseManager::open( void )
{
    if ( !_DB.open() ) // If database name (file) DNE it creates it then tries to open it
    {
        qDebug( "Database Manager: Error opening %s: %s", qPrintable( _sFile ), qPrintable( _DB.lastError().databaseText() ) );
        return false;
    }

    qDebug( "Database Manager: Opened %s", qPrintable( _sFile ) );
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
    qDebug( "Database Manager: Closed %s", qPrintable( _sFile ) );
    _DB.close();
}

//! Creates the SQLite database file.
/*!
  \return bool - Successfully built the db file.
  \see verify()
*/
bool DatabaseManager::create( void )
{
    return createTables();
}

//! Creates the tables in the SQL Lite database.
/*!
  \return bool - Successfully created the tables.
  \see verifyTables()
*/
bool DatabaseManager::createTables( void )
{
    QSqlQuery query;
    QString sSchema;
    QStringList slSplitSchema;

    qDebug( "Database Manager: Creating the tables." );

    sSchema = ""
             "CREATE TABLE department"
                 "(name TEXT,"
                 "address TEXT);"
             "CREATE TABLE Firefighters"
                 "(id INTEGER PRIMARY KEY,"
                 "PI_FirstName TEXT,"
                 "PI_MiddleName TEXT,"
                 "PI_LastName TEXT,"
                 "PI_LocalID TEXT,"
                 "PI_StateID TEXT,"
                 "PI_Address TEXT,"
                 "PI_City TEXT,"
                 "PI_State TEXT,"
                 "PI_ZipCode TEXT,"
                 "PI_Status TEXT,"
                 "PI_Hphone TEXT,"
                 "PI_Wphone TEXT,"
                 "PI_Cphone TEXT,"
                 "PI_DrvLic TEXT,"
                 "PI_CDL TEXT);"
             "CREATE TABLE training"
                 "(id INTEGER PRIMARY KEY,"
                 "title TEXT);"
             "CREATE TABLE fftraining"
                 "(id INTEGER PRIMARY KEY,"
                 "tid INTEGER,"
                 "ffid INTEGER,"
                 "ffesig TEXT,"
                 "supesig TEXT,"
                 "tdate TEXT,"
                 "FOREIGN KEY(tid) REFERENCES training(id),"
                 "FOREIGN KEY(ffid) REFERENCES firefighters(id));"
             "CREATE TABLE equipment"
                 "(id INTEGER PRIMARY KEY,"
                 "title TEXT);"
             "CREATE TABLE ffequipment"
                 "(id INTEGER PRIMARY KEY,"
                 "eqid INTEGER,"
                 "ffid INTEGER,"
                 "issued INTEGER,"
                 "size TEXT,"
                 "type TEXT,"
                 "serial TEXT,"
                 "year TEXT,"
                 "FOREIGN KEY(eqid) REFERENCES equipment(id),"
                 "FOREIGN KEY(ffid) REFERENCES firefighters(id));"     
             "CREATE TABLE Drills"
                 "(id INTEGER PRIMARY KEY,"
                 "DI_StartTime INTEGER,"
                 "DI_DrillNumber TEXT,"
                 "DI_EndTime INTEGER,"
                 "DI_Location TEXT,"
                 "DI_InHouse INTEGER,"
                 "DI_IncidentCommander TEXT,"
                 "DI_Description TEXT);"
             "CREATE TABLE drillsheet"
                 "(id INTEGER PRIMARY KEY, "
                 "did INTEGER,"
                 "ffid INTEGER,"
                 "timein TEXT,"
                 "timeout TEXT,"
                 "FOREIGN KEY(did) REFERENCES drills(id) ,"
                 "FOREIGN KEY(ffid) REFERENCES firefighters(id));"
             "CREATE TABLE inventory"
                 "(id INTEGER PRIMARY KEY,"
                 "name TEXT,"
                 "description TEXT,"
                 "category TEXT);"
             "CREATE TABLE inventorycheck"
                 "(id INTEGER PRIMARY KEY,"
                 "iid INTEGER,"
                 "name TEXT,"
                 "description TEXT,"
                 "category TEXT,"
                 "checked INTEGER)";

    // QSqlQuery::exec with SQLite will not execute multiple queries in a single execution.
    // Split the compound query into individual queries and execute each
    slSplitSchema = sSchema.split( ";" );
    for ( int i = 0; i < slSplitSchema.size(); i++ )
    {
        if ( query.exec( slSplitSchema[i] ) )
        {
            qDebug( "Database Manager: Structure Initialization: %s", qPrintable( query.lastQuery() ) );
        }
        else
        {
            qDebug( "Database Manager: Structure Initialization: %s", qPrintable( query.lastError().databaseText() ) );
            return false;
        }
    }

    return true;
}

//! Verifies the database's integrity.
/*!
  \return bool - Database is fine.
  \see build()
*/
bool DatabaseManager::verify( void )
{
    return verifyTables();
}

//! Verifies the database's table structure.
/*!
  \return bool - Database tables are fine.
  \see createTables()
*/
bool DatabaseManager::verifyTables( void )
{
    QSqlQuery qryTableNames;
    QSqlQuery qryTableInfo;
    QString sTableSchema;

    qDebug( "Database Manager: Verifying the database." );

    // While we're here, let's turn on foreign key support
    qryTableNames.exec( "PRAGMA foreign_keys = ON;" );

    // Get list of tables in database, loop through each
    qryTableNames.exec( "select tbl_name from sqlite_master;" );
    while ( qryTableNames.next() )
    {
        // Append the table name, column names and datatypes to TableSchema string
        qryTableInfo.exec( "pragma table_info(" + qryTableNames.value( 0 ).toString() + ")" );
        sTableSchema.append( qryTableNames.value( 0 ).toString() );

        while ( qryTableInfo.next() )
        {
            // The pragma table_info query returns five columns
            //  regarding the columns in the table queried:
            //  Index, Name, Datatype, Null, Default

            // Name and Datatype are relevant here
            sTableSchema.append( qryTableInfo.value(1).toString() );
            sTableSchema.append( qryTableInfo.value(2).toString() );
        }
    }

    // Calculate the md5 hash of this string
    QByteArray md5bytearray( QCryptographicHash::hash( sTableSchema.toAscii(), QCryptographicHash::Md5 ) );

    QString chksum = md5bytearray.toHex().constData();

    // And compare to expected value
    if ( chksum != "c6bc29f4490a6d43302b6c76605b7c2a" )
    {
        qDebug( "Database Manager: Invalid structure. Expected chksum c6bc29f4490a6d43302b6c76605b7c2a, but got %s", qPrintable( chksum ) );
        return false;
    }

    qDebug( "Database Manager: Valid structure." );
    return true;
}

//! Executes a query through the database.
/*!
  \param query QSqlQuery which has been prepared and bound upon.
  \return bool - Query executed successfully.
*/
bool DatabaseManager::query( QSqlQuery &query )
{
   bool ret = query.exec();
   qDebug( "Database Manager: Executing Query: %s", qPrintable( query.executedQuery() ) );
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

//! Gets a list of all of the matching DB widgets.
/*!
  \param pWidget First widget in the chain.
  \param sTabName Name of the UI tab (optional).
*/
QList<QWidget *> DatabaseManager::getWidgets( QWidget *pWidget, QString sTabName )
{
    QList<QWidget *> lWidgets;

    for ( QWidget *pTmpWidget = pWidget->nextInFocusChain(); pTmpWidget != pWidget; pTmpWidget = pTmpWidget->nextInFocusChain() )
    {
        if ( pTmpWidget->objectName().startsWith( "DB_" ) && ( sTabName == "" ||  pTmpWidget->objectName().contains( sTabName ) ) )
        {
            lWidgets += pTmpWidget;
        }
    }
    return lWidgets;
}

//! Binds UI values to the query.
/*!
  Used for insert and update.
  \param pWidget First widget in the chain.
  \param sAction Name of the action (insert, update).
  \param sTableName Name of the DB table.
  \param sTabName Name of the UI tab (optional).
*/
QSqlQuery DatabaseManager::bindValues( QWidget *pWidget, QString sQuery, QString sTabName )
{
    QList<QWidget *> lWidgets = getWidgets( pWidget, sTabName );
    QWidget *pTmpWidget;

    QSqlQuery query;
    query.prepare( sQuery );

    foreach ( pTmpWidget, lWidgets )
    {
        QLineEdit *tmplineedit = qobject_cast<QLineEdit *>( pTmpWidget );
        QTextEdit *tmptextedit = qobject_cast<QTextEdit *>( pTmpWidget );
        QDateTimeEdit *tmpdatetime = qobject_cast<QDateTimeEdit *>( pTmpWidget );
        QComboBox *tmpcombo = qobject_cast<QComboBox *>( pTmpWidget );
        QCheckBox *tmpcheck = qobject_cast<QCheckBox *>( pTmpWidget );

        if ( tmplineedit )
        {
            query.bindValue( ":" + tmplineedit->objectName(), tmplineedit->text() );
        }
        else if ( tmptextedit )
        {
            query.bindValue( ":" + tmptextedit->objectName(), tmptextedit->toPlainText() );
        }
        else if ( tmpdatetime )
        {
            query.bindValue( ":" + tmpdatetime->objectName(), tmpdatetime->dateTime().toString( "yyyy-MM-dd hh:mm:00.000" ) );
        }
        else if ( tmpcombo )
        {
            query.bindValue( ":" + tmpcombo->objectName(), tmpcombo->currentText() );
        }
        else if ( tmpcheck )
        {
            query.bindValue( ":" + tmpcheck->objectName(), tmpcheck->isChecked() );
        }
    }

    return query;
}

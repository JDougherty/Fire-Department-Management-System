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

#include "../headers/databasemanager.h"

DatabaseManager::DatabaseManager( void )
{
    _sDBFile = QString::null;

    _DB = QSqlDatabase::addDatabase( "QSQLITE" );
}

DatabaseManager::DatabaseManager( QString sDBFile )
{
    _sDBFile = sDBFile;

    _DB = QSqlDatabase::addDatabase( "QSQLITE" );
    _DB.setDatabaseName( _sDBFile );
}

DatabaseManager::~DatabaseManager( void )
{
    close();
    QSqlDatabase::removeDatabase( "QSQLITE" );
}

//! Sets the DB file path.
/*!
  \param sDBFile DB file path.
*/
void DatabaseManager::setDBFile( QString sDBFile )
{
    close();
    _sDBFile = sDBFile;
    _DB.setDatabaseName( _sDBFile );
}

//! See if the SQL Lite file exists.
/*!
  \return bool - DB file exists.
*/
bool DatabaseManager::exists( void )
{
    if ( !QFile::exists( _sDBFile ) )
    {
        qDebug( "Database: %s does not exist.", qPrintable( _sDBFile ) );
        return false;
    }

    qDebug( "Database: %s exists.", qPrintable( _sDBFile ) );
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
        qDebug( "Database: Error opening %s: %s", qPrintable( _sDBFile ), qPrintable( _DB.lastError().databaseText() ) );
        return false;
    }

    qDebug( "Database: Opened %s", qPrintable( _sDBFile ) );
    return true;
}

//! Closes the database.
void DatabaseManager::close( void )
{
    _DB.close();
}

//! Checks if the database is open or not.
/*!
  \return bool - DB opened.
*/
bool DatabaseManager::isOpen( void )
{
    return _DB.isOpen();
}

//! Deletes the SQLite database file.
/*!
  \return bool - Successfully deleted the db file.
*/
bool DatabaseManager::remove( void )
{
    close(); // Close the database if it is already open
    return QFile::remove( _sDBFile ); // Remove created database binary file
}

//! Builds the SQLite database file.
/*!
  \return bool - Successfully built the db file.
  \see verify()
*/
bool DatabaseManager::build( void )
{
    return buildStructure();
}

//! Creates the tables in the SQL Lite database.
/*!
  \return bool - Successfully created the tables.
  \see verifyStructure()
*/
bool DatabaseManager::buildStructure( void )
{
    QSqlQuery query;
    QString sSchema;
    QStringList slSplitSchema;

    sSchema = ""
             "CREATE TABLE department"
                 "(name TEXT,"
                 "address TEXT);"
             "CREATE TABLE firefighters"
                 "(id INTEGER PRIMARY KEY,"
                 "fname TEXT,"
                 "mname TEXT,"
                 "lname TEXT,"
                 "dob TEXT,"
                 "deptid TEXT,"
                 "stateid TEXT,"
                 "address TEXT,"
                 "city TEXT,"
                 "state TEXT,"
                 "zip TEXT,"
                 "joindate TEXT,"
                 "status TEXT,"
                 "hphone TEXT,"
                 "wphone TEXT,"
                 "cphone TEXT,"
                 "drvlic TEXT,"
                 "cdl TEXT);"
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
             "CREATE TABLE drills"
                 "(id INTEGER PRIMARY KEY, "
                 "location TEXT,"
                 "inhouse INTEGER,"
                 "description TEXT,"
                 "starttime INTEGER,"
                 "endtime INTEGER,"
                 "incidentcommander TEXT,"
                 "drillnum TEXT);"
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
                 "checked INTEGER);"
             "CREATE TABLE calls ("
                 "id INTEGER PRIMARY KEY,"
                 "incidentnumber INTEGER,"
                 "Location TEXT,"
                 "TravelDirections TEXT,"
                 "NumMile TEXT,"
                 "StreetPrefix TEXT,"
                 "Street TEXT,"
                 "StreetType TEXT,"
                 "StreetSuffix TEXT,"
                 "AptSuiteRm TEXT,"
                 "CityTown TEXT,"
                 "State TEXT,"
                 "ZipCode TEXT,"
                 "IncidentType TEXT,"
                 "MutualAid TEXT,"
                 "MutualAidFDID TEXT,"
                 "MutualAidState TEXT,"
                 "MutualAidIncidentNumber TEXT,"
                 "Alarm TEXT,"
                 "Arrival TEXT,"
                 "Clear TEXT,"
                 "PrimaryAction TEXT,"
                 "SecondaryAction TEXT,"
                 "Apparatus TEXT,"
                 "Personnel TEXT,"
                 "ValueOfProperty TEXT,"
                 "TotalLoss TEXT,"
                 "InjuriesFireService TEXT,"
                 "InjuriesOther TEXT,"
                 "DeathsFireService TEXT,"
                 "DeathsOther TEXT,"
                 "HazMatType TEXT,"
                 "HazMatClass TEXT,"
                 "HazMatAmount TEXT,"
                 "HazMatUnit TEXT,"
                 "PropertyDetector TEXT,"
                 "MixedUseProperty TEXT,"
                 "PropertyUse TEXT,"
                 "NumUnits TEXT,"
                 "JuvenileInvolvement TEXT,"
                 "InvolvedBusinessName1 TEXT,"
                 "InvolvedTitle1 TEXT,"
                 "InvolvedFirstName1 TEXT,"
                 "InvolvedMiddleInitial1 TEXT,"
                 "InvolvedLastName1 TEXT,"
                 "InvolvedSuffix1 TEXT,"
                 "InvolvedNumMile1 TEXT,"
                 "InvolvedStreetPrefix1 TEXT,"
                 "InvolvedStreet1 TEXT,"
                 "InvolvedStreetType1 TEXT,"
                 "InvolvedStreetSuffix1 TEXT,"
                 "InvolvedPOBox1 TEXT,"
                 "InvolvedAptSuiteRm1 TEXT,"
                 "InvolvedCityTown1 TEXT,"
                 "InvolvedState1 TEXT,"
                 "InvolvedZipCode1 TEXT,"
                 "InvolvedBusinessName2 TEXT,"
                 "InvolvedTitle2 TEXT,"
                 "InvolvedFirstName2 TEXT,"
                 "InvolvedMiddleInitial2 TEXT,"
                 "InvolvedLastName2 TEXT,"
                 "InvolvedSuffix2 TEXT,"
                 "InvolvedNumMile2 TEXT,"
                 "InvolvedStreetPrefix2 TEXT,"
                 "InvolvedStreet2 TEXT,"
                 "InvolvedStreetType2 TEXT,"
                 "InvolvedStreetSuffix2 TEXT,"
                 "InvolvedPOBox2 TEXT,"
                 "InvolvedAptSuiteRm2 TEXT,"
                 "InvolvedCityTown2 TEXT,"
                 "InvolvedState2 TEXT,"
                 "InvolvedZipCode2 TEXT,"
                 "AreaOfIgnition TEXT,"
                 "HeatSource TEXT,"
                 "ItemFirstIgnited TEXT,"
                 "TypeMaterialFirstIgnited TEXT,"
                 "CauseofIgnition TEXT,"
                 "ContributingFactor TEXT,"
                 "SpreadConfined TEXT,"
                 "HumanFactors TEXT,"
                 "HumanFactorsAge TEXT,"
                 "HumanFactorsSex TEXT,"
                 "EquipmentFactors TEXT,"
                 "EquipmentFactorsPower TEXT,"
                 "EquipmentFactorsPortability TEXT,"
                 "MobilePropertyType TEXT,"
                 "MobilePropertyMake TEXT,"
                 "BuildingType TEXT,"
                 "BuildingStatus TEXT,"
                 "BuildingHeightStories INTEGER,"
                 "MainFloorSizeFtW INTEGER,"
                 "MainFloorSizeFtH INTEGER,"
                 "StoryFireOrigin INTEGER,"
                 "FireSpread TEXT,"
                 "DetectorPresence INTEGER,"
                 "DetectorType TEXT,"
                 "DetectorPower TEXT,"
                 "DetectorOperation TEXT,"
                 "DetectorEffectiveness TEXT,"
                 "DetectorFailureReason TEXT,"
                 "AESPresence TEXT,"
                 "AESType TEXT,"
                 "AESOperation TEXT,"
                 "NumSprinklerHeadsOper INTEGER,"
                 "AESFailureReason TEXT)";


    // QSqlQuery::exec with SQLite will not execute multiple queries in a single execution.
    // Split the compound query into individual queries and execute each
    slSplitSchema = sSchema.split( ";" );
    for ( int i = 0; i < slSplitSchema.size(); i++ )
    {
        if ( query.exec( slSplitSchema[i] ) )
        {
            //qDebug( "Database: Structure Initialization: %s", qPrintable( query.lastQuery() ) );
        }
        else
        {
            //qDebug( "Database: Structure Initialization: %s", qPrintable( query.lastError().databaseText() ) );
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
    return verifyStructure();
}

//! Verifies the database's table structure.
/*!
  \return bool - Database tables are fine.
  \see buildStructure()
*/
bool DatabaseManager::verifyStructure( void )
{
    QSqlQuery qryTableNames;
    QSqlQuery qryTableInfo;
    QString sTableSchema;

    // While we're here, let's turn on foreign key support
    qryTableNames.exec( "PRAGMA foreign_keys = ON;" );

    // Get list of tables in database, loop through each
    qryTableNames.exec( "select tbl_name from sqlite_master;" );
    while( qryTableNames.next() )
    {
        // Append the table name, column names and datatypes to TableSchema string
        qryTableInfo.exec( "pragma table_info(" + qryTableNames.value(0).toString() + ")" );
        sTableSchema.append( qryTableNames.value(0).toString() );

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
    if ( chksum != "9222c8dcad4670104628f6c6beec4761" )
    {
        qDebug( "Database: Invalid structure. Expected chksum 9222c8dcad4670104628f6c6beec4761, but got %s", qPrintable( chksum ) );
        return false;
    }

    qDebug( "Database: Valid structure." );
    return true;
}

//! Wrapper to return the SQLite database last error.
/*!
  \return QSqlError - Returned by the SQLite database.
*/
QSqlError DatabaseManager::lastError( void )
{
    return _DB.lastError();
}

//! Executes a query through the database.
/*!
  \param query QSqlQuery which has been prepared and bound upon.
  \return bool - Query executed successfully.
*/
bool DatabaseManager::query( QSqlQuery &query )
{
   bool ret = query.exec();
   qDebug( "Database: Executing Query: %s", qPrintable( query.executedQuery() ) );
   return ret;
}

//! Builds the queries for all of the widgets in the focus chain.
/*!
  \param sTableName Name of the DB table.
  \param pWidget First widget in the chain.
*/
void DatabaseManager::buildQueries( QString sTableName, QString sTabName, QWidget *pWidget )
{
    QList<QWidget*> edits;
    QWidget *pTmpWidget = pWidget->nextInFocusChain();
    QString sCreateQuery, sSelectQuery, sInsertQuery, sInsertQueryValues, sUpdateQuery, sDBObjName, sObjName;

    while ( pTmpWidget != pWidget )
    {
        if ( pTmpWidget->objectName().startsWith( "DB_" ) && (sTabName == " " ||  pTmpWidget->objectName().contains( sTabName ) ) )
        {
            edits += pTmpWidget;
        }
        pTmpWidget = pTmpWidget->nextInFocusChain();
    }

    sCreateQuery = "CREATE TABLE " + sTableName + "(id INTEGER PRIMARY KEY,";
    sSelectQuery = "SELECT ";
    sInsertQuery = "INSERT INTO " + sTableName + " ( ";
    sInsertQueryValues = " VALUES ( ";
    sUpdateQuery = "UPDATE " + sTableName + " a SET ";

    foreach ( pTmpWidget, edits )
    {
        sDBObjName = pTmpWidget->objectName();

        if ( sDBObjName.startsWith( "DB_TEXT" ) )
        {
            sObjName = sDBObjName.right( sDBObjName.size() - 8 );
            sCreateQuery += sObjName + " TEXT,";
        }
        else if ( sDBObjName.startsWith( "DB_INT" ) )
        {
            sObjName = sDBObjName.right( sDBObjName.size() - 7 );
            sCreateQuery += sObjName + " INTEGER,";
        }
        else
        {
            qDebug( qPrintable( "Unrecognized DB field type" + sDBObjName + "." ) );
            continue;
        }

        sSelectQuery += sObjName + ",";

        sInsertQuery += sObjName + ",";
        sInsertQueryValues += ":" + sDBObjName + ",";

        sUpdateQuery += "a." + sObjName + " = :" + sDBObjName + ",";
    }

    sCreateQuery.replace( sCreateQuery.size() - 1, 1, QChar( ')' ) ); // replace the last char with ')'

    sSelectQuery.replace( sSelectQuery.size() - 1, 1, QChar( ' ' ) ); // replace the last char with ' '
    sSelectQuery += "FROM " + sTableName + " WHERE id = :id";

    sInsertQuery.replace( sInsertQuery.size() - 1, 1, QChar( ')' ) ); // replace the last char with ')'
    sInsertQueryValues.replace( sInsertQueryValues.size() - 1, 1, QChar( ')' ) ); // replace the last char with ')'
    sInsertQuery += sInsertQueryValues;

    sUpdateQuery.replace( sUpdateQuery.size() - 1, 1, QChar( ' ' ) ); // replace the last char with ' '
    sUpdateQuery += "WHERE a.id = :id)";

    QMap<QString, QString> uiQueries;
    uiQueries.insert( "create", sCreateQuery );
    uiQueries.insert( "select", sSelectQuery );
    uiQueries.insert( "insert", sInsertQuery );
    uiQueries.insert( "update", sUpdateQuery );
    _queryMap.insert( sTableName, uiQueries );

    qDebug( qPrintable( "Generating queries for the " + sTableName + " table." ) );
    qDebug( qPrintable( sCreateQuery ) );
    qDebug( qPrintable( sSelectQuery ) );
    qDebug( qPrintable( sInsertQuery ) );
    qDebug( qPrintable( sUpdateQuery ) );
}

bool DatabaseManager::updateUI( int iID, QString sTableName, QString sTabName, QWidget *pWidget )
{
    QList<QWidget*> edits;
    QWidget *pTmpWidget = pWidget->nextInFocusChain();

    while ( pTmpWidget != pWidget )
    {
        if ( pTmpWidget->objectName().startsWith( "DB_" ) && (sTabName == " " ||  pTmpWidget->objectName().contains( sTabName ) ) )
        {
            edits += pTmpWidget;
        }
        pTmpWidget = pTmpWidget->nextInFocusChain();
    }

    QSqlQuery updateQuery;
    updateQuery.prepare(_queryMap[sTableName]["update"]);

    foreach ( pTmpWidget, edits )
    {
        QLineEdit *tmplineedit = qobject_cast<QLineEdit *>( pTmpWidget );
        QDateTimeEdit *tmpdatetime = qobject_cast<QDateTimeEdit *>( pTmpWidget );
        QComboBox *tmpcombo = qobject_cast<QComboBox *>( pTmpWidget );
        QCheckBox *tmpcheck = qobject_cast<QCheckBox *>( pTmpWidget );

        if ( tmplineedit )
        {
            updateQuery.bindValue( ":" + tmplineedit->objectName(), tmplineedit->text() );
        }
        else if ( tmpdatetime )
        {
            updateQuery.bindValue( ":" + tmpdatetime->objectName(), tmpdatetime->dateTime().toString( "yyyy-MM-dd hh:mm:00.000" ) );
        }
        else if ( tmpcombo )
        {
            updateQuery.bindValue( ":" + tmpcombo->objectName(), tmpcombo->currentText() );
        }
        else if ( tmpcheck )
        {
            updateQuery.bindValue( ":" + tmpcheck->objectName(),tmpcheck->objectName() );
        }
    }

    updateQuery.bindValue( ":id", iID );

    QMapIterator<QString, QVariant> i( updateQuery.boundValues() );
    while ( i.hasNext() )
    {
        i.next();
        qDebug( qPrintable( i.key() + " " + qPrintable( i.value().toString() ) ) );
    }

    if ( !query( updateQuery ) )
    {
        qWarning( "Database Error: Could not update table '%s' entry #%d: %s",
                  qPrintable( sTableName ), iID, qPrintable( updateQuery.lastError().text() ) );
        return false;
    }

    qDebug( "Database: Updated table '%s' entry #%d.", qPrintable( sTableName), iID );

    return true;
}

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

DatabaseManager::DatabaseManager( QString sDatabaseName )
{
    _sDatabaseName = "";
    _sPath = "";

    _sDatabaseName = sDatabaseName;
    _sPath = buildPath( sDatabaseName );

    _DB = QSqlDatabase::addDatabase( "QSQLITE" );
    _DB.setDatabaseName( _sPath );
}

DatabaseManager::~DatabaseManager( void )
{
    close();
    QSqlDatabase::removeDatabase( "QSQLITE" );
}

/*
    Function:    DatabaseManager::buildPath
    Purpose:     Builds the file path for the database
    Parameters:
        QString sDatabaseName - file name
    Returns:     QString - the file path + file name
*/
QString DatabaseManager::buildPath( QString sDatabaseName )
{
    QString sPath;

    #ifdef Q_OS_LINUX
    // Database file must be located in user home folder in Linux
    sPath = QDir::home().path();
    sPath.append( QDir::separator() ).append( sDatabaseName );
    sPath = QDir::toNativeSeparators( qsPath );
    #else
    sPath = sDatabaseName;
    #endif

    return sPath;
}

/*
    Function:    DatabaseManager::exists
    Purpose:     See if the SQL Lite file exists
    Returns:     bool
        true - DB file exists
        false - DB file dne
*/
bool DatabaseManager::exists( void )
{
    if ( QFile::exists( _sPath ) )
    {
        qDebug( "Database file exists." );
        return true;
    }

    qDebug( "Database file does not exist." );
    return false;
}

/*
    Function:    DatabaseManager::open
    Purpose:     Attempts to open the database (and creates the file if DNE)
    Returns:     bool
        true - Successfully opened the database
        false - Unable to open the database
*/
bool DatabaseManager::open( void )
{
    if ( !_DB.open() ) // If database name (file) DNE it creates it then tries to open it
    {
        qDebug( "Error opening database: %s", qPrintable( _DB.lastError().databaseText() ) );
        return false;
    }
    return true;
}

/*
    Function:    DatabaseManager::close
    Purpose:     Closes the database
*/
void DatabaseManager::close( void )
{
    _DB.close();
}

/*
    Function:    DatabaseManager::isOpen
    Purpose:     Checks if the database is open or not
    Returns:     bool
        true - DB opened
        false - DB not opened
*/
bool DatabaseManager::isOpen( void )
{
    return _DB.isOpen();
}

/*
    Function:    DatabaseManager::remove
    Purpose:     Deletes the SQLite database file
    Returns:     bool
        true - Successfully deleted the db file
        false - Failed to delete db file

    See Also:    <Divide>
*/
bool DatabaseManager::remove( void )
{
    close(); // Close the database if it is already open
    return QFile::remove( _sPath ); // Remove created database binary file
}

/*
    Function:    DatabaseManager::build
    Purpose:     Builds the SQLite database file
    Returns:     bool
        true - Successfully built the db file
        false - Failed to build the db file

    See Also:    DatabaseManager::verify
*/
bool DatabaseManager::build( void )
{
    return buildStructure();
}

/*
    Function:    DatabaseManager::buildStructure
    Purpose:     Creates the tables in the SQLite database
    Returns:     bool
        true - Successfully created the tables
        false - Failed to create the tables

    See Also:    DatabaseManager::verifyStructure
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
            qDebug( "Database Structure Initialization: %s", qPrintable( query.lastQuery() ) );
        }
        else
        {
            qDebug( "Database Structure Initialization: %s", qPrintable( query.lastError().databaseText() ) );
            return false;
        }
    }

    return true;
}

/*
    Function:    DatabaseManager::verify
    Purpose:     Verifies the database's integrity
    Returns:     bool
        true - Database is fine
        false - Database is messed up

    See Also:    DatabaseManager::build
*/
bool DatabaseManager::verify( void )
{
    return verifyStructure();
}

/*
    Function:    DatabaseManager::verifyStructure
    Purpose:     Verifies the database's table structure
    Returns:     bool
        true - Database tables are fine
        false - Database tables are messed up

    See Also:    DatabaseManager::buildStructure
*/
bool DatabaseManager::verifyStructure( void )
{
    QSqlQuery qryTableNames;
    QSqlQuery qryTableInfo;
    QString sTableSchema;

    qDebug( "Verifying database structure." );

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

    //qDebug()<<chksum;
    //qDebug()<<TableSchema;

    // And compare to expected value
    if ( chksum != "9222c8dcad4670104628f6c6beec4761" )
    {
        return false;
    }

    return true;
}

/*
    Function:    DatabaseManager::verifyStructure
    Purpose:     Wrapper to return the SQLite database last error
    Returns:     QSqlError - Returned by the SQLite database
*/
QSqlError DatabaseManager::lastError( void )
{
    return _DB.lastError();
}

/*
    Function:    DatabaseManager::query
    Purpose:     Executes a query through the database
    Parameters:
        query - QSqlQuery which has been prepared and bound upon
    Returns:     bool
        true - Query has successfully executed
        false - Query failed to execute
*/
bool DatabaseManager::query( QSqlQuery &query )
{
   bool ret = query.exec();
   qDebug( "Database Query: %s", qPrintable( query.executedQuery() ) );
   return ret;
}

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
        qDebug( "Database Manager: %s does not exist.", qPrintable( _sDBFile ) );
        return false;
    }

    qDebug( "Database Manager: %s exists.", qPrintable( _sDBFile ) );
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
        qDebug( "Database Manager: Error opening %s: %s", qPrintable( _sDBFile ), qPrintable( _DB.lastError().databaseText() ) );
        return false;
    }

    qDebug( "Database Manager: Opened %s", qPrintable( _sDBFile ) );
    return true;
}

//! Closes the database.
void DatabaseManager::close( void )
{
    qDebug( "Database Manager: Closed %s", qPrintable( _sDBFile ) );
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
    bool bRemoved = QFile::remove( _sDBFile ); // Remove created database binary file

    if ( bRemoved )
        qDebug( "Database Manager: Removed %s", qPrintable( _sDBFile ) );
    else
        qDebug( "Database Manager: Failed to remove %s", qPrintable( _sDBFile ) );

    return bRemoved;
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
                 "checked INTEGER);"
             "CREATE TABLE Calls ("
                 "id INTEGER PRIMARY KEY,"
                 "TS_CallNum INTEGER,"
                 "AC1_Location TEXT,"
                 "AC1_TravelDirections TEXT,"
                 "AC1_NumMile TEXT,"
                 "AC1_StreetPrefix TEXT,"
                 "AC1_Street TEXT,"
                 "AC1_StreetType TEXT,"
                 "AC1_StreetSuffix TEXT,"
                 "AC1_AptSuiteRm TEXT,"
                 "AC1_CityTown TEXT,"
                 "AC1_State TEXT,"
                 "AC1_ZipCode TEXT,"
                 "AC1_IncidentType TEXT,"
                 "AC1_MutualAid TEXT,"
                 "AC1_MutualAidFDID TEXT,"
                 "AC1_MutualAidState TEXT,"
                 "AC1_MutualAidIncidentNumber TEXT,"
                 "AC1_Alarm TEXT,"
                 "AC1_Arrival TEXT,"
                 "AC1_Clear TEXT,"
                 "AC1_PrimaryAction TEXT,"
                 "AC1_SecondaryAction TEXT,"
                 "AC2_Apparatus TEXT,"
                 "AC2_Personnel TEXT,"
                 "AC2_ValueOfProperty TEXT,"
                 "AC2_TotalLoss TEXT,"
                 "AC2_InjuriesFireService TEXT,"
                 "AC2_InjuriesOther TEXT,"
                 "AC2_DeathsFireService TEXT,"
                 "AC2_DeathsOther TEXT,"
                 "AC2_HazMatType TEXT,"
                 "AC2_HazMatClass TEXT,"
                 "AC2_HazMatAmount TEXT,"
                 "AC2_HazMatUnit TEXT,"
                 "AC2_PropertyDetector TEXT,"
                 "AC2_MixedUseProperty TEXT,"
                 "AC2_PropertyUse TEXT,"
                 "AC2_NumUnits TEXT,"
                 "AC2_JuvenileInvolvement TEXT,"
                 "AF1_InvolvedBusinessName1 TEXT,"
                 "AF1_InvolvedTitle1 TEXT,"
                 "AF1_InvolvedFirstName1 TEXT,"
                 "AF1_InvolvedMiddleInitial1 TEXT,"
                 "AF1_InvolvedLastName1 TEXT,"
                 "AF1_InvolvedSuffix1 TEXT,"
                 "AF1_InvolvedNumMile1 TEXT,"
                 "AF1_InvolvedStreetPrefix1 TEXT,"
                 "AF1_InvolvedStreet1 TEXT,"
                 "AF1_InvolvedStreetType1 TEXT,"
                 "AF1_InvolvedStreetSuffix1 TEXT,"
                 "AF1_InvolvedPOBox1 TEXT,"
                 "AF1_InvolvedAptSuiteRm1 TEXT,"
                 "AF1_InvolvedCityTown1 TEXT,"
                 "AF1_InvolvedState1 TEXT,"
                 "AF1_InvolvedZipCode1 TEXT,"
                 "AF1_InvolvedBusinessName2 TEXT,"
                 "AF1_InvolvedTitle2 TEXT,"
                 "AF1_InvolvedFirstName2 TEXT,"
                 "AF1_InvolvedMiddleInitial2 TEXT,"
                 "AF1_InvolvedLastName2 TEXT,"
                 "AF1_InvolvedSuffix2 TEXT,"
                 "AF1_InvolvedNumMile2 TEXT,"
                 "AF1_InvolvedStreetPrefix2 TEXT,"
                 "AF1_InvolvedStreet2 TEXT,"
                 "AF1_InvolvedStreetType2 TEXT,"
                 "AF1_InvolvedStreetSuffix2 TEXT,"
                 "AF1_InvolvedPOBox2 TEXT,"
                 "AF1_InvolvedAptSuiteRm2 TEXT,"
                 "AF1_InvolvedCityTown2 TEXT,"
                 "AF1_InvolvedState2 TEXT,"
                 "AF1_InvolvedZipCode2 TEXT,"
                 "AF2_AreaOfIgnition TEXT,"
                 "AF2_HeatSource TEXT,"
                 "AF2_ItemFirstIgnited TEXT,"
                 "AF2_TypeMaterialFirstIgnited TEXT,"
                 "AF2_CauseOfIgnition TEXT,"
                 "AF2_ContributingFactor TEXT,"
                 "AF2_SpreadConfined TEXT,"
                 "AF2_HumanFactors TEXT,"
                 "AF2_HumanFactorsAge TEXT,"
                 "AF2_HumanFactorsSex TEXT,"
                 "AF2_EquipmentFactors TEXT,"
                 "AF2_EquipmentFactorsPower TEXT,"
                 "AF2_EquipmentFactorsPortability TEXT,"
                 "AF2_MobilePropertyType TEXT,"
                 "AF2_MobilePropertyMake TEXT,"
                 "SF_BuildingType TEXT,"
                 "SF_BuildingStatus TEXT,"
                 "SF_BuildingHeightStories INTEGER,"
                 "SF_MainFloorSizeFtW INTEGER,"
                 "SF_MainFloorSizeFtH INTEGER,"
                 "SF_StoryFireOrigin INTEGER,"
                 "SF_FireSpread TEXT,"
                 "SF_DetectorPresence INTEGER,"
                 "SF_DetectorType TEXT,"
                 "SF_DetectorPower TEXT,"
                 "SF_DetectorOperation TEXT,"
                 "SF_DetectorEffectiveness TEXT,"
                 "SF_DetectorFailureReason TEXT,"
                 "SF_AESPresence TEXT,"
                 "SF_AESType TEXT,"
                 "SF_AESOperation TEXT,"
                 "SF_NumSprinklerHeadsOper INTEGER,"
                 "SF_AESFailureReason TEXT)";

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
    if ( chksum != "bf3ff44dca466e437936daa42c85cc49" )
    {
        qDebug( "Database Manager: Invalid structure. Expected chksum bf3ff44dca466e437936daa42c85cc49, but got %s", qPrintable( chksum ) );
        return false;
    }

    qDebug( "Database Manager: Valid structure." );
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
   qDebug( "Database Manager: Executing Query: %s", qPrintable( query.executedQuery() ) );
   return ret;
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
        if ( pTmpWidget->objectName().startsWith( "DB_" ) && (sTabName == "" ||  pTmpWidget->objectName().contains( sTabName ) ) )
        {
            lWidgets += pTmpWidget;
        }
    }
    return lWidgets;
}

//! Builds the queries for all of the widgets in the focus chain.
/*!
  \param sTableName Name of the DB table.
  \param pWidget First widget in the chain.
  \param sTabName Name of the UI tab (optional).
*/
void DatabaseManager::buildQueries( QString sTableName, QWidget *pWidget, QString sTabName )
{
    QString sCreateQuery, sSelectQuery, sInsertQuery, sInsertQueryValues, sUpdateQuery, sDBObjName, sObjName;
    QList<QWidget *> lWidgets = getWidgets( pWidget, sTabName );
    QWidget *pTmpWidget;

    qDebug( "Database Manager: Generating queries for the '%s' table.", qPrintable( sTableName ) );

    sCreateQuery = "CREATE TABLE " + sTableName + "(id INTEGER PRIMARY KEY,";
    sSelectQuery = "SELECT ";
    sInsertQuery = "INSERT INTO " + sTableName + " ( ";
    sInsertQueryValues = " VALUES ( ";
    sUpdateQuery = "UPDATE " + sTableName + " SET ";

    foreach ( pTmpWidget, lWidgets )
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
        else if ( sDBObjName.startsWith( "DB_DATE" ) )
        {
            sObjName = sDBObjName.right( sDBObjName.size() - 8 );
            sCreateQuery += sObjName + " INTEGER,";
        }
        else if ( sDBObjName.startsWith( "DB_CHECK" ) )
        {
            sObjName = sDBObjName.right( sDBObjName.size() - 9 );
            sCreateQuery += sObjName + " INTEGER,";
        }
        else
        {
            qWarning( "Database Manager: Unrecognized DB field type '%s'.", qPrintable( sDBObjName ) );
            continue;
        }

        sSelectQuery += sObjName + ",";

        sInsertQuery += sObjName + ",";
        sInsertQueryValues += ":" + sDBObjName + ",";

        sUpdateQuery += sObjName + " = :" + sDBObjName + ",";
    }

    sCreateQuery.replace( sCreateQuery.size() - 1, 1, QChar( ')' ) ); // replace the last char with ')'

    sSelectQuery.replace( sSelectQuery.size() - 1, 1, QChar( ' ' ) ); // replace the last char with ' '
    sSelectQuery += "FROM " + sTableName + " WHERE id = :id";

    sInsertQuery.replace( sInsertQuery.size() - 1, 1, QChar( ')' ) ); // replace the last char with ')'
    sInsertQueryValues.replace( sInsertQueryValues.size() - 1, 1, QChar( ')' ) ); // replace the last char with ')'
    sInsertQuery += sInsertQueryValues;

    sUpdateQuery.replace( sUpdateQuery.size() - 1, 1, QChar( ' ' ) ); // replace the last char with ' '
    sUpdateQuery += "WHERE id = :id";

    QMap<QString, QString> uiQueries;
    uiQueries.insert( "create", sCreateQuery );
    uiQueries.insert( "select", sSelectQuery );
    uiQueries.insert( "insert", sInsertQuery );
    uiQueries.insert( "update", sUpdateQuery );
    _queryMap.insert( sTableName, uiQueries );

    qDebug( "Database Manager: '%s' create query: %s", qPrintable( sTableName ), qPrintable( sCreateQuery ) );
    qDebug( "Database Manager: '%s' select query: %s", qPrintable( sTableName ), qPrintable( sSelectQuery ) );
    qDebug( "Database Manager: '%s' insert query: %s", qPrintable( sTableName ), qPrintable( sInsertQuery ) );
    qDebug( "Database Manager: '%s' update query: %s", qPrintable( sTableName ), qPrintable( sUpdateQuery ) );
}

bool DatabaseManager::selectUI( int iID, QString sTableName, QWidget *pWidget, QString sTabName )
{
    QList<QWidget *> lWidgets = getWidgets( pWidget, sTabName );
    QWidget *pTmpWidget;

    QSqlQuery selectQuery;
    selectQuery.prepare( _queryMap[sTableName]["select"] );
    selectQuery.bindValue( ":id", iID );

    if ( !query( selectQuery ) )
    {
        qWarning( "Database Manager: Could not select from table '%s' entry #%d: %s",
                  qPrintable( sTableName ), iID, qPrintable( selectQuery.lastError().text() ) );
        return false;
    }

    selectQuery.next();

    QVariant result;
    int i = 0;
    foreach ( pTmpWidget, lWidgets )
    {
        QLineEdit *tmplineedit = qobject_cast<QLineEdit *>( pTmpWidget );
        QDateTimeEdit *tmpdatetime = qobject_cast<QDateTimeEdit *>( pTmpWidget );
        QComboBox *tmpcombo = qobject_cast<QComboBox *>( pTmpWidget );
        QCheckBox *tmpcheck = qobject_cast<QCheckBox *>( pTmpWidget );

        result = selectQuery.value( i );
        if ( !result.isValid() )
            break;

        if ( tmplineedit )
        {
            tmplineedit->setText( result.toString() );
        }
        else if ( tmpdatetime )
        {
            tmpdatetime->setDate( result.toDate() );
        }
        else if ( tmpcheck )
        {
            tmpcheck->setCheckState( result.toBool() ? Qt::Checked : Qt::Unchecked );
        }

        i++;
    }

    qDebug( "Database Manager: Selected from table '%s' entry #%d.", qPrintable( sTableName), iID );

    return true;
}

int DatabaseManager::insertUI( QString sTableName, QWidget *pWidget, QString sTabName )
{
    QList<QWidget *> lWidgets = getWidgets( pWidget, sTabName );
    QWidget *pTmpWidget;

    QSqlQuery insertQuery;
    insertQuery.prepare( _queryMap[sTableName]["insert"] );

    foreach ( pTmpWidget, lWidgets )
    {
        QLineEdit *tmplineedit = qobject_cast<QLineEdit *>( pTmpWidget );
        QTextEdit *tmptextedit = qobject_cast<QTextEdit *>( pTmpWidget );
        QDateTimeEdit *tmpdatetime = qobject_cast<QDateTimeEdit *>( pTmpWidget );
        QComboBox *tmpcombo = qobject_cast<QComboBox *>( pTmpWidget );
        QCheckBox *tmpcheck = qobject_cast<QCheckBox *>( pTmpWidget );

        if ( tmplineedit )
        {
            qDebug( qPrintable( tmplineedit->objectName() + " " + tmplineedit->text() ) );
            insertQuery.bindValue( ":" + tmplineedit->objectName(), tmplineedit->text() );
        }
        else if ( tmptextedit )
        {
            qDebug( qPrintable( tmptextedit->objectName() + " " + tmptextedit->toPlainText() ) );
            insertQuery.bindValue( ":" + tmptextedit->objectName(), tmptextedit->toPlainText() );
        }
        else if ( tmpdatetime )
        {
            qDebug( qPrintable( tmpdatetime->objectName() + " " + tmpdatetime->dateTime().toString( "yyyy-MM-dd hh:mm:00.000" ) ) );
            insertQuery.bindValue( ":" + tmpdatetime->objectName(), tmpdatetime->dateTime().toString( "yyyy-MM-dd hh:mm:00.000" ) );
        }
        else if ( tmpcombo )
        {
            qDebug( qPrintable( tmpcombo->objectName() + " " + tmpcombo->currentText() ) );
            insertQuery.bindValue( ":" + tmpcombo->objectName(), tmpcombo->currentText() );
        }
        else if ( tmpcheck )
        {
            qDebug( qPrintable( tmpcheck->objectName() + " " + tmpcheck->isChecked() ) );
            insertQuery.bindValue( ":" + tmpcheck->objectName(), tmpcheck->isChecked() );
        }
    }

    if ( !query( insertQuery ) )
    {
        qWarning( "Database Manager: Could not insert table '%s': %s",
                  qPrintable( sTableName ), qPrintable( insertQuery.lastError().text() ) );
        return -1;
    }

    int iID = insertQuery.lastInsertId().toInt();

    qDebug( "Database Manager: Inserted into table '%s' entry #%d.", qPrintable( sTableName), iID );

    return iID;
}

bool DatabaseManager::updateUI( int iID, QString sTableName, QWidget *pWidget, QString sTabName )
{
    QList<QWidget *> lWidgets = getWidgets( pWidget, sTabName );
    QWidget *pTmpWidget;

    QSqlQuery updateQuery;
    updateQuery.prepare( _queryMap[sTableName]["update"] );

    foreach ( pTmpWidget, lWidgets )
    {
        QLineEdit *tmplineedit = qobject_cast<QLineEdit *>( pTmpWidget );
        QTextEdit *tmptextedit = qobject_cast<QTextEdit *>( pTmpWidget );
        QDateTimeEdit *tmpdatetime = qobject_cast<QDateTimeEdit *>( pTmpWidget );
        QComboBox *tmpcombo = qobject_cast<QComboBox *>( pTmpWidget );
        QCheckBox *tmpcheck = qobject_cast<QCheckBox *>( pTmpWidget );

        if ( tmplineedit )
        {
            updateQuery.bindValue( ":" + tmplineedit->objectName(), tmplineedit->text() );
        }
        else if ( tmptextedit )
        {
            updateQuery.bindValue( ":" + tmptextedit->objectName(), tmptextedit->toPlainText() );
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
            updateQuery.bindValue( ":" + tmpcheck->objectName(), tmpcheck->isChecked() );
        }
    }

    updateQuery.bindValue( ":id", iID );

    if ( !query( updateQuery ) )
    {
        qWarning( "Database Manager: Could not update table '%s' entry #%d: %s",
                  qPrintable( sTableName ), iID, qPrintable( updateQuery.lastError().text() ) );
        return false;
    }

    qDebug( "Database Manager: Updated table '%s' entry #%d.", qPrintable( sTableName), iID );

    return true;
}

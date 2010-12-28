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



DatabaseManager::DatabaseManager(){
    _open=false;
}

DatabaseManager::~DatabaseManager(){
}


/*
   Function: open

   Verifies the database file exists and then opens the database.

   Returns:

      Boolean true upon successfully opening the database,
      false if unsuccesful.

*/
bool DatabaseManager::open(){
    // Use SQLite database driver
    db = QSqlDatabase::addDatabase("QSQLITE");

    // Database file must be located in user home folder in Linux
    #ifdef Q_OS_LINUX
    QString path(QDir::home().path());
    path.append(QDir::separator()).append(filepath);
    path = QDir::toNativeSeparators(path);
    if(QFile::exists(path)){
        qDebug("Database file exists.");
    }
    else{
        qDebug("Database file does not exist.");
    }
    db.setDatabaseName(path);


    #else
    if(QFile::exists(DATABASE_NAME)){
        qDebug("Database file exists.");
    }
    else{
        qDebug("Database file does not exist.");
    }
    db.setDatabaseName(DATABASE_NAME);
    #endif

    // Open database
    if(db.open()){
        _open=true;
        return true;
    }
    else{
        qDebug("Error opening database: %s",qPrintable(db.lastError().databaseText()));
        return false;
    }
}

/*
   Function: remove

   Deletes the SQLite database file.

   Returns:

      Boolean true upon successfully deleting the file,
      false upon failure.

   See Also:

      <Divide>
*/
bool DatabaseManager::remove(){
    // Close database
    db.close();

    #ifdef Q_OS_LINUX
    // NOTE: We have to store database file into user home folder in Linux
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("fdms.db");
    path = QDir::toNativeSeparators(path);
    return QFile::remove(path);
    #else

    // Remove created database binary file
    return QFile::remove("fdms.db");
    #endif
}


/*
   Function: init_structure

   Creates the tables in the SQLite database.

   Returns:

      Boolean true upon success, false upon failure.

   See Also:

      verify_structure
*/
bool DatabaseManager::init_structure(){
    QSqlQuery query;
    QString strQuery;
    strQuery=""
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
                 "checked INTEGER)";


    // QSqlQuery::exec with SQLite will not execute multiple queries in a single execution.
    // Split the compound query into individual queries and execute each
    QStringList strQueries=strQuery.split(";");
    for(int i=0;i<strQueries.size();i++){
        if(query.exec(strQueries[i])){
            qDebug("Database Structure Initialization: %s",qPrintable(query.lastQuery()));
        }
        else{
            qDebug("Database Structure Initialization: %s",qPrintable(query.lastError().databaseText()));
            return false;
        }
    }
    return true;
}


/*
   Function: verify_structure

   Verify that the loaded database file follows the specified schema.

   Returns:

      Boolean true if the database structure is verified correct,
      false upon failure.

   See Also:

      create_structure
*/
bool DatabaseManager::verify_structure(){
    QSqlQuery qryTableNames;
    QSqlQuery qryTableInfo;
    QString TableSchema;

    // While we're here, let's turn on foreign key support
    qryTableNames.exec("PRAGMA foreign_keys = ON;");

    // Get list of tables in database, loop through each
    qryTableNames.exec("select tbl_name from sqlite_master;");
    while(qryTableNames.next()){

        // Append the table name, column names and datatypes to TableSchema string
        qryTableInfo.exec("pragma table_info(" + qryTableNames.value(0).toString() + ")");
        TableSchema.append(qryTableNames.value(0).toString());

        while(qryTableInfo.next()){
            // The pragma table_info query returns five columns
            //  regarding the columns in the table queried:
            //  Index, Name, Datatype, Null, Default

            // Name and Datatype are relevant here
            TableSchema.append(qryTableInfo.value(1).toString());
            TableSchema.append(qryTableInfo.value(2).toString());
        }
    }

    // Calculate the md5 hash of this string
    QByteArray md5bytearray(
            QCryptographicHash::hash(TableSchema.toAscii(),
            QCryptographicHash::Md5));

    QString chksum=md5bytearray.toHex().constData();


    //qDebug()<<chksum;
    //qDebug()<<TableSchema;


    // And compare to expected value
    if(chksum!="39003742eb44f06fa70c9ad111dc2147"){
        return false;
    }

    return true;
}

/*
   Function: lastError

   Wrapper to return the SQLite database last error.

   Returns:

      QSqlError  returned by the SQLite database.

*/
QSqlError DatabaseManager::lastError(){
    return db.lastError();
}


/*
   Function: query

   Executes a query through the database.

   Parameters:

      query - QSqlQuery which has been prepared and bound upon.

   Returns:

      Bolean true if the query is successfully executed,
      false on failure.

*/
bool DatabaseManager::query(QSqlQuery query){
   QSqlQuery queryobject=query;
   bool ret=queryobject.exec();
   qDebug("Database Query: %s",qPrintable(queryobject.executedQuery()));
   return ret;
}

/*
   Function: isOpen

   Checks if the database is open or not.

   Returns:

      Bolean true if the database is open, false if closed.

*/
bool DatabaseManager::isOpen(){
    return _open;

}


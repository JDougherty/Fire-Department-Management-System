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


// init_structure()
//   Create the database schema for the SQLite database file
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
                 "tdate TEXT);"
             "CREATE TABLE equipment"
                 "(id INTEGER PRIMARY KEY,"
                 "title TEXT);"
             "CREATE TABLE ffequipment"
                 "(id INTEGER PRIMARY KEY,"
                 "eqid INTEGER,"
                 "fid INTEGER,"
                 "issued INTEGER,"
                 "size TEXT,"
                 "type TEXT,"
                 "serial TEXT,"
                 "year TEXT);"
             "CREATE TABLE drills"
                 "(id INTEGER PRIMARY KEY, "
                 "location TEXT,"
                 "inhouse INTEGER,"
                 "description TEXT,"
                 "starttime INTEGER,"
                 "endtime INTEGER,"
                 "incidentcommander TEXT,"
                 "drillnum TEXT);"
             "CREATE TABLE inventory"
                 "(id INTEGER PRIMARY KEY,"
                 "barcode TEXT,"
                 "name TEXT,"
                 "description TEXT,"
                 "category TEXT);";


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


// verify_structure
//  Verify that the loaded database file follows the specified schema
bool DatabaseManager::verify_structure(){
    QSqlQuery qryTableNames;
    QSqlQuery qryTableInfo;
    QString TableSchema;

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
    if(chksum!="d4c1086743f4e0c05ce7e3869c56afc3"){
        return false;
    }

    return true;
}







QSqlError DatabaseManager::lastError(){
    return db.lastError();
}


bool DatabaseManager::query(QSqlQuery query){
   QSqlQuery queryobject=query;
   bool ret=queryobject.exec();
   qDebug("Database Query: %s",qPrintable(queryobject.executedQuery()));
   return ret;
}

bool DatabaseManager::isOpen(){
    return this->_open;

}

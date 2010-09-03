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

#include "databasemanager.h"



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
        qDebug()<<"Notice - Database: Database file exists.";
    }
    else{
        qDebug()<<"Notice - Database: Database file does not exist.";
    }
    db.setDatabaseName(path);


    #else
    if(QFile::exists(DATABASE_NAME)){
        qDebug()<<"Notice - Database: Database file exists.";
    }
    else{
        qDebug()<<"Notice - Database: Database file does not exist.";
    }
    db.setDatabaseName(DATABASE_NAME);
    #endif

    // Open database
    if(db.open()){
        _open=true;
        return true;
    }
    else{
        qDebug()<<"Error: "<<db.lastError();
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
                 "(name varchar(128),"
                 "address varchar(128));"
             "CREATE TABLE firefighters"
                 "(id integer primary key,"
                 "fname varchar(64),"
                 "mname varchar(64),"
                 "lname varchar(64),"
                 "dob TEXT,"
                 "deptid varchar(32),"
                 "stateid varchar(32),"
                 "address varchar(128),"
                 "city varchar(32),"
                 "state varchar(2),"
                 "zip varchar(5),"
                 "joindate TEXT,"
                 "status varchar(32),"
                 "hphone varchar(16),"
                 "wphone varchar(16),"
                 "cphone varchar(16),"
                 "drvlic varchar(16),"
                 "cdl varchar(16));"
            "CREATE TABLE drills"
                 "(id integer primary key, "
                 "location varchar(128),"
                 "inhouse integer,"
                 "description text,"
                 "starttime integer,"
                 "endtime integer,"
                 "incidentcommander varchar(192),"
                 "drillnum varchar(16))";

    // QSqlQuery::exec and SQLite will not execute multiple queries in a single execution.
    // Split the compound query into individual queries and execute each
    QStringList strQueries=strQuery.split(";");
    for(int i=0;i<strQueries.size();i++){
        if(query.exec(strQueries[i])){
            qDebug()<<query.lastQuery();
        }
        else{
            qDebug()<<query.lastError();
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

    qDebug()<<chksum;
    qDebug()<<TableSchema;

    // And compare to expected value
    if(chksum!="09489c49bf0fc14fe4bf0c49d1f7110e"){
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
   qDebug()<<queryobject.executedQuery();
   return ret;
}

bool DatabaseManager::isOpen(){
    return this->_open;

}

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

#include "../headers/firefighter.h"
#include <QMessageBox>
Firefighter::Firefighter()
{

}

Firefighter::Firefighter(QVector<QString> nattributes){
    attributes=nattributes;
}


bool Firefighter::LoadAttributes(QString localid, DatabaseManager *newDb){
    attributes.clear();

    if(!(newDb->isOpen())){
        newDb->open();
    }
    QSqlQuery infoQuery;
    infoQuery.prepare("SELECT id,fname,mname,lname,"
                      "dob,deptid,stateid,"
                      "address,city,state,"
                      "zip,joindate,status,"
                      "hphone,wphone,cphone,"
                      "drvlic,cdl FROM firefighters WHERE deptid=?");
    infoQuery.addBindValue(localid);


    if(newDb->query(infoQuery)){
        infoQuery.next();
        id=infoQuery.value(0).toInt();
        for(int i=1;i<=18;i++){
            attributes.push_back(infoQuery.value(i).toString());
        }
        return true;
    }
    else{
        return false;
    }
}

bool Firefighter::InsertToDatabase(DatabaseManager *newDb){
    if(!(newDb->isOpen())){
        newDb->open();
    }
    QSqlQuery addQuery;
    addQuery.prepare("INSERT INTO firefighters "
                     "(fname,mname,lname,"
                     "dob,deptid,stateid,"
                     "address,city,state,"
                     "zip,joindate,status,"
                     "hphone,wphone,cphone,"
                     "drvlic,cdl) VALUES "
                     "(?,?,?,"
                     "?,?,?,"
                     "?,?,?,"
                     "?,?,?,"
                     "?,?,?,"
                     "?,?)");
    for(int i=0; i<attributes.size();i++){
        addQuery.addBindValue(attributes[i]);
    }
    if(newDb->query(addQuery)){
        return true;}
    else{
        return false;}

}

bool Firefighter::UpdateInDatabase(QVector<QString> nattributes, DatabaseManager *newDb){
    if(!(newDb->isOpen())){
        newDb->open();
    }

    attributes=nattributes;

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE firefighters SET "
                     "fname=?,mname=?,lname=?,"
                     "dob=?,deptid=?,stateid=?,"
                     "address=?,city=?,state=?,"
                     "zip=?,joindate=?,status=?,"
                     "hphone=?,wphone=?,cphone=?,"
                     "drvlic=?,cdl=? WHERE id=? ");
    for(int i=0; i<attributes.size();i++){
        updateQuery.addBindValue(attributes[i]);
    }

    updateQuery.addBindValue(id);

    if(newDb->query(updateQuery)){
        return true;}
    else{
        qDebug("Database Error: %s",qPrintable(updateQuery.lastError().text()));
        return false;}
}



// ACCESSORS
int Firefighter::ID(){
    return id;
}

QString Firefighter::FirstName(){
    return attributes[0];
}

QString Firefighter::MiddleName(){
    return attributes[1];
}

QString Firefighter::LastName(){
    return attributes[2];
}

QString Firefighter::Dob(){
    return attributes[3];
}

QString Firefighter::LocalID(){
    return attributes[4];
}

QString Firefighter::StateID(){
    return attributes[5];
}

QString Firefighter::Address(){
    return attributes[6];
}

QString Firefighter::City(){
    return attributes[7];
}

QString Firefighter::State(){
    return attributes[8];
}

QString Firefighter::ZipCode(){
    return attributes[9];
}

QString Firefighter::dateJoin(){
    return attributes[10];
}

QString Firefighter::Status(){
    return attributes[11];
}

QString Firefighter::Hphone(){
    return attributes[12];
}

QString Firefighter::Wphone(){
    return attributes[13];
}

QString Firefighter::Cphone(){
    return attributes[14];
}

QString Firefighter::DrvLic(){
    return attributes[15];
}

QString Firefighter::CDL(){
    return attributes[16];
}

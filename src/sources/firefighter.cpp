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

/*
   Function: loadAttributes

   Loads the attributes for firefighter with the given id
   from the database.

   Parameters:

      QString localid - The department id of the firefighter.
      DatabaseManager *newDb - The database from which to load

   Returns:

      Boolean true upon successful load, false on failure.
*/
bool Firefighter::loadAttributes(int id, DatabaseManager *newDb){
    // Clear current attributes
    attributes.clear();

    // Verify the database is open
    if(!(newDb->isOpen())){
        newDb->open();
    }

    // Create the query with parameterization
    QSqlQuery infoQuery;
    infoQuery.prepare("SELECT id,fname,mname,lname,"
                      "dob,deptid,stateid,"
                      "address,city,state,"
                      "zip,joindate,status,"
                      "hphone,wphone,cphone,"
                      "drvlic,cdl FROM firefighters WHERE id=?");
    infoQuery.addBindValue(id);

    // Execute the query
    if(newDb->query(infoQuery)){
        infoQuery.next();
        this->id=infoQuery.value(0).toInt();
        for(int i=1;i<=18;i++){
            attributes.push_back(infoQuery.value(i).toString());
        }
        qDebug("Firefighter Information (%d): Personal information retrieved successfully. ",ID());
        return true;
    }
    else{
        qWarning("Firefighter Error (%d): Could not retrieve personal information from database. Database Error: %s",ID(),qPrintable(infoQuery.lastError().text()));
        return false;
    }
}

/*
   Function: insertToDatabase

   Creates the firefighter in the database with its
   current attributes.

   Parameters:

      DatabaseManager *newDb - The database in which to save

   Returns:

      Boolean true upon successful save, false on failure.
*/
bool Firefighter::insertToDatabase(DatabaseManager *newDb){
    // Ensure the database is open
    if(!(newDb->isOpen())){
        newDb->open();
    }

    // Create the query with parameterization
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

    // Execute the query
    if(newDb->query(addQuery)){
        qDebug("Firefighter Information: New firefighter added successfully. ");
        return true;}
    else{
        qWarning("Firefighter Error: Could not add firefighter to database. Database Error: %s",qPrintable(addQuery.lastError().text()));
        return false;}

}

/*
   Function: updateAttributes

   Set the firefighter's attributes and update in the
   database.

   Parameters:

      QVector<QString> nattributes - List of new attributes
      DatabaseManager *newDb - The database in which to update

   Returns:

      Boolean true upon successful save, false on failure.
*/
bool Firefighter::updateAttributes(QVector<QString> nattributes, DatabaseManager *newDb){
    // Ensure the database is open
    if(!(newDb->isOpen())){
        newDb->open();
    }

    // Set the attributes
    attributes=nattributes;

    // Create the query with parameterization
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

    // Execute the query
    if(newDb->query(updateQuery)){
        qDebug("Firefighter Information (%d): Firefighter successfully updated in database.",ID());
        return true;}
    else{
        qWarning("Firefighter Error (%d): Could not update firefighter information in database. Database Error: %s",ID(),qPrintable(updateQuery.lastError().text()));
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

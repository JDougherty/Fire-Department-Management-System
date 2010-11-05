#include "firefighter.h"
#include <QMessageBox>
Firefighter::Firefighter()
{

}

Firefighter::Firefighter(int uid){

}

Firefighter::Firefighter(QVector<QString> nattributes){
    attributes=nattributes;
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

    /*
    addQuery.addBindValue(FirstName);
    addQuery.addBindValue(MiddleName);
    addQuery.addBindValue(LastName);
    addQuery.addBindValue(Dob);
    addQuery.addBindValue(LocalID);
    addQuery.addBindValue(StateID);
    addQuery.addBindValue(Address);
    addQuery.addBindValue(City);
    addQuery.addBindValue(State);
    addQuery.addBindValue(ZipCode);
    addQuery.addBindValue(dateJoin);
    addQuery.addBindValue(Status);
    addQuery.addBindValue(Hphone);
    addQuery.addBindValue(Wphone);
    addQuery.addBindValue(Cphone);
    addQuery.addBindValue(DrvLic);
    addQuery.addBindValue(CDL);
    */

    if(newDb->query(addQuery)){
        return true;}
    else{
        return false;}

}


// ACCESSORS
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

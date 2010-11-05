#ifndef FIREFIGHTER_H
#define FIREFIGHTER_H
#include "databasemanager.h"
#include <QVector>

class Firefighter
{
public:
    Firefighter();
    Firefighter(int uid);
    Firefighter(QVector<QString> nattributes);
    bool InsertToDatabase(DatabaseManager *newDb=0);



    // accessors
    QString FirstName();
    QString MiddleName();
    QString LastName();
    QString Dob();
    QString LocalID();
    QString StateID();
    QString Address();
    QString City();
    QString State();
    QString ZipCode();
    QString dateJoin();
    QString Status();
    QString Hphone();
    QString Wphone();
    QString Cphone();
    QString DrvLic();
    QString CDL();

private:
    QVector<QString> attributes;
};

#endif // FIREFIGHTER_H

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

#ifndef FIREFIGHTER_H
#define FIREFIGHTER_H
#include "databasemanager.h"
#include <QVector>

class Firefighter
{
public:
    Firefighter();
    Firefighter(QVector<QString> nattributes);
    bool InsertToDatabase(DatabaseManager *newDb=0);
    bool LoadAttributes(QString uid, DatabaseManager *newDb=0);
    bool UpdateInDatabase(QVector<QString> nattributes, DatabaseManager *newDb);


    // accessors
    int ID();
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
    int id;
};

#endif // FIREFIGHTER_H

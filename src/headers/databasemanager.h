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
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#define DATABASE_NAME "fdms.db"

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QSqlQuery>
#include <QVariant>
#include <QtDebug>
#include <QCryptographicHash>


class DatabaseManager : public QObject{
    public:
        DatabaseManager();
        ~DatabaseManager();


    public:
        bool open();
        bool remove();
        bool init_structure();
        bool verify_structure();
        bool query(QSqlQuery query);
        bool isOpen();


        QSqlError lastError();


    private:
        QSqlDatabase db;
        bool _open;
};


#endif

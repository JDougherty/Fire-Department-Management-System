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


#include <QtGui/QApplication>
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QDateTime>
#include "databasemanager.h"
#include "LogFunctions.h"
#include "mainwindow.h"
#include "wndnewfirefighter.h"
#include "wndsetup.h"
#include "wndActiveDrill.h"
#include "wndsplash.h"


/*
// INT MAIN FOR TESTING FORM DESIGN IN APPLICATION
int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    wndSearch w;
    w.show();
    return a.exec();
}
*/




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDateTime initstamp=QDateTime::currentDateTime();
    QString filename = "fdms.db";
    DatabaseManager db;

    setupDebugRedirection();
    qDebug("Initialized at %s",initstamp.toString().toStdString().c_str());

    MainWindow splash(0);
    splash.show();

    // Load existing databse
    if(QFile::exists(filename)){
        if(db.open()){
            qDebug("Verifying database structure.");
            if(db.verify_structure()){
                qDebug("Valid database structure.");
                wndNewFirefighter newfirefighter;
                newfirefighter.show();
            }
            else{
                QMessageBox::critical(&splash,"Critical Error","Database exists but has invalid structure.",QMessageBox::Ok);
                qCritical("Invalid database structure.");
                return 0;

            }
        }
        else{
            QMessageBox::critical(&splash,"Critical Error","Database exists but could not be opened.",QMessageBox::Ok);
            qCritical("Critical Error - Database: Database could not be opened. Exiting.");
            return 0;
        }
    }
    else{
        qDebug("Running program setup. ");
        db.open();
        db.init_structure();
        wndSetup setup;
        setup.show();
    }


    return a.exec();
}

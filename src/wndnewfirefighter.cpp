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


#include "wndnewfirefighter.h"
#include "ui_wndnewfirefighter.h"


wndNewFirefighter::wndNewFirefighter(QWidget *parent, DatabaseManager *newDb) :
    QMainWindow(parent),
    ui(new Ui::wndNewFirefighter)
{
    ui->setupUi(this);
    db=newDb;
}

wndNewFirefighter::~wndNewFirefighter()
{
    delete ui;
}

void wndNewFirefighter::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void wndNewFirefighter::btnAdd_Clicked(){
    if(!(db->isOpen())){
        db->open();
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
    addQuery.addBindValue(ui->txtFirstName->text());
    addQuery.addBindValue(ui->txtMiddleName->text());
    addQuery.addBindValue(ui->txtLastName->text());
    addQuery.addBindValue(ui->dateDob->date().toString("yyyy-MM-dd 00:00:00.000"));
    addQuery.addBindValue(ui->txtLocalID->text());
    addQuery.addBindValue(ui->txtStateID->text());
    addQuery.addBindValue(ui->txtAddress->text());
    addQuery.addBindValue(ui->txtCity->text());
    addQuery.addBindValue(ui->txtState->itemText(0));
    addQuery.addBindValue(ui->txtZipCode->text());
    addQuery.addBindValue(ui->dateJoin->date().toString("yyyy-MM-dd 00:00:00.000"));
    addQuery.addBindValue(ui->txtStatus->text());
    addQuery.addBindValue(ui->txtHphone->text());
    addQuery.addBindValue(ui->txtWphone->text());
    addQuery.addBindValue(ui->txtCphone->text());
    addQuery.addBindValue(ui->txtDrvLic->text());
    addQuery.addBindValue(ui->txtCDL->text());

    if(db->query(addQuery)){
        qDebug("New firefighter added successfully. ");
    }
    else{
        qWarning("Firefighter not added. %s",qPrintable(db->lastError().databaseText()));
    }
}

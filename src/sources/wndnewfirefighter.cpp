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


#include "../headers/wndnewfirefighter.h"
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
    QVector<QString> ffattributes;

    // Build attribute list for firefighter based on forms
    ffattributes.append(ui->txtFirstName->text());
    ffattributes.append(ui->txtMiddleName->text());
    ffattributes.append(ui->txtLastName->text());
    ffattributes.append(ui->dateDob->date().toString("yyyy-MM-dd 00:00:00.000"));
    ffattributes.append(ui->txtLocalID->text());
    ffattributes.append(ui->txtStateID->text());
    ffattributes.append(ui->txtAddress->text());
    ffattributes.append(ui->txtCity->text());
    ffattributes.append(ui->txtState->itemText(ui->txtState->currentIndex()));
    ffattributes.append(ui->txtZipCode->text());
    ffattributes.append(ui->dateJoin->date().toString("yyyy-MM-dd 00:00:00.000"));
    ffattributes.append(ui->txtStatus->text());
    ffattributes.append(ui->txtHphone->text());
    ffattributes.append(ui->txtWphone->text());
    ffattributes.append(ui->txtCphone->text());
    ffattributes.append(ui->txtDrvLic->text());
    ffattributes.append(ui->txtCDL->text());

    // Construct new firefighter with attributes
    Firefighter newFF(ffattributes);

    if(newFF.InsertToDatabase(this->db)){
        qDebug("New firefighter added successfully. ");
        QMessageBox::information(0,"Database Operation","Firefighter successfully added to database!");
    }
    else{
        QMessageBox::warning(0,"Database Operation","Firefighter was not added to database! See log file for details.");
    }
}

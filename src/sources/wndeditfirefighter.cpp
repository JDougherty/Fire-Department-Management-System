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

#include "../headers/wndeditfirefighter.h"
#include "ui_wndeditfirefighter.h"
#include<QMessageBox>
wndEditFirefighter::wndEditFirefighter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wndEditFirefighter)
{
    ui->setupUi(this);
}


wndEditFirefighter::wndEditFirefighter(QWidget *parent, DatabaseManager *newDb, QString ffid):
        QMainWindow(parent),
        ui(new Ui::wndEditFirefighter)
    {
        ui->setupUi(this);

        Firefighter *edit = new Firefighter;
        edit->LoadAttributes(ffid,newDb);
        ui->txtFirstName->setText(edit->FirstName());
        ui->txtMiddleName->setText(edit->MiddleName());
        ui->txtLastName->setText(edit->LastName());
        ui->dateDob->setDate(QVariant(edit->Dob()).toDate());
        ui->txtLocalID->setText(edit->LocalID());
        ui->txtStateID->setText(edit->StateID());
        ui->txtAddress->setText(edit->Address());
        ui->txtCity->setText(edit->City());
        ui->txtState->setCurrentIndex(ui->txtState->findText(edit->State()));
        ui->txtZipCode->setText(edit->ZipCode());
        ui->dateJoin->setDate(QVariant(edit->dateJoin()).toDate());
        ui->txtStatus->setText(edit->Status());
        ui->txtHphone->setText(edit->Hphone());
        ui->txtWphone->setText(edit->Wphone());
        ui->txtCphone->setText(edit->Cphone());
        ui->txtDrvLic->setText(edit->DrvLic());
        ui->txtCDL->setText(edit->CDL());
    }

wndEditFirefighter::~wndEditFirefighter()
{
    delete ui;
}

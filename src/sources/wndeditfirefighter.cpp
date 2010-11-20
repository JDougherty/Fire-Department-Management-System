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
        db=newDb;

        edit = new Firefighter;
        edit->LoadAttributes(ffid,db);

        updateFirefighterFields();
        updateTrainingList();

        connect(ui->btnUpdatePersonal,SIGNAL(clicked()),this,SLOT(btnUpdatePersonalClicked()));

    }


void wndEditFirefighter::btnUpdatePersonalClicked(){
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

    if(edit->UpdateInDatabase(ffattributes,db)){
        QMessageBox::information(this,"Firefighter: Update Successful","Firefighter was successfully updated in database!");
    }
    else{
        QMessageBox::warning(this,"Firefighter: Update Failed","Firefighter information failed to update! Check log for more information.");
    }


}

void wndEditFirefighter::updateFirefighterFields(){
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

void wndEditFirefighter::updateTrainingList(){


    QSqlQuery traininglist;
    traininglist.prepare("SELECT training.title,fft.tid "
                         "FROM training LEFT JOIN ("
                           "SELECT * FROM fftraining WHERE ffid=?) as fft ON "
                         "training.id=fft.tid");
    traininglist.addBindValue(edit->ID());
    if(db->query(traininglist)){
        while(traininglist.next()){
            QListWidgetItem *newitem = new QListWidgetItem(traininglist.value(0).toString());
            if(traininglist.value(1).toString()!=""){
                newitem->setCheckState(Qt::Checked);
            }
            else{
                newitem->setCheckState(Qt::Unchecked);
            }
            ui->lstTraining->addItem(newitem);

        }
    }
    else{
        qDebug("Error! Could not get training information!");
    }
}

wndEditFirefighter::~wndEditFirefighter()
{
    delete ui;
    delete edit;
}

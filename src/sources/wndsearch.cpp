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

#include "../headers/wndsearch.h"
#include "ui_wndsearch.h"
#include <QMessageBox>
#include "../headers/mainwindow.h"
wndSearch::wndSearch(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wndSearch)
{
    ui->setupUi(this);
}

wndSearch::wndSearch(QWidget *parent,
                     MainWindow *nmdiparent,
                     DatabaseManager *newDb, QString newdtype,QString query) :
        QMainWindow(parent),
        ui(new Ui::wndSearch)
{
    db=newDb;
    dtype=newdtype;
    mdiparent=nmdiparent;

    ui->setupUi(this);
    this->setWindowTitle(this->windowTitle() + dtype);

    ui->tblResults->horizontalHeader()->setStretchLastSection( true );
    ui->tblResults->setEditTriggers(0);

    if(dtype=="Firefighters"){
        ui->tblResults->setHorizontalHeaderLabels(QStringList()<<"ID"<<"Last Name"<<"First Name");
        Search(dtype,query);
    }
    else if(dtype=="Drills"){
        ui->tblResults->setHorizontalHeaderLabels(QStringList()<<"ID"<<"Date"<<"Location");
    }
    else if(dtype=="Calls"){
        ui->tblResults->setHorizontalHeaderLabels(QStringList()<<"ID"<<"Date"<<"Location");
    }


    connect(ui->tblResults->verticalHeader(),SIGNAL(sectionDoubleClicked(int)),this,SLOT(tableDoubleClicked(int)));



}

void wndSearch::tableDoubleClicked(int tmp){
    QString deptid=ui->tblResults->item(tmp,0)->data(0).toString();
    mdiparent->mdiEditFirefighter(deptid);
}

void wndSearch::Search(QString dtype, QString query){
    QSqlQuery selection;

    if(dtype=="Firefighters"){

        selection.prepare("SELECT deptid,lname,fname FROM firefighters WHERE deptid LIKE ? OR lname LIKE ? or fname LIKE ?");
        selection.addBindValue("%" + query + "%");
        selection.addBindValue("%" + query + "%");
        selection.addBindValue("%" + query + "%");

        db->query(selection);
        while(selection.next()){
            ui->tblResults->setRowCount(ui->tblResults->rowCount()+1);
            ui->tblResults->setVerticalHeaderItem(ui->tblResults->rowCount()-1, new QTableWidgetItem("*"));
            for(int i=0;i<=2;i++){
                ui->tblResults->setItem(ui->tblResults->rowCount()-1, i, new QTableWidgetItem(selection.value(i).toString()));
            }
        }
    }
}




wndSearch::~wndSearch()
{
    delete ui;
}

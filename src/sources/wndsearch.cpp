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
                     DatabaseManager *newDb, QString newdtype,QString newquery) :
        QMainWindow(parent),
        ui(new Ui::wndSearch)
{
    db=newDb;
    dtype=newdtype;
    query=newquery;
    mdiparent=nmdiparent;

    ui->setupUi(this);
    this->setWindowTitle(this->windowTitle() + dtype);

    //ui->tblResults->horizontalHeader()->setStretchLastSection( false );


    if(dtype=="Firefighters"){
       headers=QStringList()<<"ID"<<"Last Name"<<"First Name";
    }
    else if(dtype=="Drills"||dtype=="Calls"){
        headers=QStringList()<<"ID"<<"Date"<<"Location";
    }

    Search(dtype,query);


    connect(ui->tblResults,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(tableDoubleClicked(QModelIndex)));
    connect(ui->btnRefresh,SIGNAL(clicked()),this,SLOT(refreshClicked()));
    connect(ui->btnShowAll,SIGNAL(clicked()),this,SLOT(showAllClicked()));



}

void wndSearch::tableDoubleClicked(QModelIndex tmp){
    QString deptid=tmp.sibling(tmp.row(),0).data().toString();
    qDebug("%s",qPrintable(deptid));

}

void wndSearch::Search(QString dtype, QString query){

    QSqlQuery selection;

    if(dtype=="Firefighters"){
        QString querystring="SELECT deptid,lname,fname FROM firefighters";
        if(query!=""){
            querystring+=" WHERE deptid LIKE ? OR lname LIKE ? or fname LIKE ?";
            selection.prepare(querystring);
            selection.addBindValue("%" + query + "%");
            selection.addBindValue("%" + query + "%");
            selection.addBindValue("%" + query + "%");
        }
        else{
            selection.prepare(querystring);
        }

    }
    else if(dtype=="Drills"){
        QString querystring="SELECT drillnum,strftime('%m/%d/%Y',starttime),location FROM drills";
        if(query!=""){
            querystring+=" WHERE drillnum LIKE ? OR location LIKE ?";
            selection.prepare(querystring);
            selection.addBindValue("%" + query + "%");
            selection.addBindValue("%" + query + "%");
        }
        else{
            selection.prepare(querystring);
        }
    }

    db->query(selection);

    QSqlQueryModel *searchModel = new QSqlQueryModel;
    searchModel->setQuery(selection);

    searchModel->setHeaderData(0, Qt::Horizontal, headers[0]);
    searchModel->setHeaderData(1, Qt::Horizontal, headers[1]);
    searchModel->setHeaderData(2, Qt::Horizontal, headers[2]);

    // Set options for the QTableView
    ui->tblResults->setModel(searchModel);
    ui->tblResults->horizontalHeader()->setResizeMode(0,QHeaderView::Stretch);
    ui->tblResults->horizontalHeader()->setResizeMode(1,QHeaderView::Stretch);
    ui->tblResults->horizontalHeader()->setResizeMode(2,QHeaderView::Stretch);
    ui->tblResults->horizontalHeader()->show();
    ui->tblResults->verticalHeader()->hide();
    ui->tblResults->setEditTriggers(0);
}




wndSearch::~wndSearch()
{
    delete ui;
}

// PRIVATE SLOTS:

void wndSearch::refreshClicked(){
    Search(dtype,query);
}

void wndSearch::showAllClicked(){
    Search(dtype,"");
}

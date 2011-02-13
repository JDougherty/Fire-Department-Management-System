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

    if(dtype=="Firefighters"){
       headers=QStringList()<<"ID"<<"Last Name"<<"First Name";
    }
    else if(dtype=="Drills"||dtype=="Calls"){
        headers=QStringList()<<"ID"<<"Date"<<"Location";
    }

    Search(dtype,query);

    ui->tblResults->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tblResults,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(tableDoubleClicked(QModelIndex)));
    connect(ui->tblResults,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(resultsContextMenu(const QPoint &)));
    connect(ui->btnRefresh,SIGNAL(clicked()),this,SLOT(refreshClicked()));
    connect(ui->btnShowAll,SIGNAL(clicked()),this,SLOT(showAllClicked()));

}


wndSearch::~wndSearch()
{
    delete ui;
}


void wndSearch::Search(QString dtype, QString query){

    QSqlQuery selection;

    if(dtype=="Firefighters"){
        QString querystring="SELECT id,deptid,lname,fname FROM firefighters";
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
        QString querystring="SELECT id,drillnum,strftime('%m/%d/%Y',starttime),location FROM drills";
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

    else if(dtype=="Calls"){
        QString querystring="SELECT id,incidentnumber,strftime('%m/%d/%Y',alarm),location FROM calls";
        if(query!=""){
            querystring+=" WHERE incidentnumber LIKE ? OR location LIKE ?";
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

    searchModel->setHeaderData(1, Qt::Horizontal, headers[0]);
    searchModel->setHeaderData(2, Qt::Horizontal, headers[1]);
    searchModel->setHeaderData(3, Qt::Horizontal, headers[2]);

    // Apply the model to the table
    ui->tblResults->setModel(searchModel);

    // Set columns to stretch to percentage of width of window
    ui->tblResults->horizontalHeader()->setResizeMode(0,QHeaderView::Stretch);
    ui->tblResults->horizontalHeader()->setResizeMode(1,QHeaderView::Stretch);
    ui->tblResults->horizontalHeader()->setResizeMode(2,QHeaderView::Stretch);

    // Show the column header, hide the row header
    ui->tblResults->horizontalHeader()->show();
    ui->tblResults->verticalHeader()->hide();

    // Do not allow editing
    ui->tblResults->setEditTriggers(0);

    // Hide the primary key column
    ui->tblResults->hideColumn(0);
}


// PRIVATE SLOTS:

void wndSearch::tableDoubleClicked(QModelIndex tmp){
    QString id=tmp.sibling(tmp.row(),0).data().toString();
    if(dtype=="Firefighters"){
        mdiparent->mdiEditFirefighter(id.toInt());
    }
    if(dtype=="Drills"){
        mdiparent->mdiEditDrill(id.toInt());
    }
    if(dtype=="Calls"){
        mdiparent->mdiEditCall(id.toInt());
    }
}

void wndSearch::refreshClicked(){
    Search(dtype,query);
}

void wndSearch::showAllClicked(){
    Search(dtype,"");
}

void wndSearch::resultsContextMenu(const QPoint &pos){
    QMenu *menu = new QMenu;
    QModelIndex cell = ui->tblResults->indexAt(pos);
    if(cell.isValid()){
        lastCellRightClicked=cell;

        menu->addAction("Delete", this, SLOT(resultsDeleteDatum()));
        menu->exec(ui->tblResults->mapToGlobal(pos));
    }
}

void wndSearch::resultsDeleteDatum(){
    QString id=lastCellRightClicked.sibling(lastCellRightClicked.row(),0).data().toString();
    if(dtype=="Firefighters"){
        if(QMessageBox::question(0,"Firefighter Delete","Are you sure you wish to delete this firefighter?",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
            QSqlQuery deleteFirefighter;
            deleteFirefighter.prepare("DELETE FROM firefighters WHERE id=?");
            deleteFirefighter.addBindValue(id);
            if(db->query(deleteFirefighter)){
                qDebug("Firefighter Information: Firefighter with department id %s successfully deleted.",qPrintable(id));
                Search(dtype,query);
            }
            else{
                qWarning("Firefighter Information: Firefighter with department id %s could not be deleted. Error: %s",qPrintable(id),qPrintable(deleteFirefighter.lastError().text()));
                QMessageBox::warning(0,"Firefighter Error","Could not delete firefighter with department id "+id+". See log for more information.");
            }
        }
    }
}

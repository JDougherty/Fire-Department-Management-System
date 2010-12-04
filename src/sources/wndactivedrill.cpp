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

#include "../headers/wndactivedrill.h"
#include "ui_wndactivedrill.h"

wndActiveDrill::wndActiveDrill(QWidget *parent,DatabaseManager *newDb) :
    QMainWindow(parent),
    ui(new Ui::wndActiveDrill)
{
    db=newDb;
    drillid=0;

    if(!insert()){
        delete this;
    }

    ui->setupUi(this);

    ui->dateDrillStart->setDateTime(QDateTime::currentDateTime());
    ui->dateDrillEnd->setDateTime(QDateTime::currentDateTime().addSecs(60*60*2));

    ui->txtIDScan->setFocus();

    ui->tblTimesheet->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->btnSaveDrill,SIGNAL(clicked()),this,SLOT(updateInformation()));

    connect(ui->txtIDScan,SIGNAL(returnPressed()),this,SLOT(scanId()));
    connect(ui->btnSignIn,SIGNAL(clicked()),this,SLOT(scanId()));
    connect(ui->tblTimesheet,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(sheetContextMenu(const QPoint &)));


}

wndActiveDrill::~wndActiveDrill()
{
    delete ui;
}

// PRIVATE MEMBERS:

bool wndActiveDrill::insert(){
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT max(id)+1 FROM drills");
    if(db->query(selectQuery)){
        selectQuery.first();
        drillid=selectQuery.value(0).toInt();

        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO drills (id) VALUES (?)");
        insertQuery.addBindValue(selectQuery.value(drillid));

        if(db->query(insertQuery)){
            qDebug("Drill Information: Inserted new drill to database.");
            return true;
        }
        else{
            QMessageBox::warning(0,"Drill Error","Could not insert new drill to database. See log for more information.");
            qWarning("Drill Error (%d): Could not insert new drill to database. Database Error: %s",drillid,qPrintable(insertQuery.lastError().text()));
            return false;
        }
    }
    else{
        QMessageBox::warning(0,"Drill Error","Could not insert new drill to database. See log for more information.");
        qWarning("Drill Error: Could not retrieve new drill ID. Database Error: %s",qPrintable(selectQuery.lastError().text()));
        return false;
    }
}

void wndActiveDrill::updateSheet(){
    QSqlQuery selectSheet;
    selectSheet.prepare("SELECT firefighters.fname||' '||firefighters.lname||' ('||firefighters.deptid||')',"
                        "strftime('%H:%M',drillsheet.timein),strftime('%H:%M',drillsheet.timeout) FROM drillsheet "
                        "JOIN firefighters ON drillsheet.ffid=firefighters.id WHERE did=?");
    selectSheet.addBindValue(drillid);
    db->query(selectSheet);
    QSqlQueryModel *sheetModel = new QSqlQueryModel;
    sheetModel->setQuery(selectSheet);

    sheetModel->setHeaderData(0, Qt::Horizontal, tr("Name (ID)"));
    sheetModel->setHeaderData(1, Qt::Horizontal, tr("Time in"));
    sheetModel->setHeaderData(2, Qt::Horizontal, tr("Time out"));

    // Set options for the QTableView
    ui->tblTimesheet->setModel(sheetModel);
    ui->tblTimesheet->setColumnWidth(0,200);
    ui->tblTimesheet->setColumnWidth(1,80);
    ui->tblTimesheet->setColumnWidth(2,80);
    ui->tblTimesheet->horizontalHeader()->show();
    ui->tblTimesheet->verticalHeader()->hide();

}

// PRIVATE SLOTS:


void wndActiveDrill::updateInformation(){
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE drills SET drillnum=?,location=?,description=?,starttime=?,endtime=?,inhouse=?,incidentcommander=? WHERE id=?");
    updateQuery.addBindValue(ui->txtDrillNum->text());
    updateQuery.addBindValue(ui->txtLocation->toPlainText());
    updateQuery.addBindValue(ui->txtDescription->toPlainText());
    updateQuery.addBindValue(ui->dateDrillStart->dateTime().toString("yyyy-MM-dd hh:mm:00.000"));
    updateQuery.addBindValue(ui->dateDrillEnd->dateTime().toString("yyyy-MM-dd hh:mm:00.000"));
    updateQuery.addBindValue(ui->chkInHouse->isChecked());
    updateQuery.addBindValue(ui->txtIncidentCommander->text());
    updateQuery.addBindValue(drillid);
    if(db->query(updateQuery)){
        qDebug("Drill Information (%d): Drill information successfully updated in database.",drillid);
        QMessageBox::information(0,"Drill Information","Drill information successfully updated in database.");
    }
    else{
        qWarning("Drill Error (%d): Drill information could not be updated in database. Database Error: %s",drillid,qPrintable(updateQuery.lastError().text()));
        QMessageBox::warning(0,"Drill Error","Drill information could not be updated in database. See log for more information.");
    }
}


void wndActiveDrill::scanId(){

    // Get the primary key of the firefighter based on department id
    QSqlQuery selectFirefighter;
    QString ffdeptid = ui->txtIDScan->text();
    int ffid=0;

    selectFirefighter.prepare("SELECT id FROM firefighters WHERE deptid=?");
    selectFirefighter.addBindValue(ffdeptid);

    // Execute query and check for errors
    if(!(db->query(selectFirefighter))){
        qWarning("Drill Error (%d): Could not retrieve id for firefighter with department id %s. Error: %s",drillid,qPrintable(ffdeptid),qPrintable(selectFirefighter.lastError().text()));
        QMessageBox::warning(0,"Drill Error","Could not retrieve id for firefighter with department id '"+ffdeptid+"'. See log for more information.");
        return;
    }

    else{

        // Check if a firefighter was found with the given department id
        if(!(selectFirefighter.first())){
            QMessageBox::information(0,"Drill Information","Firefighter with department id "+ffdeptid+" does not exist.");
            return;
        }

        else{

            // Firefighter found, retrieve primary key id
            ffid=selectFirefighter.value(0).toInt();
        }
    }

    // Check if the firefighter is in the drill sheet for this drill, i.e. signed in or not
    QSqlQuery ffCheck;

    ffCheck.prepare("SELECT * FROM drillsheet WHERE did=? AND ffid=?");
    ffCheck.addBindValue(drillid);
    ffCheck.addBindValue(ffid);

    // Execute query and check for errors
    if(!(db->query(ffCheck))){
        qWarning("Drill Error (%d): Could not check sign in status of firefighter with id %d. Error: %s",drillid,ffid,qPrintable(ffCheck.lastError().text()));
        QMessageBox::warning(0,"Drill Error:","Could not check the sign in status of firefighter with department id '"+ffdeptid+"'. See log for more information.");
        return;
    }

    else{
        // Firefighter is not yet signed in
        if(!ffCheck.first()){
            // Insert the firefighter to the drill sheet, i.e. sign them in
            QSqlQuery insertFirefighterToSheet;

            insertFirefighterToSheet.prepare("INSERT INTO drillsheet (did,ffid,timein) VALUES (?,?,?)");
            insertFirefighterToSheet.addBindValue(drillid);
            insertFirefighterToSheet.addBindValue(ffid);
            insertFirefighterToSheet.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:00.000"));

            // Execute query and check for errors
            if(!(db->query(insertFirefighterToSheet))){
                qWarning("Drill Error (%d): Could not sign in firefighter with id %d. Error: %s",drillid,ffid,qPrintable(ffCheck.lastError().text()));
                QMessageBox::warning(0,"Drill Error:","Could not sign in firefighter with department id '"+ffdeptid+"'. See log for more information.");
                return;
            }
            updateSheet();
        }

        // Firefighter is signed in
        else{
            // Update the firefighter in the drill sheet, i.e. sign them out
            QSqlQuery updateFirefighterInSheet;

            updateFirefighterInSheet.prepare("UPDATE drillsheet SET timeout=? WHERE did=? AND ffid=?");
            updateFirefighterInSheet.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:00.000"));
            updateFirefighterInSheet.addBindValue(drillid);
            updateFirefighterInSheet.addBindValue(ffid);

            // Execute query and check for errors
            if(!(db->query(updateFirefighterInSheet))){
                qWarning("Drill Error (%d): Could not sign out firefighter with id %d. Error: %s",drillid,ffid,qPrintable(ffCheck.lastError().text()));
                QMessageBox::warning(0,"Drill Error:","Could not sign out firefighter with department id '"+ffdeptid+"'. See log for more information.");
                return;
            }
            updateSheet();
        }
    }
}

void wndActiveDrill::sheetContextMenu(const QPoint &pos){
    QMenu *menu = new QMenu;
    QModelIndex cell = ui->tblTimesheet->indexAt(pos);
    if(cell.isValid()){
        lastCellRightClicked=cell;

        menu->addAction("Remove firefighter", this, SLOT(sheetRemoveFirefighter()));
        menu->addAction("Update time in", this, SLOT(sheetRemoveFirefighter()));
        menu->addAction("Update time out", this, SLOT(sheetRemoveFirefighter()));
        menu->exec(ui->tblTimesheet->mapToGlobal(pos));
    }
}

void wndActiveDrill::sheetRemoveFirefighter(){
    QString deptid=lastCellRightClicked.sibling(lastCellRightClicked.row(),0).data().toString();
    if(QMessageBox::question(0,"Drill Confirmation","Are you sure you would like to remove firefighter "+deptid+"?",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
        deptid=deptid.mid(deptid.lastIndexOf("(")+1,deptid.lastIndexOf(")")-deptid.lastIndexOf("(")-1);
        int ffid=0;

        QSqlQuery selectFirefighter;
        selectFirefighter.prepare("SELECT id FROM firefighters WHERE deptid=?");
        selectFirefighter.addBindValue(deptid);

        if(!selectFirefighter.exec()){
            qWarning("Drill Error (%d): Could not retrive id for firefighter with department id %s. Error: %s",drillid,qPrintable(deptid),
                     qPrintable(selectFirefighter.lastError().text()));
            QMessageBox::warning(0,"Drill Error:","Could not retrive id for firefighter with department id "+deptid+". See log for more information.");
            return;
        }
        selectFirefighter.first();
        ffid=selectFirefighter.value(0).toInt();

        QSqlQuery removeFirefighter;
        removeFirefighter.prepare("DELETE FROM drillsheet WHERE did=? and ffid=?");
        removeFirefighter.addBindValue(drillid);
        removeFirefighter.addBindValue(ffid);

        if(!removeFirefighter.exec()){
            qWarning("Drill Error (%d): Could not delete firefighter with id %d from drillsheet. Error: %s",drillid,ffid,
                     qPrintable(selectFirefighter.lastError().text()));
            QMessageBox::warning(0,"Drill Error:","Could not remove firefighter with department id "+deptid+". See log for more information.");
            return;
        }
        updateSheet();
    }
}

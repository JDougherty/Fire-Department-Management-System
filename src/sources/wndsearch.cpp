#include "wndsearch.h"
#include "ui_wndsearch.h"

wndSearch::wndSearch(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wndSearch)
{
    ui->setupUi(this);
}

wndSearch::wndSearch(QWidget *parent, DatabaseManager *newDb, QString dtype,QString query) :
        QMainWindow(parent),
        ui(new Ui::wndSearch)
{
    ui->setupUi(this);
    db=newDb;
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

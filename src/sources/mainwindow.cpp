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


#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, DatabaseManager *newDb) :
    QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
    db=newDb;

    mdiArea = new QMdiArea;
    mdiArea->setBackground(QBrush::QBrush(QColor::QColor(128,0,0)));
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);



    //windowMapper = new QSignalMapper(this);
    //connect(windowMapper, SIGNAL(mapped(QWidget*)),this, SLOT(setActiveSubWindow(QWidget*)));



    connect(ui->actFirefighterAdd, SIGNAL(triggered()), this, SLOT(mdiNewFirefighter()));
    connect(ui->actNew_Drill, SIGNAL(triggered()), this, SLOT(mdiActiveDrill()));

    connect(ui->actSearch, SIGNAL(triggered()), this, SLOT(menuSearchTriggered()));

    QWidget *spacer=new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->toolBar->addWidget(spacer);
    //ui->toolBar->addSeparator();
    ui->toolBar->addWidget(ui->lblSearch);
    ui->toolBar->addWidget(ui->txtSearch);
    ui->toolBar->addWidget(ui->cmbSearch );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
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

void MainWindow::StatusUpdate(QString message, int timeout){
    ui->statusBar->showMessage(message,timeout);
}


void MainWindow::txtSearchReturnPressed(){
    wndSearch *child= new wndSearch(this, this, db, ui->cmbSearch->currentText(), ui->txtSearch->text());
    mdiArea->addSubWindow(child);
    child->show();

}



void MainWindow::menuSearchTriggered()
{
    ui->txtSearch->setFocus();
}

// THESE FUNCTIONS SHOW CHILD MDI WINDOWS
void MainWindow::mdiNewFirefighter()
{
    wndNewFirefighter *child = new wndNewFirefighter(this,db);
    mdiArea->addSubWindow(child);
    child->show();
}


void MainWindow::mdiActiveDrill()
{
    wndActiveDrill *child = new wndActiveDrill;
    mdiArea->addSubWindow(child);
    child->show();
}

void MainWindow::mdiEditFirefighter(QString deptid){
    wndEditFirefighter *child = new wndEditFirefighter(this,db,deptid);
    mdiArea->addSubWindow(child);
    child->show();
}

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


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mdiArea = new QMdiArea;
    mdiArea->setBackground(QBrush::QBrush(QColor::QColor(128,0,0)));
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);



    //windowMapper = new QSignalMapper(this);
    //connect(windowMapper, SIGNAL(mapped(QWidget*)),this, SLOT(setActiveSubWindow(QWidget*)));

    this->showMaximized();


    connect(ui->actFirefighterAdd, SIGNAL(triggered()), this, SLOT(mdiNewFirefighter()));
    connect(ui->actSearch, SIGNAL(triggered()), this, SLOT(mdiSearch()));
    connect(ui->actNew_Drill, SIGNAL(triggered()), this, SLOT(mdiActiveDrill()));


    ui->toolBar->addSeparator();
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


// THESE FUNCTIONS SHOW CHILD MDI WINDOWS
void MainWindow::mdiNewFirefighter()
{
    wndNewFirefighter *child = new wndNewFirefighter;
    mdiArea->addSubWindow(child);
    child->show();
}

void MainWindow::mdiSearch()
{
    wndSearch *child = new wndSearch;
    mdiArea->addSubWindow(child);
    child->show();
}

void MainWindow::mdiActiveDrill()
{
    wndActiveDrill *child = new wndActiveDrill;
    mdiArea->addSubWindow(child);
    child->show();
}


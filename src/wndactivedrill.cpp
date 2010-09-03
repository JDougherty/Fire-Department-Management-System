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

#include "wndActiveDrill.h"
#include "ui_wndActiveDrill.h"
#include <QMessageBox>

wndActiveDrill::wndActiveDrill(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wndActiveDrill)
{
    ui->setupUi(this);

    ui->dateDrillStart->setDate(QDate::currentDate());
    ui->dateDrillEnd->setDate(QDate::currentDate());

    ui->txtDrillNum->setFocus();

    ui->tblTimesheet->setColumnWidth(0,200);
    ui->tblTimesheet->setColumnWidth(1,80);
    ui->tblTimesheet->setColumnWidth(2,80);
    ui->tblTimesheet->horizontalHeader();


}

wndActiveDrill::~wndActiveDrill()
{
    delete ui;
}

void wndActiveDrill::txtSignIn_textEdited(){
    QMessageBox::critical(this,"Fatal Error",this->ui->txtIDScan->text(),QMessageBox::Ok);
}


void wndActiveDrill::changeEvent(QEvent *e)
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


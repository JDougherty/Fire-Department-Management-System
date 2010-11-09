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

#include "../headers/wndsplash.h"
#include "ui_wndsplash.h"

wndSplash::wndSplash(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wndSplash)
{
    ui->setupUi(this);
}

wndSplash::~wndSplash()
{
    delete ui;
}

void wndSplash::changeEvent(QEvent *e)
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


void wndSplash::StatusUpdate(QString message, int timeout){
    ui->statusbar->showMessage(message,timeout);
}

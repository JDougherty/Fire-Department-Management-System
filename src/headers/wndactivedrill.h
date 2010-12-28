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

#ifndef wndActiveDrill_H
#define wndActiveDrill_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QMenu>
#include "databasemanager.h"

namespace Ui {
    class wndActiveDrill;
}

class wndActiveDrill : public QMainWindow {
    Q_OBJECT
public:
    wndActiveDrill(QWidget *parent = 0, DatabaseManager *db=0, int id=0);
    ~wndActiveDrill();

private:
    Ui::wndActiveDrill *ui;
    DatabaseManager *db;
    int drillid;
    QModelIndex lastCellRightClicked;

    bool insert();
    bool read();
    void updateSheet();

private slots:
    void updateInformation();
    void scanId();
    void sheetContextMenu(const QPoint &pos);
    void sheetRemoveFirefighter();

};

#endif // wndActiveDrill_H

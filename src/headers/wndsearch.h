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

#ifndef WNDSEARCH_H
#define WNDSEARCH_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QSqlQueryModel>
#include <QStringList>
#include "databasemanager.h"
#include "wndeditfirefighter.h"
#include "mainwindow.h"

class MainWindow;

namespace Ui {
    class wndSearch;
}

class wndSearch : public QMainWindow
{
    Q_OBJECT

public:
    explicit wndSearch(QWidget *parent = 0);
    explicit wndSearch(QWidget *parent = 0,
                       MainWindow *nmdiparent=0,
                       DatabaseManager *newDb=0, QString newdtype="", QString query="");
    ~wndSearch();

private:
    Ui::wndSearch *ui;
    DatabaseManager *db;
    QString dtype;
    QString query;
    QStringList headers;
    MainWindow *mdiparent;

    void Search(QString dtype, QString query);

private slots:
    void tableDoubleClicked(QModelIndex);
    void refreshClicked();
    void showAllClicked();
};

#endif // WNDSEARCH_H

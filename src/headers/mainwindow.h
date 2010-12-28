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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QMdiArea>
#include <QToolButton>
#include <QSpacerItem>
#include "databasemanager.h"
// Children Forms
#include "wndnewfirefighter.h"
#include "wndactivedrill.h"
#include "wndsearch.h"
#include "wndinventorycontrol.h"
#include "wndinventorycheck.h"

QT_END_NAMESPACE

namespace Ui {
    class MainWindow;
}



class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    MainWindow(QWidget *parent2 = 0, DatabaseManager *newDb=0);
    ~MainWindow();
    QMdiArea *mdiArea;
    void StatusUpdate(QString message,int timeout=0);

    void mdiEditFirefighter(int id);
    void mdiActiveDrill(int id);

protected:
    void changeEvent(QEvent *e);

private slots:
    void mdiNewFirefighter();
    void mdiActiveDrill();
    void mdiInventoryControl();
    void mdiInventoryCheck();


    void menuSearchTriggered();

    void txtSearchReturnPressed();


private:

    QSignalMapper *windowMapper;
    Ui::MainWindow *ui;

    DatabaseManager *db;
};

#endif // MAINWINDOW_H

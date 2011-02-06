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


#ifndef WNDSETUP_H
#define WNDSETUP_H

#include <QMainWindow>
#include "databasemanager.h"
#include "settingsmanager.h"
#include "mainwindow.h"

namespace Ui {
    class wndSetup;
}

class wndSetup : public QMainWindow {
    Q_OBJECT
public:
    wndSetup(QWidget *parent = 0, DatabaseManager *newDb = 0, SettingsManager *sm = 0, MainWindow *mw = 0);
    ~wndSetup();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::wndSetup *_pUI;
    DatabaseManager *_pDB;
    SettingsManager *_pSM;
    MainWindow *_pMW;

    int _iInstallType;

    enum { NOT_DEFINED, NEW_INST, EXISTING_INST };

    void clearAndHideProgressBars();
private slots:
    void on_btnExInstFinish_clicked();
    void on_btnExInstDBSettings_clicked();
    void on_btnNewInstFinish_clicked();
    void on_btnNewInstDBSettings_clicked();
    void on_btnNewInstFDSettings_clicked();
    void on_btnExInstDBFile_clicked();
    void on_radioExInst_clicked();
    void on_radioNewInst_clicked();
    void on_btnSetupContinue_clicked();
    void on_btnNewInstDBLocation_clicked();
};

#endif // WNDSETUP_H


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
#include <QMessageBox>
#include "databasemanager.h"
#include "settingsmanager.h"
#include "mainwindow.h"

namespace Ui
{
    class wndSetup;
}

//! The interface and logic for setting up the FDMS.
/*!
  Users can either connect to an existing FDMS database or create
  an enitrely new installation.
*/
class wndSetup : public QMainWindow
{
    Q_OBJECT

    private:
        //! Installation methods
        enum {
            NOT_DEFINED,    /*!< Method not selected. */
            NEW_INST,       /*!< Configure a new DB. */
            EXISTING_INST   /*!< Connect to an existing DB. */
        };

        Ui::wndSetup            *_pUI;
        DatabaseManager         *_pDB;
        SettingsManager         *_pSM;
        MainWindow              *_pMW;

        int                     _iInstallType;

        void                    clearAndHideProgressBars( void );

    private slots:
        void                    on_btnExInstFinish_clicked( void );
        void                    on_btnExInstDBSettings_clicked( void );
        void                    on_btnNewInstFinish_clicked( void );
        void                    on_btnNewInstDBSettings_clicked( void );
        void                    on_btnNewInstFDSettings_clicked( void );
        void                    on_btnExInstDBFile_clicked( void );
        void                    on_radioExInst_clicked( void );
        void                    on_radioNewInst_clicked( void );
        void                    on_btnSetupContinue_clicked( void );
        void                    on_btnNewInstDBLocation_clicked( void );

    protected:
        void                    changeEvent( QEvent *e );

    public:
                                wndSetup( QWidget *pParent, DatabaseManager *newDb, SettingsManager *sm, MainWindow *pMW );
                                ~wndSetup( void );
};

#endif // WNDSETUP_H


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
#include "wndactivecall.h"
#include "wndsearch.h"
#include "wndinventorycontrol.h"
#include "wndinventorycheck.h"

QT_END_NAMESPACE

namespace Ui
{
    class MainWindow;
}

//! The program's main window.
class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::MainWindow          *_pUI;
        DatabaseManager         *_pDB;

    public:
        QMdiArea                *mdiArea;

                                MainWindow( QWidget *pParent, DatabaseManager *pDB );
                                ~MainWindow( void );

        void                    statusUpdate( QString message,int iTimeout = 0 );
        void                    mdiEditFirefighter( int iID );
        void                    mdiEditDrill( int iID );
        void                    mdiEditCall( int iID );

    protected:
        void                    changeEvent( QEvent *e );

    private slots:
        void                    mdiSearch( void );
        void                    mdiAddFirefighter( void );
        void                    mdiAddDrill( void );
        void                    mdiAddCall( void );
        void                    mdiInventoryControl( void );
        void                    mdiInventoryCheck( void );
};

#endif // MAINWINDOW_H

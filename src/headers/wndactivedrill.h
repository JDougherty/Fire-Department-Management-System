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

#ifndef WNDACTIVEDRILL_H
#define WNDACTIVEDRILL_H

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

    private:
        Ui::wndActiveDrill      *_pUI;
        DatabaseManager         *_pDB;

        int                     _iID;

        QModelIndex             lastCellRightClicked;

        bool                    insert( void );
        bool                    read( void );
        void                    updateSheet( void );

    private slots:
        void                    updateInformation( void );
        void                    scanId( void );
        void                    sheetContextMenu( const QPoint &pos );
        void                    sheetRemoveFirefighter( void );

    public:
                                wndActiveDrill( QWidget *pParent, DatabaseManager *pDB );
                                wndActiveDrill( QWidget *pParent, DatabaseManager *pDB, int iID );
                                ~wndActiveDrill( void );
};

#endif // WNDACTIVEDRILL_H

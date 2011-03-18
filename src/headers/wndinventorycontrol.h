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

#ifndef WNDINVENTORYCONTROL_H
#define WNDINVENTORYCONTROL_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include "databasemanager.h"

namespace Ui
{
    class wndInventoryControl;
}

class wndInventoryControl : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::wndInventoryControl *_pUI;
        DatabaseManager         *_pDB;

        void                    printLabel( QVector<int> itemRow );

    private slots:
        void                    createItem( void );
        void                    deleteItem( QModelIndex );
        void                    refreshMasterList( void );
        void                    printLabelCurrent( void );
        void                    printLabelAll( void );

    public:
                                wndInventoryControl( QWidget *pParent, DatabaseManager *pDB );
                                ~wndInventoryControl( void );
};

#endif // WNDINVENTORYCONTROL_H

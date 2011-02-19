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

#ifndef WNDFIREFIGHTER_H
#define WNDFIREFIGHTER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include "databasemanager.h"
#include "firefighter.h"

namespace Ui
{
    class wndFirefighter;
}

class wndFirefighter : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::wndFirefighter      *_pUI;
        DatabaseManager         *_pDB;

        Firefighter             _FF;

        bool                    _bAddFirefighter;

    private slots:
        void                    btnSaveFirefighterClicked( void );

    public:
                                wndFirefighter( QWidget *parent, DatabaseManager *pDB );
                                wndFirefighter( QWidget *parent, DatabaseManager *pDB, int iID );
                                ~wndFirefighter( void );
};

#endif // WNDFIREFIGHTER_H

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
#include "wndfirefighter.h"
#include "mainwindow.h"

class MainWindow;

namespace Ui
{
    class wndSearch;
}

//! Show search results in an interactable table.
class wndSearch : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::wndSearch           *_pUI;
        MainWindow              *_pMW;
        DatabaseManager         *_pDB;

        QString                 _sSearchType,
                                _sSearch;

        QStringList             _slTableHeaders;

        QModelIndex             _lastCellRightClicked;

        void                    Search( QString sSearchType, QString sSearch );

    private slots:
        void                    tableDoubleClicked( QModelIndex cell );
        void                    refreshClicked( void );
        void                    showAllClicked( void );
        void                    resultsContextMenu( const QPoint &point );
        void                    resultsDeleteDatum( void );

    public:
                                wndSearch( QWidget *pParent, MainWindow *pMW, DatabaseManager *pDB, QString sSearchType, QString sQuery );
                                ~wndSearch( void );
};

#endif // WNDSEARCH_H

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
#include <QListWidgetItem>
#include "databaseitem.h"

namespace Ui
{
    class wndFirefighter;
}

//! GUI for adding a firefighter and editing firefighter data.
class wndFirefighter : public QMainWindow, public DatabaseItem
{
    Q_OBJECT

    private:
        Ui::wndFirefighter      *_pUI;

        void                    loadTrainingList( void );
        void                    toggleTrainingFields( QListWidgetItem *item );
        void                    enableTrainingFields( bool bEnabled );

        void                    loadEquipmentList( void );
        void                    toggleEquipmentFields( QListWidgetItem *item );
        void                    enableEquipmentFields( bool bEnabled );

    private slots:
        void                    btnSavePersonalInfoClicked( void );

        void                    trainingItemClicked( QListWidgetItem *item );
        void                    btnSaveTrainingItemClicked( void );
        void                    loadTrainingItem( QListWidgetItem *item );

        void                    equipmentItemClicked( QListWidgetItem *item );
        void                    btnSaveEquipmentItemClicked( void );
        void                    loadEquipmentItem( QListWidgetItem *item );

    public:
                                wndFirefighter( QWidget *parent, DatabaseManager *pDB );
                                wndFirefighter( QWidget *parent, DatabaseManager *pDB, int iID );

                                ~wndFirefighter( void );

        bool                    Insert( void );
        bool                    Update( void );
        bool                    Select( void );

        bool                    BuildQueries( void );
        static bool             Create( DatabaseManager *pDB );
        static bool             Delete( DatabaseManager *pDB, int iID );
};

#endif // WNDFIREFIGHTER_H

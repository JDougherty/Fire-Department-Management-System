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

#ifndef WNDEDITFIREFIGHTER_H
#define WNDEDITFIREFIGHTER_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "databasemanager.h"
#include "firefighter.h"

namespace Ui
{
    class wndEditFirefighter;
}

class wndEditFirefighter : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::wndEditFirefighter  *_pUI;
        DatabaseManager         *_pDB;
        Firefighter             _FF;

        void                    updateFirefighterFields( void );

        void                    updateTrainingList( void );
        void                    toggleTrainingInformationEnabled( QListWidgetItem *item );

        void                    updateEquipmentList( void );
        void                    toggleEquipmentInformationEnabled( QListWidgetItem *item );

    private slots:
        void                    btnUpdatePersonalClicked( void );

        void                    trainingItemClicked( QListWidgetItem *item );
        void                    btnUpdateTrainingClicked( void );
        void                    updateTrainingInfo( QListWidgetItem *item );

        void                    equipmentItemClicked( QListWidgetItem *item );
        void                    btnUpdateEquipmentClicked( void );
        void                    updateEquipmentInfo( QListWidgetItem *item );

    public:
                                wndEditFirefighter( QWidget *pParent, DatabaseManager *pDB );
                                wndEditFirefighter( QWidget *pParent, DatabaseManager *pDB, int id );
                                ~wndEditFirefighter( void );
};

#endif // WNDEDITFIREFIGHTER_H

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

#include "../headers/wndfirefighter.h"
#include "ui_wndfirefighter.h"

//! Constructor for adding a new firefighter.
/*!
  Hide extra tabs and change the window and button names.
*/
wndFirefighter::wndFirefighter( QWidget *pParent, DatabaseManager *pDB ) :
    QMainWindow( pParent ), _pUI( new Ui::wndFirefighter )
{
    _pUI->setupUi( this );
    _pDB = pDB;
    _bAddFirefighter = true;

    // Hide these tabs since we want to just enter basic info first
    _pUI->tabWidget->removeTab( 3 ); // tabReports
    _pUI->tabWidget->removeTab( 2 ); // tabEquipment
    _pUI->tabWidget->removeTab( 1 ); // tabTraining

    this->setWindowTitle( "Add Firefighter" );
    _pUI->btnSaveFirefighter->setText( "Add Firefighter" );
}

//! Constructor for adding editing a firefighter.
/*!
  Hide extra tabs and change the window and button names.
*/
wndFirefighter::wndFirefighter( QWidget *pParent, DatabaseManager *pDB, int iID ) :
    QMainWindow( pParent ), _pUI( new Ui::wndFirefighter )
{
    _pUI->setupUi( this );
    _pDB = pDB;
    _bAddFirefighter = false;

    this->setWindowTitle( "Edit Firefighter" );
    _pUI->btnSaveFirefighter->setText( "Save Firefighter" );
}

wndFirefighter::~wndFirefighter( void )
{
    delete _pUI;
}

void wndFirefighter::btnSaveFirefighterClicked( void )
{
    bool bSaveResult = true;

    _FF.firstName( _pUI->txtFirstName->text() );
    _FF.middleName( _pUI->txtMiddleName->text() );
    _FF.lastName( _pUI->txtLastName->text() );
    _FF.dob( _pUI->dateDob->date().toString( "yyyy-MM-dd 00:00:00.000" ) );
    _FF.localID( _pUI->txtLocalID->text() );
    _FF.stateID( _pUI->txtStateID->text() );
    _FF.address( _pUI->txtAddress->text() );
    _FF.city( _pUI->txtCity->text() );
    _FF.state( _pUI->txtState->itemText( _pUI->txtState->currentIndex() ) );
    _FF.zipCode( _pUI->txtZipCode->text() );
    _FF.dateJoin( _pUI->dateJoin->date().toString( "yyyy-MM-dd 00:00:00.000" ) );
    _FF.status( _pUI->txtStatus->text() );
    _FF.hphone( _pUI->txtHphone->text() );
    _FF.wphone( _pUI->txtWphone->text() );
    _FF.cphone( _pUI->txtCphone->text() );
    _FF.drvLic( _pUI->txtDrvLic->text() );
    _FF.cdl( _pUI->txtCDL->text() );

    bSaveResult = _FF.save( _pDB );
    if ( bSaveResult )
    {
        QMessageBox::information( 0, "Firefighter Information", "Firefighter successfully added to database!" );
    }
    else
    {
        QMessageBox::warning( 0, "Firefighter Error", "Firefighter could not be added to database! See log file for details." );
    }

    // if successfully added a firefighter
    if ( _bAddFirefighter && bSaveResult )
    {
        _bAddFirefighter = false;

        // show the additional tabs
        _pUI->tabWidget->addTab( _pUI->tabTraining, "Training" );
        _pUI->tabWidget->addTab( _pUI->tabEquipment, "Equipment" );
        _pUI->tabWidget->addTab( _pUI->tabReports, "Reports" );

        this->setWindowTitle( "Edit Firefighter" );
        _pUI->btnSaveFirefighter->setText( "Save Firefighter" );
    }
}

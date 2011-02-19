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

#include "../headers/wndnewfirefighter.h"
#include "ui_wndnewfirefighter.h"

wndNewFirefighter::wndNewFirefighter( QWidget *pParent, DatabaseManager *pDB ) :
    QMainWindow( pParent ), _pUI( new Ui::wndNewFirefighter )
{
    _pUI->setupUi( this );
    _pDB = pDB;
}

wndNewFirefighter::~wndNewFirefighter( void )
{
    delete _pUI;
}

void wndNewFirefighter::btnAddClicked( void )
{
    Firefighter newFF;

    newFF.firstName( _pUI->txtFirstName->text() );
    newFF.middleName( _pUI->txtMiddleName->text() );
    newFF.lastName( _pUI->txtLastName->text() );
    newFF.dob( _pUI->dateDob->date().toString( "yyyy-MM-dd 00:00:00.000" ) );
    newFF.localID( _pUI->txtLocalID->text() );
    newFF.stateID( _pUI->txtStateID->text() );
    newFF.address( _pUI->txtAddress->text() );
    newFF.city( _pUI->txtCity->text() );
    newFF.state( _pUI->txtState->itemText( _pUI->txtState->currentIndex() ) );
    newFF.zipCode( _pUI->txtZipCode->text() );
    newFF.dateJoin( _pUI->dateJoin->date().toString( "yyyy-MM-dd 00:00:00.000" ) );
    newFF.status( _pUI->txtStatus->text() );
    newFF.hphone( _pUI->txtHphone->text() );
    newFF.wphone( _pUI->txtWphone->text() );
    newFF.cphone( _pUI->txtCphone->text() );
    newFF.drvLic( _pUI->txtDrvLic->text() );
    newFF.cdl( _pUI->txtCDL->text() );

    if ( newFF.save( _pDB ) )
    {
        QMessageBox::information( 0, "Firefighter Information", "Firefighter successfully added to database!" );
    }
    else
    {
        QMessageBox::warning( 0, "Firefighter Error", "Firefighter could not be added to database! See log file for details." );
    }
}

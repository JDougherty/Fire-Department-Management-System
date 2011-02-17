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
    QVector<QString> ffattributes;

    // Build attribute list for firefighter based on forms
    ffattributes.append( _pUI->txtFirstName->text() );
    ffattributes.append( _pUI->txtMiddleName->text() );
    ffattributes.append( _pUI->txtLastName->text() );
    ffattributes.append( _pUI->dateDob->date().toString( "yyyy-MM-dd 00:00:00.000" ) );
    ffattributes.append( _pUI->txtLocalID->text() );
    ffattributes.append( _pUI->txtStateID->text() );
    ffattributes.append( _pUI->txtAddress->text() );
    ffattributes.append( _pUI->txtCity->text() );
    ffattributes.append( _pUI->txtState->itemText( _pUI->txtState->currentIndex() ) );
    ffattributes.append( _pUI->txtZipCode->text() );
    ffattributes.append( _pUI->dateJoin->date().toString( "yyyy-MM-dd 00:00:00.000" ) );
    ffattributes.append( _pUI->txtStatus->text() );
    ffattributes.append( _pUI->txtHphone->text() );
    ffattributes.append( _pUI->txtWphone->text() );
    ffattributes.append( _pUI->txtCphone->text() );
    ffattributes.append( _pUI->txtDrvLic->text() );
    ffattributes.append( _pUI->txtCDL->text() );

    Firefighter newFF;

    if ( newFF.insertToDatabase( ffattributes, _pDB ) )
    {
        QMessageBox::information( 0, "Firefighter Information","Firefighter successfully added to database!" );
    }
    else
    {
        QMessageBox::warning( 0, "Firefighter Error", "Firefighter could not be added to database! See log file for details." );
    }
}

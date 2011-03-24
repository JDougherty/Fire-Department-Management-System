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

#include "../headers/wndactivecall.h"
#include "ui_wndactivecall.h"

//! Constructor for adding a new call.
/*!
  Hide extra tabs and change the window and button names.
  \param pDB Pointer to the database manager.
*/
wndActiveCall::wndActiveCall( QWidget *pParent, DatabaseManager *pDB ) :
    QMainWindow( pParent ), DatabaseItem( pDB, -1 )
{
    _pUI = new Ui::wndActiveCall;
    _pUI->setupUi( this );
}

//! Constructor for editing a call.
/*!
  Load the call's data.
  \param pDB Pointer to the database manager.
  \param iID Call's DB id.
*/
wndActiveCall::wndActiveCall( QWidget *pParent, DatabaseManager *pDB, int iID ) :
    QMainWindow( pParent ), DatabaseItem( pDB, iID )
{
    _pUI = new Ui::wndActiveCall;
    _pUI->setupUi( this );

    Select();
}

wndActiveCall::~wndActiveCall( void )
{
    delete _pUI;
}

//! Updates the calls's information in the database when the Save button is clicked.
void wndActiveCall::btnSaveCallClicked( void )
{
    if ( _iID <= 0 )
    {
        if ( Insert() )
            QMessageBox::information( this, "Call Added", "Call has been added." );
        else
            QMessageBox::warning( this, "Call Error", "Call could not be added! See log file more information." );
    }
    else
    {
        if ( Update() )
            QMessageBox::information( this, "Call Updated", "Call has been updated." );
        else
            QMessageBox::warning( this, "Call Error", "Call could not be updated! See log for more information." );
    }
}

bool wndActiveCall::Insert( void )
{
    _iID = _pDB->insertUI( _pUI->tabWidget->nextInFocusChain(), "Calls" );
    return ( _iID > 0 ) ? true : false;
}

bool wndActiveCall::Update( void )
{
    return _pDB->updateUI( _iID, _pUI->tabWidget->nextInFocusChain(), "Calls" );
}

bool wndActiveCall::Select( void )
{
    return _pDB->selectUI( _iID, _pUI->tabWidget->nextInFocusChain(), "Calls" );
}

bool wndActiveCall::BuildQueries( void )
{
    _pDB->buildQueries( _pUI->tabWidget->nextInFocusChain(), "Calls" );
    return true;
}

bool wndActiveCall::Create( DatabaseManager *pDB )
{
    return pDB->createUI( "Calls" );
}

bool wndActiveCall::Delete( DatabaseManager *pDB, int iID )
{
    return pDB->deleteUI( iID, "Calls" );
}

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

#include "wndCall.h"
#include "ui_wndCall.h"

//! Constructor for adding a new call.
wndCall::wndCall( QWidget *pParent ) :
    QMainWindow( pParent )
{
    _pUI = new Ui::wndCall;
    _pUI->setupUi( this );
    _iID = -1;
}

//! Constructor for editing a call.
/*!
  \param iID Call's DB id.
*/
wndCall::wndCall( QWidget *pParent, int iID ) :
    QMainWindow( pParent )
{
    _pUI = new Ui::wndCall;
    _pUI->setupUi( this );
    _iID = iID;
}

wndCall::~wndCall( void )
{
    delete _pUI;
}

//! Updates the calls's information in the database when the Save button is clicked.
void wndCall::btnSaveCallClicked( void )
{

}

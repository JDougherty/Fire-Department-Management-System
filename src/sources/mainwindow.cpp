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

#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

/*!
  \param pParent Pointer to the parent window.
  \param pDB Pointer to the database manager.
*/
MainWindow::MainWindow( QWidget *pParent, DatabaseManager *pDB ) :
    QMainWindow( pParent ), _pUI( new Ui::MainWindow )
{
    QWidget *spacer;

    _pUI->setupUi( this );
    _pDB = pDB;

    mdiArea = new QMdiArea;
    mdiArea->setBackground( QBrush::QBrush( QColor::QColor( 128, 0, 0 ) ) );
    mdiArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    mdiArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    setCentralWidget( mdiArea );

    spacer = new QWidget( this );
    spacer->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    _pUI->toolBar->addWidget( spacer );
    _pUI->toolBar->addSeparator();
    _pUI->toolBar->addWidget( _pUI->lblSearch );
    _pUI->toolBar->addWidget( _pUI->txtSearch );
    _pUI->toolBar->addWidget( _pUI->cmbSearch );
}

MainWindow::~MainWindow( void )
{
    delete _pUI;
}

void MainWindow::changeEvent( QEvent *e )
{
    QMainWindow::changeEvent( e );

    switch ( e->type() )
    {
        case QEvent::LanguageChange:
            _pUI->retranslateUi( this );
            break;
        default:
            break;
    }
}

//! Sets the status bar message.
/*!
  \param sMessage Message to be displayed.
  \param iTimeout Amount of time to display the message.
*/
void MainWindow::statusUpdate( QString sMessage, int iTimeout )
{
    _pUI->statusBar->showMessage( sMessage, iTimeout );
}

//! User pressed enter in the search bar.
void MainWindow::mdiSearch( void )
{
    wndSearch *child = new wndSearch( this, this, _pDB, _pUI->cmbSearch->currentText(), _pUI->txtSearch->text() );
    mdiArea->addSubWindow( child );
    child->show();
}

//! User clicked a button to add a drill.
void MainWindow::mdiAddDrill( void )
{
    wndActiveDrill *child = new wndActiveDrill( this, _pDB );
    mdiArea->addSubWindow( child );
    child->show();
}

//! User clicked a button to edit a drill.
void MainWindow::mdiEditDrill( int iID )
{
    wndActiveDrill *child = new wndActiveDrill( this, _pDB, iID );
    mdiArea->addSubWindow( child );
    child->show();
}

//! User clicked a button to add a call.
void MainWindow::mdiAddCall( void )
{
    wndActiveCall *child = new wndActiveCall( this, _pDB );
    mdiArea->addSubWindow( child );
    child->show();
}

//! User clicked a button to edit a call.
void MainWindow::mdiEditCall( int iID )
{
    wndActiveCall *child = new wndActiveCall( this, _pDB, iID );
    mdiArea->addSubWindow( child );
    child->show();
}

//! User clicked a button to modify the inventory.
void MainWindow::mdiInventoryControl( void )
{
    wndinventorycontrol *child = new wndinventorycontrol;
    mdiArea->addSubWindow( child );
    child->show();
}

//! User clicked a button to check the inventory.
void MainWindow::mdiInventoryCheck( void )
{
    wndInventoryCheck *child = new wndInventoryCheck;
    mdiArea->addSubWindow( child );
    child->show();
}

//! User clicked a button to add a firefighter.
void MainWindow::mdiAddFirefighter( void )
{
    wndFirefighter *child = new wndFirefighter( this, _pDB );
    mdiArea->addSubWindow( child );
    child->show();
}

//! User clicked a button to edit a firefighter.
void MainWindow::mdiEditFirefighter( int iID )
{
    wndFirefighter *child = new wndFirefighter( this, _pDB, iID );
    mdiArea->addSubWindow( child );
    child->show();
}

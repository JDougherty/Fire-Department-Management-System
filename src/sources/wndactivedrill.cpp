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

#include "../headers/wndactivedrill.h"
#include "ui_wndactivedrill.h"

wndActiveDrill::wndActiveDrill( QWidget *pParent, DatabaseManager *pDB) :
    QMainWindow( pParent ), DatabaseItem( pDB, -1 )
{
    _pUI = new Ui::wndActiveDrill;
    _pUI->setupUi( this );

    _pUI->DB_DATE_DI_StartTime->setDateTime( QDateTime::currentDateTime() );
    _pUI->DB_DATE_DI_EndTime->setDateTime( QDateTime::currentDateTime().addSecs( 60 * 60 * 2 ) ) ;

    _pUI->DB_TEXT_IDScan->setFocus();

    _pUI->tblTimesheet->setContextMenuPolicy( Qt::CustomContextMenu );

    _pDB->buildQueries( _pUI->centralWidget->nextInFocusChain(), "Drills", "_DI_" );
    Insert();
}

wndActiveDrill::wndActiveDrill( QWidget *pParent, DatabaseManager *pDB, int iID ) :
    QMainWindow( pParent ), DatabaseItem( pDB, iID )
{
    _pUI = new Ui::wndActiveDrill;
    _pUI->setupUi( this );

    _pUI->tblTimesheet->setContextMenuPolicy( Qt::CustomContextMenu );

    _pDB->buildQueries( _pUI->centralWidget->nextInFocusChain(), "Drills", "_DI_" );
    Select();
    updateSheet();
}

wndActiveDrill::~wndActiveDrill( void )
{
    delete _pUI;
}

// PRIVATE MEMBERS:

void wndActiveDrill::updateSheet( void )
{
    QSqlQuery selectSheet;
    selectSheet.prepare( "SELECT Firefighters.PI_FirstName||' '||Firefighters.PI_LastName||' ('||Firefighters.PI_LocalID||')',"
                         "strftime('%H:%M',drillsheet.timein),strftime('%H:%M',drillsheet.timeout) FROM drillsheet "
                         "JOIN Firefighters ON drillsheet.ffid=Firefighters.id WHERE did=?" );
    selectSheet.addBindValue( _iID );

    _pDB->query( selectSheet );

    QSqlQueryModel *sheetModel = new QSqlQueryModel;
    sheetModel->setQuery( selectSheet );
    sheetModel->setHeaderData( 0, Qt::Horizontal, tr( "Name (ID)" ) );
    sheetModel->setHeaderData( 1, Qt::Horizontal, tr( "Time in" ) );
    sheetModel->setHeaderData( 2, Qt::Horizontal, tr( "Time out" ) );

    // Set options for the QTableView
    _pUI->tblTimesheet->setModel( sheetModel );
    _pUI->tblTimesheet->setColumnWidth( 0, 200 );
    _pUI->tblTimesheet->setColumnWidth( 1, 80 );
    _pUI->tblTimesheet->setColumnWidth( 2, 80 );
    _pUI->tblTimesheet->horizontalHeader()->show();
    _pUI->tblTimesheet->verticalHeader()->hide();
}

// PRIVATE SLOTS:

void wndActiveDrill::updateInformation( void )
{
    if ( Update() )
    {
        QMessageBox::information( this, "Drill Updated", "Drill has been updated." );
    }
    else
    {
        QMessageBox::warning( this, "Drill Error", "Drill could not be updated! See log for more information." );
    }
}


void wndActiveDrill::scanId( void )
{
    // Get the primary key of the firefighter based on department id
    QSqlQuery selectFirefighter;
    QString ffdeptid = _pUI->DB_TEXT_IDScan->text();
    int ffid = 0;

    selectFirefighter.prepare( "SELECT id FROM Firefighters WHERE PI_LocalID=?" );
    selectFirefighter.addBindValue( ffdeptid );

    // Execute query and check for errors
    if ( !( _pDB->query( selectFirefighter ) ) )
    {
        qWarning( "Drill Error (%d): Could not retrieve id for firefighter with department id %s. Error: %s",
                  _iID, qPrintable( ffdeptid ), qPrintable( selectFirefighter.lastError().text() ) );
        QMessageBox::warning( this, "Drill Error", "Could not retrieve id for firefighter with department id '" + ffdeptid + "'. See log for more information." );
        return;
    }
    else
    {
        // Check if a firefighter was found with the given department id
        if ( !(selectFirefighter.first() ) )
        {
            QMessageBox::information( this, "Drill Information", "Firefighter with department id " + ffdeptid + " does not exist." );
            return;
        }
        else
        {
            // Firefighter found, retrieve primary key id
            ffid = selectFirefighter.value( 0 ).toInt();
        }
    }

    // Check if the firefighter is in the drill sheet for this drill, i.e. signed in or not
    QSqlQuery ffCheck;
    ffCheck.prepare( "SELECT * FROM drillsheet WHERE did=? AND ffid=?" );
    ffCheck.addBindValue( _iID );
    ffCheck.addBindValue( ffid );

    // Execute query and check for errors
    if ( !( _pDB->query( ffCheck ) ) )
    {
        qWarning( "Drill Error (%d): Could not check sign in status of firefighter with id %d. Error: %s", _iID, ffid, qPrintable( ffCheck.lastError().text() ) );
        QMessageBox::warning( this, "Drill Error:", "Could not check the sign in status of firefighter with department id '" + ffdeptid + "'. See log for more information." );
        return;
    }
    else
    {
        // Firefighter is not yet signed in
        if ( !ffCheck.first() )
        {
            // Insert the firefighter to the drill sheet, i.e. sign them in
            QSqlQuery insertFirefighterToSheet;
            insertFirefighterToSheet.prepare( "INSERT INTO drillsheet (did,ffid,timein) VALUES (?,?,?)" );
            insertFirefighterToSheet.addBindValue( _iID );
            insertFirefighterToSheet.addBindValue( ffid );
            insertFirefighterToSheet.addBindValue( QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:00.000" ) );

            // Execute query and check for errors
            if ( !( _pDB->query( insertFirefighterToSheet ) ) )
            {
                qWarning( "Drill Error (%d): Could not sign in firefighter with id %d. Error: %s", _iID, ffid, qPrintable( ffCheck.lastError().text() ) );
                QMessageBox::warning( this, "Drill Error:", "Could not sign in firefighter with department id '" + ffdeptid + "'. See log for more information." );
                return;
            }

            updateSheet();
        }
        else // Firefighter is signed in
        {
            // Update the firefighter in the drill sheet, i.e. sign them out
            QSqlQuery updateFirefighterInSheet;
            updateFirefighterInSheet.prepare( "UPDATE drillsheet SET timeout=? WHERE did=? AND ffid=?" );
            updateFirefighterInSheet.addBindValue( QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:00.000" ) );
            updateFirefighterInSheet.addBindValue( _iID );
            updateFirefighterInSheet.addBindValue( ffid );

            // Execute query and check for errors
            if ( !( _pDB->query( updateFirefighterInSheet ) ) )
            {
                qWarning( "Drill Error (%d): Could not sign out firefighter with id %d. Error: %s", _iID, ffid, qPrintable( ffCheck.lastError().text() ) );
                QMessageBox::warning( this, "Drill Error:", "Could not sign out firefighter with department id '" + ffdeptid + "'. See log for more information." );
                return;
            }

            updateSheet();
        }
    }
}

void wndActiveDrill::sheetContextMenu( const QPoint &pos )
{
    QMenu *menu = new QMenu;
    QModelIndex cell = _pUI->tblTimesheet->indexAt( pos );

    if ( cell.isValid() )
    {
        lastCellRightClicked = cell;

        menu->addAction( "Remove firefighter", this, SLOT( sheetRemoveFirefighter() ) );
        menu->addAction( "Update time in", this, SLOT( sheetRemoveFirefighter() ) );
        menu->addAction( "Update time out", this, SLOT( sheetRemoveFirefighter() ) );
        menu->exec( _pUI->tblTimesheet->mapToGlobal( pos ) );
    }
}

void wndActiveDrill::sheetRemoveFirefighter( void )
{
    QString deptid = lastCellRightClicked.sibling( lastCellRightClicked.row(), 0 ).data().toString();

    if ( QMessageBox::question( this, "Drill Confirmation", "Are you sure you would like to remove firefighter " + deptid + "?",
                                QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
    {
        deptid = deptid.mid( deptid.lastIndexOf( "(" ) + 1, deptid.lastIndexOf( ")" ) - deptid.lastIndexOf( "(" ) - 1 );
        int ffid = 0;

        QSqlQuery selectFirefighter;
        selectFirefighter.prepare( "SELECT id FROM Firefighters WHERE PI_LocalID=?" );
        selectFirefighter.addBindValue( deptid );

        if ( !selectFirefighter.exec() )
        {
            qWarning( "Drill Error (%d): Could not retrive id for firefighter with department id %s. Error: %s",
                      _iID, qPrintable( deptid ), qPrintable( selectFirefighter.lastError().text() ) );
            QMessageBox::warning( this, "Drill Error:", "Could not retrive id for firefighter with department id " + deptid + ". See log for more information." );
            return;
        }

        selectFirefighter.first();
        ffid = selectFirefighter.value( 0 ).toInt();

        QSqlQuery removeFirefighter;
        removeFirefighter.prepare( "DELETE FROM drillsheet WHERE did=? and ffid=?" );
        removeFirefighter.addBindValue( _iID );
        removeFirefighter.addBindValue( ffid );

        if ( !removeFirefighter.exec() )
        {
            qWarning( "Drill Error (%d): Could not delete firefighter with id %d from drillsheet. Error: %s",
                      _iID, ffid, qPrintable( selectFirefighter.lastError().text() ) );
            QMessageBox::warning( this, "Drill Error:", "Could not remove firefighter with department id " + deptid + ". See log for more information." );
            return;
        }

        updateSheet();
    }

}

bool wndActiveDrill::Insert( void )
{
    _iID = _pDB->insertUI( _pUI->centralWidget->nextInFocusChain(), "Drills", "_DI_" );
    return ( _iID > 0 ) ? true : false;
}

bool wndActiveDrill::Update( void )
{
    return _pDB->updateUI( _iID, _pUI->centralWidget->nextInFocusChain(), "Drills", "_DI_" );
}

bool wndActiveDrill::Select( void )
{
    return _pDB->selectUI( _iID, _pUI->centralWidget->nextInFocusChain(), "Drills", "_DI_" );
}

bool wndActiveDrill::BuildQueries( void )
{
    _pDB->buildQueries( _pUI->centralWidget->nextInFocusChain(), "Drills", "_DI_" );
    return true;
}

bool wndActiveDrill::Create( DatabaseManager *pDB )
{
    return pDB->createUI( "Drills" );
}

bool wndActiveDrill::Delete( DatabaseManager *pDB, int iID )
{
    return pDB->deleteUI( iID, "Drills" );
}

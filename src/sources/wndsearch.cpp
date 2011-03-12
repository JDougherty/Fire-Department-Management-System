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

#include <QMessageBox>
#include "../headers/mainwindow.h"
#include "../headers/wndsearch.h"
#include "ui_wndsearch.h"

/*!
  \param pParent Pointer to the parent widget.
  \param pMW Pointer to the main window; called to launch windows for editing search results.
  \param pDB Pointer to the database manager; for querying the DB.
  \param sSearchType Search category; firefighter, call, drills, etc.
  \param sSearch User search query.
*/
wndSearch::wndSearch( QWidget *pParent, MainWindow *pMW, DatabaseManager *pDB, QString sSearchType, QString sSearch ) :
        QMainWindow( pParent ), _pUI( new Ui::wndSearch )
{
    _pUI->setupUi( this );
    _pMW = pMW;
    _pDB = pDB;

    _sSearchType = sSearchType;
    _sSearch = sSearch;

    this->setWindowTitle( this->windowTitle() + _sSearchType );

    if ( _sSearchType == "Firefighters" )
    {
       _slTableHeaders = QStringList() << "ID" << "Last Name" << "First Name";
    }
    else if ( _sSearchType == "Drills" || _sSearchType == "Calls" )
    {
        _slTableHeaders = QStringList() << "ID" << "Date" << "Location";
    }

    Search( _sSearchType, _sSearch );

    _pUI->tblResults->setContextMenuPolicy( Qt::CustomContextMenu );
}

wndSearch::~wndSearch( void )
{
    delete _pUI;
}

//! Runs a search query and populates the search window with the results.
/*!
  \param sSearchType Search category; firefighter, call, drills, etc.
  \param sSearch User search query.
*/
void wndSearch::Search( QString sSearchType, QString sSearch )
{
    QSqlQueryModel *pSearchModel = new QSqlQueryModel;
    QSqlQuery qrySelection;

    if ( sSearchType == "Firefighters" )
    {
        QString sSelection = "SELECT id,PI_LocalID,PI_LastName,PI_FirstName FROM Firefighters";
        if ( sSearch != "" )
        {
            sSelection += " WHERE PI_LocalID LIKE ? OR PI_LastName LIKE ? OR PI_FirstName LIKE ?";
            qrySelection.prepare( sSelection );
            qrySelection.addBindValue( "%" + sSearch + "%" );
            qrySelection.addBindValue( "%" + sSearch + "%" );
            qrySelection.addBindValue( "%" + sSearch + "%" );
        }
        else
        {
            qrySelection.prepare( sSelection );
        }
    }
    else if ( sSearchType == "Drills" )
    {
        QString sSelection = "SELECT id,drillnum,strftime('%m/%d/%Y',starttime),location FROM drills";
        if ( sSearch != "" )
        {
            sSelection += " WHERE drillnum LIKE ? OR location LIKE ?";
            qrySelection.prepare( sSelection );
            qrySelection.addBindValue( "%" + sSearch + "%" );
            qrySelection.addBindValue( "%" + sSearch + "%" );
        }
        else{
            qrySelection.prepare( sSelection );
        }
    }
    else if ( sSearchType == "Calls" )
    {
        QString sSelection = "SELECT id,TS_CallNum,strftime('%m/%d/%Y',AC1_Alarm),AC1_Location FROM Calls";
        if ( sSearch != "" )
        {
            sSelection += " WHERE TS_CallNum LIKE ? OR AC1_Location LIKE ?";
            qrySelection.prepare( sSelection );
            qrySelection.addBindValue( "%" + sSearch + "%" );
            qrySelection.addBindValue( "%" + sSearch + "%" );
        }
        else
        {
            qrySelection.prepare( sSelection );
        }
    }

    _pDB->query( qrySelection );

    pSearchModel->setQuery( qrySelection );

    pSearchModel->setHeaderData( 1, Qt::Horizontal, _slTableHeaders[0] );
    pSearchModel->setHeaderData( 2, Qt::Horizontal, _slTableHeaders[1] );
    pSearchModel->setHeaderData( 3, Qt::Horizontal, _slTableHeaders[2] );

    // Apply the model to the table
    _pUI->tblResults->setModel( pSearchModel );

    // Set columns to stretch to percentage of width of window
    _pUI->tblResults->horizontalHeader()->setResizeMode( 0, QHeaderView::Stretch );
    _pUI->tblResults->horizontalHeader()->setResizeMode( 1, QHeaderView::Stretch );
    _pUI->tblResults->horizontalHeader()->setResizeMode( 2, QHeaderView::Stretch );

    // Show the column header, hide the row header
    _pUI->tblResults->horizontalHeader()->show();
    _pUI->tblResults->verticalHeader()->hide();

    // Do not allow editing
    _pUI->tblResults->setEditTriggers( 0 );

    // Hide the primary key column
    _pUI->tblResults->hideColumn( 0 );
}


// PRIVATE SLOTS:
//! User double clicked a cell to edit it.
/*!
  \param cell Cell that the user double clicked.
*/
void wndSearch::tableDoubleClicked( QModelIndex cell )
{
    QString sID = cell.sibling( cell.row(), 0 ).data().toString();

    if ( _sSearchType == "Firefighters" )
    {
        _pMW->mdiEditFirefighter( sID.toInt() );
    }
    else if ( _sSearchType == "Drills" )
    {
        _pMW->mdiEditDrill( sID.toInt() );
    }
    else if ( _sSearchType == "Calls" )
    {
        _pMW->mdiEditCall( sID.toInt() );
    }
}

//! User clicked a button to refresh the search results.
void wndSearch::refreshClicked( void )
{
    Search( _sSearchType, _sSearch );
}

//! User clicked a button to show all results.
void wndSearch::showAllClicked( void )
{
    Search( _sSearchType, "" );
}

//! User right clicked a cell; show a drop down menu.
/*!
  \param point Point on the table where the user right clicked.
*/
void wndSearch::resultsContextMenu( const QPoint &point )
{
    QMenu *pMenu = new QMenu;
    QModelIndex cell = _pUI->tblResults->indexAt( point );

    if ( cell.isValid() )
    {
        _lastCellRightClicked = cell;

        pMenu->addAction( "Delete", this, SLOT( resultsDeleteDatum() ) );
        pMenu->exec( _pUI->tblResults->mapToGlobal( point ) );
    }
}

//! User right clicked a cell and selected delete.
/*!
  Delete the corresponding entry from the database.
*/
void wndSearch::resultsDeleteDatum( void )
{
    QString sID = _lastCellRightClicked.sibling( _lastCellRightClicked.row(), 0 ).data().toString();

    if ( _sSearchType == "Firefighters" )
    {
        if ( QMessageBox::question( 0, "Delete firefighter?", "Are you sure you wish to delete this firefighter?", QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
        {
            QSqlQuery qryDeleteFirefighter;

            qryDeleteFirefighter.prepare( "DELETE FROM firefighters WHERE id=?" );
            qryDeleteFirefighter.addBindValue( sID );

            if ( _pDB->query( qryDeleteFirefighter ) )
            {
                qDebug( "Firefighter Information: Firefighter with department id %s successfully deleted.", qPrintable( sID ) );
                Search( _sSearchType, _sSearch );
            }
            else
            {
                qWarning( "Firefighter Information: Firefighter with department id %s could not be deleted. Error: %s",
                          qPrintable( sID ), qPrintable( qryDeleteFirefighter.lastError().text() ) );
                QMessageBox::warning( 0, "Error", "Could not delete firefighter with department id " + sID + ". See log for more information." );
            }
        }
    }
    else if ( _sSearchType == "Drills" || _sSearchType == "Calls" )
    {
        QMessageBox::warning( 0, "Error", "Sorry, but this is not yet implemented." );
    }
}

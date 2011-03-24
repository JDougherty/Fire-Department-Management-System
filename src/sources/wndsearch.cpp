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
       _slTableHeaders = QStringList() << "Local ID" << "Last Name" << "First Name";
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
        // split on (0 or more commas and one or more spaces) or (1 or more commas and 0 or more spaces)
        QStringList searchList = sSearch.split(QRegExp(",*\\s+|,+\\s*"));
        QString sSelection = "SELECT id,PI_LocalID,PI_LastName,PI_FirstName FROM Firefighters";

        if ( sSearch != "" )
        {
            sSelection += " WHERE PI_LocalID LIKE ? OR PI_LastName LIKE ? OR PI_FirstName LIKE ?";

            if ( searchList.size() > 1 ) // more than one search term
            {
                QString sQuestionMarks;
                for ( int i = 0; i < searchList.size(); i++ ) // need i question marks for i search terms
                {
                    sQuestionMarks += "?, ";
                }
                sQuestionMarks = sQuestionMarks.left( sQuestionMarks.size() - 2 );

                sSelection += " OR PI_LocalID COLLATE NOCASE IN (" + sQuestionMarks + ") OR ( PI_LastName COLLATE NOCASE IN (" +
                              sQuestionMarks + ") AND PI_FirstName COLLATE NOCASE IN (" + sQuestionMarks + ") )";

                qrySelection.prepare( sSelection );
                qrySelection.addBindValue( "%" + sSearch + "%" );
                qrySelection.addBindValue( "%" + sSearch + "%" );
                qrySelection.addBindValue( "%" + sSearch + "%" );

                for ( int i = 0; i < 3; i++ )
                {
                    for ( int j = 0; j < searchList.size(); j++ )
                    {
                        qrySelection.addBindValue( searchList[j] );
                    }
                }
            }
            else
            {
                qrySelection.prepare( sSelection );
                qrySelection.addBindValue( "%" + sSearch + "%" );
                qrySelection.addBindValue( "%" + sSearch + "%" );
                qrySelection.addBindValue( "%" + sSearch + "%" );
            }
        }
        else
        {
            qrySelection.prepare( sSelection );
        }
    }
    else if ( sSearchType == "Drills" )
    {
        QString sSelection = "SELECT id,DI_DrillNumber,strftime('%m/%d/%Y',DI_StartTime),DI_Location FROM Drills";
        if ( sSearch != "" )
        {
            sSelection += " WHERE DI_DrillNumber LIKE ? OR DI_Location LIKE ?";
            qrySelection.prepare( sSelection );
            qrySelection.addBindValue( "%" + sSearch + "%" );
            qrySelection.addBindValue( "%" + sSearch + "%" );
        }
        else
        {
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
        if ( QMessageBox::question( this, "Delete Firefighter?", "Are you sure you wish to delete this firefighter?", QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
        {
            if ( wndFirefighter::Delete( _pDB, sID.toInt() ) )
            {
                qDebug( "Search: Firefighter with local id %s successfully deleted.", qPrintable( sID ) );
                Search( _sSearchType, _sSearch );
            }
            else
            {
                qWarning( "Search: Firefighter with local id %s could not be deleted. Error: %s",
                          qPrintable( sID ), qPrintable( _pDB->lastError().text() ) );
                QMessageBox::warning( this, "Error", "Could not delete firefighter with local id " + sID + ". See log for more information." );
            }
        }
    }
    else if ( _sSearchType == "Drills" )
    {
        if ( QMessageBox::question( this, "Delete Drill?", "Are you sure you wish to delete this drill?", QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
        {
            if ( wndActiveDrill::Delete( _pDB, sID.toInt() ) )
            {
                qDebug( "Search: Drill with id %s successfully deleted.", qPrintable( sID ) );
                Search( _sSearchType, _sSearch );
            }
            else
            {
                qWarning( "Search: Drill with id %s could not be deleted. Error: %s",
                          qPrintable( sID ), qPrintable( _pDB->lastError().text() ) );
                QMessageBox::warning( this, "Error", "Could not delete drill with id " + sID + ". See log for more information." );
            }
        }
    }
    else if ( _sSearchType == "Calls" )
    {
        if ( QMessageBox::question( this, "Delete Call?", "Are you sure you wish to delete this call?", QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
        {
            if ( wndActiveCall::Delete( _pDB, sID.toInt() ) )
            {
                qDebug( "Search: Call with id %s successfully deleted.", qPrintable( sID ) );
                Search( _sSearchType, _sSearch );
            }
            else
            {
                qWarning( "Search: Call with id %s could not be deleted. Error: %s",
                          qPrintable( sID ), qPrintable( _pDB->lastError().text() ) );
                QMessageBox::warning( this, "Error", "Could not delete call with id " + sID + ". See log for more information." );
            }
        }
    }
    else
    {
        QMessageBox::warning( this, "Error", "Sorry, but this is not yet implemented." );
    }
}

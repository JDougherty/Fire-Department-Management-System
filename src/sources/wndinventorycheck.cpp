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

#include "../headers/wndinventorycheck.h"
#include "ui_wndinventorycheck.h"

//! Constructor for checking the inventory.
/*!
  \param pDB Pointer to the database manager.
*/
wndInventoryCheck::wndInventoryCheck( QWidget *pParent, DatabaseManager *pDB ) :
    QMainWindow( pParent ), _pUI( new Ui::wndInventoryCheck )
{
    _pUI->setupUi(this);
    _pDB = pDB;

    populateCategory();
    refreshTables();
}

wndInventoryCheck::~wndInventoryCheck( void )
{
    delete _pUI;
}

//! Populates the category combobox with distrinct item categories.
void wndInventoryCheck::populateCategory( void )
{
    _pUI->cmbCategory->addItem( "[All]" );
    QSqlQuery selectCategories;
    selectCategories.prepare( "SELECT DISTINCT category FROM inventory" );
    if ( _pDB->query( selectCategories ) )
    {
        while ( selectCategories.next() )
        {
            _pUI->cmbCategory->addItem( selectCategories.value( 0 ).toString() );
        }
    }
}

//! Populates the checked in and not checked in item tables.
void wndInventoryCheck::refreshTables( void )
{
    QSqlQuery checkedQuery;
    checkedQuery.prepare( "SELECT iid,name FROM inventorycheck WHERE checked=1" );
    _pDB->query( checkedQuery );
    QSqlQueryModel *checkmodel = new QSqlQueryModel;
    checkmodel->setQuery(checkedQuery);

    // Set header values
    checkmodel->setHeaderData( 0, Qt::Horizontal, tr( "ID" ) );
    checkmodel->setHeaderData( 1, Qt::Horizontal, tr( "Name" ) );

    // Set options for the QTableView
    _pUI->tblCheckedIn->setModel( checkmodel );
    _pUI->tblCheckedIn->verticalHeader()->hide();
    _pUI->tblCheckedIn->horizontalHeader()->setResizeMode( 0, QHeaderView::Stretch );
    _pUI->tblCheckedIn->horizontalHeader()->setResizeMode( 1, QHeaderView::Stretch );

    QSqlQuery ncheckedQuery;
    ncheckedQuery.prepare( "SELECT iid,name FROM inventorycheck WHERE checked=0" );
    _pDB->query( ncheckedQuery );
    QSqlQueryModel *ncheckmodel = new QSqlQueryModel;
    ncheckmodel->setQuery( ncheckedQuery );

    // Set header values
    ncheckmodel->setHeaderData( 0, Qt::Horizontal, tr( "ID" ) );
    ncheckmodel->setHeaderData( 1, Qt::Horizontal, tr( "Name" ) );

    // Set options for the QTableView
    _pUI->tblNotCheckedIn->setModel( ncheckmodel );
    _pUI->tblNotCheckedIn->verticalHeader()->hide();
    _pUI->tblNotCheckedIn->horizontalHeader()->setResizeMode( 0, QHeaderView::Stretch );
    _pUI->tblNotCheckedIn->horizontalHeader()->setResizeMode( 1, QHeaderView::Stretch );
}

//! Removes all items from the checked in table.
void wndInventoryCheck::resetInventoryCheck( void )
{
    if ( QMessageBox::question( this, "Inventory Information: Confirm Reset", "Are you sure you would like to reset the inventory check?",
                                QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
    {

        QSqlQuery qryDelete( "DELETE FROM inventorycheck WHERE 1=1" );
        _pDB->query( qryDelete );

        QSqlQuery copyQuery;
        // If the filter category is all, do not condition SELECT query
        if ( _pUI->cmbCategory->currentText() == "[All]" )
        {
            copyQuery.prepare( "INSERT INTO inventorycheck (iid,name,description,category,checked)"
                               "SELECT id,name,description,category,0 FROM inventory" );
        }
        else // Otherwise, append the filter text to a condition in the query
        {
            copyQuery.prepare( "INSERT INTO inventorycheck (iid,name,description,category,checked)"
                               "SELECT id,name,description,category,0 FROM inventory WHERE inventory.category=?" );
            copyQuery.addBindValue( _pUI->cmbCategory->currentText() );
        }

        if ( !_pDB->query( copyQuery ) )
        {
            QMessageBox::warning( this, "Inventory Error", "Could not copy inventory into check table. See log for more information." );
            qWarning( "Inventory Error: Could not copy inventory into check table. Database Error: %s", qPrintable( copyQuery.lastError().text() ) );
        }
        refreshTables();
    }
}

//! Removes all items from the checked in table.
void wndInventoryCheck::itemScanned( void )
{
    QSqlQuery updateQuery;
    updateQuery.prepare( "UPDATE inventorycheck SET checked=1 WHERE id=?" );
    updateQuery.addBindValue( _pUI->txtScanID->text() );
    if ( _pDB->query( updateQuery ) )
    {
        if ( updateQuery.numRowsAffected() == 1 )
        {
            refreshTables();
        }
        else
        {
            QMessageBox::information( this, "Inventory Information", "Item with ID " + _pUI->txtScanID->text() + " not found in not-checked list." );
        }
    }
    else
    {
        QMessageBox::warning( this, "Inventory Error", "There was a problem checking this item into inventory. See log for more information." );
    }
    _pUI->txtScanID->clear();
    _pUI->txtScanID->setFocus();
}

//! Print the checked in and missing items.
void wndInventoryCheck::printReport( void )
{
    QPrinter printer;
    printer.setPaperSize( QPrinter::Letter );
    printer.setPageMargins( 1, 1, 1, 1, QPrinter::Inch );

    QPrintDialog *dialog = new QPrintDialog( &printer, this );
    if ( dialog->exec() != QDialog::Accepted )
    {
        return;
    }

    // PDF printing:
    //printer.setOutputFormat(QPrinter::PdfFormat);
    //printer.setOutputFileName("test.pdf");

    // Build the painter data which is printed
    QPainter painter;

    if ( !painter.begin( &printer ) ) // Link the painter to the printer
    {
        qWarning("Printer Error: Could not link painter to printer. ");
        return;
    }

    painter.setFont( QFont( "Courier New", 12, QFont::Bold ) );

    int pw = (int)( printer.pageRect( QPrinter::DevicePixel ).width() );
    int ph = (int)( printer.pageRect( QPrinter::DevicePixel ).height() );
    int y = 0;
    painter.drawText( 0, 0, pw, ph, Qt::AlignHCenter, "Station 40 - Youngsville Fire Department\n"
                     "Inventory Audit Report\n"  + QDate::currentDate().toString( "dddd the d of MMMM yyyy" ) );
    y = 80;
    if ( _pUI->chkCheckedItems->isChecked() )
    {
        painter.drawText( 0, y, pw, ph, Qt::AlignLeft, "Checked Items" );
        y += 20;

        for ( int i = 0; i < _pUI->tblCheckedIn->model()->rowCount(); i++ )
        {
            painter.drawText( 20, y, pw, ph, Qt::AlignLeft, _pUI->tblCheckedIn->model()->index( i, 1 ).data().toString() );
            y += 20;
        }
    }

    if ( _pUI->chkMissingItems->isChecked() )
    {
        painter.drawText( 0, y, pw, ph, Qt::AlignLeft, "Missing Items" );
        y += 20;
        for ( int i=0; i < _pUI->tblNotCheckedIn->model()->rowCount(); i++ )
        {
            painter.drawText( 20, y, pw, ph, Qt::AlignLeft, _pUI->tblNotCheckedIn->model()->index( i, 1 ).data().toString() );
            y += 20;
        }
    }
    painter.end();
}

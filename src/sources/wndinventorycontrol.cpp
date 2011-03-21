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

#include "../headers/wndinventorycontrol.h"
#include "ui_wndinventorycontrol.h"

//! Constructor for modifying the inventory.
/*!
  \param pDB Pointer to the database manager.
*/
wndInventoryControl::wndInventoryControl( QWidget *pParent,DatabaseManager *pDB ) :
    QMainWindow( pParent ), _pUI( new Ui::wndInventoryControl )
{
    _pUI->setupUi( this );
    _pDB = pDB;

    _pUI->cmbCategoryFilter->addItem( "[All]" );
    QSqlQuery selectCategories;
    selectCategories.prepare( "SELECT DISTINCT category FROM inventory" );
    if ( _pDB->query( selectCategories ) )
    {
        while( selectCategories.next() )
        {
            _pUI->cmbCategoryFilter->addItem( selectCategories.value( 0 ).toString() );
        }
    }

    refreshMasterList();
}

wndInventoryControl::~wndInventoryControl( void )
{
    delete _pUI;
}

//! Inserts an item into the inventory.
/*!
  Uses the fields txtNewName, txtNewDescription, and txtNewCategory from the form.
  \see deleteItem()
*/
void wndInventoryControl::createItem( void )
{
    QSqlQuery insertItem;
    insertItem.prepare( "INSERT INTO inventory (name,description,category) VALUES(?,?,?)" );
    insertItem.addBindValue( _pUI->txtNewName->text() );
    insertItem.addBindValue( _pUI->txtNewDescription->toPlainText() );
    insertItem.addBindValue( _pUI->txtNewCategory->text() );

    if ( _pDB->query( insertItem ) )
    {
        qDebug( "Inventory Information: Inventory item added successfully." );
        QMessageBox::information( this, "Inventory Information", "Item successfully added to database!" );
        _pUI->txtNewName->clear();
        _pUI->txtNewDescription->clear();
        _pUI->txtNewCategory->clear();
        _pUI->txtNewName->setFocus();
    }
    else
    {
        qWarning( "Inventory Error: Inventory item could not be added. Database Error: %s",
                  qPrintable(insertItem.lastError().text() ) );
        QMessageBox::warning( this, "Inventory Error", "Item could not be added to database! See log file for details." );
    }
    refreshMasterList();
}

//! Deletes the item that was double clicked from the inventory.
/*!
  \param item Item to be deleted.
  \see createItem()
*/
void wndInventoryControl::deleteItem( QModelIndex item )
{
    QString itemname = _pUI->tblInventory->model()->data( _pUI->tblInventory->model()->index( item.row(), 1 ) ).toString();

    if ( QMessageBox::question( this, "Confirm Delete", "Are you sure you would like to remove item " + itemname + " from the master inventory?",
                             QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
    {
            QString id = _pUI->tblInventory->model()->data( _pUI->tblInventory->model()->index( item.row(), 0 ) ).toString();
            QSqlQuery deleteQuery;
            deleteQuery.prepare( "DELETE FROM inventory WHERE id=?" );
            deleteQuery.addBindValue( id );
            _pDB->query( deleteQuery );
            refreshMasterList();
    }
}

//! Loads all items from inventory into the table view in the window.
void wndInventoryControl::refreshMasterList( void )
{
    QSqlQuery selectInventory;

    // If the filter category is all, do not condition SELECT query
    if ( _pUI->cmbCategoryFilter->currentText() == "[All]" )
    {
        selectInventory.prepare( "SELECT * FROM inventory" );
    }  
    else // Otherwise, append the filter text to a condition in the query
    {
        selectInventory.prepare( "SELECT * FROM inventory WHERE category=?" );
        selectInventory.addBindValue( _pUI->cmbCategoryFilter->currentText() );
    }

    if ( _pDB->query( selectInventory ) )
    {
        // Create a SQL Query Model for the QTableView
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery( selectInventory );

        // Set header values
        model->setHeaderData( 0, Qt::Horizontal, tr( "Barcode" ) );
        model->setHeaderData( 1, Qt::Horizontal, tr( "Name" ) );
        model->setHeaderData( 2, Qt::Horizontal, tr( "Description" ) );
        model->setHeaderData( 3, Qt::Horizontal, tr( "Category" ) );

        // Set options for the QTableView
        _pUI->tblInventory->setModel( model );
        _pUI->tblInventory->verticalHeader()->hide();
        _pUI->tblInventory->horizontalHeader()->setResizeMode( 1, QHeaderView::Stretch );
        _pUI->tblInventory->horizontalHeader()->setResizeMode( 2, QHeaderView::Stretch );
        _pUI->tblInventory->horizontalHeader()->setResizeMode( 3, QHeaderView::Stretch );
    }
}

//! Prints the barcode label for a number of items in the master inventory list.
/*!
  \param itemRow The row of the item for which to print the barcode lable.
  \see printLabelCurrent()
*/
void wndInventoryControl::printLabel( QVector<int> itemRow )
{
    QPrinter printer;

    // The labels used are 2.25"x0.75"
    // Set page size and margins accordingly
    qreal labelwidth = 2.25;
    qreal labelheight = 0.75;
    printer.setPaperSize( QSizeF( labelwidth, labelheight ), QPrinter::Inch );
    printer.setPageMargins( 0, 0, 0, 0, QPrinter::Inch );

    // PDF printing:
    //printer.setOutputFormat(QPrinter::PdfFormat);
    //printer.setOutputFileName("test.pdf");

    // Build the painter data which is printed
    QPainter painter;

    if ( !painter.begin( &printer ) ) // Link the painter to the printer
    {
        qWarning( "Printer Error: Could not link painter to printer." );
        return;
    }

    for ( int i = 0; i < itemRow.size(); i++ )
    {
        // Get the id column of the QTableView.
        QString codestring = "*" + _pUI->tblInventory->model()->data( _pUI->tblInventory->model()->index( itemRow[i] ,0 ) ).toString() + "*";

        // Draw the plaintext id centered at the top of the label
        painter.setFont( QFont( "Verdana", 10 ) );
        painter.drawText( 0 ,0, (int)( labelwidth * printer.resolution() ), (int)( labelheight * printer.resolution() ),
                          Qt::AlignHCenter, codestring );

        // Switch to the barcode font and do the same
        painter.setFont( QFont( "Free 3 of 9 Extended", 32 ) );
        painter.drawText( 0, 15, (int)( labelwidth * printer.resolution() ), (int)( labelheight * printer.resolution() ),
                          Qt::AlignHCenter, codestring );

        if ( i < itemRow.size() - 1 )
            printer.newPage();
    }

    painter.end(); // Send output
}

//! Prints the barcode label for the currently selected item in the master inventory list.
/*!
  \see printLabel()
*/
void wndInventoryControl::printLabelCurrent( void )
{
    // Verify an item is selected to print for
    if ( _pUI->tblInventory->currentIndex().isValid() )
    {
        // Find the row the currently selected cell is in
        printLabel( QVector<int>( _pUI->tblInventory->currentIndex().row() ) );
    }
}

//! Prints the barcode label for the all items in the master inventory list.
/*!
  \see printLabel()
*/
void wndInventoryControl::printLabelAll( void )
{
    QVector<int> itemRows;
    for ( int i = 0; i < _pUI->tblInventory->model()->rowCount(); i++ )
    {
        itemRows.push_back( i );
    }
    printLabel( itemRows );
}

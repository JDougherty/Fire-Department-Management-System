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

wndinventorycontrol::wndinventorycontrol(QWidget *parent,DatabaseManager *newDb) :
    QMainWindow(parent),
    ui(new Ui::wndinventorycontrol)
{
    ui->setupUi(this);

    ui->cmbCategoryFilter->addItem("[All]");
    QSqlQuery selectCategories;
    selectCategories.prepare("SELECT DISTINCT category FROM inventory");
    if(db->query(selectCategories)){
        while(selectCategories.next()){
            ui->cmbCategoryFilter->addItem(selectCategories.value(0).toString());
        }
    }

    db=newDb;

    connect(ui->cmbCategoryFilter,SIGNAL(currentIndexChanged(QString)),this,SLOT(RefreshMasterList()));
    connect(ui->btnAdd,SIGNAL(clicked()),this,SLOT(CreateItem()));
    connect(ui->tblInventory,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(DeleteItem(QModelIndex)));
    connect(ui->btnPrintLabel,SIGNAL(clicked()),this,SLOT(PrintLabelCurrent()));
    connect(ui->btnPrintAll,SIGNAL(clicked()),this,SLOT(PrintLabelAll()));
    RefreshMasterList();
}

wndinventorycontrol::~wndinventorycontrol()
{
    delete ui;
}

/*
   Function: CreateItem

   Inserts an item into the database using fields
   txtNewName, txtNewDescription, and txtNewCategory
   from the form.

   See Also:

      <DeleteItem>
*/
void wndinventorycontrol::CreateItem()
{
    QSqlQuery insertItem;
    insertItem.prepare("INSERT INTO inventory (name,description,category)"
                       "VALUES(?,?,?)");
    insertItem.addBindValue(ui->txtNewName->text());
    insertItem.addBindValue(ui->txtNewDescription->toPlainText());
    insertItem.addBindValue(ui->txtNewCategory->text());
    if(db->query(insertItem)){
        qDebug("Inventory Information: Inventory item added successfully. ");
        QMessageBox::information(0,"Inventory Information","Item successfully added to database!");
        ui->txtNewName->clear();
        ui->txtNewDescription->clear();
        ui->txtNewCategory->clear();
        ui->txtNewName->setFocus();
    }
    else{
        qWarning("Inventory Error: Inventory item could not be added. Database Error: %s",qPrintable(insertItem.lastError().text()));
        QMessageBox::warning(0,"Inventory Error","Item could not be added to database! See log file for details.");
    }
    RefreshMasterList();
}

/*
   Function: DeleteItem

   Deletes the item that was double clicked
   from the database.

   See Also:

      <CreateItem>
*/
void wndinventorycontrol::DeleteItem(QModelIndex item){
    QString itemname=ui->tblInventory->model()->data(
            ui->tblInventory->model()->index(item.row(),1)
            ).toString();
    if(QMessageBox::question(0,"Confirm Delete",
        "Are you sure you would like to remove item " + itemname + " from the master inventory?",
        QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){

            QString id=ui->tblInventory->model()->data(
                    ui->tblInventory->model()->index(item.row(),0)
                    ).toString();
            QSqlQuery deleteQuery;
            deleteQuery.prepare("DELETE FROM inventory WHERE id=?");
            deleteQuery.addBindValue(id);
            db->query(deleteQuery);
            RefreshMasterList();
    }
}


/*
   Function: RefreshMasterList

   Loads all items from inventory into the table view
   in the window.

*/
void wndinventorycontrol::RefreshMasterList(){

    QSqlQuery selectInventory;
    // If the filter category is all, do not condition SELECT query
    if(ui->cmbCategoryFilter->currentText()=="[All]"){
        selectInventory.prepare("SELECT * FROM inventory");
    }

    // Otherwise, append the filter text to a condition in the query
    else{
        selectInventory.prepare("SELECT * FROM inventory WHERE category=?");
        selectInventory.addBindValue(ui->cmbCategoryFilter->currentText());
    }


    if(db->query(selectInventory)){
        // Create a SQL Query Model for the QTableView
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(selectInventory);

        // Set header values
        model->setHeaderData(0, Qt::Horizontal, tr("Barcode"));
        model->setHeaderData(1, Qt::Horizontal, tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, tr("Description"));
        model->setHeaderData(3, Qt::Horizontal, tr("Category"));

        // Set options for the QTableView
        ui->tblInventory->setModel(model);
        ui->tblInventory->verticalHeader()->hide();
        ui->tblInventory->horizontalHeader()->setResizeMode(1,QHeaderView::Stretch);
        ui->tblInventory->horizontalHeader()->setResizeMode(2,QHeaderView::Stretch);
        ui->tblInventory->horizontalHeader()->setResizeMode(3,QHeaderView::Stretch);
    }
}

/*
   Function: PrintLabel

   Prints the barcode label for a number of items
   in the master inventory list at position itemrow.

   Parameters:

      itemrow - The row of the item for which to
      print the barcode lable.


   See Also:

      <PrintLabelCurrent>
*/
void wndinventorycontrol::PrintLabel(QVector<int> itemrow)
{
    QPrinter printer;

    // The labels used are 2.25"x0.75"
    // Set page size and margins accordingly
    qreal labelwidth=2.25;
    qreal labelheight=0.75;
    printer.setPaperSize(QSizeF(labelwidth,labelheight),QPrinter::Inch);
    printer.setPageMargins(0,0,0,0,QPrinter::Inch);

    // PDF printing:
    //printer.setOutputFormat(QPrinter::PdfFormat);
    //printer.setOutputFileName("test.pdf");

    // Build the painter data which is printed
    QPainter painter;

    if (! painter.begin(&printer)) { // Link the painter to the printer
             qWarning("Printer Error: Could not link painter to printer. ");
             return;
         }

    for(int i=0;i<itemrow.size();i++){
        // Get the id column of the QTableView.
        QString codestring = "*" + ui->tblInventory->model()->data(
                             ui->tblInventory->model()->index(itemrow[i],0)
                             ).toString() + "*";

        // Draw the plaintext id centered at the top of the label
        painter.setFont(QFont("Verdana",10));
        painter.drawText(0,0,
                         (int)(labelwidth*printer.resolution()),
                         (int)(labelheight*printer.resolution()),
                         Qt::AlignHCenter,
                         codestring);

        // Switch to the barcode font and do the same
        painter.setFont(QFont("Free 3 of 9 Extended",32));
        painter.drawText(0,15,
                         (int)(labelwidth*printer.resolution()),
                         (int)(labelheight*printer.resolution()),
                         Qt::AlignHCenter,
                         codestring);

        if(i<itemrow.size()-1)
            printer.newPage();
    }
    // Send output
    painter.end();
}


/*
   Function: PrintLabelCurrent

   Prints the barcode label for the currently selected item
   in the master inventory list.


   See Also:

      <PrintLabel>
*/
void wndinventorycontrol::PrintLabelCurrent(){
    // Verify an item is selected to print for
    if(ui->tblInventory->currentIndex().isValid()){
        //  Find the row the currently selected cell is in
        PrintLabel(QVector<int>(ui->tblInventory->currentIndex().row()));
    }
}

void wndinventorycontrol::PrintLabelAll(){
    QVector<int> itemrows;
    for(int i=0;i<ui->tblInventory->model()->rowCount();i++){
        itemrows.push_back(i);
    }
    PrintLabel(itemrows);
}

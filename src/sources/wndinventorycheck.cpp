#include "../headers/wndinventorycheck.h"
#include "ui_wndinventorycheck.h"

wndInventoryCheck::wndInventoryCheck(QWidget *parent,DatabaseManager *newDb) :
    QMainWindow(parent),
    ui(new Ui::wndInventoryCheck)
{
    ui->setupUi(this);
    populateCategory();
    RefreshTables();
    db=newDb;
    connect(ui->btnReset,SIGNAL(clicked()),this,SLOT(ResetInventoryCheck()));
    connect(ui->txtScanID,SIGNAL(returnPressed()),this,SLOT(itemScanned()));
    connect(ui->btnScan,SIGNAL(clicked()),this,SLOT(itemScanned()));
    connect(ui->btnReport,SIGNAL(clicked()),this,SLOT(printReport()));
}

wndInventoryCheck::~wndInventoryCheck()
{
    delete ui;
}


void wndInventoryCheck::populateCategory(){
    ui->cmbCategory->addItem("[All]");
    QSqlQuery selectCategories;
    selectCategories.prepare("SELECT DISTINCT category FROM inventory");
    if(db->query(selectCategories)){
        while(selectCategories.next()){
            ui->cmbCategory->addItem(selectCategories.value(0).toString());
        }
    }
}

void wndInventoryCheck::RefreshTables(){
    QSqlQuery checkedQuery;
    checkedQuery.prepare("SELECT iid,name FROM inventorycheck WHERE checked=1");
    db->query(checkedQuery);
    QSqlQueryModel *checkmodel = new QSqlQueryModel;
    checkmodel->setQuery(checkedQuery);

    // Set header values
    checkmodel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    checkmodel->setHeaderData(1, Qt::Horizontal, tr("Name"));

    // Set options for the QTableView
    ui->tblCheckedIn->setModel(checkmodel);
    ui->tblCheckedIn->verticalHeader()->hide();
    ui->tblCheckedIn->horizontalHeader()->setResizeMode(0,QHeaderView::Stretch);
    ui->tblCheckedIn->horizontalHeader()->setResizeMode(1,QHeaderView::Stretch);

    QSqlQuery ncheckedQuery;
    ncheckedQuery.prepare("SELECT iid,name FROM inventorycheck WHERE checked=0");
    db->query(ncheckedQuery);
    QSqlQueryModel *ncheckmodel = new QSqlQueryModel;
    ncheckmodel->setQuery(ncheckedQuery);

    // Set header values
    ncheckmodel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    ncheckmodel->setHeaderData(1, Qt::Horizontal, tr("Name"));

    // Set options for the QTableView
    ui->tblNotCheckedIn->setModel(ncheckmodel);
    ui->tblNotCheckedIn->verticalHeader()->hide();
    ui->tblNotCheckedIn->horizontalHeader()->setResizeMode(0,QHeaderView::Stretch);
    ui->tblNotCheckedIn->horizontalHeader()->setResizeMode(1,QHeaderView::Stretch);

}


void wndInventoryCheck::ResetInventoryCheck(){
    if(QMessageBox::question(0,"Inventory Information: Confirm Reset","Are you sure you would like to reset the inventory check?",QMessageBox::Yes,QMessageBox::No)
        == QMessageBox::Yes){

        QSqlQuery qryDelete ("DELETE FROM inventorycheck WHERE 1=1");
        db->query(qryDelete);

        QSqlQuery copyQuery;
        // If the filter category is all, do not condition SELECT query
        if(ui->cmbCategory->currentText()=="[All]"){
            copyQuery.prepare("INSERT INTO inventorycheck (iid,name,description,category,checked) SELECT id,name,description,category,0 FROM inventory");
        }

        // Otherwise, append the filter text to a condition in the query
        else{
            copyQuery.prepare("INSERT INTO inventorycheck (iid,name,description,category,checked) SELECT id,name,description,category,0 FROM inventory WHERE inventory.category=?");
            copyQuery.addBindValue(ui->cmbCategory->currentText());
        }
        if(db->query(copyQuery)){

        }
        else{
            QMessageBox::warning(0,"Inventory Error","Could not copy inventory into check table. See log for more information.");
            qWarning("Inventory Error: Could not copy inventory into check table. Database Error: %s",qPrintable(copyQuery.lastError().text()));
        }
        RefreshTables();
    }
}

void wndInventoryCheck::itemScanned(){
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE inventorycheck SET checked=1 WHERE id=?");
    updateQuery.addBindValue(ui->txtScanID->text());
    if(db->query(updateQuery)){
        if(updateQuery.numRowsAffected()==1){
            RefreshTables();
        }
        else{
            QMessageBox::information(0,"Inventory Information","Item with ID " + ui->txtScanID->text() + " not found in not-checked list.");
        }
    }
    else{
        QMessageBox::warning(0,"Inventory Error","There was a problem checking this item into inventory. See log for more information.");

    }
    ui->txtScanID->clear();
    ui->txtScanID->setFocus();
}


void wndInventoryCheck::printReport(){
    QPrinter printer;
    printer.setPaperSize(QPrinter::Letter);
    printer.setPageMargins(1,1,1,1,QPrinter::Inch);

    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    if(dialog->exec()!=QDialog::Accepted){
        return;
    }

    // PDF printing:
    //printer.setOutputFormat(QPrinter::PdfFormat);
    //printer.setOutputFileName("test.pdf");

    // Build the painter data which is printed
    QPainter painter;

    if (! painter.begin(&printer)) { // Link the painter to the printer
             qWarning("Printer Error: Could not link painter to printer. ");
             return;
    }

    painter.setFont(QFont("Courier New",12,QFont::Bold));

    int pw=(int)(printer.pageRect(QPrinter::DevicePixel).width());
    int ph=(int)(printer.pageRect(QPrinter::DevicePixel).height());
    int y=0;
    painter.drawText(0,0,pw,ph,
                     Qt::AlignHCenter,
                     "Station 40 - Youngsville Fire Department\n"
                     "Inventory Audit Report\n"  + QDate::currentDate().toString("dddd the d of MMMM yyyy"));
    y=80;
    if(ui->chkCheckedItems->isChecked()){
        painter.drawText(0,y,pw,ph,Qt::AlignLeft,"Checked Items");
        y+=20;

        for(int i=0;i<ui->tblCheckedIn->model()->rowCount();i++){
            painter.drawText(20,y,pw,ph,Qt::AlignLeft,
                ui->tblCheckedIn->model()->index(i,1).data().toString());
            y+=20;
        }
    }
    if(ui->chkMissingItems->isChecked()){
        painter.drawText(0,y,pw,ph,Qt::AlignLeft,"Missing Items");
        y+=20;
        for(int i=0;i<ui->tblNotCheckedIn->model()->rowCount();i++){
            painter.drawText(20,y,pw,ph,Qt::AlignLeft,
                ui->tblNotCheckedIn->model()->index(i,1).data().toString());
            y+=20;
        }
    }
    painter.end();
}

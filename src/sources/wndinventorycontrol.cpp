#include "../headers/wndinventorycontrol.h"
#include "ui_wndinventorycontrol.h"

wndinventorycontrol::wndinventorycontrol(QWidget *parent,DatabaseManager *newDb) :
    QMainWindow(parent),
    ui(new Ui::wndinventorycontrol)
{
    ui->setupUi(this);
    db=newDb;
    ui->cmbCategoryFilter->addItem("[All]");
    QSqlQuery selectCategories;
    selectCategories.prepare("SELECT DISTINCT category FROM inventory");
    if(db->query(selectCategories)){
        while(selectCategories.next()){
            ui->cmbCategoryFilter->addItem(selectCategories.value(0).toString());
        }
    }
}

wndinventorycontrol::~wndinventorycontrol()
{
    delete ui;
}

void wndinventorycontrol::on_btnAdd_clicked()
{
    QSqlQuery insertItem;
    insertItem.prepare("INSERT INTO inventory (name,description,category)"
                       "VALUES(?,?,?)");
    insertItem.addBindValue(ui->txtNewName->text());
    insertItem.addBindValue(ui->txtNewDescription->toPlainText());
    insertItem.addBindValue(ui->txtNewCategory->text());
    if(db->query(insertItem)){
        qDebug("Inventory item added successfully. ");
        QMessageBox::information(0,"Database Operation","Item successfully added to database!");
        ui->txtNewName->clear();
        ui->txtNewDescription->clear();
        ui->txtNewCategory->clear();
        ui->txtNewName->setFocus();
    }
    else{
        qWarning("Invetory item not added. %s",qPrintable(insertItem.lastError().text()));
        QMessageBox::warning(0,"Database Operation","Item was not added to database! See log file for details.");
    }
}


void wndinventorycontrol::on_cmbCategoryFilter_currentIndexChanged(QString )
{
    QSqlQuery selectInventory;
    if(ui->cmbCategoryFilter->currentText()=="[All]"){
        selectInventory.prepare("SELECT * FROM inventory");
    }
    else{
        selectInventory.prepare("SELECT * FROM inventory WHERE category=?");
        selectInventory.addBindValue(ui->cmbCategoryFilter->currentText());
    }

    if(db->query(selectInventory)){
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(selectInventory);
        model->setHeaderData(0, Qt::Horizontal, tr("Barcode"));
        model->setHeaderData(1, Qt::Horizontal, tr("Name"));
        model->setHeaderData(2, Qt::Horizontal, tr("Description"));
        model->setHeaderData(3, Qt::Horizontal, tr("Category"));

        ui->tblInventory->setModel(model);
        ui->tblInventory->verticalHeader()->hide();
        ui->tblInventory->horizontalHeader()->setResizeMode(1,QHeaderView::Stretch);
        ui->tblInventory->horizontalHeader()->setResizeMode(2,QHeaderView::Stretch);
        ui->tblInventory->horizontalHeader()->setResizeMode(3,QHeaderView::Stretch);
    }
}

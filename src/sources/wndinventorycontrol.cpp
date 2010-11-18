#include "../headers/wndinventorycontrol.h"
#include "ui_wndinventorycontrol.h"

wndinventorycontrol::wndinventorycontrol(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wndinventorycontrol)
{
    ui->setupUi(this);
    ui->tblInventory->horizontalHeader()->setResizeMode(1,QHeaderView::Stretch);
    ui->tblInventory->horizontalHeader()->setResizeMode(2,QHeaderView::Stretch);
    ui->tblInventory->horizontalHeader()->setResizeMode(3,QHeaderView::Stretch);
}

wndinventorycontrol::~wndinventorycontrol()
{
    delete ui;
}

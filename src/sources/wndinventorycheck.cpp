#include "../headers/wndinventorycheck.h"
#include "ui_wndinventorycheck.h"

wndInventoryCheck::wndInventoryCheck(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wndInventoryCheck)
{
    ui->setupUi(this);
}

wndInventoryCheck::~wndInventoryCheck()
{
    delete ui;
}

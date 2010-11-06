#include "wndsearch.h"
#include "ui_wndsearch.h"

wndSearch::wndSearch(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wndSearch)
{
    ui->setupUi(this);
}

wndSearch::~wndSearch()
{
    delete ui;
}

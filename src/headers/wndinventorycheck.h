#ifndef WNDINVENTORYCHECK_H
#define WNDINVENTORYCHECK_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QDate>
#include "databasemanager.h"

namespace Ui {
    class wndInventoryCheck;
}

class wndInventoryCheck : public QMainWindow
{
    Q_OBJECT

public:
    explicit wndInventoryCheck(QWidget *parent = 0,DatabaseManager *newDb=0);
    ~wndInventoryCheck();

private:
    Ui::wndInventoryCheck *ui;
    DatabaseManager *db;
    void populateCategory();
    void RefreshTables();

private slots:
    void ResetInventoryCheck();
    void itemScanned();
    void printReport();
};

#endif // WNDINVENTORYCHECK_H

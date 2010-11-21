#ifndef WNDINVENTORYCONTROL_H
#define WNDINVENTORYCONTROL_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include "databasemanager.h"

namespace Ui {
    class wndinventorycontrol;
}

class wndinventorycontrol : public QMainWindow
{
    Q_OBJECT

public:
    explicit wndinventorycontrol(QWidget *parent = 0,DatabaseManager *newDb=0);
    ~wndinventorycontrol();

private:
    Ui::wndinventorycontrol *ui;
    DatabaseManager *db;
    void PrintLabel(QVector<int> itemrow);

private slots:
    void CreateItem();
    void DeleteItem(QModelIndex);
    void RefreshMasterList();
    void PrintLabelCurrent();
    void PrintLabelAll();
};

#endif // WNDINVENTORYCONTROL_H

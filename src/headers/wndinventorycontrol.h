#ifndef WNDINVENTORYCONTROL_H
#define WNDINVENTORYCONTROL_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQueryModel>
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

private slots:
    void on_cmbCategoryFilter_currentIndexChanged(QString );
    void on_btnAdd_clicked();
};

#endif // WNDINVENTORYCONTROL_H

#ifndef WNDACTIVECALL_H
#define WNDACTIVECALL_H

#include <QMainWindow>
#include <QMessageBox>
#include <QList>
#include "databasemanager.h"

namespace Ui {
    class wndActiveCall;
}

class wndActiveCall : public QMainWindow
{
    Q_OBJECT

public:
    explicit wndActiveCall(QWidget *parent = 0,DatabaseManager *newDb=0);
    ~wndActiveCall();

private:
    Ui::wndActiveCall *ui;
    DatabaseManager *db;

private slots:
    void on_pushButton_clicked();
};

#endif // WNDACTIVECALL_H

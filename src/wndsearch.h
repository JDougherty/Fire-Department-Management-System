#ifndef WNDSEARCH_H
#define WNDSEARCH_H

#include <QMainWindow>
#include "databasemanager.h"

namespace Ui {
    class wndSearch;
}

class wndSearch : public QMainWindow
{
    Q_OBJECT

public:
    explicit wndSearch(QWidget *parent = 0);
    explicit wndSearch(QWidget *parent = 0, DatabaseManager *newDb=0, QString dtype="", QString query="");
    ~wndSearch();

private:
    Ui::wndSearch *ui;
    void Search(QString dtype, QString query);
    DatabaseManager *db;
};

#endif // WNDSEARCH_H

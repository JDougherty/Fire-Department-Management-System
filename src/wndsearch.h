#ifndef WNDSEARCH_H
#define WNDSEARCH_H

#include <QMainWindow>

namespace Ui {
    class wndSearch;
}

class wndSearch : public QMainWindow
{
    Q_OBJECT

public:
    explicit wndSearch(QWidget *parent = 0);
    ~wndSearch();

private:
    Ui::wndSearch *ui;
};

#endif // WNDSEARCH_H

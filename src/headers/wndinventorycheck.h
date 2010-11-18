#ifndef WNDINVENTORYCHECK_H
#define WNDINVENTORYCHECK_H

#include <QMainWindow>

namespace Ui {
    class wndInventoryCheck;
}

class wndInventoryCheck : public QMainWindow
{
    Q_OBJECT

public:
    explicit wndInventoryCheck(QWidget *parent = 0);
    ~wndInventoryCheck();

private:
    Ui::wndInventoryCheck *ui;
};

#endif // WNDINVENTORYCHECK_H

#ifndef WNDACTIVECALL_H
#define WNDACTIVECALL_H

#include <QMainWindow>
#include <QList>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QObjectList>

namespace Ui {
    class wndActiveCall;
}

class wndActiveCall : public QMainWindow
{
    Q_OBJECT

public:
    explicit wndActiveCall(QWidget *parent = 0);
    ~wndActiveCall();

private:
    Ui::wndActiveCall *ui;

private slots:
    void on_pushButton_clicked();
};

#endif // WNDACTIVECALL_H

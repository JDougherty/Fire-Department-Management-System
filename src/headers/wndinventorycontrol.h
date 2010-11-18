#ifndef WNDINVENTORYCONTROL_H
#define WNDINVENTORYCONTROL_H

#include <QMainWindow>

namespace Ui {
    class wndinventorycontrol;
}

class wndinventorycontrol : public QMainWindow
{
    Q_OBJECT

public:
    explicit wndinventorycontrol(QWidget *parent = 0);
    ~wndinventorycontrol();

private:
    Ui::wndinventorycontrol *ui;
};

#endif // WNDINVENTORYCONTROL_H

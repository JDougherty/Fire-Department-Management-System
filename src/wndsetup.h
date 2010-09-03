/*
    Fire Department Management System
    Copyright (C) 2010  Joseph W. Dougherty

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#ifndef WNDSETUP_H
#define WNDSETUP_H

#include <QMainWindow>

namespace Ui {
    class wndSetup;
}

class wndSetup : public QMainWindow {
    Q_OBJECT
public:
    wndSetup(QWidget *parent = 0);
    ~wndSetup();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::wndSetup *ui;
};

#endif // WNDSETUP_H

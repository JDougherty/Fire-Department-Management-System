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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDir>
#include <QPluginLoader>
#include <QMainWindow>
#include <QMdiArea>
#include <QMessageBox>

#include "plugins/DatabasePlugin.h"
#include "plugins/MDIWindowPlugin.h"
#include "MDIWindow.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::MainWindow *ui;
        QMdiArea                *mdiArea;
        bool loadPlugin();
        DatabasePlugin *_DatabasePlugin;
        MDIWindowPlugin *_MDIWindowPlugin;

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();
};

#endif // MAINWINDOW_H

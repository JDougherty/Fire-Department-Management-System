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

#include "../headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);

    mdiArea = new QMdiArea;
    mdiArea->setBackground( QBrush::QBrush( QColor::QColor( 128, 128, 128 ) ) );
    mdiArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    mdiArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    setCentralWidget( mdiArea );

    if (!loadPlugin()) {
        QMessageBox::information(this, "Error", "Could not load the plugin");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::loadPlugin()
{
    QDir pluginsDir(qApp->applicationDirPath());
    qDebug( qPrintable( qApp->applicationDirPath() ) );

    #if defined(Q_OS_WIN)
    if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
    {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#elif defined(Q_OS_MAC)
    if (pluginsDir.dirName() == "MacOS") {
        pluginsDir.cdUp();
        pluginsDir.cdUp();
        pluginsDir.cdUp();
    }
#endif

    pluginsDir.cd( "plugins" );

    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            DatabasePlugin *databasePlugin = qobject_cast<DatabasePlugin *>(plugin);
            MDIWindowPlugin *mdiWindowPlugin = qobject_cast<MDIWindowPlugin *>(plugin);
            if (databasePlugin)
            {
                _DatabasePlugin = databasePlugin;
            }
            if (mdiWindowPlugin)
            {
                _MDIWindowPlugin = mdiWindowPlugin;
                _MDIWindowPlugin->menuBar( ui->menuTools );
                _MDIWindowPlugin->getInstance( this, mdiArea );
            }
        }
    }
    return true;
}

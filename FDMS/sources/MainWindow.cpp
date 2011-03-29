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

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow (QWidget *pParent ) :
    QMainWindow( pParent )
{
    _pUI = new Ui::MainWindow;
    _pUI->setupUi( this );

    _pMDIArea = new QMdiArea;
    _pMDIArea->setBackground( QBrush::QBrush( QColor::QColor( 128, 128, 128 ) ) );
    _pMDIArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    _pMDIArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    setCentralWidget( _pMDIArea );
}

MainWindow::~MainWindow( void )
{
    delete _pUI;
}

void MainWindow::registerPlugins( void )
{
    PluginManager *pm = getPluginManager();

    foreach ( MDIWindowPlugin *mdiWindowPlugin, pm->lMDIWindowPlugins )
    {
        mdiWindowPlugin->menuBar( _pUI->menuTools );
        mdiWindowPlugin->getInstance( this, _pMDIArea );
    }
}

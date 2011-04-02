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

#ifndef WNDFIREFIGHTERPLUGIN_H
#define WNDFIREFIGHTERPLUGIN_H

#include <QMenu>
#include <QObject>
#include <QtCore/QtPlugin>

#include "plugins/DependencyList.h"
#include "plugins/MDIWindowPlugin.h"
#include "plugins/PluginInfo.h"
#include "MDIWindow.h"
#include "wndFirefighter.h"

class wndFirefighterPlugin : public QObject, MDIWindowPlugin
{
    Q_OBJECT
    Q_INTERFACES( MDIWindowPlugin )

    public:
        PluginInfo                  getPluginInfo( void );
        DependencyList              getDependencies( void );

        MDIWindow *                 getInstance( QWidget *pParent );
        MDIWindow *                 getInstance( QWidget *pParent, QMdiArea *pMDIArea );

        void                        menuBar( QMenu *pMenuBar );
};

#endif // WNDFIREFIGHTERPLUGIN_H

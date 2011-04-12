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

#ifndef MDIWINDOWPLUGIN_H
#define MDIWINDOWPLUGIN_H

#include <QMdiArea>
#include <QMenu>
#include <QString>

#include "BasePlugin.h"
#include "MDIWindow.h"

class MDIWindowPlugin : public BasePlugin
{
    public:
        virtual                     ~MDIWindowPlugin( void ) {}

        virtual MDIWindow *         getInstance( QWidget *pParent, QMdiArea *pMDIArea ) = 0;

        virtual void                menuBar( QMenu *pMenuBar ) = 0;
};

Q_DECLARE_INTERFACE( MDIWindowPlugin, "com.FDS.Plugin.MDIWindow/1.0" );

#endif // MDIWINDOWPLUGIN_H

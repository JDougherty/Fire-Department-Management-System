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

#include "wndCallPlugin.h"

PluginInfo wndCallPlugin::getInfo( void )
{
    return PluginInfo( "wndCall", "0.01" );
}

DependencyList wndCallPlugin::getDependencies( void )
{
    DependencyList dependencies;
    dependencies.add( PluginInfo( "Call", "0.01" ) );
    return dependencies;
}

void wndCallPlugin::addToMenuBar( QMenu *pMenuBar )
{
    QIcon icon;
    icon.addFile( QString::fromUtf8( ":/icons/AddCall.png" ), QSize(), QIcon::Normal, QIcon::Off );
    QAction *a = new QAction(icon, tr( "Add Call"), pMenuBar );

    connect( a, SIGNAL( triggered() ), this, SLOT( showWindow() ) );
    pMenuBar->addAction( a );
}

void wndCallPlugin::showWindow( void )
{
    MDIWindow *pMDIWindow = getInstance( NULL );
    _pMDIArea->addSubWindow(pMDIWindow);
    pMDIWindow->show();
}

MDIWindow* wndCallPlugin::getInstance( QWidget *pParent )
{
    return new wndCall( pParent );
}

Q_EXPORT_PLUGIN2( wndcall, wndCallPlugin );

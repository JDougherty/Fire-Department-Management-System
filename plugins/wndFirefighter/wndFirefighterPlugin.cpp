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

#include "wndFirefighterPlugin.h"

PluginInfo wndFirefighterPlugin::getInfo( void )
{
    return PluginInfo( "wndFirefighter", "0.01" );
}

DependencyList wndFirefighterPlugin::getDependencies( void )
{
    DependencyList dependencies;
    dependencies.add( PluginInfo( "Firefighter", "0.01" ) );
    return dependencies;
}

void wndFirefighterPlugin::addToMenuBar( QMenu *pMenuBar )
{
    QIcon icon;
    icon.addFile( QString::fromUtf8( ":/icons/AddFirefighter.png" ), QSize(), QIcon::Normal, QIcon::Off );
    QAction *a = new QAction(icon, tr( "Add Firefighter"), pMenuBar );

    connect( a, SIGNAL( triggered() ), this, SLOT( showWindow() ) );
    pMenuBar->addAction( a );
}

void wndFirefighterPlugin::showWindow( void )
{
    MDIWindow *pMDIWindow = getInstance( NULL );
    _pMDIArea->addSubWindow(pMDIWindow);
    pMDIWindow->show();
}

MDIWindow* wndFirefighterPlugin::getInstance( QWidget *pParent )
{
    return new wndFirefighter( pParent );
}

Q_EXPORT_PLUGIN2( wndfirefighter, wndFirefighterPlugin );

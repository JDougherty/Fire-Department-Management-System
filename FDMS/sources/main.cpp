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

#include <QObject>
#include <QtGui/QApplication>

#include "managers/DatabaseManager.h"
#include "managers/PluginManager.h"
#include "managers/SettingManager.h"
#include "wndMain.h"
#include "wndSetup.h"

int main( int argc, char *argv[] )
{
    QApplication application( argc, argv );
    SettingManager *pSM = SettingManager::getInstance();
    DatabaseManager *pDBM = DatabaseManager::getInstance();
    PluginManager *pPM = PluginManager::getInstance();

    if ( !pSM->existsFile() || !pSM->loadValues() )
    {
        qDebug( "%s", qPrintable( QObject::tr( "Running setup." ) ) );
        wndSetup s;
        s.show();
        return application.exec();
    }

    if ( !pDBM->getFile() || !pDBM->existsFile() || !pDBM->open() )
    {
        int iResult = QMessageBox::critical( 0, QObject::tr( "Error" ), QObject::tr( "DatabaseManager could not be initialized. Run setup?" ), QMessageBox::Yes | QMessageBox::No );

        switch ( iResult )
        {
            case QMessageBox::Yes:
            {
                qDebug( "%s", qPrintable( QObject::tr( "Running setup." ) ) );
                wndSetup s;
                s.show();
                return application.exec();
            }
            case QMessageBox::No:
            {
                QMessageBox::critical( 0, QObject::tr( "Error" ), QObject::tr( "Startup cannnot continue. Closing program." ), QMessageBox::Ok );
                qCritical( "%s", qPrintable( QObject::tr( "Startup cannot continue." ) ) );
                return 0;
            }
        }
    }

    if ( !pPM->getFolder() || !pPM->existsFolder() ||!pPM->loadPlugins() )
    {
        int iResult = QMessageBox::critical( 0, QObject::tr( "Error" ), QObject::tr( "PluginManager could not be initialized. Run setup?" ),
                                             QMessageBox::Yes | QMessageBox::No );

        switch ( iResult )
        {
            case QMessageBox::Yes:
            {
                qDebug( "%s", qPrintable( QObject::tr( "Running program setup." ) ) );
                wndSetup s;
                s.show();
                return application.exec();
            }
            case QMessageBox::No:
            {
                QMessageBox::critical( 0, QObject::tr( "Error" ), QObject::tr( "Startup cannnot continue. Closing program." ), QMessageBox::Ok );
                qCritical( "%s", qPrintable( QObject::tr( "Startup cannot continue." ) ) );
                return 0;
            }
        }
    }

    getWNDMain()->registerWithPlugins();
    getWNDMain()->show();
    return application.exec();
}

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

#include <QtGui/QApplication>
#include <QMessageBox>
#include <QString>
#include <QDateTime>
#include <QFontDatabase>
#include <QSettings>

#include "../headers/LogFunctions.h"
#include "../headers/databasemanager.h"
#include "../headers/mainwindow.h"
#include "../headers/wndsetup.h"

int main( int argc, char *argv[] )
{
    QApplication application( argc, argv );
    QSettings settings( "config.ini", QSettings::IniFormat );
    QString sDBFilename;
    DatabaseManager db( "fdms.db" );
    MainWindow mw( 0, &db );

    // save the settings
    settings.beginGroup( "database" );
    settings.setValue( "filename", "fdms.db" );
    settings.endGroup();

    // load the settings
    sDBFilename = settings.value( "database/filename" ).toString();

    //setupDebugRedirection();

    qDebug( "Initialized at %s", QDateTime::currentDateTime().toString().toStdString().c_str() );

    QFile res( ":/fonts/FRE3OF9X.TTF" );
    if ( res.open( QIODevice::ReadOnly ) )
    {
        QFontDatabase::addApplicationFontFromData( res.readAll() );
    }
    else
    {
        qWarning( "Resource Error: Could not load Free 3 of 9 Extended barcode font." );
    }

    if ( !db.exists() )
    {
        wndSetup setup( 0, &db, &mw );
        setup.show();

        qDebug( "Running program setup." );

        if ( !db.open() )
        {
            QMessageBox::critical( &setup, "Critical Error", "Database could not be opened.", QMessageBox::Ok );
            qCritical( "Critical Error - Database: Could not be opened." );
            return 0;
        }

        if ( !db.build() )
        {
            QMessageBox::critical( &setup, "Critical Error", "Database could not be built.", QMessageBox::Ok );
            qCritical( "Critical Error - Database: Could not be built." );
            return 0;
        }

        if ( !db.verify() )
        {
            QMessageBox::critical( &setup, "Critical Error", "Database has an invalid structure.", QMessageBox::Ok );
            qCritical( "Critical Error - Database: Invalid structure." );
            return 0;
        }

         return application.exec();
    }
    else
    {
        mw.showMaximized();

        if ( !db.open() )
        {
            QMessageBox::critical( &mw, "Critical Error", "Database could not be opened.", QMessageBox::Ok );
            qCritical( "Critical Error - Database: Could not be opened." );
            return 0;
        }

        if ( !db.verify() )
        {
            QMessageBox::critical( &mw, "Critical Error", "Database has an invalid structure.", QMessageBox::Ok );
            qCritical( "Critical Error - Database: Invalid structure." );
            return 0;
        }

         return application.exec();
    }
}

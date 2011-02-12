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

#ifndef LOGFUNCTIONS_H
#define LOGFUNCTIONS_H

#include <QFile>
#include <QTextStream>

QFile debugLogFile;
QTextStream debugErr;

//! Prepend message type labels to textstream output
void msgRedirection( QtMsgType type, const char *msg )
{
    switch ( type )
    {
        case QtDebugMsg:
            debugErr << "Debug Notice: " << QString( msg ) << endl;
            break;
        case QtWarningMsg:
            debugErr << "Warning: " << msg << endl;
            break;
        case QtCriticalMsg:
            debugErr << "Critical :" << msg << endl;
            break;
        case QtFatalMsg:
            debugErr << "Fatal: " << msg << endl;
            abort();
    }
}

//! Redirect all debug output to a log file
void setupDebugRedirection()
{
    debugLogFile.setFileName( "fdms.log" );
    debugErr.setDevice( &debugLogFile );
    debugLogFile.open( QIODevice::Append | QIODevice::Text );
    qInstallMsgHandler( msgRedirection );
    debugErr << endl;
}

#endif // LOGFUNCTIONS_H

#ifndef LOGFUNCTIONS_H
#define LOGFUNCTIONS_H
#include<QFile>
#include<QTextStream>

QFile debugLogFile;
QTextStream debugErr;

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

void setupDebugRedirection()
{
    debugLogFile.setFileName( "fdms.log" );
    debugErr.setDevice( &debugLogFile );
    debugLogFile.open( QIODevice::WriteOnly | QIODevice::Text );
    qInstallMsgHandler( msgRedirection );
}


#endif // LOGFUNCTIONS_H

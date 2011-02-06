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

#include "../headers/settingsmanager.h"

SettingsManager::SettingsManager( QString sConfigName )
{
    _sConfigName = sConfigName;
    _sPath = buildPath( _sConfigName );
    _sDBFile = QString::null;

    _pSettings = new QSettings( "config.ini", QSettings::IniFormat );
}

SettingsManager::~SettingsManager( void )
{
    delete _pSettings;
}

/*
    Function:    DatabaseManager::buildPath
    Purpose:     Builds the file path for the config file
    Parameters:
        QString sFileName - file name
    Returns:     QString - the file path + file name
*/
QString SettingsManager::buildPath( QString sFileName )
{
    QString sFilePath;

    #ifdef Q_OS_LINUX
    // Database file must be located in user home folder in Linux
    sFilePath = QDir::home().sFilePath();
    sFilePath.append( QDir::separator() ).append( sFileName );
    sFilePath = QDir::toNativeSeparators( sFilePath );
    #else
    sFilePath = sFileName;
    #endif

    return sFilePath;
}

/*
    Function:    SettingsManager::exists
    Purpose:     See if the config file exists
    Returns:     bool
        true - Config file exists
        false - Config file dne
*/
bool SettingsManager::exists( void )
{
    if ( !QFile::exists( _sPath ) )
    {
        qDebug( "%s does not exist.", qPrintable( _sPath ) );
        return false;
    }

    qDebug( "%s exists.", qPrintable( _sPath ) );
    return true;
}

/*
    Function:    SettingsManager::remove
    Purpose:     Deletes the config file
    Returns:     bool
        true - Successfully deleted the config file
        false - Failed to delete config file

    See Also:    <Divide>
*/
bool SettingsManager::remove( void )
{
    return QFile::remove( _sPath ); // Remove created database binary file
}

void SettingsManager::setDBFile( QString sDBFile )
{
    _sDBFile = sDBFile;
}

QString SettingsManager::getDBFile( void )
{
    return _sDBFile;
}

void SettingsManager::load( void )
{
    _sDBFile = _pSettings->value( "database/file" ).toString();
}

void SettingsManager::save( void )
{
    _pSettings->beginGroup( "database" );
    _pSettings->setValue( "file", _sDBFile );
    _pSettings->endGroup();
}

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

SettingsManager* SettingsInstance( void )
{
        static SettingsManager sm;
        return &sm;
}

/*!
  \param sConfigName Name of the configuration file.
*/
SettingsManager::SettingsManager( void )
{
    _pSettings = new QSettings( QSettings::IniFormat, QSettings::UserScope, "FDMS", "FDMS" );

    _sDBFile = QString::null;
}

SettingsManager::~SettingsManager( void )
{
    delete _pSettings;
}

//! See if the config file exists.
/*!
  \return bool - Config file exists.
*/
bool SettingsManager::exists( void )
{
    if ( !QFile::exists( _pSettings->fileName() ) )
    {
        qDebug( "Settings Manager: %s does not exist.", qPrintable( _pSettings->fileName() ) );
        return false;
    }

    qDebug( "Settings Manager: %s exists.", qPrintable( _pSettings->fileName() ) );
    return true;
}

//! Deletes the config file.
/*!
  \return bool - Able to remove the config file.
*/
bool SettingsManager::remove( void )
{
    return QFile::remove( _pSettings->fileName() );
}

//! Sets DB File string.
/*!
  \param sDBFile Path + file name of the database.
*/
void SettingsManager::setDBFile( QString sDBFile )
{
    _sDBFile = sDBFile;
}

//! Gets DB File string.
/*!
  \return QString - DB file path.
*/
QString SettingsManager::getDBFile( void )
{
    return _sDBFile;
}

//! Load the values from the config file.
void SettingsManager::load( void )
{
    qDebug( "Settings Manager: Loading values from %s", qPrintable( _pSettings->fileName() ) );
    _sDBFile = _pSettings->value( "database/file" ).toString();
}

//! Save values to the config file.
void SettingsManager::save( void )
{
    qDebug( "Settings Manager: Saving values to %s", qPrintable( _pSettings->fileName() ) );
    _pSettings->beginGroup( "database" );
    _pSettings->setValue( "file", _sDBFile );
    _pSettings->endGroup();
}

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

#include "managers/SettingManager.h"

SettingManager* SettingManager::getInstance( void )
{
    static SettingManager sm;
    return &sm;
}

SettingManager::SettingManager( void )
{
    _pSettings = new QSettings( QSettings::IniFormat, QSettings::UserScope, "FDMS", "FDMS" );
}

SettingManager::~SettingManager( void )
{
    if ( existsFile() ) saveValues();
    delete _pSettings;
}

bool SettingManager::existsFile( void )
{
    if ( !QFile::exists( _pSettings->fileName() ) )
    {
        qDebug( qPrintable( QObject::QObject::tr( "SettingManager: %s does not exist." ) ), qPrintable( _pSettings->fileName() ) );
        return false;
    }

    qDebug( qPrintable( QObject::tr( "SettingManager: %s exists." ) ), qPrintable( _pSettings->fileName() ) );
    return true;
}

bool SettingManager::deleteFile( void )
{
    bool bRemoved = QFile::remove( _pSettings->fileName() ); // Remove the INI file

    if ( bRemoved )
        qDebug( qPrintable( QObject::tr( "SettingManager: Removed %s" ) ), qPrintable( _pSettings->fileName() ) );
    else
        qDebug( qPrintable( QObject::tr( "SettingManager: Failed to remove %s" ) ), qPrintable( _pSettings->fileName() ) );

    return bRemoved;
}

bool SettingManager::saveValues( void )
{
    qDebug( qPrintable( QObject::tr( "SettingManager: Saving values to %s" ) ), qPrintable( _pSettings->fileName() ) );

    QMapIterator<QString, QVariant> itr( _Entries );
    while ( itr.hasNext() )
    {
        itr.next();
        _pSettings->setValue( itr.key(), itr.value() );
    }

    return true;
}

bool SettingManager::loadValues( void )
{
    QStringList keys = _pSettings->allKeys();
    QVariant vValue;

    qDebug( qPrintable( QObject::tr( "SettingManager: Loading values from %s" ) ), qPrintable( _pSettings->fileName() ) );
    _Entries.clear();

    foreach ( QString sKey, keys )
    {
        vValue = _pSettings->value( sKey );
        _Entries.insert( sKey, vValue );
        qDebug( qPrintable( QObject::tr( "SettingManager: Loaded %s : %s" ) ), qPrintable( sKey ), qPrintable( vValue.toString() ) );
    }

    return true;
}

bool SettingManager::setValue( QString sKey, QVariant vValue )
{
    _Entries.insert( sKey, vValue );
    qDebug( qPrintable( QObject::tr( "SettingManager: Set %s : %s", qPrintable( sKey ) ) ), qPrintable( vValue.toString() ) );

    return true;
}

QVariant SettingManager::getValue( QString sKey )
{

    qDebug( qPrintable( QObject::tr( "SettingManager: Get %s : %s", qPrintable( sKey ) ) ), qPrintable( _Entries[sKey].toString() ) );
    return _Entries[sKey];
}

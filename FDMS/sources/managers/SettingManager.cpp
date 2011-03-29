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

#include <QFile>
#include <QDir>

#include "managers/SettingManager.h"

SettingManager* GetSettingManager( void )
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
    delete _pSettings;
}

void SettingManager::set( QString sKey, QVariant vValue )
{
    _Entries.insert( sKey, vValue );
    qDebug( "SettingManager: Set %s:%s", qPrintable( key ), qPrintable( value.toString() ) );
}

bool SettingManager::exists( void )
{
    if ( !QFile::exists( _pSettings->fileName() ) )
    {
        qDebug( "SettingManager: %s does not exist.", qPrintable( _pSettings->fileName() ) );
        return false;
    }

    qDebug( "SettingManager: %s exists.", qPrintable( _pSettings->fileName() ) );
    return true;
}

bool SettingManager::remove( void )
{
    return QFile::remove( _pSettings->fileName() );
}

void SettingManager::load( void )
{
    QStringList keys = _pSettings->allKeys();
    QVariant value;

    qDebug( "SettingManager: Loading values from %s", qPrintable( _pSettings->fileName() ) );
    _Entries.clear();

    foreach ( QString key, keys )
    {
        value = _pSettings->value( key );
        _Entries.insert( key, value );
        qDebug( "SettingManager: Loaded %s:%s", qPrintable( key ), qPrintable( value.toString() ) );
    }
}

void SettingManager::save( void )
{
    qDebug( "SettingManager: Saving values to %s", qPrintable( _pSettings->fileName() ) );

    QMapIterator<QString, QVariant> itr( _Entries );
    while ( itr.hasNext() )
    {
        itr.next();
        _pSettings->setValue( itr.key(), itr.value() );
    }
}

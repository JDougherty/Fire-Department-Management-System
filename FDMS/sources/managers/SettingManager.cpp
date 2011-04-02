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

SettingManager* getSettingManager( void )
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
    save();
    delete _pSettings;
}

bool SettingManager::initialize( void )
{
    if ( !exists() ) return false;

    load();
    return true;
}

bool SettingManager::exists( void )
{
    if ( !QFile::exists( _pSettings->fileName() ) )
    {
        qDebug( qPrintable( QObject::QObject::tr( "SettingManager: %s does not exist." ) ), qPrintable( _pSettings->fileName() ) );
        return false;
    }

    qDebug( qPrintable( QObject::tr( "SettingManager: %s exists." ) ), qPrintable( _pSettings->fileName() ) );
    return true;
}

void SettingManager::set( QString sKey, QVariant vValue )
{
    _Entries.insert( sKey, vValue );
    qDebug( qPrintable( QObject::tr( "SettingManager: Set %s : %s", qPrintable( sKey ) ) ), qPrintable( vValue.toString() ) );
}

QVariant SettingManager::get( QString sKey )
{

    qDebug( qPrintable( QObject::tr( "SettingManager: Get %s : %s", qPrintable( sKey ) ) ), qPrintable( _Entries[sKey].toString() ) );
    return _Entries[sKey];
}

bool SettingManager::remove( void )
{
    return QFile::remove( _pSettings->fileName() );
}

void SettingManager::load( void )
{
    QStringList keys = _pSettings->allKeys();
    QVariant vValue;

    qDebug( qPrintable( QObject::tr( "SettingManager: Loading values from %s" ) ), qPrintable( _pSettings->fileName() ) );
    _Entries.clear();

    foreach ( QString sKey, keys )
    {
        vValue = _pSettings->value( sKey );
        _Entries.insert( sKey, vValue );
        qDebug( qPrintable( QObject::tr( "SettingManager: Loaded %s:%s" ) ), qPrintable( sKey ), qPrintable( vValue.toString() ) );
    }
}

void SettingManager::save( void )
{
    qDebug( qPrintable( QObject::tr( "SettingManager: Saving values to %s" ) ), qPrintable( _pSettings->fileName() ) );

    QMapIterator<QString, QVariant> itr( _Entries );
    while ( itr.hasNext() )
    {
        itr.next();
        _pSettings->setValue( itr.key(), itr.value() );
    }
}

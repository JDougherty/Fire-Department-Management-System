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

#include "Firefighter.h"

Firefighter::Firefighter( void ) :
        DatabaseItem( -1 )
{
}

Firefighter::Firefighter( int iID ) :
        DatabaseItem( iID )
{
    _iID = iID;
    load();
}

bool Firefighter::createTable( void )
{
    /*DatabaseManager *pDBM = getDatabaseManager();
    QString queryString;
    QSqlQuery query;

    queryString = "CREATE TABLE Plugins (name TEXT, version TEXT, hash TEXT)";

    if ( !query.prepare( queryString ) )
    {
        qDebug( qPrintable( QObject::tr( "Plugin: Could not prepare query '%s' due to: %s" ) ),
                qPrintable( queryString ), qPrintable( pDBM->lastError().text() ) );
        qDebug( "%s", qPrintable( QObject::tr( "Plugin: Could not create table." ) ) );
        return false;
    }

    if ( !pDBM->query( query ) )
    {
        qDebug( qPrintable( QObject::tr( "Plugin: Could not run query '%s' due to: %s" ) ),
                qPrintable( queryString ), qPrintable( pDBM->lastError().text() ) );
        qDebug( "%s", qPrintable( QObject::tr( "Plugin: Could not create table." ) ) );
        return false;
    }

    return true;*/
    return true;
}

bool Firefighter::save( void )
{
    /*QSqlTableModel model( 0, getDatabaseManagerConnection() );

    model.setTable( "Plugins" );
    model.insertRow( 0 );
    model.setData( model.index( 0, 0 ), pluginInfo.getName() );
    model.setData( model.index( 0, 1 ), pluginInfo.getVersion() );
    model.setData( model.index( 0, 2 ), sHash );

    if ( !model.submitAll() )
    {
        qDebug( qPrintable( QObject::tr( "Plugin: Could not save %s with hash %s due to: %s" ) ),
                qPrintable( pluginInfo.toString() ), qPrintable( sHash ), qPrintable( model.lastError().text() ) );
        return false;
    }
*/
    qDebug( qPrintable( QObject::tr( "Firefighter: Saved %d" ) ), _iID );
    return true;
}

bool Firefighter::load( void )
{
    /*QSqlTableModel model( 0, getDatabaseManagerConnection() );
    QString sName, sVersion, sHash;

    model.setTable( "Plugins" );

    if ( !model.select() )
    {
        qDebug( qPrintable( QObject::tr( "Plugin: Could not load plugins due to: %s" ) ), qPrintable( model.lastError().text() ) );
        return false;
    }

    for ( int i = 0; i < model.rowCount(); i++ )
    {
        sName = model.record( i ).value( "name" ).toString();
        sVersion = model.record( i ).value( "version" ).toString();
        sHash = model.record( i ).value( "hash" ).toString();
        lInstalledPlugins.push_back( QPair<PluginInfo, QString>( PluginInfo( sName, sVersion ), sHash ) );
    }*/

    qDebug( qPrintable( QObject::tr( "Firefighter: Loaded %d" ) ), _iID );
    return true;
}


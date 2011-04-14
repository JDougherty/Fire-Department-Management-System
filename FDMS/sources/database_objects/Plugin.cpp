#include "database_objects/Plugin.h"

bool Plugin::createTable( void )
{
    DatabaseManager *pDBM = DatabaseManager::getInstance();
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

    return true;
}

bool Plugin::save( PluginInfo pluginInfo, QString sHash )
{
    QSqlTableModel model( 0, DatabaseManager::getInstance()->getConnection() );

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

    qDebug( qPrintable( QObject::tr( "Plugin: Saved %s with hash %s" ) ), qPrintable( pluginInfo.toString() ), qPrintable( sHash ) );
    return true;
}

bool Plugin::load( QList<QPair<PluginInfo, QString> > &lInstalledPlugins )
{
    QSqlTableModel model( 0, DatabaseManager::getInstance()->getConnection() );
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
    }

    return true;
}


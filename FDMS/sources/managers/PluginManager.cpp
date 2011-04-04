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

#include "managers/PluginManager.h"

PluginManager* getPluginManager( void )
{
    static PluginManager db;
    return &db;
}

PluginManager::PluginManager( void )
{
    _sFolder = QString::null;
}

PluginManager::~PluginManager( void )
{

}

bool PluginManager::initialize( void )
{
    SettingManager *sm = getSettingManager();

    _sFolder = sm->get( "plugins/folder" ).toString();

    return true;
}

bool PluginManager::setFolder( QString sFolder )
{
    SettingManager *sm = getSettingManager();

    sm->set( "plugins/folder", sFolder );
    _sFolder = sFolder;

    return true;
}

//! See if the folder exists.
/*!
  \return bool - Plugin folder exists.
*/
bool PluginManager::exists( void )
{
    if ( _sFolder == QString::null || !QDir( _sFolder ).exists() )
    {
        qDebug( qPrintable( QObject::tr( "PluginManager: %s folder does not exist." ) ), qPrintable( _sFolder ) );
        return false;
    }

    qDebug( qPrintable( QObject::tr( "PluginManager: %s folder exists." ) ), qPrintable( _sFolder ) );
    return true;
}

QString PluginManager::getPluginHash( QString sFileName )
{
    QCryptographicHash crypto( QCryptographicHash::Sha1 );
    QFile file( sFileName );
    QString sHash;

    if ( !file.open( QFile::ReadOnly ) )
    {
        qDebug( qPrintable( QObject::tr( "PluginManager: Failed to get the hash of %s" ) ), qPrintable( sFileName ) );
        return sHash;
    }

    while ( !file.atEnd() )
    {
        crypto.addData( file.read( 8192 ) );
    }

    sHash = crypto.result().toHex().constData();
    qDebug( qPrintable( QObject::tr( "PluginManager: Hash of %s is %s" ) ), qPrintable( sFileName ), qPrintable( sHash ) );


    return sHash;
}

bool PluginManager::install( QList<PluginInfo> lInstallThesePlugins )
{
    QDir pluginsDir( _sFolder );

    qDebug( "%s", qPrintable( QObject::tr( "PluginManager: Installing plugins." ) ) );

    lDatabasePlugins.clear();
    lMDIWindowPlugins.clear();
    lPlugins.clear();

    if ( !Plugin::createTable() )
    {
        qDebug( "%s", qPrintable( QObject::tr( "PluginManager: Could not create table." ) ) );
        return false;
    }

    foreach ( QString sFileName, pluginsDir.entryList( QDir::Files ) )
    {
        QPluginLoader pluginLoader( pluginsDir.absoluteFilePath( sFileName ) );
        QObject *pPlugin = pluginLoader.instance();

        if ( pPlugin )
        {
            DatabasePlugin *pDatabasePlugin = qobject_cast<DatabasePlugin*>( pPlugin );
            MDIWindowPlugin *pMDIWindowPlugin = qobject_cast<MDIWindowPlugin*>( pPlugin );

            if ( pDatabasePlugin && lInstallThesePlugins.contains( pDatabasePlugin->getInfo() ) )
            {
                if ( !Plugin::save( pDatabasePlugin->getInfo(), getPluginHash( pluginsDir.absoluteFilePath( sFileName ) ) ) )
                {
                    qDebug( qPrintable( QObject::tr( "PluginManager: Failed to install %s." ) ), qPrintable( pDatabasePlugin->getInfo().toString() ) );
                    return false;
                }

                qDebug( qPrintable( QObject::tr( "PluginManager: Installed %s." ) ), qPrintable( pDatabasePlugin->getInfo().toString() ) );
                lDatabasePlugins.append( pDatabasePlugin );
                lPlugins.append( (BasePlugin*)pDatabasePlugin );

            }
            else if ( pMDIWindowPlugin && lInstallThesePlugins.contains( pMDIWindowPlugin->getInfo() ) )
            {
                if ( !Plugin::save( pMDIWindowPlugin->getInfo(), getPluginHash( pluginsDir.absoluteFilePath( sFileName ) ) ) )
                {
                    qDebug( qPrintable( QObject::tr( "PluginManager: Failed to install %s." ) ), qPrintable( pMDIWindowPlugin->getInfo().toString() ) );
                    return false;
                }

                qDebug( qPrintable( QObject::tr( "PluginManager: Installed %s." ) ), qPrintable( pMDIWindowPlugin->getInfo().toString() ) );
                lMDIWindowPlugins.append( pMDIWindowPlugin );
                lPlugins.append( (BasePlugin*)pMDIWindowPlugin );
            }
        }
    }
    return true;
}

bool PluginManager::load( )
{
    QList<QPair<PluginInfo, QString> > installedPlugins;
    QPair<PluginInfo, QString> installedPlugin;
    QDir pluginsDir( _sFolder );

    qDebug( "%s", qPrintable( QObject::tr( "PluginManager: Loading plugins." ) ) );

    lDatabasePlugins.clear();
    lMDIWindowPlugins.clear();
    lPlugins.clear();

    if ( !Plugin::load( installedPlugins ) )
    {
        qDebug( "%s", qPrintable( QObject::tr( "PluginManager: Could not load plugins." ) ) );
        return false;
    }

    foreach ( installedPlugin, installedPlugins )
    {
        foreach ( QString sFileName, pluginsDir.entryList( QDir::Files ) )
        {
            QPluginLoader pluginLoader( pluginsDir.absoluteFilePath( sFileName ) );
            QObject *pPlugin = pluginLoader.instance();

            if ( pPlugin )
            {
                DatabasePlugin *pDatabasePlugin = qobject_cast<DatabasePlugin*>( pPlugin );
                MDIWindowPlugin *pMDIWindowPlugin = qobject_cast<MDIWindowPlugin*>( pPlugin );

                if ( pDatabasePlugin && pDatabasePlugin->getInfo() == installedPlugin.first )
                {
                    QString sHash = getPluginHash( pluginsDir.absoluteFilePath( sFileName ) );

                    if ( sHash != installedPlugin.second )
                    {
                        qDebug( qPrintable( QObject::tr( "PluginManager: Failed to load %s expected hash %s but file had %s" ) ),
                                qPrintable( installedPlugin.first.toString() ), qPrintable( installedPlugin.second ), qPrintable( sHash ) );
                        return false;
                    }

                    qDebug( qPrintable( QObject::tr( "PluginManager: Loaded %s." ) ), qPrintable( pDatabasePlugin->getInfo().toString() ) );
                    lDatabasePlugins.append( pDatabasePlugin );
                    lPlugins.append( (BasePlugin*)pDatabasePlugin );

                }
                else if ( pMDIWindowPlugin && pMDIWindowPlugin->getInfo() == installedPlugin.first )
                {
                    QString sHash = getPluginHash( pluginsDir.absoluteFilePath( sFileName ) );

                    if ( sHash != installedPlugin.second )
                    {
                        qDebug( qPrintable( QObject::tr( "PluginManager: Failed to load %s expected hash %s but file had %s" ) ),
                                qPrintable( installedPlugin.first.toString() ), qPrintable( installedPlugin.second ), qPrintable( sHash ) );
                        return false;
                    }

                    qDebug( qPrintable( QObject::tr( "PluginManager: Loaded %s." ) ), qPrintable( pMDIWindowPlugin->getInfo().toString() ) );
                    lMDIWindowPlugins.append( pMDIWindowPlugin );
                    lPlugins.append( (BasePlugin*)pMDIWindowPlugin );
                }
            }
        }
    }
    return true;
}

QList<BasePlugin*> PluginManager::findAll( QString sFolder )
{
    QDir pluginsDir( sFolder );
    QList<BasePlugin*> lPlugins;

    qDebug( "%s", qPrintable( QObject::tr( "PluginManager: Finding plugins." ) ) );

    if ( sFolder.isEmpty() )
        return lPlugins;

    foreach ( QString sFileName, pluginsDir.entryList( QDir::Files ) )
    {
        QPluginLoader pluginLoader( pluginsDir.absoluteFilePath( sFileName ) );
        QObject *pPlugin = pluginLoader.instance();

        if ( pPlugin )
        {
            DatabasePlugin *pDatabasePlugin = qobject_cast<DatabasePlugin*>( pPlugin );
            MDIWindowPlugin *pMDIWindowPlugin = qobject_cast<MDIWindowPlugin*>( pPlugin );

            if ( pDatabasePlugin )
            {
                qDebug( qPrintable( QObject::tr( "PluginManager: Found %s." ) ), qPrintable( pDatabasePlugin->getInfo().toString() ) );
                lPlugins.append( (BasePlugin*)pDatabasePlugin );
            }
            else if ( pMDIWindowPlugin )
            {
                qDebug( qPrintable( QObject::tr( "PluginManager: Found %s." ) ), qPrintable( pMDIWindowPlugin->getInfo().toString() ) );
                lPlugins.append( (BasePlugin*)pMDIWindowPlugin );
            }
        }
    }

    return lPlugins;
}

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

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QSqlQuery>
#include <QVariant>
#include <QtDebug>
#include <QCryptographicHash>
#include <QDir>
#include <QWidget>
#include <QMap>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QCheckBox>

//! Handles a DB connection and verifies DB integrity.
/*!
  Basically a wrapper for QSqlDatabase.
*/
class DatabaseManager : public QObject
{
    private:
        QSqlDatabase            _DB;

        QString                 _sDBFile; //!< DB file path.

        QMap<QString, QMap<QString, QString> > _queryMap; //!< Dictionary containing UI queries

        bool                    buildStructure( void );
        bool                    verifyStructure( void );

        QList<QWidget *>        getWidgets( QWidget *pWidget, QString sTabName );

    public:
                                DatabaseManager( void );
                                DatabaseManager( QString sDBFile );
                                ~DatabaseManager( void );

        void                    setDBFile( QString sDBFile );

        bool                    exists( void );
        bool                    open( void );
        bool                    isOpen( void );
        void                    close( void );

        bool                    build( void );
        void                    buildQueries( QString sTableName, QWidget *pWidget, QString sTabName = "" );
        bool                    verify( void );
        bool                    remove( void );

        bool                    selectUI( int iID, QString sTableName, QWidget *pWidget, QString sTabName = "" );
        int                     insertUI( QString sTableName, QWidget *pWidget, QString sTabName = "" );
        bool                    updateUI( int iID, QString sTableName, QWidget *pWidget, QString sTabName = "" );

        bool                    query( QSqlQuery &qry );

        QSqlError               lastError( void );
};

#endif

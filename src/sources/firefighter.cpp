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

#include "../headers/firefighter.h"
#include <QMessageBox>

Firefighter::Firefighter( void )
{
    _iID = -1;
}

//! Loads the attributes for firefighter with the given id from the database.
/*!
  \param iID Firefighter id.
  \param pDB Pointer to the database manager.
  \returns True upon successful load, false on failure.
*/
bool Firefighter::loadAttributes( int iID, DatabaseManager *pDB )
{
    QSqlQuery infoQuery;

    _iID = iID;

    // Clear current attributes
    _attributes.clear();

    // Create the query with parameterization
    infoQuery.prepare( "SELECT id,fname,mname,lname,"
                      "dob,deptid,stateid,"
                      "address,city,state,"
                      "zip,joindate,status,"
                      "hphone,wphone,cphone,"
                      "drvlic,cdl FROM firefighters WHERE id=?" );
    infoQuery.addBindValue( _iID );

    // Execute the query
    if ( pDB->query( infoQuery ) )
    {
        infoQuery.next();

        for ( int i = 1; i <= 18; i++ )
        {
            _attributes.push_back( infoQuery.value( i ).toString() );
        }
        qDebug( "Firefighter Information (%d): Personal information retrieved successfully.", _iID );
        return true;
    }
    else
    {
        qWarning( "Firefighter Error (%d): Could not retrieve personal information from database. Database Error: %s", _iID, qPrintable( infoQuery.lastError().text() ) );
        return false;
    }
}

//! Creates the firefighter in the database with its current attributes.
/*!
  \param pDB Pointer to the database manager.
  \returns True upon successful save, false on failure.
*/
bool Firefighter::insertToDatabase( QVector<QString> attributes, DatabaseManager *pDB )
{
    _attributes = attributes;

    QSqlQuery addQuery;
    addQuery.prepare( "INSERT INTO firefighters "
                     "(fname,mname,lname,"
                     "dob,deptid,stateid,"
                     "address,city,state,"
                     "zip,joindate,status,"
                     "hphone,wphone,cphone,"
                     "drvlic,cdl) VALUES "
                     "(?,?,?,"
                     "?,?,?,"
                     "?,?,?,"
                     "?,?,?,"
                     "?,?,?,"
                     "?,?)" );

    for ( int i = 0; i < _attributes.size(); i++ )
    {
        addQuery.addBindValue( _attributes[i] );
    }

    // Execute the query
    if ( pDB->query( addQuery ) )
    {
        qDebug( "Firefighter Information: New firefighter added successfully." );
        return true;
    }
    else
    {
        qWarning( "Firefighter Error: Could not add firefighter to database. Database Error: %s", qPrintable( addQuery.lastError().text() ) );
        return false;
    }
}

//!  Set the firefighter's attributes and update in the database.
/*!
  \param attributes List of new attributes
  \param pDB Pointer to the database manager.
  \returns True upon successful save, false on failure.
*/
bool Firefighter::updateAttributes( QVector<QString> attributes, DatabaseManager *pDB )
{
    QSqlQuery updateQuery;

    // Set the attributes
    _attributes = attributes;

    // Create the query with parameterization
    updateQuery.prepare( "UPDATE firefighters SET "
                     "fname=?,mname=?,lname=?,"
                     "dob=?,deptid=?,stateid=?,"
                     "address=?,city=?,state=?,"
                     "zip=?,joindate=?,status=?,"
                     "hphone=?,wphone=?,cphone=?,"
                     "drvlic=?,cdl=? WHERE id=? " );

    for ( int i = 0; i < _attributes.size(); i++)
    {
        updateQuery.addBindValue( _attributes[i] );
    }

    updateQuery.addBindValue( _iID );

    // Execute the query
    if ( pDB->query( updateQuery ) )
    {
        qDebug( "Firefighter Information (%d): Firefighter successfully updated in database.", _iID );
        return true;
    }
    else
    {
        qWarning( "Firefighter Error (%d): Could not update firefighter information in database. Database Error: %s", _iID, qPrintable( updateQuery.lastError().text() ) );
        return false;
    }
}


// ACCESSORS
int Firefighter::id( void )
{
    return _iID;
}

QString Firefighter::firstName( void )
{
    return _attributes[0];
}

QString Firefighter::middleName( void )
{
    return _attributes[1];
}

QString Firefighter::lastName( void )
{
    return _attributes[2];
}

QString Firefighter::dob( void )
{
    return _attributes[3];
}

QString Firefighter::localID( void )
{
    return _attributes[4];
}

QString Firefighter::stateID( void )
{
    return _attributes[5];
}

QString Firefighter::address( void )
{
    return _attributes[6];
}

QString Firefighter::city( void )
{
    return _attributes[7];
}

QString Firefighter::state( void )
{
    return _attributes[8];
}

QString Firefighter::zipCode( void )
{
    return _attributes[9];
}

QString Firefighter::dateJoin( void )
{
    return _attributes[10];
}

QString Firefighter::status( void )
{
    return _attributes[11];
}

QString Firefighter::hphone( void )
{
    return _attributes[12];
}

QString Firefighter::wphone( void )
{
    return _attributes[13];
}

QString Firefighter::cphone( void )
{
    return _attributes[14];
}

QString Firefighter::drvLic( void )
{
    return _attributes[15];
}

QString Firefighter::cdl( void )
{
    return _attributes[16];
}

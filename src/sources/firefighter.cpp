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
    for ( int i = 0; i < 17; i++ )
    {
        _attributes.append( "" );
    }

    _iID = -1;
}

//! Saves the attributes for the firefighter to the database.
/*!
  If the firefighter does not exist then insert otherwise update.
  \param pDB Pointer to the database manager.
  \returns True upon successful save, false on failure.
*/
bool Firefighter::save( DatabaseManager *pDB )
{
    if ( _iID == -1 )
    {
        return insert( pDB );
    }

    return update( pDB );
}

//! Creates the firefighter in the database with its current attributes.
/*!
  \param pDB Pointer to the database manager.
  \returns True upon successful save, false on failure.
*/
bool Firefighter::insert( DatabaseManager *pDB )
{
    QSqlQuery insertQuery;

    insertQuery.prepare( "INSERT INTO firefighters "
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
        insertQuery.addBindValue( _attributes[i] );
    }

    // Execute the query
    if ( !pDB->query( insertQuery ) )
    {
        qWarning( "Firefighter Error: Could not add firefighter to database. Database Error: %s", qPrintable( insertQuery.lastError().text() ) );
        return false;
    }

    _iID = insertQuery.lastInsertId().toInt();
    qDebug( "Firefighter Information (%d): New firefighter added successfully.", _iID );
    return true;
}

//!  Set the firefighter's attributes and update in the database.
/*!
  \param attributes List of new attributes
  \param pDB Pointer to the database manager.
  \returns True upon successful save, false on failure.
*/
bool Firefighter::update( DatabaseManager *pDB )
{
    QSqlQuery updateQuery;

    updateQuery.prepare( "UPDATE firefighters SET "
                     "fname=?,mname=?,lname=?,"
                     "dob=?,deptid=?,stateid=?,"
                     "address=?,city=?,state=?,"
                     "zip=?,joindate=?,status=?,"
                     "hphone=?,wphone=?,cphone=?,"
                     "drvlic=?,cdl=? WHERE id=? " );

    for ( int i = 0; i < _attributes.size(); i++ )
    {
        updateQuery.addBindValue( _attributes[i] );
    }

    updateQuery.addBindValue( _iID );

    // Execute the query
    if ( !pDB->query( updateQuery ) )
    {
        qWarning( "Firefighter Error (%d): Could not update firefighter information in database. Database Error: %s",
                  _iID, qPrintable( updateQuery.lastError().text() ) );
        return false;

    }

    qDebug( "Firefighter Information (%d): Firefighter successfully updated in database.", _iID );
    return true;
}

//! Loads the attributes for firefighter with the given id from the database.
/*!
  \param pDB Pointer to the database manager.
  \param iID Firefighter id.
  \returns True upon successful load, false on failure.
*/
bool Firefighter::load( DatabaseManager *pDB, int iID )
{
    QSqlQuery selectQuery;

    _iID = iID;

    // Create the query with parameterization
    selectQuery.prepare( "SELECT fname,mname,lname,"
                      "dob,deptid,stateid,"
                      "address,city,state,"
                      "zip,joindate,status,"
                      "hphone,wphone,cphone,"
                      "drvlic,cdl FROM firefighters WHERE id=?" );
    selectQuery.addBindValue( _iID );

    // Execute the query
    if ( !pDB->query( selectQuery ) )
    {
        qWarning( "Firefighter Error (%d): Could not retrieve personal information from database. Database Error: %s",
                  _iID, qPrintable( selectQuery.lastError().text() ) );
        return false;

    }

    selectQuery.next();

    for ( int i = 0; i < _attributes.size(); i++ )
    {
        _attributes[i] =  selectQuery.value( i ).toString();
    }
    qDebug( "Firefighter Information (%d): Personal information retrieved successfully.", _iID );
    return true;
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

// SETTERS
void Firefighter::id( int iID )
{
    _iID = iID;
}

void Firefighter::firstName( QString s )
{
    _attributes[0] = s;
}

void Firefighter::middleName( QString s )
{
    _attributes[1] = s;
}

void Firefighter::lastName( QString s )
{
    _attributes[2] = s;
}

void Firefighter::dob( QString s )
{
    _attributes[3] = s;
}

void Firefighter::localID( QString s )
{
    _attributes[4] = s;
}

void Firefighter::stateID( QString s )
{
    _attributes[5] = s;
}

void Firefighter::address( QString s )
{
    _attributes[6] = s;
}

void Firefighter::city( QString s )
{
    _attributes[7] = s;
}

void Firefighter::state( QString s )
{
    _attributes[8] = s;
}

void Firefighter::zipCode( QString s )
{
    _attributes[9] = s;
}

void Firefighter::dateJoin( QString s )
{
    _attributes[10] = s;
}

void Firefighter::status( QString s )
{
    _attributes[11] = s;
}

void Firefighter::hphone( QString s )
{
    _attributes[12] = s;
}

void Firefighter::wphone( QString s )
{
    _attributes[13] = s;
}

void Firefighter::cphone( QString s )
{
    _attributes[14] = s;
}

void Firefighter::drvLic( QString s )
{
    _attributes[15] = s;
}

void Firefighter::cdl( QString s )
{
    _attributes[16] = s;
}


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

#include "../headers/wndfirefighter.h"
#include "ui_wndfirefighter.h"

//! Constructor for adding a new firefighter.
/*!
  Hide extra tabs and change the window and button names.
  \param pDB Pointer to the database manager.
*/
wndFirefighter::wndFirefighter( QWidget *pParent, DatabaseManager *pDB ) :
    QMainWindow( pParent ), _pUI( new Ui::wndFirefighter )
{
    _pUI->setupUi( this );
    _pDB = pDB;
    _bAddFirefighter = true;

    // Hide these tabs since we want to just enter basic info first
    _pUI->tabWidget->removeTab( 3 ); // tabReports
    _pUI->tabWidget->removeTab( 2 ); // tabEquipment
    _pUI->tabWidget->removeTab( 1 ); // tabTraining

    this->setWindowTitle( "Add Firefighter" );
    _pUI->btnSavePersonalInfo->setText( "Add Firefighter" );

    // Disable the training and equipment fields
    enableTrainingFields( false );
    enableEquipmentFields( false );
}

//! Constructor for editing a firefighter.
/*!
  Load the firefighter's data.
  \param pDB Pointer to the database manager.
  \param iID Firefighter's DB id.
*/
wndFirefighter::wndFirefighter( QWidget *pParent, DatabaseManager *pDB, int iID ) :
    QMainWindow( pParent ), _pUI( new Ui::wndFirefighter )
{
    _pUI->setupUi( this );
    _pDB = pDB;
    _bAddFirefighter = false;

    this->setWindowTitle( "Edit Firefighter" );
    _pUI->btnSavePersonalInfo->setText( "Save Firefighter" );

    _FF.load( pDB, iID );
    loadPersonalInfo();
    loadTrainingList();
    loadEquipmentList();

    // Disable the training and equipment fields
    enableTrainingFields( false );
    enableEquipmentFields( false );
}

wndFirefighter::~wndFirefighter( void )
{
    delete _pUI;
}

/*****************************************************************************************************************/
/* PERSONAL INFORMATION                                                                                          */
/*****************************************************************************************************************/

//! Populate the personal info tab with the firefighter's data.
void wndFirefighter::loadPersonalInfo( void )
{
    _pUI->txtFirstName->setText( _FF.firstName() );
    _pUI->txtMiddleName->setText( _FF.middleName() );
    _pUI->txtLastName->setText( _FF.lastName() );
    _pUI->dateDob->setDate( QVariant( _FF.dob() ).toDate() );
    _pUI->txtLocalID->setText( _FF.localID() );
    _pUI->txtStateID->setText( _FF.stateID() );
    _pUI->txtAddress->setText( _FF.address() );
    _pUI->txtCity->setText( _FF.city() );
    _pUI->txtState->setCurrentIndex( _pUI->txtState->findText( _FF.state() ) );
    _pUI->txtZipCode->setText( _FF.zipCode());
    _pUI->dateJoin->setDate( QVariant( _FF.dateJoin() ).toDate() );
    _pUI->txtStatus->setText( _FF.status() );
    _pUI->txtHphone->setText( _FF.hphone() );
    _pUI->txtWphone->setText( _FF.wphone() );
    _pUI->txtCphone->setText( _FF.cphone() );
    _pUI->txtDrvLic->setText( _FF.drvLic() );
    _pUI->txtCDL->setText( _FF.cdl() );
}

//! Updates the firefighter's personal information in the database when the Update button is clicked.
void wndFirefighter::btnSavePersonalInfoClicked( void )
{
    _FF.firstName( _pUI->txtFirstName->text() );
    _FF.middleName( _pUI->txtMiddleName->text() );
    _FF.lastName( _pUI->txtLastName->text() );
    _FF.dob( _pUI->dateDob->date().toString( "yyyy-MM-dd 00:00:00.000" ) );
    _FF.localID( _pUI->txtLocalID->text() );
    _FF.stateID( _pUI->txtStateID->text() );
    _FF.address( _pUI->txtAddress->text() );
    _FF.city( _pUI->txtCity->text() );
    _FF.state( _pUI->txtState->itemText( _pUI->txtState->currentIndex() ) );
    _FF.zipCode( _pUI->txtZipCode->text() );
    _FF.dateJoin( _pUI->dateJoin->date().toString( "yyyy-MM-dd 00:00:00.000" ) );
    _FF.status( _pUI->txtStatus->text() );
    _FF.hphone( _pUI->txtHphone->text() );
    _FF.wphone( _pUI->txtWphone->text() );
    _FF.cphone( _pUI->txtCphone->text() );
    _FF.drvLic( _pUI->txtDrvLic->text() );
    _FF.cdl( _pUI->txtCDL->text() );

    if ( _bAddFirefighter )
    {
        if ( _FF.save( _pDB  ) )
        {
            QMessageBox::information( 0, "Firefighter Information", "Firefighter successfully added to database!" );

            _bAddFirefighter = false;

            // show the additional tabs
            _pUI->tabWidget->addTab( _pUI->tabTraining, "Training" );
            _pUI->tabWidget->addTab( _pUI->tabEquipment, "Equipment" );
            _pUI->tabWidget->addTab( _pUI->tabReports, "Reports" );

            this->setWindowTitle( "Edit Firefighter" );
            _pUI->btnSavePersonalInfo->setText( "Save Firefighter" );

            loadTrainingList();
            loadEquipmentList();
        }
        else
        {
            QMessageBox::warning( 0, "Firefighter Error", "Firefighter could not be added to database! See log file for details." );
        }
    }
    else
    {
        if ( _FF.save( _pDB ) )
        {
            QMessageBox::information( this, "Firefighter Information: Update", "Firefighter was successfully updated in database!" );
        }
        else
        {
            QMessageBox::warning( this, "Firefighter Error: Update", "Firefighter information failed to update! See log for more information." );
        }
    }
}

/*****************************************************************************************************************/
/* TRAINING INFORMATION                                                                                          */
/*****************************************************************************************************************/

//! Populate the training tab with all of the individual training items.
void wndFirefighter::loadTrainingList( void )
{
    QSqlQuery traininglist;

    _pUI->lstTraining->clear();

    traininglist.prepare( "SELECT training.title,fft.tid "
                          "FROM training LEFT JOIN ("
                          "SELECT * FROM fftraining WHERE ffid=?) as fft ON "
                          "training.id=fft.tid" );
    traininglist.addBindValue( _FF.id() );

    if ( _pDB->query( traininglist ) )
    {
        while ( traininglist.next() )
        {
            QListWidgetItem *newitem = new QListWidgetItem( traininglist.value( 0 ).toString() );
            if ( traininglist.value( 1 ).toString() != "" )
            {
                newitem->setCheckState( Qt::Checked );
            }
            else
            {
                newitem->setCheckState( Qt::Unchecked );
            }
            _pUI->lstTraining->addItem( newitem );
        }
    }
    else
    {
        qWarning( "Firefighter Error (%d): Could not get training exam information. Database Error: %s",
                 _FF.id(), qPrintable( traininglist.lastError().text() ) );
    }
}

//! Links or unliks a training exam to the firefighter being edited.
/*!
  It is invoked by checking or unchecking the checkbox on a training exam in the training exam list.
  \param item The exam being linked or unlinked.
  \see loadTrainingItem
  \see btnUpdateTrainingItemClicked
*/
void wndFirefighter::trainingItemClicked( QListWidgetItem *item )
{
    QString exam( item->data( Qt::DisplayRole ).toString() );

    // If the item is being checked, i.e. added:
    if ( item->checkState() == Qt::Checked )
    {
        // Build a query to add the information to the database
        QSqlQuery addFFTraining;

        addFFTraining.prepare( "INSERT INTO fftraining (tid,ffid) SELECT id,? FROM training WHERE title=?" );
        addFFTraining.addBindValue( _FF.id() );
        addFFTraining.addBindValue( exam );

        // And execute the query, catching any problems
        if ( !_pDB->query( addFFTraining ) )
        {
            qWarning( "Firefighter Error (%d): Could not link training exam '%s'. Database Error: %s",
                     _FF.id(), qPrintable( exam ), qPrintable( addFFTraining.lastError().text() ) );
        }

        toggleTrainingFields( item );
    }
    else // If the item is being unchecked, i.e. removed
    {
        // First verify they intend to destruct information
        if ( QMessageBox::question( 0, "Training: Confirm Removal", "Are you sure you would like to remove this exam information?",
                                    QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
        {

            // If so, build a query to remove the link from the database
            QSqlQuery removeFFTraining;
            removeFFTraining.prepare( "DELETE FROM fftraining WHERE ffid=? AND tid=(SELECT id FROM training WHERE title=?)" );
            removeFFTraining.addBindValue( _FF.id() );
            removeFFTraining.addBindValue( exam );

            // Attempt to execute the query, catching any problems
            if ( !_pDB->query( removeFFTraining ) )
            {
                qWarning( "Firefighter Error (%d): Could not unlink training exam '%s'. Database Error: %s",
                        _FF.id() ,qPrintable( exam ), qPrintable( removeFFTraining.lastError().text() ) );
            }

            toggleTrainingFields( item );
        }
        else // If the uncheck was not intended, replace the check without destroying information
        {
            // Note: We cannot just set the checkStatus of item to Qt::Checked
            //  because this would call this function again, thereby creating
            //  a duplicate item in the database.
            loadTrainingList();
        }
    }
}

//! Enable or disable the item the user clicked in the training list.
/*!
  \param item List item that the user clicked.
*/
void wndFirefighter::toggleTrainingFields( QListWidgetItem *item )
{
    if ( item->checkState() == Qt::Checked )
    {
        enableTrainingFields( true );
    }
    else
    {
        enableTrainingFields( false );
        _pUI->txtFFSig->clear();
        _pUI->txtSupSig->clear();
        _pUI->dateTraining->setDate( QDate( 2000,1,1 ) );
    }
}

//! Enable or disable the training fields.
/*!
  \param bEnabled Disable or enable.
*/
void wndFirefighter::enableTrainingFields( bool bEnabled )
{
    _pUI->txtFFSig->setEnabled( bEnabled );
    _pUI->txtSupSig->setEnabled( bEnabled );
    _pUI->dateTraining->setEnabled( bEnabled );
    _pUI->btnSaveTrainingItem->setEnabled( bEnabled );
}

//! Loads the signature and date information for the highlighted training exam.
/*!
  \see trainingItemClicked
  \see btnUpdateTrainingItemClicked
*/
void wndFirefighter::loadTrainingItem( QListWidgetItem *item )
{
    if ( item )
    {
        toggleTrainingFields( item );
        QString exam( item->data( Qt::DisplayRole ).toString() );
        QSqlQuery selectQuery;
        selectQuery.prepare( "SELECT ffesig,supesig,tdate FROM fftraining WHERE ffid=? AND tid=(SELECT id FROM training WHERE title=?)" );
        selectQuery.addBindValue( _FF.id() );
        selectQuery.addBindValue( exam );

        if ( _pDB->query( selectQuery ) )
        {
            selectQuery.next();
            _pUI->txtFFSig->setText( selectQuery.value( 0 ).toString() );
            _pUI->txtSupSig->setText( selectQuery.value( 1 ).toString() );
            _pUI->dateTraining->setDate( selectQuery.value( 2 ).toDate() );
        }
        else
        {
            qWarning( "Firefighter Error (%d): Could not retrieve information for training exam '%s'. Database Error: %s",
                     _FF.id(), qPrintable( exam ), qPrintable( selectQuery.lastError().text() ) );
        }
    }
}

//! Updates the signature and date information for the highlighted training exam.
/*!
  \see trainingItemClicked
  \see loadTrainingItem
*/
void wndFirefighter::btnSaveTrainingItemClicked( void )
{
    if ( _pUI->lstTraining->currentItem() )
    {
        QString exam( _pUI->lstTraining->currentItem()->data( Qt::DisplayRole ).toString() );
        QSqlQuery updateQuery;

        updateQuery.prepare( "UPDATE fftraining SET ffesig=?, supesig=?, tdate=? WHERE ffid=? AND tid=(SELECT id FROM training WHERE title=?)" );
        updateQuery.addBindValue( _pUI->txtFFSig->text() );
        updateQuery.addBindValue( _pUI->txtSupSig->text() );
        updateQuery.addBindValue( _pUI->dateTraining->date().toString( "yyyy-MM-dd 00:00:00.000" ) );
        updateQuery.addBindValue( _FF.id() );
        updateQuery.addBindValue( exam );

        if ( _pDB->query( updateQuery ) )
        {
            QMessageBox::information( 0, "Firefighter Information: Training Update", "Training exam information successfully updated." );
        }
        else
        {
            QMessageBox::warning( 0, "Firefighter Error: Training Update",
                                  "There was a problem updating the training exam information. See log for more information." );
            qWarning( "Firefighter Error (%d): Could not update training exam '%s'. Database Error: %s",
                     _FF.id(), qPrintable( exam ), qPrintable( updateQuery.lastError().text() ) );
        }
    }
}

/*****************************************************************************************************************/
/* EQUIPMENT INFORMATION                                                                                         */
/*****************************************************************************************************************/

//! Populate the equipment tab with all of the individual equipment items.
void wndFirefighter::loadEquipmentList( void )
{
    QSqlQuery equipmentlist;

    _pUI->lstEquipment->clear();

    equipmentlist.prepare( "SELECT equipment.title,ffe.eqid "
                           "FROM equipment LEFT JOIN ("
                           "SELECT * FROM ffequipment WHERE ffid=?) as ffe ON "
                           "equipment.id=ffe.eqid" );
    equipmentlist.addBindValue( _FF.id() );

    if ( _pDB->query( equipmentlist ) )
    {
        while ( equipmentlist.next() )
        {
            QListWidgetItem *newitem = new QListWidgetItem( equipmentlist.value( 0 ).toString() );
            if ( equipmentlist.value( 1 ).toString() != "" )
            {
                newitem->setCheckState( Qt::Checked );
            }
            else
            {
                newitem->setCheckState( Qt::Unchecked );
            }
            _pUI->lstEquipment->addItem( newitem );
        }
    }
    else
    {
        qWarning( "Firefighter Error (%d): Could not get equipment information. Database Error: %s",
                 _FF.id(), qPrintable( equipmentlist.lastError().text() ) );
    }
}

//! Links or unlinks a piece of equipment to the firefighter being edited.
/*!
  It is invoked by checking or unchecking the checkbox on an item in the equipment list.
  \param item The item being linked or unlinked.
  \see loadEquipmentItem
  \see btnSaveEquipmentItemClicked
*/
void wndFirefighter::equipmentItemClicked( QListWidgetItem *item )
{
    QString equip( item->data( Qt::DisplayRole ).toString() );

    // If the item is being checked, i.e. added:
    if ( item->checkState() == Qt::Checked )
    {
        // Build a query to add the information to the database
        QSqlQuery addFFequip;

        addFFequip.prepare( "INSERT INTO ffequipment (eqid,ffid) SELECT id,? FROM equipment WHERE title=?" );
        addFFequip.addBindValue( _FF.id() );
        addFFequip.addBindValue( equip );

        // And execute the query, catching any problems
        if ( !_pDB->query( addFFequip ) )
        {
            qWarning( "Firefighter Error (%d): Could not link equipment '%s'. Database Error: %s",
                     _FF.id(), qPrintable( equip ), qPrintable( addFFequip.lastError().text() ) );
        }

        toggleEquipmentFields( item );
    }
    else // If the item is being unchecked, i.e. removed
    {
        // First verify they intend to destruct information
        if ( QMessageBox::question( 0, "Equipment: Confirm Removal", "Are you sure you would like to remove this piece of equipment?",
                                   QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes )
        {

            // If so, build a query to remove the link from the database
            QSqlQuery removeFFEquip;
            removeFFEquip.prepare( "DELETE FROM ffequipment WHERE ffid=? AND eqid=(SELECT id FROM equipment WHERE title=?)" );
            removeFFEquip.addBindValue( _FF.id() );
            removeFFEquip.addBindValue( equip );

            // Attempt to execute the query, catching any problems
            if ( !_pDB->query( removeFFEquip )  )
            {
                qWarning("Firefighter Error (%d): Could not unlink equipment '%s'. Database Error: %s",
                        _FF.id(), qPrintable( equip ), qPrintable( removeFFEquip.lastError().text() ) );
            }

            toggleEquipmentFields( item );
        }
        else // If the uncheck was not intended, replace the check without destroying information
        {
            // Note: We cannot just set the checkStatus of item to Qt::Checked
            //  because this would call this function again, thereby creating
            //  a duplicate item in the database.
            loadEquipmentList();
        }
    }
}

//! Enable or disable the item the user clicked in the equipment list.
/*!
  \param item List item that the user clicked.
*/
void wndFirefighter::toggleEquipmentFields( QListWidgetItem *item )
{
    if ( item->checkState() == Qt::Checked )
    {
        enableEquipmentFields( true );
    }
    else
    {
        enableEquipmentFields( false );
        _pUI->txtEquipSerial->clear();
        _pUI->txtEquipType->clear();
        _pUI->txtEquipSize->clear();
        _pUI->txtEquipYear->clear();
    }
}

//! Enable or disable the equipment fields.
/*!
  \param bEnabled Disable or enable.
*/
void wndFirefighter::enableEquipmentFields( bool bEnabled )
{
    _pUI->txtEquipSerial->setEnabled( bEnabled );
    _pUI->txtEquipType->setEnabled( bEnabled );
    _pUI->txtEquipSize->setEnabled( bEnabled );
    _pUI->txtEquipYear->setEnabled( bEnabled );
    _pUI->radEquipmentNew->setEnabled( bEnabled );
    _pUI->radEquipmentUsed->setEnabled( bEnabled );
    _pUI->btnSaveEquipmentItem->setEnabled( bEnabled );
}

//! Loads the signature and date information for the highlighted training exam.
/*!
  \see equipmentItemClicked
  \see btnSaveEquipmentItemClicked
*/
void wndFirefighter::loadEquipmentItem( QListWidgetItem *item )
{
    toggleEquipmentFields( item );
    QString equip( item->data( Qt::DisplayRole ).toString() );
    QSqlQuery selectQuery;
    selectQuery.prepare( "SELECT issued,size,type,serial,year FROM ffequipment WHERE ffid=? AND eqid=(SELECT id FROM equipment WHERE title=?)" );
    selectQuery.addBindValue( _FF.id() );
    selectQuery.addBindValue( equip );

    if ( _pDB->query( selectQuery ) )
    {
        selectQuery.next();

        _pUI->radEquipmentNew->setChecked( selectQuery.value( 0 ).toBool() ? 1 : 0);
        _pUI->radEquipmentUsed->setChecked( selectQuery.value( 0 ).toBool() ? 0 : 1 );
        _pUI->txtEquipSize->setText( selectQuery.value( 1 ).toString() );
        _pUI->txtEquipType->setText( selectQuery.value( 2 ).toString() );
        _pUI->txtEquipSerial->setText( selectQuery.value( 3 ).toString() );
        _pUI->txtEquipYear->setText( selectQuery.value( 4 ).toString() );
    }
    else
    {
        qWarning( "Firefighter Error (%d): Could not retrieve information for equipment '%s'. Database Error: %s",
                 _FF.id(), qPrintable( equip ), qPrintable( selectQuery.lastError().text() ) );
    }
}

//! Updates the size, type, and serial information for the highlighted equipment item.
/*!
  \see equipmentItemClicked
  \see loadEquipmentItem
*/
void wndFirefighter::btnSaveEquipmentItemClicked( void )
{
    if ( _pUI->lstEquipment->currentItem() )
    {
        QString equip( _pUI->lstEquipment->currentItem()->data( Qt::DisplayRole ).toString() );
        QSqlQuery updateQuery;
        updateQuery.prepare( "UPDATE ffequipment SET issued=?, size=?, type=?, serial=?, year=? WHERE ffid=? AND eqid=(SELECT id FROM equipment WHERE title=?)" );
        updateQuery.addBindValue( _pUI->radEquipmentNew->isChecked() ? 1 : 0 );
        updateQuery.addBindValue( _pUI->txtEquipSize->text() );
        updateQuery.addBindValue( _pUI->txtEquipType->text() );
        updateQuery.addBindValue( _pUI->txtEquipSerial->text() );
        updateQuery.addBindValue( _pUI->txtEquipYear->text() );
        updateQuery.addBindValue(_FF.id() );
        updateQuery.addBindValue( equip );

        if ( _pDB->query( updateQuery ) )
        {
            QMessageBox::information( 0, "Firefighter Information: Equipment Update","Equipment information successfully updated." );
        }
        else
        {
            QMessageBox::warning( 0, "Firefighter Error: Equipment Update",
                                  "There was a problem updating the equipment information. See log for more information." );
            qWarning( "Firefighter Error (%d): Could not update equipment '%s'. Database Error: %s",
                     _FF.id(), qPrintable( equip ), qPrintable( updateQuery.lastError().text() ) );
        }
    }
}


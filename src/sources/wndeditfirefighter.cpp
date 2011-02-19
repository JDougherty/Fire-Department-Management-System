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

#include<QMessageBox>
#include "../headers/wndeditfirefighter.h"
#include "ui_wndeditfirefighter.h"

wndEditFirefighter::wndEditFirefighter( QWidget *pParent, DatabaseManager *pDB ) :
    QMainWindow( pParent ), _pUI( new Ui::wndEditFirefighter )
{
    _pUI->setupUi( this );
    _pDB = pDB;
}


wndEditFirefighter::wndEditFirefighter( QWidget *pParent, DatabaseManager *pDB, int id ):
        QMainWindow( pParent ), _pUI( new Ui::wndEditFirefighter )
{

    _pUI->setupUi(this);
    _pDB = pDB;

    if ( !_FF.load( id, _pDB ) )
    {
        QMessageBox::warning( 0 ,"Firefighter Error: Read", "Could not retrieve firefighter information from database. See log for more information." );
    }

    // Update the personal information fields, training list, and equipment list
    updateFirefighterFields();
    updateTrainingList();
    updateEquipmentList();

    // connect the ui object signals to the appropriate slots
    connect(_pUI->lstTraining,SIGNAL(itemChanged(QListWidgetItem*)),this,SLOT(trainingItemClicked(QListWidgetItem*)));
    connect(_pUI->btnUpdateTraining,SIGNAL(clicked()),this,SLOT(btnUpdateTrainingClicked()));
    connect(_pUI->lstTraining,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(updateTrainingInfo(QListWidgetItem*)));

    connect(_pUI->lstEquipment,SIGNAL(itemChanged(QListWidgetItem*)),this,SLOT(equipmentItemClicked(QListWidgetItem*)));
    connect(_pUI->btnUpdateEquipment,SIGNAL(clicked()),this,SLOT(btnUpdateEquipmentClicked()));
    connect(_pUI->lstEquipment,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(updateEquipmentInfo(QListWidgetItem*)));
}

wndEditFirefighter::~wndEditFirefighter( void )
{
    delete _pUI;
}

// private:
void wndEditFirefighter::updateFirefighterFields( void )
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

void wndEditFirefighter::updateTrainingList( void )
{
    _pUI->lstTraining->clear();

    QSqlQuery traininglist;
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
                newitem->setCheckState(Qt::Checked);
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

void wndEditFirefighter::toggleTrainingInformationEnabled( QListWidgetItem* item )
{
    if ( item->checkState() == Qt::Checked )
    {
        _pUI->txtFFSig->setEnabled( 1 );
        _pUI->txtSupSig->setEnabled( 1 );
        _pUI->dateTraining->setEnabled( 1 );
        _pUI->btnUpdateTraining->setEnabled( 1 );
    }
    else
    {
        _pUI->txtFFSig->setEnabled( 0 );
        _pUI->txtSupSig->setEnabled( 0 );
        _pUI->dateTraining->setEnabled( 0 );
        _pUI->btnUpdateTraining->setEnabled( 0 );
        _pUI->txtFFSig->clear();
        _pUI->txtSupSig->clear();
    }
}


void wndEditFirefighter::updateEquipmentList()
{
    _pUI->lstEquipment->clear();

    QSqlQuery equipmentlist;
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
    else{
        qWarning( "Firefighter Error (%d): Could not get equipment information. Database Error: %s",
                 _FF.id(), qPrintable( equipmentlist.lastError().text() ) );
    }
}

void wndEditFirefighter::toggleEquipmentInformationEnabled( QListWidgetItem* item )
{
    if ( item->checkState() == Qt::Checked )
    {
        _pUI->txtEquipSerial->setEnabled( 1 );
        _pUI->txtEquipType->setEnabled( 1 );
        _pUI->txtEquipSize->setEnabled( 1 );
        _pUI->txtEquipYear->setEnabled( 1 );
        _pUI->radEquipmentNew->setEnabled( 1 );
        _pUI->radEquipmentUsed->setEnabled( 1 );
        _pUI->btnUpdateEquipment->setEnabled( 1 );
    }
    else
    {
        _pUI->txtEquipSerial->setEnabled( 0 );
        _pUI->txtEquipType->setEnabled( 0 );
        _pUI->txtEquipSize->setEnabled( 0 );
        _pUI->txtEquipYear->setEnabled( 0 );
        _pUI->radEquipmentNew->setEnabled( 0 );
        _pUI->radEquipmentUsed->setEnabled( 0 );
        _pUI->btnUpdateEquipment->setEnabled( 0 );
    }
}

/*
** private slots:
*/


/*
** PERSONAL INFORMATION
*/

/*
   Function: btnUpdatePersonalClicked

   Updates the firefighter's personal information in the database
   when the Update button is clicked.

*/
void wndEditFirefighter::btnUpdatePersonalClicked( void )
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

    if ( _FF.save( _pDB ) )
    {
        QMessageBox::information( this, "Firefighter Information: Update",
                                  "Firefighter was successfully updated in database!" );
    }
    else
    {
        QMessageBox::warning( this, "Firefighter Error: Update",
                              "Firefighter information failed to update! See log for more information." );
    }
}

/*
** TRAINING INFORMATION
*/

/*
   Function: trainingItemClicked

   Links or unliks a training exam to the firefighter being edited.
   It is invoked by checking or unchecking the checkbox on a training
   exam in the training exam list.

   Parameters:

      QListWidgetItem* item - The exam being linked or unlinked.

   See Also:

      <btnUpdateTrainingClicked>
*/
void wndEditFirefighter::trainingItemClicked( QListWidgetItem* item )
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
            qWarning( "Firefighter Error (%d): Could not link training exam `%s`. Database Error: %s",
                     _FF.id(), qPrintable( exam ), qPrintable( addFFTraining.lastError().text() ) );
        }

        toggleTrainingInformationEnabled( item );
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
                qWarning( "Firefighter Error (%d): Could not unlink training exam `%s`. Database Error: %s",
                        _FF.id() ,qPrintable( exam ), qPrintable( removeFFTraining.lastError().text() ) );
            }

            toggleTrainingInformationEnabled( item );
        }
        else // If the uncheck was not intended, replace the check without destroying information
        {
            // Note: We cannot just set the checkStatus of item to Qt::Checked
            //  because this would call this function again, thereby creating
            //  a duplicate item in the database.
            updateTrainingList();
        }
    }
}

/*
   Function: btnUpdateTrainingClicked

   Updates the signature and date information for the
   highlighted training exam in the database for the
   firefighter currently being edited.


   See Also:

      <trainingItemClicked>
*/
void wndEditFirefighter::btnUpdateTrainingClicked( void )
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
            qWarning( "Firefighter Error (%d): Could not update training exam `%s`. Database Error: %s",
                     _FF.id(), qPrintable( exam ), qPrintable( updateQuery.lastError().text() ) );
        }
    }
}

void wndEditFirefighter::updateTrainingInfo( QListWidgetItem *item )
{
    if ( item )
    {
        toggleTrainingInformationEnabled( item );
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
            qWarning( "Firefighter Error (%d): Could not retrieve information for training exam `%s`. Database Error: %s",
                     _FF.id(), qPrintable( exam ), qPrintable( selectQuery.lastError().text() ) );
        }
    }
}



/*
** EQUIPMENT INFORMATION
*/
void wndEditFirefighter::equipmentItemClicked( QListWidgetItem *item )
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
            qWarning( "Firefighter Error (%d): Could not link equipment `%s`. Database Error: %s",
                     _FF.id(), qPrintable( equip ), qPrintable( addFFequip.lastError().text() ) );
        }

        toggleEquipmentInformationEnabled( item );
    }
    else // If the item is being unchecked, i.e. removed
    {
        // First verify they intend to destruct information
        if ( QMessageBox::question( 0, "Equipment: Confirm Removal", "Are you sure you would like to remove this exam information?",
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
                qWarning("Firefighter Error (%d): Could not unlink equipment `%s`. Database Error: %s",
                        _FF.id(), qPrintable( equip ), qPrintable( removeFFEquip.lastError().text() ) );
            }

            toggleEquipmentInformationEnabled( item );
        }
        else // If the uncheck was not intended, replace the check without destroying information
        {
            // Note: We cannot just set the checkStatus of item to Qt::Checked
            //  because this would call this function again, thereby creating
            //  a duplicate item in the database.
            updateEquipmentList();
        }
    }
}


void wndEditFirefighter::btnUpdateEquipmentClicked( void )
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
            qWarning( "Firefighter Error (%d): Could not update equipment `%s`. Database Error: %s",
                     _FF.id(), qPrintable( equip ), qPrintable( updateQuery.lastError().text() ) );
        }
    }
}

void wndEditFirefighter::updateEquipmentInfo( QListWidgetItem *item )
{
        toggleEquipmentInformationEnabled( item );
        QString equip( item->data( Qt::DisplayRole ).toString() );
        QSqlQuery selectQuery;
        selectQuery.prepare( "SELECT issued,size,type,serial,year FROM ffequipment WHERE ffid=? AND eqid=(SELECT id FROM equipment WHERE title=?)" );
        selectQuery.addBindValue( _FF.id() );
        selectQuery.addBindValue( equip );

        if ( _pDB->query( selectQuery ) )
        {
            selectQuery.next();

            _pUI->radEquipmentNew->setChecked( selectQuery.value( 0 ).toBool() ? 1 :  0);
            _pUI->radEquipmentUsed->setChecked( selectQuery.value( 0 ).toBool() ? 0 : 1 );
            _pUI->txtEquipSize->setText( selectQuery.value( 1 ).toString() );
            _pUI->txtEquipType->setText( selectQuery.value( 2 ).toString() );
            _pUI->txtEquipSerial->setText( selectQuery.value( 3 ).toString() );
            _pUI->txtEquipYear->setText( selectQuery.value( 4 ).toString() );

        }
        else
        {
            qWarning( "Firefighter Error (%d): Could not retrieve information for equipment `%s`. Database Error: %s",
                     _FF.id(), qPrintable( equip ), qPrintable( selectQuery.lastError().text() ) );
        }
}

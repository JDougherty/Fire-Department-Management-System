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

#include "../headers/wndeditfirefighter.h"
#include "ui_wndeditfirefighter.h"
#include<QMessageBox>

wndEditFirefighter::wndEditFirefighter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wndEditFirefighter)
{
    ui->setupUi(this);

}


wndEditFirefighter::wndEditFirefighter(QWidget *parent, DatabaseManager *newDb, QString ffid):
        QMainWindow(parent),
        ui(new Ui::wndEditFirefighter)
    {

        ui->setupUi(this);
        db=newDb;

        // Create a firefighter object and load its attributes
        edit = new Firefighter;
        if(!edit->loadAttributes(ffid,db)){
            QMessageBox::warning(0,"Firefighter Error: Read","Could not retrieve firefighter information from database. See log for more information.");
        }

        // Update the personal information fields, training list, and equipment list
        updateFirefighterFields();
        updateTrainingList();
        updateEquipmentList();

        // connect the ui object signals to the appropriate slots
        connect(ui->btnUpdatePersonal,SIGNAL(clicked()),this,SLOT(btnUpdatePersonalClicked()));

        connect(ui->lstTraining,SIGNAL(itemChanged(QListWidgetItem*)),this,SLOT(trainingItemClicked(QListWidgetItem*)));
        connect(ui->btnUpdateTraining,SIGNAL(clicked()),this,SLOT(btnUpdateTrainingClicked()));
        connect(ui->lstTraining,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(updateTrainingInfo(QListWidgetItem*)));

        connect(ui->lstEquipment,SIGNAL(itemChanged(QListWidgetItem*)),this,SLOT(equipmentItemClicked(QListWidgetItem*)));
        connect(ui->btnUpdateEquipment,SIGNAL(clicked()),this,SLOT(btnUpdateEquipmentClicked()));
        connect(ui->lstEquipment,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(updateEquipmentInfo(QListWidgetItem*)));

    }


wndEditFirefighter::~wndEditFirefighter()
{
    delete ui;
    delete edit;
}

// private:

void wndEditFirefighter::updateFirefighterFields(){
    ui->txtFirstName->setText(edit->FirstName());
    ui->txtMiddleName->setText(edit->MiddleName());
    ui->txtLastName->setText(edit->LastName());
    ui->dateDob->setDate(QVariant(edit->Dob()).toDate());
    ui->txtLocalID->setText(edit->LocalID());
    ui->txtStateID->setText(edit->StateID());
    ui->txtAddress->setText(edit->Address());
    ui->txtCity->setText(edit->City());
    ui->txtState->setCurrentIndex(ui->txtState->findText(edit->State()));
    ui->txtZipCode->setText(edit->ZipCode());
    ui->dateJoin->setDate(QVariant(edit->dateJoin()).toDate());
    ui->txtStatus->setText(edit->Status());
    ui->txtHphone->setText(edit->Hphone());
    ui->txtWphone->setText(edit->Wphone());
    ui->txtCphone->setText(edit->Cphone());
    ui->txtDrvLic->setText(edit->DrvLic());
    ui->txtCDL->setText(edit->CDL());
}


void wndEditFirefighter::updateTrainingList(){
    ui->lstTraining->clear();

    QSqlQuery traininglist;
    traininglist.prepare("SELECT training.title,fft.tid "
                         "FROM training LEFT JOIN ("
                           "SELECT * FROM fftraining WHERE ffid=?) as fft ON "
                         "training.id=fft.tid");
    traininglist.addBindValue(edit->ID());
    if(db->query(traininglist)){
        while(traininglist.next()){
            QListWidgetItem *newitem = new QListWidgetItem(traininglist.value(0).toString());
            if(traininglist.value(1).toString()!=""){
                newitem->setCheckState(Qt::Checked);
            }
            else{
                newitem->setCheckState(Qt::Unchecked);
            }
            ui->lstTraining->addItem(newitem);

        }
    }
    else{
        qWarning("Firefighter Error (%d): Could not get training exam information. Database Error: %s",
                 edit->ID(),qPrintable(traininglist.lastError().text()));
    }
}

void wndEditFirefighter::toggleTrainingInformationEnabled(QListWidgetItem* item){
    if(item->checkState()==Qt::Checked){
        ui->txtFFSig->setEnabled(1);
        ui->txtSupSig->setEnabled(1);
        ui->dateTraining->setEnabled(1);
        ui->btnUpdateTraining->setEnabled(1);
    }
    else{
        ui->txtFFSig->setEnabled(0);
        ui->txtSupSig->setEnabled(0);
        ui->dateTraining->setEnabled(0);
        ui->btnUpdateTraining->setEnabled(0);
        ui->txtFFSig->clear();
        ui->txtSupSig->clear();
    }
}


void wndEditFirefighter::updateEquipmentList(){
    ui->lstEquipment->clear();

    QSqlQuery equipmentlist;
    equipmentlist.prepare("SELECT equipment.title,ffe.eqid "
                         "FROM equipment LEFT JOIN ("
                           "SELECT * FROM ffequipment WHERE ffid=?) as ffe ON "
                         "equipment.id=ffe.eqid");
    equipmentlist.addBindValue(edit->ID());
    if(db->query(equipmentlist)){
        while(equipmentlist.next()){
            QListWidgetItem *newitem = new QListWidgetItem(equipmentlist.value(0).toString());
            if(equipmentlist.value(1).toString()!=""){
                newitem->setCheckState(Qt::Checked);
            }
            else{
                newitem->setCheckState(Qt::Unchecked);
            }
            ui->lstEquipment->addItem(newitem);

        }
    }
    else{
        qWarning("Firefighter Error (%d): Could not get equipment information. Database Error: %s",
                 edit->ID(),qPrintable(equipmentlist.lastError().text()));
    }
}

void wndEditFirefighter::toggleEquipmentInformationEnabled(QListWidgetItem* item){
    if(item->checkState()==Qt::Checked){
        ui->txtEquipSerial->setEnabled(1);
        ui->txtEquipType->setEnabled(1);
        ui->txtEquipSize->setEnabled(1);
        ui->txtEquipYear->setEnabled(1);
        ui->radEquipmentNew->setEnabled(1);
        ui->radEquipmentUsed->setEnabled(1);
        ui->btnUpdateEquipment->setEnabled(1);
    }
    else{
        ui->txtEquipSerial->setEnabled(0);
        ui->txtEquipType->setEnabled(0);
        ui->txtEquipSize->setEnabled(0);
        ui->txtEquipYear->setEnabled(0);
        ui->radEquipmentNew->setEnabled(0);
        ui->radEquipmentUsed->setEnabled(0);
        ui->btnUpdateEquipment->setEnabled(0);
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
void wndEditFirefighter::btnUpdatePersonalClicked(){
    QVector<QString> ffattributes;

    // Build attribute list for firefighter based on forms
    ffattributes.append(ui->txtFirstName->text());
    ffattributes.append(ui->txtMiddleName->text());
    ffattributes.append(ui->txtLastName->text());
    ffattributes.append(ui->dateDob->date().toString("yyyy-MM-dd 00:00:00.000"));
    ffattributes.append(ui->txtLocalID->text());
    ffattributes.append(ui->txtStateID->text());
    ffattributes.append(ui->txtAddress->text());
    ffattributes.append(ui->txtCity->text());
    ffattributes.append(ui->txtState->itemText(ui->txtState->currentIndex()));
    ffattributes.append(ui->txtZipCode->text());
    ffattributes.append(ui->dateJoin->date().toString("yyyy-MM-dd 00:00:00.000"));
    ffattributes.append(ui->txtStatus->text());
    ffattributes.append(ui->txtHphone->text());
    ffattributes.append(ui->txtWphone->text());
    ffattributes.append(ui->txtCphone->text());
    ffattributes.append(ui->txtDrvLic->text());
    ffattributes.append(ui->txtCDL->text());

    if(edit->updateAttributes(ffattributes,db)){
        QMessageBox::information(this,"Firefighter Information: Update","Firefighter was successfully updated in database!");
    }
    else{
        QMessageBox::warning(this,"Firefighter Error: Update","Firefighter information failed to update! See log for more information.");
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
void wndEditFirefighter::trainingItemClicked(QListWidgetItem* item){

    QString exam(item->data(Qt::DisplayRole).toString());
    // If the item is being checked, i.e. added:
    if(item->checkState()==Qt::Checked){

        // Build a query to add the information to the database
        QSqlQuery addFFTraining;

        addFFTraining.prepare("INSERT INTO fftraining (tid,ffid) SELECT id,? FROM training WHERE title=?");
        addFFTraining.addBindValue(edit->ID());
        addFFTraining.addBindValue(exam);

        // And execute the query, catching any problems
        if(!db->query(addFFTraining)){
            qWarning("Firefighter Error (%d): Could not link training exam `%s`. Database Error: %s",
                     edit->ID(),qPrintable(exam),qPrintable(addFFTraining.lastError().text()));
        }
    }

    // If the item is being unchecked, i.e. removed
    else{

        // First verify they intend to destruct information
        if(QMessageBox::question(0,"Training: Confirm Removal","Are you sure you would like to remove this exam information?",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){

            // If so, build a query to remove the link from the database
            QSqlQuery removeFFTraining;
            removeFFTraining.prepare("DELETE FROM fftraining WHERE ffid=? AND tid=(SELECT id FROM training WHERE title=?)");
            removeFFTraining.addBindValue(edit->ID());
            removeFFTraining.addBindValue(exam);

            // Attempt to execute the query, catching any problems
            if(!db->query(removeFFTraining)){
                qWarning("Firefighter Error (%d): Could not unlink training exam `%s`. Database Error: %s",
                        edit->ID(),qPrintable(exam),qPrintable(removeFFTraining.lastError().text()));
            }
        }

        // If the uncheck was not intended, replace the check without destroying information
        else{
            // Note: We cannot just set the checkStatus of item to Qt::Checked
            //  because this would call this function again, thereby creating
            //  a duplicate item in the database.
            updateTrainingList();
        }
    }
    toggleTrainingInformationEnabled(item);
}


/*
   Function: btnUpdateTrainingClicked

   Updates the signature and date information for the
   highlighted training exam in the database for the
   firefighter currently being edited.


   See Also:

      <trainingItemClicked>
*/
void wndEditFirefighter::btnUpdateTrainingClicked(){
    if(ui->lstTraining->currentItem()){
        QString exam(ui->lstTraining->currentItem()->data(Qt::DisplayRole).toString());
        QSqlQuery updateQuery;

        updateQuery.prepare("UPDATE fftraining SET ffesig=?, supesig=?, tdate=? WHERE ffid=? AND tid=(SELECT id FROM training WHERE title=?)");
        updateQuery.addBindValue(ui->txtFFSig->text());
        updateQuery.addBindValue(ui->txtSupSig->text());
        updateQuery.addBindValue(ui->dateTraining->date().toString("yyyy-MM-dd 00:00:00.000"));
        updateQuery.addBindValue(edit->ID());
        updateQuery.addBindValue(exam);

        if(db->query(updateQuery)){
            QMessageBox::information(0,"Firefighter Information: Training Update","Training exam information successfully updated.");
        }
        else{
            QMessageBox::warning(0,"Firefighter Error: Training Update","There was a problem updating the training exam information. See log for more information.");
            qWarning("Firefighter Error (%d): Could not update training exam `%s`. Database Error: %s",
                     edit->ID(),qPrintable(exam),qPrintable(updateQuery.lastError().text()));
        }
    }
}

void wndEditFirefighter::updateTrainingInfo(QListWidgetItem* item){
        toggleTrainingInformationEnabled(item);
        QString exam(item->data(Qt::DisplayRole).toString());
        QSqlQuery selectQuery;
        selectQuery.prepare("SELECT ffesig,supesig,tdate FROM fftraining WHERE ffid=? AND tid=(SELECT id FROM training WHERE title=?)");
        selectQuery.addBindValue(edit->ID());
        selectQuery.addBindValue(exam);
        if(db->query(selectQuery)){
            selectQuery.next();
            ui->txtFFSig->setText(selectQuery.value(0).toString());
            ui->txtSupSig->setText(selectQuery.value(1).toString());
            ui->dateTraining->setDate(selectQuery.value(2).toDate());
        }
        else{
            qWarning("Firefighter Error (%d): Could not retrieve information for training exam `%s`. Database Error: %s",
                     edit->ID(),qPrintable(exam),qPrintable(selectQuery.lastError().text()));
        }
}



/*
** EQUIPMENT INFORMATION
*/


void wndEditFirefighter::equipmentItemClicked(QListWidgetItem* item){

    QString equip(item->data(Qt::DisplayRole).toString());
    // If the item is being checked, i.e. added:
    if(item->checkState()==Qt::Checked){

        // Build a query to add the information to the database
        QSqlQuery addFFequip;

        addFFequip.prepare("INSERT INTO ffequipment (eqid,ffid) SELECT id,? FROM equipment WHERE title=?");
        addFFequip.addBindValue(edit->ID());
        addFFequip.addBindValue(equip);

        // And execute the query, catching any problems
        if(!db->query(addFFequip)){
            qWarning("Firefighter Error (%d): Could not link equipment `%s`. Database Error: %s",
                     edit->ID(),qPrintable(equip),qPrintable(addFFequip.lastError().text()));
        }
    }

    // If the item is being unchecked, i.e. removed
    else{

        // First verify they intend to destruct information
        if(QMessageBox::question(0,"Equipment: Confirm Removal","Are you sure you would like to remove this exam information?",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){

            // If so, build a query to remove the link from the database
            QSqlQuery removeFFEquip;
            removeFFEquip.prepare("DELETE FROM ffequipment WHERE ffid=? AND eqid=(SELECT id FROM equipment WHERE title=?)");
            removeFFEquip.addBindValue(edit->ID());
            removeFFEquip.addBindValue(equip);

            // Attempt to execute the query, catching any problems
            if(!db->query(removeFFEquip)){
                qWarning("Firefighter Error (%d): Could not unlink equipment `%s`. Database Error: %s",
                        edit->ID(),qPrintable(equip),qPrintable(removeFFEquip.lastError().text()));
            }
        }

        // If the uncheck was not intended, replace the check without destroying information
        else{
            // Note: We cannot just set the checkStatus of item to Qt::Checked
            //  because this would call this function again, thereby creating
            //  a duplicate item in the database.
            updateEquipmentList();
        }
    }
    toggleEquipmentInformationEnabled(item);
}


void wndEditFirefighter::btnUpdateEquipmentClicked(){
    if(ui->lstEquipment->currentItem()){
        QString equip(ui->lstEquipment->currentItem()->data(Qt::DisplayRole).toString());
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE ffequipment SET issued=?, size=?, type=?, serial=?, year=? WHERE ffid=? AND eqid=(SELECT id FROM equipment WHERE title=?)");
        updateQuery.addBindValue(ui->radEquipmentNew->isChecked()?1:0);
        updateQuery.addBindValue(ui->txtEquipSize->text());
        updateQuery.addBindValue(ui->txtEquipType->text());
        updateQuery.addBindValue(ui->txtEquipSerial->text());
        updateQuery.addBindValue(ui->txtEquipYear->text());
        updateQuery.addBindValue(edit->ID());
        updateQuery.addBindValue(equip);
        if(db->query(updateQuery)){
            QMessageBox::information(0,"Firefighter Information: Equipment Update","Equipment information successfully updated.");
        }
        else{
            QMessageBox::warning(0,"Firefighter Error: Equipment Update","There was a problem updating the equipment information. See log for more information.");
            qWarning("Firefighter Error (%d): Could not update equipment `%s`. Database Error: %s",
                     edit->ID(),qPrintable(equip),qPrintable(updateQuery.lastError().text()));
        }
    }
}

void wndEditFirefighter::updateEquipmentInfo(QListWidgetItem* item){
        toggleEquipmentInformationEnabled(item);
        QString equip(item->data(Qt::DisplayRole).toString());
        QSqlQuery selectQuery;
        selectQuery.prepare("SELECT issued,size,type,serial,year FROM ffequipment WHERE ffid=? AND eqid=(SELECT id FROM equipment WHERE title=?)");
        selectQuery.addBindValue(edit->ID());
        selectQuery.addBindValue(equip);
        if(db->query(selectQuery)){
            selectQuery.next();

            ui->radEquipmentNew->setChecked(selectQuery.value(0).toBool()?1:0);
            ui->radEquipmentUsed->setChecked(selectQuery.value(0).toBool()?0:1);
            ui->txtEquipSize->setText(selectQuery.value(1).toString());
            ui->txtEquipType->setText(selectQuery.value(2).toString());
            ui->txtEquipSerial->setText(selectQuery.value(3).toString());
            ui->txtEquipYear->setText(selectQuery.value(4).toString());

        }
        else{
            qWarning("Firefighter Error (%d): Could not retrieve information for equipment `%s`. Database Error: %s",
                     edit->ID(),qPrintable(equip),qPrintable(selectQuery.lastError().text()));
        }
}

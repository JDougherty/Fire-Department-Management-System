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
        edit->LoadAttributes(ffid,db);

        // Update the personal information text fields in the ui
        updateFirefighterFields();

        // Update the list of training exams
        updateTrainingList();

        // connect the ui object signals to the appropriate slots
        connect(ui->btnUpdatePersonal,SIGNAL(clicked()),this,SLOT(btnUpdatePersonalClicked()));
        connect(ui->lstTraining,SIGNAL(itemChanged(QListWidgetItem*)),this,SLOT(trainingItemClicked(QListWidgetItem*)));
        connect(ui->btnUpdateTraining,SIGNAL(clicked()),this,SLOT(btnUpdateTrainingClicked()));
        connect(ui->lstTraining,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(updateTrainingInfo(QListWidgetItem*)));

    }


wndEditFirefighter::~wndEditFirefighter()
{
    delete ui;
    delete edit;
}


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
        qDebug("Error! Could not get training information!");
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

/*
** private slots:
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

    if(edit->UpdateInDatabase(ffattributes,db)){
        QMessageBox::information(this,"Firefighter: Update Successful","Firefighter was successfully updated in database!");
    }
    else{
        QMessageBox::warning(this,"Firefighter: Update Failed","Firefighter information failed to update! Check log for more information.");
    }
}


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
            qWarning("Could not link training exam %s to firefighter with id %d. Error: %s",
                     qPrintable(exam),edit->ID(),qPrintable(addFFTraining.lastError().text()));
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
                qWarning("Could not unlink training exam %s to firefighter with id %d. Error: %s",
                        qPrintable(exam),edit->ID(),qPrintable(removeFFTraining.lastError().text()));
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

    QString exam(ui->lstTraining->currentItem()->data(Qt::DisplayRole).toString());
    QSqlQuery updateQuery;

    updateQuery.prepare("UPDATE fftraining SET ffesig=?, supesig=?, tdate=? WHERE ffid=? AND tid=(SELECT id FROM training WHERE title=?)");
    updateQuery.addBindValue(ui->txtFFSig->text());
    updateQuery.addBindValue(ui->txtSupSig->text());
    updateQuery.addBindValue(ui->dateTraining->date().toString("yyyy-MM-dd 00:00:00.000"));
    updateQuery.addBindValue(edit->ID());
    updateQuery.addBindValue(exam);

    if(db->query(updateQuery)){
        QMessageBox::information(0,"Training: Update","Training exam information successfully updated.");
    }
    else{
        QMessageBox::warning(0,"Training: Update","There was a problem updating the training exam information. Please see the log for details.");
        qWarning("Could not update training exam %s for firefighter with id %d. Error: %s",
                 qPrintable(exam),edit->ID(),qPrintable(updateQuery.lastError().text()));
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
            qWarning("Could not retrieve information for training exam %s for firefighter with id %d. Error: %s",
                     qPrintable(exam),edit->ID(),qPrintable(selectQuery.lastError().text()));
        }
}


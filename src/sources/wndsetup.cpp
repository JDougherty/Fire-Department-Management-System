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

#include <QFileDialog>

#include "../headers/wndsetup.h"
#include "ui_wndsetup.h"

wndSetup::wndSetup( QWidget *parent, DatabaseManager *newDb, MainWindow *newMw ) :
        QMainWindow( parent ),
        ui( new Ui::wndSetup )
{
    ui->setupUi( this );
    db = newDb;
    mw = newMw;

    _iInstallType = NOT_DEFINED;

    // Doesnt delete the tabs
    ui->tabWidget->removeTab( 5 ); // tabExInstFinish
    ui->tabWidget->removeTab( 4 ); // tabExInstDBSettings
    ui->tabWidget->removeTab( 3 ); // tabNewInstFinish
    ui->tabWidget->removeTab( 2 ); // tabNewInstDBSettings
    ui->tabWidget->removeTab( 1 ); // tabExInstFDSettings
}

wndSetup::~wndSetup( void )
{
    delete ui;
}

void wndSetup::changeEvent( QEvent *e )
{
    QMainWindow::changeEvent( e );

    switch ( e->type() )
    {
        case QEvent::LanguageChange:
            ui->retranslateUi( this );
            break;
        default:
            break;
    }
}

void wndSetup::on_btnSetupContinue_clicked()
{
    if ( ui->radioExInst->isChecked() || ui->radioNewInst->isChecked() )
    {
        ui->tabWidget->setCurrentIndex( 1 );
    }
    else
    {
        QMessageBox::warning( this, "Error", "Please select an installation option.", QMessageBox::Ok );
    }
}

void wndSetup::on_radioExInst_clicked()
{
    // Clicking the radio button even if checked calls this function so see if we need to do anything
    if ( _iInstallType != EXISTING_INST )
    {
        qDebug( "Install existing instance." );

        // got to hide the tabs for existing installation
        if ( _iInstallType == NEW_INST )
        {
            ui->tabWidget->removeTab( 3 ); // tabNewInstFinish
            ui->tabWidget->removeTab( 2 ); // tabNewInstDBSettings
            ui->tabWidget->removeTab( 1 ); // tabNewInstFDSettings
        }

        // add back the tabs for the new installation
        ui->tabWidget->addTab( ui->tabExInstDBSettings, "Step 1: Database Settings" );
        ui->tabWidget->addTab( ui->tabExInstFinish, "Finish" );

        _iInstallType = EXISTING_INST;
    }
}

void wndSetup::on_btnExInstDBFile_clicked()
{
    QString sDBFile = QFileDialog::getOpenFileName( this, "Select the database file.", QString::null, "*.db" );

    if ( !sDBFile.isEmpty() )
    {
        qDebug( "Database file is now %s", sDBFile.toStdString().c_str() );
        ui->leExInstDBLocation->setText( sDBFile );
    }
}

void wndSetup::on_btnExInstDBSettings_clicked()
{
    ui->tabWidget->setCurrentIndex( 2 ); // tabExInstFinish
}

void wndSetup::on_btnExInstFinish_clicked()
{
    QString sDBFile;

    sDBFile = ui->leExInstDBLocation->text();
    if ( sDBFile == "" )
    {
        ui->tabWidget->setCurrentIndex( 1 ); // tabExInstDBSettings
        QMessageBox::warning( this, "Error", "Please select a database file.", QMessageBox::Ok );
        return;
    }

    if ( mw != NULL )
    {
        mw->showMaximized();
        hide();
    }
}

void wndSetup::on_radioNewInst_clicked()
{
    // Clicking the radio button even if checked calls this function so see if we need to do anything
    if ( _iInstallType != NEW_INST )
    {
        qDebug( "Install new instance." );

        // got to hide the tabs for existing installation
        if ( _iInstallType == EXISTING_INST )
        {
            ui->tabWidget->removeTab( 2 ); // tabExInstFinish
            ui->tabWidget->removeTab( 1 ); // tabExInstDBSettings
        }

        // add back the tabs for the new installation
        ui->tabWidget->addTab( ui->tabNewInstFDSettings, "Step 1: Fire Department Information" );
        ui->tabWidget->addTab( ui->tabNewInstDBSettings, "Step 2: Database Settings" );
        ui->tabWidget->addTab( ui->tabNewInstFinish, "Finish" );

        _iInstallType = NEW_INST;
    }
}

void wndSetup::on_btnNewInstDBLocation_clicked()
{
    QString sDBLocation =  QFileDialog::getExistingDirectory( this, "", QString::null, QFileDialog::ShowDirsOnly );

    if ( !sDBLocation.isEmpty() )
    {
        qDebug( "Database path is now %s", sDBLocation.toStdString().c_str() );
        ui->leNewInstDBLocation->setText( sDBLocation );
    }
}

void wndSetup::on_btnNewInstFDSettings_clicked()
{
     ui->tabWidget->setCurrentIndex( 2 ); // tabNewInstDBSettings
}

void wndSetup::on_btnNewInstDBSettings_clicked()
{
     ui->tabWidget->setCurrentIndex( 3 ); // tabNewInstFinish
}

void wndSetup::on_btnNewInstFinish_clicked()
{
    QString sDBLocation;

    sDBLocation = ui->leNewInstDBLocation->text();
    if ( sDBLocation == "" )
    {
        ui->tabWidget->setCurrentIndex( 2 ); // tabNewInstDBSettings
        QMessageBox::warning( this, "Error", "Please select a location to place the database file.", QMessageBox::Ok );
        return;
    }

    if ( mw != NULL )
    {
        mw->showMaximized();
        hide();
    }
}

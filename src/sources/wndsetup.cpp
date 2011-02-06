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

wndSetup::wndSetup( QWidget *parent, DatabaseManager *pDB, SettingsManager *pSM, MainWindow *pMW ) :
        QMainWindow( parent ),
        _pUI( new Ui::wndSetup )
{
    _pUI->setupUi( this );
    _pDB = pDB;
    _pSM = pSM;
    _pMW = pMW;

    _iInstallType = NOT_DEFINED;

    // Doesnt delete the tabs
    _pUI->tabWidget->removeTab( 5 ); // tabExInstFinish
    _pUI->tabWidget->removeTab( 4 ); // tabExInstDBSettings
    _pUI->tabWidget->removeTab( 3 ); // tabNewInstFinish
    _pUI->tabWidget->removeTab( 2 ); // tabNewInstDBSettings
    _pUI->tabWidget->removeTab( 1 ); // tabNewInstFDSettings

    clearAndHideProgressBars();
}

wndSetup::~wndSetup( void )
{
    delete _pUI;
}

void wndSetup::changeEvent( QEvent *e )
{
    QMainWindow::changeEvent( e );

    switch ( e->type() )
    {
        case QEvent::LanguageChange:
            _pUI->retranslateUi( this );
            break;
        default:
            break;
    }
}

void wndSetup::clearAndHideProgressBars( void )
{
    _pUI->progExInstStatus->setValue( 0 );
    _pUI->progExInstStatus->hide();
    _pUI->lblExInstStatus->setText( QString::null );
    _pUI->lblExInstStatus->hide();

    _pUI->progNewInstStatus->setValue( 0 );
    _pUI->progNewInstStatus->hide();
    _pUI->lblNewInstStatus->setText( QString::null );
    _pUI->lblNewInstStatus->hide();
}

void wndSetup::on_btnSetupContinue_clicked()
{
    if ( _pUI->radioExInst->isChecked() || _pUI->radioNewInst->isChecked() )
    {
        _pUI->tabWidget->setCurrentIndex( 1 );
    }
    else
    {
        QMessageBox::warning( this, "Error", "Please select an installation option.", QMessageBox::Ok );
    }
}

/*
    Using an existing instance
*/
void wndSetup::on_radioExInst_clicked()
{
    // Clicking the radio button even if checked calls this function so see if we need to do anything
    if ( _iInstallType != EXISTING_INST )
    {
        qDebug( "Setup: User wants to install an existing instance." );

        // got to hide the tabs for existing installation
        if ( _iInstallType == NEW_INST )
        {
            _pUI->tabWidget->removeTab( 3 ); // tabNewInstFinish
            _pUI->tabWidget->removeTab( 2 ); // tabNewInstDBSettings
            _pUI->tabWidget->removeTab( 1 ); // tabNewInstFDSettings
        }

        // add back the tabs for the new installation
        _pUI->tabWidget->addTab( _pUI->tabExInstDBSettings, "Step 1: Database Settings" );
        _pUI->tabWidget->addTab( _pUI->tabExInstFinish, "Finish" );

        _iInstallType = EXISTING_INST;
    }
}

void wndSetup::on_btnExInstDBFile_clicked()
{
    QString sDBFile = QFileDialog::getOpenFileName( this, "Select the database file.", QString::null, "*.db" );

    if ( !sDBFile.isEmpty() )
    {
        qDebug( "Setup: Database file: %s", sDBFile.toStdString().c_str() );
        _pUI->leExInstDBLocation->setText( sDBFile );
    }
}

void wndSetup::on_btnExInstDBSettings_clicked()
{
    _pUI->tabWidget->setCurrentIndex( 2 ); // tabExInstFinish
}

void wndSetup::on_btnExInstFinish_clicked()
{
    QString sDBFile;

    _pUI->progExInstStatus->show();
    _pUI->lblExInstStatus->show();

    // Check user input
    _pUI->lblExInstStatus->setText( QString( "Checking user input." ) );

    sDBFile = _pUI->leExInstDBLocation->text();
    if ( sDBFile == "" )
    {
        _pUI->tabWidget->setCurrentIndex( 1 ); // tabExInstDBSettings
        QMessageBox::warning( this, "Error", "Please select a database file.", QMessageBox::Ok );
        clearAndHideProgressBars();
        return;
    }
    _pUI->progExInstStatus->setValue( 15 );

    if ( !QFile::exists( sDBFile ) )
    {
        _pUI->tabWidget->setCurrentIndex( 1 ); // tabExInstDBSettings
        QMessageBox::warning( this, "Error", "Please select a file that exists.", QMessageBox::Ok );
        clearAndHideProgressBars();
        return;
    }
    _pUI->progExInstStatus->setValue( 30 );

    // Try connecting to the database
    _pUI->lblExInstStatus->setText( QString( "Accessing the database." ) );

    _pDB->setDBFile( sDBFile );

    if ( !_pDB->open() )
    {
        QMessageBox::critical( this, "Critical Error", "Database could not be opened.", QMessageBox::Ok );
        qCritical( "Critical Error - Database: Could not be opened." );
        clearAndHideProgressBars();
        return;
    }
    _pUI->progExInstStatus->setValue( 70 );

    if ( !_pDB->verify() )
    {
        QMessageBox::critical( this, "Critical Error", "Database has an invalid structure.", QMessageBox::Ok );
        qCritical( "Critical Error - Database: Invalid structure." );
        clearAndHideProgressBars();
        return;
    }
    _pUI->progExInstStatus->setValue( 100 );

    _pSM->setDBFile( sDBFile );
    _pSM->save();

    if ( _pMW != NULL )
    {
        _pMW->showMaximized();
        hide();
    }
}

/*
    Installing a new instance
*/
void wndSetup::on_radioNewInst_clicked()
{
    // Clicking the radio button even if checked calls this function so see if we need to do anything
    if ( _iInstallType != NEW_INST )
    {
        qDebug( "Setup: User wants to install a new instance." );

        // got to hide the tabs for existing installation
        if ( _iInstallType == EXISTING_INST )
        {
            _pUI->tabWidget->removeTab( 2 ); // tabExInstFinish
            _pUI->tabWidget->removeTab( 1 ); // tabExInstDBSettings
        }

        // add back the tabs for the new installation
        _pUI->tabWidget->addTab( _pUI->tabNewInstFDSettings, "Step 1: Fire Department Information" );
        _pUI->tabWidget->addTab( _pUI->tabNewInstDBSettings, "Step 2: Database Settings" );
        _pUI->tabWidget->addTab( _pUI->tabNewInstFinish, "Finish" );

        _iInstallType = NEW_INST;
    }
}

void wndSetup::on_btnNewInstDBLocation_clicked()
{
    QString sDBLocation =  QFileDialog::getExistingDirectory( this, "", QString::null, QFileDialog::ShowDirsOnly );

    if ( !sDBLocation.isEmpty() )
    {
        qDebug( "Setup: Database path: %s", sDBLocation.toStdString().c_str() );
        _pUI->leNewInstDBLocation->setText( sDBLocation );
    }
}

void wndSetup::on_btnNewInstFDSettings_clicked()
{
     _pUI->tabWidget->setCurrentIndex( 2 ); // tabNewInstDBSettings
}

void wndSetup::on_btnNewInstDBSettings_clicked()
{
     _pUI->tabWidget->setCurrentIndex( 3 ); // tabNewInstFinish
}

void wndSetup::on_btnNewInstFinish_clicked()
{
    QString sDBLocation;
    QString sDBFile;

    _pUI->progNewInstStatus->show();
    _pUI->lblNewInstStatus->show();

    // Check user input
    _pUI->lblNewInstStatus->setText( QString( "Checking user input." ) );

    sDBLocation = _pUI->leNewInstDBLocation->text();
    if ( sDBLocation == "" )
    {
        _pUI->tabWidget->setCurrentIndex( 2 ); // tabNewInstDBSettings
        QMessageBox::warning( this, "Error", "Please select a location to place the database file.", QMessageBox::Ok );
        clearAndHideProgressBars();
        return;
    }
    _pUI->progNewInstStatus->setValue( 15 );

    if ( !QFile::exists( sDBLocation ) )
    {
        _pUI->tabWidget->setCurrentIndex( 2 ); // tabNewInstDBSettings
        QMessageBox::warning( this, "Error", "Please select a location that exists.", QMessageBox::Ok );
        clearAndHideProgressBars();
        return;
    }
    _pUI->progNewInstStatus->setValue( 30 );

    // Try setting up the database
    _pUI->lblNewInstStatus->setText( QString( "Setting up the database." ) );

    sDBFile = sDBLocation;
    sDBFile.append( QDir::separator() ).append( "fdms.db" );
    sDBFile = QDir::toNativeSeparators( sDBFile );

    _pDB->setDBFile( sDBFile );

    if ( !_pDB->open() )
    {
        QMessageBox::critical( this, "Critical Error", "Database could not be opened.", QMessageBox::Ok );
        qCritical( "Critical Error - Database: Could not be opened." );
        clearAndHideProgressBars();
        return;
    }
    _pUI->progNewInstStatus->setValue( 45 );

    if ( !_pDB->build() )
    {
        QMessageBox::critical( this, "Critical Error", "Database could not be built.", QMessageBox::Ok );
        qCritical( "Critical Error - Database: Could not be built." );
        clearAndHideProgressBars();
        return;
    }
    _pUI->progNewInstStatus->setValue( 80 );

    if ( !_pDB->verify() )
    {
        QMessageBox::critical( this, "Critical Error", "Database has an invalid structure.", QMessageBox::Ok );
        qCritical( "Critical Error - Database: Invalid structure." );
        clearAndHideProgressBars();
        return;
    }
    _pUI->progNewInstStatus->setValue( 100 );

    _pSM->setDBFile( sDBFile );
    _pSM->save();

    if ( _pMW != NULL )
    {
        _pMW->showMaximized();
        hide();
    }
}

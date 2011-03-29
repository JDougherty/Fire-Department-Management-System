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

#include "wndSetup.h"
#include "ui_wndSetup.h"

/*!
  \param pParent Pointer to the parent widget.
*/
wndSetup::wndSetup( QWidget *pParent ) :
        QMainWindow( pParent )
{
    _pUI = new Ui::wndSetup;
    _pUI->setupUi( this );

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

//! Hides and resets the progress bars and status labels.
/*!
  Called when setup fails for any reason.
*/
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

//! User clicked "Continue" on the main setup tab
void wndSetup::on_btnSetupContinue_clicked( void )
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

//! User chose to connect to an existing instance
void wndSetup::on_radioExInst_clicked( void )
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

        _iInstallType = EXISTING_INST;
    }
}

//! User clicked browse button to select DB file
void wndSetup::on_btnExInstDBFile_clicked( void )
{
    QString sDBFile = QFileDialog::getOpenFileName( this, "Select the database file.", QString::null, "*.db" );

    if ( !sDBFile.isEmpty() )
    {
        qDebug( "Setup: Database file: %s", qPrintable( sDBFile ) );
        _pUI->leExInstDBLocation->setText( sDBFile );
    }
}

//! User clicked "Continue" on DB Settings tab
void wndSetup::on_btnExInstDBSettings_clicked( void )
{
    if ( _pUI->leExInstDBLocation->text().isEmpty() )
    {
        QMessageBox::warning( this, "Error", "Please select a database file.", QMessageBox::Ok );
    }
    else
    {
        _pUI->tabWidget->addTab( _pUI->tabExInstFinish, "Finish" );
        _pUI->tabWidget->setCurrentIndex( 2 ); // tabExInstFinish
    }
}

//! User clicked "Finish"
/*!
  Checks user input, opens and validates the DB, saves the settings, and
  launches the main menu.
*/
void wndSetup::on_btnExInstFinish_clicked( void )
{
    SettingManager *pSM = getSettingManager();
    DatabaseManager *pDM = getDatabaseManager();
    QString sDBFile;

    _pUI->progExInstStatus->show();
    _pUI->lblExInstStatus->show();

    // Check user input
    _pUI->lblExInstStatus->setText( QString( "Checking user input." ) );
    _pUI->progExInstStatus->setValue( 1 ); // forces the ui to update and show the text and progress bar

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

    // Try connecting to the database
    _pUI->lblExInstStatus->setText( QString( "Opening the database." ) );
    _pUI->progExInstStatus->setValue( 30 );

    pDM->setFile( sDBFile );
    if ( !pDM->open() )
    {
        QMessageBox::critical( this, "Critical Error", "Database could not be opened.", QMessageBox::Ok );
        qCritical( "Setup: Critical Error - Database: Could not be opened." );
        clearAndHideProgressBars();
        return;
    }

    _pUI->lblExInstStatus->setText( QString( "Verifying the database." ) );
    _pUI->progExInstStatus->setValue( 50 );

    if ( !pDM->verify() )
    {
        QMessageBox::critical( this, "Critical Error", "Database has an invalid structure.", QMessageBox::Ok );
        qCritical( "Setup: Critical Error - Database: Invalid structure." );
        clearAndHideProgressBars();
        return;
    }

    // Save the configuration file
    _pUI->lblExInstStatus->setText( QString( "Saving configuration file." ) );
    _pUI->progExInstStatus->setValue( 80 );

    pSM->save();

    // All done
    _pUI->lblExInstStatus->setText( QString( "Finished." ) );
    _pUI->progExInstStatus->setValue( 100 );

    hide();
}

/*
    Installing a new instance
*/

//! User chose to setup a new FDMS instance
void wndSetup::on_radioNewInst_clicked( void )
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

        _iInstallType = NEW_INST;
    }
}

//! User clicked browse button to select DB location
void wndSetup::on_btnNewInstDBLocation_clicked( void )
{
    QString sDBLocation =  QFileDialog::getExistingDirectory( this, "", QString::null, QFileDialog::ShowDirsOnly );

    if ( !sDBLocation.isEmpty() )
    {
        qDebug( "Setup: Database path: %s", qPrintable( sDBLocation ) );
        _pUI->leNewInstDBLocation->setText( sDBLocation );
    }
}

//! User clicked "Continue" on FD Settings tab
void wndSetup::on_btnNewInstFDSettings_clicked( void )
{
     _pUI->tabWidget->setCurrentIndex( 2 ); // tabNewInstDBSettings
}

//! User clicked "Continue" on DB Settings tab
void wndSetup::on_btnNewInstDBSettings_clicked( void )
{
    if ( _pUI->leNewInstDBLocation->text().isEmpty() )
    {
        QMessageBox::warning( this, "Error", "Please select a location to place the database file.", QMessageBox::Ok );
    }
    else
    {
         _pUI->tabWidget->addTab( _pUI->tabNewInstFinish, "Finish" );
        _pUI->tabWidget->setCurrentIndex( 3 ); // tabNewInstFinish
    }
}

//! User clicked "Finish"
/*!
  Checks user input, opens, builds, and validates the DB, saves the settings, and
  launches the main menu.
*/
void wndSetup::on_btnNewInstFinish_clicked( void )
{
    SettingManager *pSM = getSettingManager();
    DatabaseManager *pDM = getDatabaseManager();
    QString sDBLocation;
    QString sDBFile;

    _pUI->progNewInstStatus->show();
    _pUI->lblNewInstStatus->show();

    // Check user input
    _pUI->lblNewInstStatus->setText( QString( "Checking user input." ) );
    _pUI->progNewInstStatus->setValue( 1 ); // forces the ui to update and show the text and progress bar

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

    // Try setting up the database
    _pUI->lblNewInstStatus->setText( QString( "Opening the database." ) );
    _pUI->progNewInstStatus->setValue( 30 );

    sDBFile = sDBLocation;
    sDBFile.append( QDir::separator() ).append( "fdms.db" );
    sDBFile = QDir::toNativeSeparators( sDBFile );

    pDM->setFile( sDBFile );
    if ( pDM->exists() )
    {
        int iResult = QMessageBox::question( this, "Overwrite database?", "Database file already exists in this directory.\nOverwrite the file?",
                                             QMessageBox::Yes | QMessageBox::No );

        switch ( iResult )
        {
           case QMessageBox::Yes:
               pDM->removeFile();
               break;
           case QMessageBox::No:
               _pUI->tabWidget->setCurrentIndex( 2 ); // tabNewInstDBSettings
               QMessageBox::warning( this, "Select database location.", "Please select a new database location.", QMessageBox::Ok );
               clearAndHideProgressBars();
               return;
           default:
               QMessageBox::critical( this, "Critical Error", "Default case reached.", QMessageBox::Ok );
               qCritical( "Setup: Critical Error - Default case reached." );
               clearAndHideProgressBars();
               return;
         }
    }

    if ( !pDM->open() )
    {
        QMessageBox::critical( this, "Critical Error", "Database could not be opened.", QMessageBox::Ok );
        qCritical( "Setup: Critical Error - Database: Could not be opened." );
        clearAndHideProgressBars();
        return;
    }

    _pUI->lblNewInstStatus->setText( QString( "Building the database." ) );
    _pUI->progNewInstStatus->setValue( 45 );

    if ( !pDM->create() )
    {
        QMessageBox::critical( this, "Critical Error", "Database could not be created.", QMessageBox::Ok );
        qCritical( "Setup: Critical Error - Database: Could not be created." );
        clearAndHideProgressBars();
        return;
    }

    _pUI->lblNewInstStatus->setText( QString( "Verifying the database." ) );
    _pUI->progNewInstStatus->setValue( 60 );

    if ( !pDM->verify() )
    {
        QMessageBox::critical( this, "Critical Error", "Database has an invalid structure.", QMessageBox::Ok );
        qCritical( "Setup: Critical Error - Database: Invalid structure." );
        clearAndHideProgressBars();
        return;
    }

    //Save the configuration file
    _pUI->progNewInstStatus->setValue( 80 );
    _pUI->lblNewInstStatus->setText( QString( "Saving configuration file." ) );

    pSM->save();

    // All done
    _pUI->lblNewInstStatus->setText( QString( "Finished." ) );
    _pUI->progNewInstStatus->setValue( 100 );

    hide();
}

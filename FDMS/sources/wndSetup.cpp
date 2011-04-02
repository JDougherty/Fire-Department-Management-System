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

pgIntro::pgIntro( QWidget *pParent )
    : QWizardPage( pParent )
{
    QVBoxLayout *pBoxLayout = new QVBoxLayout;
    QFont font;

    setTitle( tr( "Setup Information" ) );

    pLabelIntro = new QLabel( tr( "Welcome to the setup for the Fire Department Management System. "
                            "Please select an installation process below. Refer to the documentation "
                            "if you are unsure of what a specific step requires." ) );
    pLabelOptions = new QLabel( tr( "If you are seeing this window, your FDMS configuration file was not "
                                  "found. If this is not your first time launching the Fire Department "
                                  "Management System, you may wish to close this window now and refer to "
                                  "the documentation for restoring the program." ) );

    pRadioNewInstallation = new QRadioButton( tr( "Set up a new instace of the Fire Department Management System " ) );
    pRadioExistingInstallation = new QRadioButton( tr( "Connect to an existing instance of the Fire Department "
                                                       "Management System") );

    pBoxLayout->addWidget( pLabelIntro );
    pBoxLayout->addSpacing( 15 );
    pBoxLayout->addWidget( pLabelOptions );
    pBoxLayout->addSpacing( 40 );
    pBoxLayout->addWidget( pRadioNewInstallation );
    pBoxLayout->addWidget( pRadioExistingInstallation );

    setLayout( pBoxLayout );

    pRadioNewInstallation->setChecked( true );

    registerField( "newInstallation", pRadioNewInstallation );
    registerField( "existingInstallation", pRadioExistingInstallation );

    font.setPointSize( 10 );
    pLabelIntro->setFont( font );
    pLabelOptions->setFont( font );
    pRadioNewInstallation->setFont( font );
    pRadioExistingInstallation->setFont( font );

    pLabelIntro->setWordWrap( true );
    pLabelOptions->setWordWrap( true );
}

int pgIntro::nextId( void ) const
{
    if ( pRadioNewInstallation->isChecked() )
        return wndSetup::NewDatabase;
    else
        return wndSetup::ExistingDatabase;
}

pgNewDatabase::pgNewDatabase( QWidget *pParent )
    : QWizardPage( pParent )
{
    QGridLayout *pGridLayout = new QGridLayout();
    QFont font;

    setTitle( tr( "Database Settings" ) );

    pLabelFolder = new QLabel( tr( "Database Folder" ) );
    pLineEditFolder = new QLineEdit();
    pButtonFolder = new QPushButton( tr( "Browse..." ) );

    pGridLayout->addWidget( pLabelFolder, 0, 0 );
    pGridLayout->addWidget( pLineEditFolder, 0, 1 );
    pGridLayout->addWidget( pButtonFolder, 0, 3 );

    setLayout( pGridLayout );

    registerField( "database.folder*", pLineEditFolder );
    connect( pButtonFolder, SIGNAL( clicked() ), this, SLOT( browse() ) );

    pLineEditFolder->setReadOnly( true );

    font.setPointSize( 10 );
    pLabelFolder->setFont( font );
    pButtonFolder->setFont( font );
}

int pgNewDatabase::nextId( void ) const
{
    return wndSetup::Plugins;
}

void pgNewDatabase::cleanupPage( void )
{
    pLineEditFolder->setText( tr( "" ) );
}

void pgNewDatabase::browse( void )
{
    QString sFolder =  QFileDialog::getExistingDirectory( this, "Select the database folder.", QString::null, QFileDialog::ShowDirsOnly );

    if ( !sFolder.isEmpty() )
    {
        qDebug( "Setup: Database folder: %s", qPrintable( sFolder ) );
        pLineEditFolder->setText( sFolder );
    }
}

pgExistingDatabase::pgExistingDatabase( QWidget *pParent )
    : QWizardPage( pParent )
{
    QGridLayout *pGridLayout = new QGridLayout();
    QFont font;

    setTitle( tr( "Database Settings" ) );

    pLabelFile = new QLabel( tr( "Database File" ) );
    pLineEditFile= new QLineEdit();
    pButtonFile = new QPushButton( tr( "Browse..." ) );

    pGridLayout->addWidget( pLabelFile, 0, 0 );
    pGridLayout->addWidget( pLineEditFile, 0, 1 );
    pGridLayout->addWidget( pButtonFile, 0, 3 );

    setLayout( pGridLayout );

    registerField( "database.file*", pLineEditFile );
    connect( pButtonFile, SIGNAL( clicked() ), this, SLOT( browse() ) );

    pLineEditFile->setReadOnly( true );

    font.setPointSize( 10 );
    pLabelFile->setFont( font );
    pButtonFile->setFont( font );
}

int pgExistingDatabase::nextId( void ) const
{
    return wndSetup::Plugins;
}

bool pgExistingDatabase::isComplete( void )
{
    DatabaseManager *pDBM = getDatabaseManager();

    if ( !QFile::exists( pLineEditFile->text() ) )
    {
        QMessageBox::critical( this, tr( "Error" ), tr( "Please select a database file that exists." ), QMessageBox::Ok );
        return false;
    }

    pDBM->setFile( pLineEditFile->text() );
    if ( !pDBM->open() )
    {
        QMessageBox::critical( this, tr( "Error" ), tr( "Database could not be opened." ), QMessageBox::Ok );
        return false;
    }

    if ( !pDBM->verify() )
    {
        QMessageBox::critical( this, tr( "Error" ), tr( "Database has an invalid structure." ), QMessageBox::Ok );
        return false;
    }

    return true;
}

void pgExistingDatabase::cleanupPage( void )
{
    pLineEditFile->setText( tr( "" ) );
}

void pgExistingDatabase::browse( void )
{
    QString sFile = QFileDialog::getOpenFileName( this, tr( "Select the database file." ), QString::null, "*.db" );

    if ( !sFile.isEmpty() )
    {
        qDebug( qPrintable( tr( "Setup: Database file: %s" ) ), qPrintable( sFile ) );
        pLineEditFile->setText( sFile );
    }
}

void pgPlugins::addPlugin( QAbstractItemModel *model, const QString &name, const QString &version, const QString &filename )
{
    model->insertRow( 0 );
    //model->setData( model->index( 0, 0 ), Qt::Unchecked, Qt::CheckStateRole );
    model->setData( model->index( 0, 0 ), name );
    model->setData( model->index( 0, 1 ), version );
    model->setData( model->index( 0, 2 ), filename );
}

pgPlugins::pgPlugins( QWidget *pParent )
    : QWizardPage( pParent )
{
    QGridLayout *pGridLayout = new QGridLayout();
    QVBoxLayout *pBoxLayout = new QVBoxLayout();
    QFont font;

    setTitle( tr( "Plugin Settings" ) );

    pLabelFolder = new QLabel( tr( "Plugin Folder" ) );
    pLineEditFolder = new QLineEdit();
    pButtonFolder = new QPushButton( tr( "Browse..." ) );
    pGroupBoxPlugins = new QGroupBox( tr( "Plugins" ) );
    pTreeViewPlugins = new QTreeView();

    pGridLayout->addWidget( pLabelFolder, 0, 0 );
    pGridLayout->addWidget( pLineEditFolder, 0, 1 );
    pGridLayout->addWidget( pButtonFolder, 0, 3 );
    pGridLayout->setRowMinimumHeight( 1, 15 );
    pGridLayout->addWidget( pGroupBoxPlugins, 2, 0, 3, 0 );
    pBoxLayout->addWidget( pTreeViewPlugins );

    pGroupBoxPlugins->setLayout( pBoxLayout );
    setLayout( pGridLayout );

    registerField( "plugins.folder*", pLineEditFolder );
    connect( pButtonFolder, SIGNAL( clicked() ), this, SLOT( browse() ) );

    pTreeViewPlugins->setSelectionMode( QTreeView::MultiSelection );
    pTreeViewPlugins->setSelectionBehavior( QAbstractItemView::SelectRows );
    pTreeViewPlugins->setEditTriggers( QAbstractItemView::NoEditTriggers );
    pTreeViewPlugins->setRootIsDecorated( false );
    pTreeViewPlugins->setSortingEnabled( true );

    pLineEditFolder->setReadOnly( true );

    font.setPointSize( 10 );
    pLabelFolder->setFont( font );
    pButtonFolder->setFont( font );
}

bool pgPlugins::isComplete( void )
{
    PluginManager *pPM = getPluginManager();
    bool bAllMet, bMet;

    foreach ( BasePlugin *pPlugin1, pPM->lDatabasePlugins )
    {
        bAllMet = true;
        foreach ( PluginInfo dependency, pPlugin1->getDependencies() )
        {
            bMet = false;
            foreach ( BasePlugin *pPlugin2, pPM->lDatabasePlugins )
            {
                if ( pPlugin2->getPluginInfo() == dependency )
                {
                    bMet = true;
                    break;
                }
            }

            if ( !bMet )
            {
                bAllMet = false;
                break;
            }
        }

        if ( !bAllMet )
        {
            QMessageBox::critical( this, tr( "Error" ), tr( "Plugin " ) + pPlugin1->getPluginInfo().getName() +
                                   tr( "requires " ) + pPlugin1->getDependencies().toString() + "." );
            return false;
        }
    }

    return true;
}

void pgPlugins::cleanupPage( void )
{
    QStandardItemModel *model = new QStandardItemModel( 0, 0, this );
    pTreeViewPlugins->setModel( model );
    pLineEditFolder->setText( tr( "" ) );
}

void pgPlugins::browse( void )
{
    QString sFolder =  QFileDialog::getExistingDirectory( this, tr( "Select the plugin folder." ), QString::null, QFileDialog::ShowDirsOnly );

    if ( !sFolder.isEmpty() )
    {
        QStandardItemModel *model = new QStandardItemModel( 0, 3, this );
        PluginManager *pPM = getPluginManager();

        model->setHeaderData( 0, Qt::Horizontal, tr( "Name" ) );
        model->setHeaderData( 1, Qt::Horizontal, tr( "Version" ) );
        model->setHeaderData( 2, Qt::Horizontal, tr( "Dependencies" ) );

        qDebug( qPrintable( tr( "Setup: Plugin folder: %s" ) ), qPrintable( sFolder ) );

        if ( !pPM->setFolder( sFolder ) )
        {
            QMessageBox::critical( this, tr( "Error" ), tr( "Could not open plugin folder." ) );
            return;
        }

        pLineEditFolder->setText( sFolder );

        if ( !pPM->load() )
        {
            QMessageBox::critical( this, tr( "Error" ), tr( "Could not load plugins." ) );
            return;
        }

        foreach( DatabasePlugin *pPlugin, pPM->lDatabasePlugins )
            addPlugin( model, pPlugin->getPluginInfo().getName(), pPlugin->getPluginInfo().getVersion(), pPlugin->getDependencies().toString() );

        foreach( MDIWindowPlugin *pPlugin, pPM->lMDIWindowPlugins )
            addPlugin( model, pPlugin->getPluginInfo().getName(), pPlugin->getPluginInfo().getVersion(), pPlugin->getDependencies().toString() );

        pTreeViewPlugins->setModel( model );

        //pTreeViewPlugins->header()->resizeSection( 0, 30 );
        pTreeViewPlugins->header()->resizeSection( 0, 200 );
        pTreeViewPlugins->header()->resizeSection( 1, 60 );
        pTreeViewPlugins->header()->resizeSection( 2, 200 );
    }
}

/*!
  \param pParent Pointer to the parent widget.
*/
wndSetup::wndSetup( QWidget *pParent ) :
        QWizard( pParent )
{
    QIcon icon;

    icon.addFile( QString::fromUtf8( ":/icons/Icon.png" ), QSize(), QIcon::Normal, QIcon::Off );

    setWindowTitle( tr( "Fire Department Management System" ) );
    setWindowIcon( icon );
    setWizardStyle( QWizard::ClassicStyle );
    setMinimumSize( 650, 400 );
    setMaximumSize( 650, 400 );

    setPage( Intro, new pgIntro );
    setPage( NewDatabase, new pgNewDatabase );
    setPage( ExistingDatabase, new pgExistingDatabase );
    setPage( Plugins, new pgPlugins );

    clearAndHideProgressBars();
}

wndSetup::~wndSetup( void )
{
}

//! Hides and resets the progress bars and status labels.
/*!
  Called when setup fails for any reason.
*/
void wndSetup::clearAndHideProgressBars( void )
{
   /*_pUI->progExInstStatus->setValue( 0 );
    _pUI->progExInstStatus->hide();
    _pUI->lblExInstStatus->setText( QString::null );
    _pUI->lblExInstStatus->hide();

    _pUI->progNewInstStatus->setValue( 0 );
    _pUI->progNewInstStatus->hide();
    _pUI->lblNewInstStatus->setText( QString::null );
    _pUI->lblNewInstStatus->hide();*/
}

//! User clicked "Continue" on the main setup tab
void wndSetup::on_btnSetupContinue_clicked( void )
{
    /*if ( _pUI->radioExInst->isChecked() || _pUI->radioNewInst->isChecked() )
    {
        _pUI->tabWidget->setCurrentIndex( 1 );
    }
    else
    {
        QMessageBox::warning( this, "Error", "Please select an installation option.", QMessageBox::Ok );
    }*/
}

//! User clicked browse button to select plugin folder
void wndSetup::on_btnPluginSettingsFolder_clicked( void )
{
    /*QString sPluginFolder =  QFileDialog::getExistingDirectory( this, "", QString::null, QFileDialog::ShowDirsOnly );

    if ( !sPluginFolder.isEmpty() )
    {
        qDebug( "Setup: Plugin path: %s", qPrintable( sPluginFolder ) );
        _pUI->lePluginSettingsFolder->setText( sPluginFolder );

        QStringList plugins = PluginManager::findPlugins( sPluginFolder );

                // Hide the primary key column
                //_pUI->tblResults->hideColumn( 0 );

        QStringList a;
        a << "aaaaa" << "BBBB" << "CCCCC" << "DDDD";
        QStandardItemModel model(4, 4);
        model.setHorizontalHeaderLabels(a);
        for (int row = 0; row < 4; ++row) {
            for (int column = 0; column < 4; ++column) {
                QStandardItem *item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
                model.setItem(row, column, item);
            }
        }

        //model.setHeaderData(0, Qt::Horizontal, "AAAAAAA");
        _pUI->tblPluginSettingsPlugins->setModel(&model);
    }*/
}

//! User clicked "Continue" on the plugin settings tab
void wndSetup::on_btnPluginSettings_clicked( void )
{
    /*if ( _pUI->leExInstDBLocation->text().isEmpty() )
    {
        QMessageBox::warning( this, "Error", "Please select a plugin folder.", QMessageBox::Ok );
    }
    else
    {
         _pUI->tabWidget->setCurrentIndex( 2 );
    }*/
}

/*****************************************************************************************************************/
/* EXISTING INSTANCE                                                                                             */
/*****************************************************************************************************************/

//! User chose to connect to an existing instance
void wndSetup::on_radioExInst_clicked( void )
{
    /*// Clicking the radio button even if checked calls this function so see if we need to do anything
    if ( _iInstallType != EXISTING_INST )
    {
        qDebug( "Setup: User wants to install an existing instance." );

        // got to hide the tabs for existing installation
        if ( _iInstallType == NEW_INST )
        {
            _pUI->tabWidget->removeTab( 4 ); // tabNewInstFinish
            _pUI->tabWidget->removeTab( 3 ); // tabNewInstDBSettings
            _pUI->tabWidget->removeTab( 2 ); // tabNewInstFDSettings
            _pUI->tabWidget->removeTab( 1 ); // tabPluginSettings
        }

        // add back the tabs for the new installation
        _pUI->tabWidget->addTab( _pUI->tabPluginSettings, "Step 1: Plugin Settings" );
        _pUI->tabWidget->addTab( _pUI->tabExInstDBSettings, "Step 2: Database Settings" );

        _iInstallType = EXISTING_INST;
    }*/
}

//! User clicked browse button to select DB file
void wndSetup::on_btnExInstDBFile_clicked( void )
{
    /*QString sDBFile = QFileDialog::getOpenFileName( this, "Select the database file.", QString::null, "*.db" );

    if ( !sDBFile.isEmpty() )
    {
        qDebug( "Setup: Database file: %s", qPrintable( sDBFile ) );
        _pUI->leExInstDBLocation->setText( sDBFile );
    }*/
}

//! User clicked "Continue" on DB Settings tab
void wndSetup::on_btnExInstDBSettings_clicked( void )
{
    /*if ( _pUI->leExInstDBLocation->text().isEmpty() )
    {
        QMessageBox::warning( this, "Error", "Please select a database file.", QMessageBox::Ok );
    }
    else
    {
        _pUI->tabWidget->addTab( _pUI->tabExInstFinish, "Finish" );
        _pUI->tabWidget->setCurrentIndex( 3 ); // tabExInstFinish
    }*/
}

//! User clicked "Finish"
/*!
  Checks user input, opens and validates the DB, saves the settings, and
  launches the main menu.
*/
void wndSetup::on_btnExInstFinish_clicked( void )
{
    /*SettingManager *pSM = getSettingManager();
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
        _pUI->tabWidget->setCurrentIndex( 2 ); // tabExInstDBSettings
        QMessageBox::warning( this, "Error", "Please select a database file.", QMessageBox::Ok );
        clearAndHideProgressBars();
        return;
    }

    _pUI->progExInstStatus->setValue( 15 );

    if ( !QFile::exists( sDBFile ) )
    {
        _pUI->tabWidget->setCurrentIndex( 2 ); // tabExInstDBSettings
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

    hide();*/
}

/*****************************************************************************************************************/
/* NEW INSTANCE                                                                                                  */
/*****************************************************************************************************************/

//! User chose to setup a new FDMS instance
void wndSetup::on_radioNewInst_clicked( void )
{
    /*// Clicking the radio button even if checked calls this function so see if we need to do anything
    if ( _iInstallType != NEW_INST )
    {
        qDebug( "Setup: User wants to install a new instance." );

        // got to hide the tabs for existing installation
        if ( _iInstallType == EXISTING_INST )
        {
            _pUI->tabWidget->removeTab( 3 ); // tabExInstFinish
            _pUI->tabWidget->removeTab( 2 ); // tabExInstDBSettings
            _pUI->tabWidget->removeTab( 1 ); // tabPluginSettings
        }

        // add back the tabs for the new installation
        _pUI->tabWidget->addTab( _pUI->tabPluginSettings, "Step 1: Plugin Settings" );
        _pUI->tabWidget->addTab( _pUI->tabNewInstFDSettings, "Step 2: Fire Department Information" );
        _pUI->tabWidget->addTab( _pUI->tabNewInstDBSettings, "Step 3: Database Settings" );

        _iInstallType = NEW_INST;
    }*/
}

//! User clicked "Continue" on FD Settings tab
void wndSetup::on_btnNewInstFDSettings_clicked( void )
{
     //_pUI->tabWidget->setCurrentIndex( 3 ); // tabNewInstDBSettings
}

//! User clicked browse button to select DB location
void wndSetup::on_btnNewInstDBLocation_clicked( void )
{
    /*QString sDBLocation =  QFileDialog::getExistingDirectory( this, "", QString::null, QFileDialog::ShowDirsOnly );

    if ( !sDBLocation.isEmpty() )
    {
        qDebug( "Setup: Database path: %s", qPrintable( sDBLocation ) );
        _pUI->leNewInstDBLocation->setText( sDBLocation );
    }*/
}

//! User clicked "Continue" on DB Settings tab
void wndSetup::on_btnNewInstDBSettings_clicked( void )
{
    /*if ( _pUI->leNewInstDBLocation->text().isEmpty() )
    {
        QMessageBox::warning( this, "Error", "Please select a location to place the database file.", QMessageBox::Ok );
    }
    else
    {
         _pUI->tabWidget->addTab( _pUI->tabNewInstFinish, "Finish" );
        _pUI->tabWidget->setCurrentIndex( 4 ); // tabNewInstFinish
    }*/
}

//! User clicked "Finish"
/*!
  Checks user input, opens, builds, and validates the DB, saves the settings, and
  launches the main menu.
*/
void wndSetup::on_btnNewInstFinish_clicked( void )
{
    /*SettingManager *pSM = getSettingManager();
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
        _pUI->tabWidget->setCurrentIndex( 3 ); // tabNewInstDBSettings
        QMessageBox::warning( this, "Error", "Please select a location to place the database file.", QMessageBox::Ok );
        clearAndHideProgressBars();
        return;
    }

    _pUI->progNewInstStatus->setValue( 15 );

    if ( !QFile::exists( sDBLocation ) )
    {
        _pUI->tabWidget->setCurrentIndex( 3 ); // tabNewInstDBSettings
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

    hide();*/
}

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

/*****************************************************************************************************************/
/* wndSetup                                                                                             wndSetup */
/*****************************************************************************************************************/

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

    setPage( INTRO, new pgIntro( this ) );
    setPage( NEW_DATABASE, new pgNewDatabase( this ) );
    setPage( EXISTING_DATABASE, new pgExistingDatabase( this ) );
    setPage( PLUGINS, new pgPlugins( this ) );
    setPage( INSTALL, new pgInstall( this ) );
    setPage( FINISH, new pgFinish( this ) );

    setOption( QWizard::NoBackButtonOnStartPage );
    setOption( QWizard::NoBackButtonOnLastPage );
}

wndSetup::~wndSetup( void )
{
}

void wndSetup::accept( void )
{
    getWNDMain()->show();
    hide();
}

/*****************************************************************************************************************/
/* pgIntro                                                                                               pgIntro */
/*****************************************************************************************************************/

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

    pRadioNewInstallation->setChecked( true );

    font.setPointSize( 10 );
    pLabelIntro->setFont( font );
    pLabelOptions->setFont( font );
    pRadioNewInstallation->setFont( font );
    pRadioExistingInstallation->setFont( font );

    pLabelIntro->setWordWrap( true );
    pLabelOptions->setWordWrap( true );

    setLayout( pBoxLayout );

    registerField( "newInstallation", pRadioNewInstallation );
    registerField( "existingInstallation", pRadioExistingInstallation );
}

int pgIntro::nextId( void ) const
{
    if ( pRadioNewInstallation->isChecked() )
        return wndSetup::NEW_DATABASE;
    else
        return wndSetup::EXISTING_DATABASE;
}

/*****************************************************************************************************************/
/* pgNewDatabase                                                                                   pgNewDatabase */
/*****************************************************************************************************************/

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

    pLineEditFolder->setReadOnly( true );

    font.setPointSize( 10 );
    pLabelFolder->setFont( font );
    pButtonFolder->setFont( font );

    setLayout( pGridLayout );

    registerField( "database.folder", pLineEditFolder );
    connect( pButtonFolder, SIGNAL( clicked() ), this, SLOT( browse() ) );
}

int pgNewDatabase::nextId( void ) const
{
    return wndSetup::PLUGINS;
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

/*****************************************************************************************************************/
/* pgExistingDatabase                                                                         pgExistingDatabase */
/*****************************************************************************************************************/

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

    pLineEditFile->setReadOnly( true );

    font.setPointSize( 10 );
    pLabelFile->setFont( font );
    pButtonFile->setFont( font );

    setLayout( pGridLayout );

    registerField( "database.file*", pLineEditFile );
    connect( pButtonFile, SIGNAL( clicked() ), this, SLOT( browse() ) );
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

int pgExistingDatabase::nextId( void ) const
{
    return wndSetup::PLUGINS;
}

void pgExistingDatabase::cleanupPage( void )
{
    pLineEditFile->setText( tr( "" ) );
}


bool pgExistingDatabase::validatePage( void )
{
    DatabaseManager *pDBM = getDatabaseManager();

    if ( QFile::exists( pLineEditFile->text() ) )
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

/*****************************************************************************************************************/
/* pgPlugins                                                                                           pgPlugins */
/*****************************************************************************************************************/

pgPlugins::pgPlugins( QWidget *pParent )
    : QWizardPage( pParent )
{
    QGridLayout *pGridLayout = new QGridLayout();
    QVBoxLayout *pBoxLayout = new QVBoxLayout();
    QStandardItemModel *pModel;
    QFont font;

    setTitle( tr( "Plugin Settings" ) );

    pLabelFolder = new QLabel( tr( "Plugin Folder" ) );
    pLineEditFolder = new QLineEdit();
    pButtonFolder = new QPushButton( tr( "Browse..." ) );
    pGroupBoxPlugins = new QGroupBox( tr( "Plugins" ) );
    pTreeViewPlugins = new QTreeView();
    pModel = new QStandardItemModel( 0, 0, pTreeViewPlugins );

    pGridLayout->addWidget( pLabelFolder, 0, 0 );
    pGridLayout->addWidget( pLineEditFolder, 0, 1 );
    pGridLayout->addWidget( pButtonFolder, 0, 3 );
    pGridLayout->setRowMinimumHeight( 1, 15 );
    pGridLayout->addWidget( pGroupBoxPlugins, 2, 0, 3, 0 );
    pBoxLayout->addWidget( pTreeViewPlugins );

    pTreeViewPlugins->setSelectionMode( QTreeView::MultiSelection );
    pTreeViewPlugins->setSelectionBehavior( QAbstractItemView::SelectRows );
    pTreeViewPlugins->setEditTriggers( QAbstractItemView::NoEditTriggers );
    pTreeViewPlugins->setRootIsDecorated( false );
    pTreeViewPlugins->setSortingEnabled( true );

    pLineEditFolder->setReadOnly( true );

    font.setPointSize( 10 );
    pLabelFolder->setFont( font );
    pButtonFolder->setFont( font );

    pTreeViewPlugins->setModel( pModel );

    pGroupBoxPlugins->setLayout( pBoxLayout );
    setLayout( pGridLayout );

    registerField( "plugins.folder", pLineEditFolder );
    connect( pButtonFolder, SIGNAL( clicked() ), this, SLOT( browse() ) );
}

void pgPlugins::addPlugin( QAbstractItemModel *pModel, const QString &sName, const QString &sVersion, const QString &sDependencies )
{
    pModel->insertRow( 0 );
    //pModel->setData( pModel->index( 0, 0 ), Qt::Unchecked, Qt::CheckStateRole );
    pModel->setData( pModel->index( 0, 0 ), sName );
    pModel->setData( pModel->index( 0, 1 ), sVersion );
    pModel->setData( pModel->index( 0, 2 ), sDependencies );
}

void pgPlugins::browse( void )
{
    QString sFolder = QFileDialog::getExistingDirectory( this, tr( "Select the plugin folder." ), QString::null, QFileDialog::ShowDirsOnly );

    if ( !sFolder.isEmpty() )
    {
        QStandardItemModel *pModel = new QStandardItemModel( 0, 0, pTreeViewPlugins );

        pModel->setHeaderData( 0, Qt::Horizontal, tr( "Name" ) );
        pModel->setHeaderData( 1, Qt::Horizontal, tr( "Version" ) );
        pModel->setHeaderData( 2, Qt::Horizontal, tr( "Dependencies" ) );

        pLineEditFolder->setText( sFolder );
        qDebug( qPrintable( tr( "Setup: Plugin folder: %s" ) ), qPrintable( sFolder ) );

        /*if ( !pPM->setFolder( sFolder ) )
        {
            QMessageBox::critical( this, tr( "Error" ), tr( "Could not open plugin folder." ) );
            return;
        }

        if ( !pPM->load() )
        {
            QMessageBox::critical( this, tr( "Error" ), tr( "Could not load plugins." ) );
            return;
        }*/

        foreach ( BasePlugin *pPlugin, PluginManager::findAll( sFolder ) )
            addPlugin( pModel, pPlugin->getPluginInfo().getName(), pPlugin->getPluginInfo().getVersion(), pPlugin->getDependencies().toString() );

        //pTreeViewPlugins->header()->resizeSection( 0, 30 );
        pTreeViewPlugins->header()->resizeSection( 0, 200 );
        pTreeViewPlugins->header()->resizeSection( 1, 60 );
        pTreeViewPlugins->header()->resizeSection( 2, 200 );

        pTreeViewPlugins->setModel( pModel );
    }
}

void pgPlugins::cleanupPage( void )
{
    QStandardItemModel *pModel = new QStandardItemModel( 0, 0, pTreeViewPlugins );
    pTreeViewPlugins->setModel( pModel );
    pLineEditFolder->setText( tr( "" ) );
}

bool pgPlugins::validatePage( void )
{
    QList<BasePlugin*> lPlugins = PluginManager::findAll( pLineEditFolder->text() );
    QList<BasePlugin*> lPluginsSelected;

    // loop over the selected rows
    foreach ( QModelIndex index, pTreeViewPlugins->selectionModel()->selectedRows() )
    {
        QString sPluginName = pTreeViewPlugins->model()->data( index ).toString();
        QString sVersion = pTreeViewPlugins->model()->data( index.sibling( index.row(), index.column() + 1 ) ).toString();

        // find this plugin
        foreach ( BasePlugin *pPlugin, lPlugins )
        {
            if ( pPlugin->getPluginInfo().getName().compare( sPluginName ) == 0 &&
                 pPlugin->getPluginInfo().getVersion().compare( sVersion ) == 0 )
            {
                lPluginsSelected.push_back( pPlugin );
            }
        }
    }

    foreach ( BasePlugin *pPlugin, lPluginsSelected )
    {
        if ( !pPlugin->dependenciesMet( lPluginsSelected ) )
        {
            QMessageBox::critical( this, tr( "Error" ), tr( "Plugin " ) + pPlugin->getPluginInfo().getName() +
                                               tr( " requires " ) + pPlugin->getDependencies().toString() + "." );
            return false;
        }
        break;
    }

    return true;
}

/*****************************************************************************************************************/
/* pgInstall                                                                                           pgInstall */
/*****************************************************************************************************************/

pgInstall::pgInstall( QWidget *pParent )
    : QWizardPage( pParent )
{
    QVBoxLayout *pBoxLayout = new QVBoxLayout;
    QFont font;

    bInstalled = false;

    setTitle( tr( "Install" ) );

    pLabelInfo = new QLabel( tr( "Click install to start the installation process." ) );

    pBoxLayout->addWidget( pLabelInfo );

    font.setPointSize( 10 );
    pLabelInfo->setFont( font );

    pLabelInfo->setWordWrap( true );

    setLayout( pBoxLayout );

    setButtonText( QWizard::NextButton, tr( "Install" ) );
}

bool pgInstall::validatePage( void )
{
    if ( !bInstalled )
    {
        bInstalled = true;
        wizard()->button( QWizard::BackButton )->setDisabled( true );
        wizard()->button( QWizard::CancelButton )->setDisabled( true );
        pLabelInfo->setText( tr( "Installation complete." ) );
        setButtonText( QWizard::NextButton, tr( "Next" ) );
        return false;
    }

    return true;
}

/*****************************************************************************************************************/
/* pgFinish                                                                                             pgFinish */
/*****************************************************************************************************************/

pgFinish::pgFinish( QWidget *pParent )
    : QWizardPage( pParent )
{
    QVBoxLayout *pBoxLayout = new QVBoxLayout;
    QFont font;

    setTitle( tr( "Setup Complete" ) );

    pLabelOutro = new QLabel( tr( "Thank you for choosing the Fire Department Management System!" ) );

    pBoxLayout->addWidget( pLabelOutro );

    font.setPointSize( 10 );
    pLabelOutro->setFont( font );

    pLabelOutro->setWordWrap( true );

    setLayout( pBoxLayout );
}

void pgFinish::initializePage( void )
{
    wizard()->setOption( QWizard::NoCancelButton );
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

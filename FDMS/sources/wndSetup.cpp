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
    getWNDMain()->registerPlugins();
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

    registerField( "database.folder*", pLineEditFolder );
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
    QString sDatabaseFile = pLineEditFile->text();

    if ( !pDBM->setFile( sDatabaseFile ) )
    {
        QMessageBox::critical( this, tr( "Error" ), tr( "Could not set database file." ) );
        return false;
    }

    if ( !pDBM->exists() )
    {
        QMessageBox::critical( this, tr( "Error" ), tr( "Database file does not exist." ) );
        return false;
    }

    if ( !pDBM->initialize() )
    {
        QMessageBox::critical( this, tr( "Error" ), tr( "Could not initialize the database manager." ) );
        return false;
    }

    if ( !pDBM->open() )
    {
        QMessageBox::critical( this, tr( "Error" ), tr( "Could not open database file." ) );
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

    qRegisterMetaType<QList<PluginInfo> >( "QList<PluginInfo>" );
    registerField( "plugins.folder*", pLineEditFolder );
    registerField( "plugins.selected", this, "getPluginInfo" );
    connect( pButtonFolder, SIGNAL( clicked() ), this, SLOT( browse() ) );
}

QList<PluginInfo> pgPlugins::getPluginInfo( void )
{
    return lPluginInfo;
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
        QStandardItemModel *pModel = new QStandardItemModel( 0, 3, pTreeViewPlugins );

        pModel->setHeaderData( 0, Qt::Horizontal, tr( "Name" ) );
        pModel->setHeaderData( 1, Qt::Horizontal, tr( "Version" ) );
        pModel->setHeaderData( 2, Qt::Horizontal, tr( "Dependencies" ) );

        pLineEditFolder->setText( sFolder );
        qDebug( qPrintable( tr( "Setup: Plugin folder: %s" ) ), qPrintable( sFolder ) );

        if ( field( "newInstallation" ).toBool() )
        {
            foreach ( BasePlugin *pPlugin, PluginManager::findAll( sFolder ) )
                addPlugin( pModel, pPlugin->getInfo().getName(), pPlugin->getInfo().getVersion(), pPlugin->getDependencies().toString() );

            pTreeViewPlugins->setModel( pModel );
        }
        else if ( field( "existingInstallation" ).toBool() )
        {
            PluginManager *pPM = getPluginManager();

            if ( !pPM->setFolder( sFolder ) )
            {
                QMessageBox::critical( this, tr( "Error" ), tr( "Could not set plugin folder." ) );
                this->wizard()->button( QWizard::NextButton )->setEnabled( false );
                return;
            }

            if ( !pPM->exists( ) )
            {
                QMessageBox::critical( this, tr( "Error" ), tr( "Plugin folder does not exist." ) );
                this->wizard()->button( QWizard::NextButton )->setEnabled( false );
                return;
            }

            if ( !pPM->initialize() )
            {
                QMessageBox::critical( this, tr( "Error" ), tr( "Could not initialize the plugin manager." ) );
                this->wizard()->button( QWizard::NextButton )->setEnabled( false );
                return;
            }

            if ( !pPM->load( ) )
            {
                QMessageBox::critical( this, tr( "Error" ), tr( "Could not load required plugins." ) );
                this->wizard()->button( QWizard::NextButton )->setEnabled( false );
                return;
            }

            foreach ( BasePlugin *pPlugin, pPM->lPlugins )
                addPlugin( pModel, pPlugin->getInfo().getName(), pPlugin->getInfo().getVersion(), pPlugin->getDependencies().toString() );

            pTreeViewPlugins->setSelectionMode( QTreeView::NoSelection );
            pTreeViewPlugins->setModel( pModel );
            pTreeViewPlugins->selectionModel()->select( pTreeViewPlugins->model()->index(0,0), QItemSelectionModel::Select | QItemSelectionModel::Columns );
            pTreeViewPlugins->selectionModel()->select( pTreeViewPlugins->model()->index(0,1), QItemSelectionModel::Select | QItemSelectionModel::Columns );
            pTreeViewPlugins->selectionModel()->select( pTreeViewPlugins->model()->index(0,2), QItemSelectionModel::Select | QItemSelectionModel::Columns );

            wizard()->button( QWizard::NextButton )->setEnabled( true );
        }
        else
        {
            QMessageBox::critical( this, tr( "Error" ), tr( "Unknown installation type." ) );
            this->wizard()->button( QWizard::NextButton )->setEnabled( false );
            return;
        }

        //pTreeViewPlugins->header()->resizeSection( 0, 30 );
        pTreeViewPlugins->header()->resizeSection( 0, 200 );
        pTreeViewPlugins->header()->resizeSection( 1, 60 );
        pTreeViewPlugins->header()->resizeSection( 2, 200 );
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
     QList<BasePlugin*> lPlugins;
     QList<BasePlugin*> lPluginsSelected;
     lPluginInfo.clear();

    if ( field( "newInstallation" ).toBool() )
    {
        // get all of the plugins in the folder
        lPlugins = PluginManager::findAll( pLineEditFolder->text() );

        // loop over the selected rows and match the plugin info up
        foreach ( QModelIndex index, pTreeViewPlugins->selectionModel()->selectedRows() )
        {
            QString sPluginName = pTreeViewPlugins->model()->data( index ).toString();
            QString sVersion = pTreeViewPlugins->model()->data( index.sibling( index.row(), index.column() + 1 ) ).toString();
            bool bFound = false;

            // find this plugin
            foreach ( BasePlugin *pPlugin, lPlugins )
            {
                if ( pPlugin->getInfo().getName().compare( sPluginName ) == 0 &&
                     pPlugin->getInfo().getVersion().compare( sVersion ) == 0 )
                {
                    lPluginsSelected.push_back( pPlugin );
                    lPluginInfo.push_back( pPlugin->getInfo() );
                    bFound = true;
                }
            }

            if ( !bFound )
            {
                QMessageBox::critical( this, tr( "Error" ), tr( "The selected plugin could not be found in the folder." ) );
                return false;
            }
        }

        // check dependencies
        foreach ( BasePlugin *pPlugin1, lPluginsSelected )
        {
            foreach ( PluginInfo requiredPlugin, pPlugin1->getDependencies() )
            {
                bool bMet = false;
                foreach ( BasePlugin *pPlugin2, lPluginsSelected )
                {
                    if ( requiredPlugin == pPlugin2->getInfo() )
                    {
                        bMet = true;
                        break;
                    }
                }
                if ( !bMet )
                {
                    QMessageBox::critical( this, tr( "Error" ), tr( "Plugin " ) + pPlugin1->getInfo().getName() +
                        tr( " requires " ) + requiredPlugin.toString() + "." );
                    return false;
                }
            }
        }
    }
    else if ( field( "existingInstallation" ).toBool() )
    {
        // browse() already loaded the plugins into the plugin manager
        lPluginsSelected = getPluginManager()->lPlugins;
    }
    else
    {
        QMessageBox::critical( this, tr( "Error" ), tr( "Unknown installation type." ) );
        return false;
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
        DatabaseManager *pDBM = getDatabaseManager();
        PluginManager *pPM = getPluginManager();
        QString sDatabaseFolder = field( "database.folder" ).toString();
        QString sPluginFolder = field( "plugins.folder" ).toString();
        QList<PluginInfo> lPluginInfo = field( "plugins.selected" ).value<QList<PluginInfo> >();

        if ( !pDBM->setFile( sDatabaseFolder + QDir::separator() + "fdms.db" ) )
        {
            QMessageBox::critical( this, tr( "Error" ), tr( "Could not set database file." ) );
            return false;
        }

        if ( !pDBM->initialize() )
        {
            QMessageBox::critical( this, tr( "Error" ), tr( "Could not initialize the database manager." ) );
            return false;
        }

        if ( field( "newInstallation" ).toBool() && pDBM->exists() )
        {
            int iResult = QMessageBox::question( this, QObject::tr( "Existing database detected." ), QObject::tr( "An existing database "
                "was detected.\n\nWould you like to remove it so that installation can continue?" ), QMessageBox::Yes | QMessageBox::No );

            switch ( iResult )
            {
                case QMessageBox::Yes:
                {
                    if ( !pDBM->removeFile() )
                    {
                        QMessageBox::critical( this, QObject::tr( "Error" ), QObject::tr( "Failed to remove the file. Installation "
                            "cannot continue." ), QMessageBox::Ok );
                        qDebug( "%s", qPrintable( QObject::tr( "Failed to remove the file. Installation cannot continue." ) ) );
                        return false;
                    }
                    break;
                }
                case QMessageBox::No:
                {
                    QMessageBox::critical( this, QObject::tr( "Error" ), QObject::tr( "Installation cannot continue without first "
                        "removing the database file." ), QMessageBox::Ok );
                    qDebug( "%s", qPrintable( QObject::tr( "Installation cannot continue without first removing the database file." ) ) );
                    return false;
                }
            }
        }

        if ( !pDBM->open() )
        {
            QMessageBox::critical( this, tr( "Error" ), tr( "Could not open database file." ) );
            return false;
        }

        if ( !pPM->setFolder( sPluginFolder ) )
        {
            QMessageBox::critical( this, tr( "Error" ), tr( "Could not set plugin folder." ) );
            return false;
        }

        if ( !pPM->exists() )
        {
            QMessageBox::critical( this, tr( "Error" ), tr( "Plugin folder does not exist." ) );
            return false;
        }

        if ( !pPM->initialize() )
        {
            QMessageBox::critical( this, tr( "Error" ), tr( "Could not initialize the plugin manager." ) );
            return false;
        }

        if ( field( "newInstallation" ).toBool() && !pPM->install( lPluginInfo ) )
        {
            QMessageBox::critical( this, tr( "Error" ), tr( "Could not install plugins." ) );
            return false;
        }

        if ( !pPM->load() )
        {
            QMessageBox::critical( this, tr( "Error" ), tr( "Could not load plugins." ) );
            return false;
        }

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

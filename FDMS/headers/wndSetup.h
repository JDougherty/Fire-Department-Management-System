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

#ifndef WNDSETUP_H
#define WNDSETUP_H

#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QRadioButton>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <QWizard>

#include "managers/DatabaseManager.h"
#include "managers/PluginManager.h"
#include "managers/SettingManager.h"
#include "plugins/BasePlugin.h"
#include "plugins/DependencyList.h"

//! The interface and logic for setting up the FDMS.
/*!
  Users can either connect to an existing FDMS database or create
  an enitrely new installation.
*/
class wndSetup : public QWizard
{
    Q_OBJECT

    private:
        //! Installation methods
        enum {
            NOT_DEFINED,    /*!< Method not selected. */
            NEW_INST,       /*!< Configure a new DB. */
            EXISTING_INST   /*!< Connect to an existing DB. */
        };

        int                         _iInstallType;

        void                        clearAndHideProgressBars( void );

    private slots:
        void                        on_btnSetupContinue_clicked( void );
        void                        on_btnPluginSettingsFolder_clicked( void );
        void                        on_btnPluginSettings_clicked( void );

        void                        on_radioExInst_clicked( void );
        void                        on_btnExInstDBFile_clicked( void );
        void                        on_btnExInstDBSettings_clicked( void );
        void                        on_btnExInstFinish_clicked( void );

        void                        on_radioNewInst_clicked( void );
        void                        on_btnNewInstFDSettings_clicked( void );
        void                        on_btnNewInstDBLocation_clicked( void );
        void                        on_btnNewInstDBSettings_clicked( void );
        void                        on_btnNewInstFinish_clicked( void );

    public:
                                    wndSetup( QWidget *pParent = 0 );
                                    ~wndSetup( void );

        enum { Intro, NewDatabase, ExistingDatabase, Plugins, Finish };
};

class pgIntro : public QWizardPage
{
    Q_OBJECT

    private:
        int                         nextId( void ) const;

        QLabel                      *pLabelIntro, *pLabelOptions;
        QRadioButton                *pRadioNewInstallation, *pRadioExistingInstallation;

    public:
                                    pgIntro( QWidget *pParent = 0 );
};

class pgNewDatabase : public QWizardPage
{
    Q_OBJECT

    private:
        QLabel                      *pLabelFolder;
        QLineEdit                   *pLineEditFolder;
        QPushButton                 *pButtonFolder;

    protected slots:
        void                        browse( void );

    public:
                                    pgNewDatabase( QWidget *pParent = 0 );

        int                         nextId( void ) const;
        void                        cleanupPage( void );
};

class pgExistingDatabase : public QWizardPage
{
    Q_OBJECT

    private:
        QLabel                      *pLabelFile;
        QLineEdit                   *pLineEditFile;
        QPushButton                 *pButtonFile;

    protected slots:
        void                        browse( void );

    public:
                                    pgExistingDatabase( QWidget *pParent = 0 );

        int                         nextId( void ) const;
        bool                        isComplete( void ) ;
        void                        cleanupPage( void );
};

class pgPlugins : public QWizardPage
{
    Q_OBJECT

    private:
        QLabel                      *pLabelFolder;
        QLineEdit                   *pLineEditFolder;
        QPushButton                 *pButtonFolder;

        QGroupBox                   *pGroupBoxPlugins;
        QTreeView                   *pTreeViewPlugins;

        void                        addPlugin( QAbstractItemModel *model, const QString &name,
                                               const QString &version, const QString &filename );

    protected slots:
        void                        browse( void );

    public:
                                    pgPlugins( QWidget *pParent = 0 );

        bool                        isComplete( void ) ;
        void                        cleanupPage( void );
};

#endif // WNDSETUP_H


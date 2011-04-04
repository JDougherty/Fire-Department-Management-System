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
#include "wndMain.h"

//! The interface and logic for setting up the FDMS.
/*!
  Users can either connect to an existing FDMS database or create
  an enitrely new installation.
*/
class wndSetup : public QWizard
{
    Q_OBJECT

    public:
                                    wndSetup( QWidget *pParent = 0 );
                                    ~wndSetup( void );

        void                        accept( void );

        enum { INTRO, NEW_DATABASE, EXISTING_DATABASE, PLUGINS, INSTALL, FINISH };
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
        void                        cleanupPage( void );
        bool                        validatePage( void );
};

class pgPlugins : public QWizardPage
{
    Q_OBJECT
    Q_PROPERTY( QList<PluginInfo> getPluginInfo READ getPluginInfo )

    private:
        QList<PluginInfo>           lPluginInfo;
        QLabel                      *pLabelFolder;
        QLineEdit                   *pLineEditFolder;
        QPushButton                 *pButtonFolder;
        QGroupBox                   *pGroupBoxPlugins;
        QTreeView                   *pTreeViewPlugins;

        void                        addPlugin( QAbstractItemModel *pModel, const QString &sName,
                                               const QString &sVersion, const QString &sDependencies );

    protected slots:
        void                        browse( void );

    public:
                                    pgPlugins( QWidget *pParent = 0 );

        QList<PluginInfo>           getPluginInfo( void );

        void                        cleanupPage( void );
        bool                        validatePage( void );
};
Q_DECLARE_METATYPE( QList<PluginInfo> );

class pgInstall : public QWizardPage
{
    Q_OBJECT

    private:
        QLabel                      *pLabelInfo;
        bool                        bInstalled;

    public:
                                    pgInstall( QWidget *pParent = 0 );

        bool                        validatePage( void );
};

class pgFinish : public QWizardPage
{
    Q_OBJECT

    private:
        QLabel                      *pLabelOutro;

    public:
                                    pgFinish( QWidget *pParent = 0 );

        void                        initializePage( void );
};

#endif // WNDSETUP_H

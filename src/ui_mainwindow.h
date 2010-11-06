/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Nov 6 14:40:46 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actQuit;
    QAction *actSearch;
    QAction *actFirefighterAdd;
    QAction *actAbout;
    QAction *actNew_Drill;
    QAction *actionNew_Call;
    QWidget *centralWidget;
    QComboBox *cmbSearch;
    QLineEdit *txtSearch;
    QLabel *lblSearch;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuHelp;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(611, 415);
        QIcon icon;
        icon.addFile(QString::fromUtf8("Logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actQuit = new QAction(MainWindow);
        actQuit->setObjectName(QString::fromUtf8("actQuit"));
        actSearch = new QAction(MainWindow);
        actSearch->setObjectName(QString::fromUtf8("actSearch"));
        actFirefighterAdd = new QAction(MainWindow);
        actFirefighterAdd->setObjectName(QString::fromUtf8("actFirefighterAdd"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/Firefighter_Base.png"), QSize(), QIcon::Normal, QIcon::Off);
        actFirefighterAdd->setIcon(icon1);
        actAbout = new QAction(MainWindow);
        actAbout->setObjectName(QString::fromUtf8("actAbout"));
        actNew_Drill = new QAction(MainWindow);
        actNew_Drill->setObjectName(QString::fromUtf8("actNew_Drill"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/Drill_Base.png"), QSize(), QIcon::Normal, QIcon::Off);
        actNew_Drill->setIcon(icon2);
        actionNew_Call = new QAction(MainWindow);
        actionNew_Call->setObjectName(QString::fromUtf8("actionNew_Call"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/Call_Base.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_Call->setIcon(icon3);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        cmbSearch = new QComboBox(centralWidget);
        cmbSearch->setObjectName(QString::fromUtf8("cmbSearch"));
        cmbSearch->setGeometry(QRect(500, 0, 111, 20));
        txtSearch = new QLineEdit(centralWidget);
        txtSearch->setObjectName(QString::fromUtf8("txtSearch"));
        txtSearch->setGeometry(QRect(370, 0, 121, 20));
        txtSearch->setMaximumSize(QSize(121, 16777215));
        lblSearch = new QLabel(centralWidget);
        lblSearch->setObjectName(QString::fromUtf8("lblSearch"));
        lblSearch->setGeometry(QRect(320, 0, 46, 13));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 611, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setIconSize(QSize(32, 32));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        MainWindow->insertToolBarBreak(toolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actQuit);
        menuTools->addAction(actSearch);
        menuTools->addSeparator();
        menuTools->addAction(actFirefighterAdd);
        menuTools->addAction(actNew_Drill);
        menuTools->addAction(actionNew_Call);
        menuHelp->addAction(actAbout);
        toolBar->addAction(actFirefighterAdd);
        toolBar->addAction(actNew_Drill);
        toolBar->addAction(actionNew_Call);

        retranslateUi(MainWindow);
        QObject::connect(actQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Fire Department Management System", 0, QApplication::UnicodeUTF8));
        actQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actSearch->setText(QApplication::translate("MainWindow", "Search", 0, QApplication::UnicodeUTF8));
        actFirefighterAdd->setText(QApplication::translate("MainWindow", "Firefighter Add", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actFirefighterAdd->setToolTip(QApplication::translate("MainWindow", "Firefighter Add", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actNew_Drill->setText(QApplication::translate("MainWindow", "New Drill", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actNew_Drill->setToolTip(QApplication::translate("MainWindow", "New Drill", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionNew_Call->setText(QApplication::translate("MainWindow", "New Call", 0, QApplication::UnicodeUTF8));
        cmbSearch->clear();
        cmbSearch->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Firefighters", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Drills", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Calls", 0, QApplication::UnicodeUTF8)
        );
        lblSearch->setText(QApplication::translate("MainWindow", "Search:", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

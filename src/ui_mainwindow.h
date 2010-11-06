/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri Nov 5 19:49:59 2010
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
#include <QtGui/QHeaderView>
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
    QAction *actActive_Drill;
    QWidget *centralWidget;
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
        actQuit = new QAction(MainWindow);
        actQuit->setObjectName(QString::fromUtf8("actQuit"));
        actSearch = new QAction(MainWindow);
        actSearch->setObjectName(QString::fromUtf8("actSearch"));
        actFirefighterAdd = new QAction(MainWindow);
        actFirefighterAdd->setObjectName(QString::fromUtf8("actFirefighterAdd"));
        actAbout = new QAction(MainWindow);
        actAbout->setObjectName(QString::fromUtf8("actAbout"));
        actActive_Drill = new QAction(MainWindow);
        actActive_Drill->setObjectName(QString::fromUtf8("actActive_Drill"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
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
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actQuit);
        menuTools->addAction(actSearch);
        menuTools->addSeparator();
        menuTools->addAction(actFirefighterAdd);
        menuTools->addSeparator();
        menuTools->addAction(actActive_Drill);
        menuHelp->addAction(actAbout);

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
        actActive_Drill->setText(QApplication::translate("MainWindow", "Active Drill", 0, QApplication::UnicodeUTF8));
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

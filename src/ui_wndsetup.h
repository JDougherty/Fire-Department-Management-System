/********************************************************************************
** Form generated from reading UI file 'wndsetup.ui'
**
** Created: Fri Nov 5 18:24:42 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WNDSETUP_H
#define UI_WNDSETUP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCommandLinkButton>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wndSetup
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QCommandLinkButton *commandLinkButton;
    QWidget *tab_3;
    QWidget *tab_2;

    void setupUi(QMainWindow *wndSetup)
    {
        if (wndSetup->objectName().isEmpty())
            wndSetup->setObjectName(QString::fromUtf8("wndSetup"));
        wndSetup->resize(652, 412);
        centralwidget = new QWidget(wndSetup);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 631, 391));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 0, 251, 41));
        QFont font;
        font.setPointSize(18);
        label->setFont(font);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 50, 601, 71));
        QFont font1;
        font1.setPointSize(10);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_2->setWordWrap(true);
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 110, 601, 71));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_3->setWordWrap(true);
        commandLinkButton = new QCommandLinkButton(tab);
        commandLinkButton->setObjectName(QString::fromUtf8("commandLinkButton"));
        commandLinkButton->setGeometry(QRect(510, 310, 101, 41));
        commandLinkButton->setLayoutDirection(Qt::LeftToRight);
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidget->addTab(tab_3, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        wndSetup->setCentralWidget(centralwidget);

        retranslateUi(wndSetup);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(wndSetup);
    } // setupUi

    void retranslateUi(QMainWindow *wndSetup)
    {
        wndSetup->setWindowTitle(QApplication::translate("wndSetup", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("wndSetup", "Setup Information", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("wndSetup", "Welcome to the setup for the Fire Department Management System. Using the tabs at the top of this window, please complete all steps in this setup process. Refer to the documentation if you are unsure what a specific step requires. ", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("wndSetup", "If you are seeing this window, your FDMS database file was not found. If this is not your first time launching the Fire Department Management System, you may wish to close this window now and refer to the documentation to restore your FDMS database file. ", 0, QApplication::UnicodeUTF8));
        commandLinkButton->setText(QApplication::translate("wndSetup", "Continue", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("wndSetup", "Setup", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("wndSetup", "Step 1:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("wndSetup", "Step 2:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class wndSetup: public Ui_wndSetup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WNDSETUP_H

/********************************************************************************
** Form generated from reading UI file 'wndsearch.ui'
**
** Created: Fri Nov 5 20:18:18 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WNDSEARCH_H
#define UI_WNDSEARCH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wndSearch
{
public:
    QWidget *centralwidget;
    QTableWidget *tableWidget;
    QTabWidget *tabWidget;
    QWidget *tabFirefighters;
    QWidget *tabDrills;
    QWidget *tabCalls;

    void setupUi(QMainWindow *wndSearch)
    {
        if (wndSearch->objectName().isEmpty())
            wndSearch->setObjectName(QString::fromUtf8("wndSearch"));
        wndSearch->resize(331, 332);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wndSearch->sizePolicy().hasHeightForWidth());
        wndSearch->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(wndSearch);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 110, 311, 211));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 311, 91));
        tabFirefighters = new QWidget();
        tabFirefighters->setObjectName(QString::fromUtf8("tabFirefighters"));
        tabWidget->addTab(tabFirefighters, QString());
        tabDrills = new QWidget();
        tabDrills->setObjectName(QString::fromUtf8("tabDrills"));
        tabWidget->addTab(tabDrills, QString());
        tabCalls = new QWidget();
        tabCalls->setObjectName(QString::fromUtf8("tabCalls"));
        tabWidget->addTab(tabCalls, QString());
        wndSearch->setCentralWidget(centralwidget);

        retranslateUi(wndSearch);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(wndSearch);
    } // setupUi

    void retranslateUi(QMainWindow *wndSearch)
    {
        wndSearch->setWindowTitle(QApplication::translate("wndSearch", "Search", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("wndSearch", "ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("wndSearch", "Last Name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("wndSearch", "First name", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabFirefighters), QApplication::translate("wndSearch", "Firefighters", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabDrills), QApplication::translate("wndSearch", "Drills", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabCalls), QApplication::translate("wndSearch", "Calls", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class wndSearch: public Ui_wndSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WNDSEARCH_H

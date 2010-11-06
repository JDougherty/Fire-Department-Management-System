/********************************************************************************
** Form generated from reading UI file 'wndsearch.ui'
**
** Created: Sat Nov 6 17:49:35 2010
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
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wndSearch
{
public:
    QWidget *centralwidget;
    QTableWidget *tblResults;

    void setupUi(QMainWindow *wndSearch)
    {
        if (wndSearch->objectName().isEmpty())
            wndSearch->setObjectName(QString::fromUtf8("wndSearch"));
        wndSearch->resize(322, 332);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wndSearch->sizePolicy().hasHeightForWidth());
        wndSearch->setSizePolicy(sizePolicy);
        wndSearch->setMinimumSize(QSize(322, 332));
        centralwidget = new QWidget(wndSearch);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tblResults = new QTableWidget(centralwidget);
        if (tblResults->columnCount() < 3)
            tblResults->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblResults->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblResults->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblResults->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tblResults->setObjectName(QString::fromUtf8("tblResults"));
        tblResults->setGeometry(QRect(10, 10, 302, 311));
        tblResults->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tblResults->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        wndSearch->setCentralWidget(centralwidget);

        retranslateUi(wndSearch);

        QMetaObject::connectSlotsByName(wndSearch);
    } // setupUi

    void retranslateUi(QMainWindow *wndSearch)
    {
        wndSearch->setWindowTitle(QApplication::translate("wndSearch", "Search Results: ", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tblResults->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("wndSearch", "COL1", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tblResults->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("wndSearch", "COL2", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tblResults->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("wndSearch", "COL3", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class wndSearch: public Ui_wndSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WNDSEARCH_H

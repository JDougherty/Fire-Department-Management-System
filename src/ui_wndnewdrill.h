/********************************************************************************
** Form generated from reading UI file 'wndnewdrill.ui'
**
** Created: Tue Aug 31 02:20:38 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WNDNEWDRILL_H
#define UI_WNDNEWDRILL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wndActiveDrill
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QDateTimeEdit *dateDrillStart;
    QDateTimeEdit *dateDrillEnd;
    QLabel *label_3;
    QLineEdit *txtDrillNum;
    QLabel *label_4;
    QLineEdit *txtLocation;
    QGroupBox *groupBox_2;
    QLineEdit *txtIDScan;
    QPushButton *btnSignIn;
    QTableWidget *tableWidget;

    void setupUi(QMainWindow *wndActiveDrill)
    {
        if (wndActiveDrill->objectName().isEmpty())
            wndActiveDrill->setObjectName(QString::fromUtf8("wndActiveDrill"));
        wndActiveDrill->resize(661, 521);
        centralwidget = new QWidget(wndActiveDrill);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(340, 10, 311, 201));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 70, 41, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(160, 70, 41, 16));
        dateDrillStart = new QDateTimeEdit(groupBox);
        dateDrillStart->setObjectName(QString::fromUtf8("dateDrillStart"));
        dateDrillStart->setGeometry(QRect(10, 90, 141, 20));
        dateDrillStart->setCalendarPopup(true);
        dateDrillEnd = new QDateTimeEdit(groupBox);
        dateDrillEnd->setObjectName(QString::fromUtf8("dateDrillEnd"));
        dateDrillEnd->setGeometry(QRect(160, 90, 141, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 20, 61, 16));
        txtDrillNum = new QLineEdit(groupBox);
        txtDrillNum->setObjectName(QString::fromUtf8("txtDrillNum"));
        txtDrillNum->setGeometry(QRect(10, 40, 71, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(120, 20, 61, 16));
        txtLocation = new QLineEdit(groupBox);
        txtLocation->setObjectName(QString::fromUtf8("txtLocation"));
        txtLocation->setGeometry(QRect(120, 40, 171, 20));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 321, 501));
        txtIDScan = new QLineEdit(groupBox_2);
        txtIDScan->setObjectName(QString::fromUtf8("txtIDScan"));
        txtIDScan->setEnabled(false);
        txtIDScan->setGeometry(QRect(10, 20, 211, 23));
        btnSignIn = new QPushButton(groupBox_2);
        btnSignIn->setObjectName(QString::fromUtf8("btnSignIn"));
        btnSignIn->setEnabled(false);
        btnSignIn->setGeometry(QRect(230, 19, 75, 23));
        tableWidget = new QTableWidget(groupBox_2);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEnabled(false);
        tableWidget->setGeometry(QRect(10, 50, 301, 441));
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(3);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(20);
        tableWidget->verticalHeader()->setMinimumSectionSize(10);
        wndActiveDrill->setCentralWidget(centralwidget);

        retranslateUi(wndActiveDrill);

        QMetaObject::connectSlotsByName(wndActiveDrill);
    } // setupUi

    void retranslateUi(QMainWindow *wndActiveDrill)
    {
        wndActiveDrill->setWindowTitle(QApplication::translate("wndActiveDrill", "Active Drill", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("wndActiveDrill", "Drill Information", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("wndActiveDrill", "Start:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("wndActiveDrill", "End:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("wndActiveDrill", "Drill Number:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("wndActiveDrill", "Location:", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("wndActiveDrill", "Timesheet", 0, QApplication::UnicodeUTF8));
        btnSignIn->setText(QApplication::translate("wndActiveDrill", "Sign In / Out", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("wndActiveDrill", "Name", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("wndActiveDrill", "Time In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("wndActiveDrill", "Time Out", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class wndActiveDrill: public Ui_wndActiveDrill {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WNDNEWDRILL_H

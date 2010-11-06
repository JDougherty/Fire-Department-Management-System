/********************************************************************************
** Form generated from reading UI file 'wndactivedrill.ui'
**
** Created: Fri Nov 5 18:24:42 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WNDACTIVEDRILL_H
#define UI_WNDACTIVEDRILL_H

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
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wndActiveDrill
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox_2;
    QLineEdit *txtIDScan;
    QPushButton *btnSignIn;
    QTableWidget *tblTimesheet;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QDateTimeEdit *dateDrillStart;
    QDateTimeEdit *dateDrillEnd;
    QLabel *label_3;
    QLineEdit *txtDrillNum;
    QLabel *label_4;
    QTextEdit *textEdit;
    QPushButton *btnSaveDrill;

    void setupUi(QMainWindow *wndActiveDrill)
    {
        if (wndActiveDrill->objectName().isEmpty())
            wndActiveDrill->setObjectName(QString::fromUtf8("wndActiveDrill"));
        wndActiveDrill->resize(661, 451);
        centralwidget = new QWidget(wndActiveDrill);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(270, 10, 381, 431));
        txtIDScan = new QLineEdit(groupBox_2);
        txtIDScan->setObjectName(QString::fromUtf8("txtIDScan"));
        txtIDScan->setEnabled(true);
        txtIDScan->setGeometry(QRect(10, 20, 211, 23));
        btnSignIn = new QPushButton(groupBox_2);
        btnSignIn->setObjectName(QString::fromUtf8("btnSignIn"));
        btnSignIn->setEnabled(true);
        btnSignIn->setGeometry(QRect(230, 19, 75, 23));
        tblTimesheet = new QTableWidget(groupBox_2);
        if (tblTimesheet->columnCount() < 3)
            tblTimesheet->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblTimesheet->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblTimesheet->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblTimesheet->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        if (tblTimesheet->rowCount() < 5)
            tblTimesheet->setRowCount(5);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tblTimesheet->setItem(0, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tblTimesheet->setItem(0, 1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tblTimesheet->setItem(0, 2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tblTimesheet->setItem(1, 0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tblTimesheet->setItem(1, 1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tblTimesheet->setItem(1, 2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tblTimesheet->setItem(2, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tblTimesheet->setItem(2, 1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tblTimesheet->setItem(2, 2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tblTimesheet->setItem(3, 0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tblTimesheet->setItem(3, 1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tblTimesheet->setItem(3, 2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tblTimesheet->setItem(4, 0, __qtablewidgetitem15);
        tblTimesheet->setObjectName(QString::fromUtf8("tblTimesheet"));
        tblTimesheet->setEnabled(true);
        tblTimesheet->setGeometry(QRect(10, 50, 359, 371));
        tblTimesheet->setFrameShadow(QFrame::Sunken);
        tblTimesheet->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tblTimesheet->setShowGrid(true);
        tblTimesheet->setGridStyle(Qt::SolidLine);
        tblTimesheet->setCornerButtonEnabled(false);
        tblTimesheet->setRowCount(5);
        tblTimesheet->setColumnCount(3);
        tblTimesheet->horizontalHeader()->setVisible(true);
        tblTimesheet->horizontalHeader()->setCascadingSectionResizes(false);
        tblTimesheet->horizontalHeader()->setDefaultSectionSize(119);
        tblTimesheet->horizontalHeader()->setHighlightSections(true);
        tblTimesheet->horizontalHeader()->setMinimumSectionSize(80);
        tblTimesheet->verticalHeader()->setVisible(false);
        tblTimesheet->verticalHeader()->setDefaultSectionSize(20);
        tblTimesheet->verticalHeader()->setMinimumSectionSize(20);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 251, 251));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 41, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 70, 41, 16));
        dateDrillStart = new QDateTimeEdit(groupBox);
        dateDrillStart->setObjectName(QString::fromUtf8("dateDrillStart"));
        dateDrillStart->setGeometry(QRect(10, 40, 141, 20));
        dateDrillStart->setCalendarPopup(true);
        dateDrillEnd = new QDateTimeEdit(groupBox);
        dateDrillEnd->setObjectName(QString::fromUtf8("dateDrillEnd"));
        dateDrillEnd->setGeometry(QRect(10, 90, 141, 20));
        dateDrillEnd->setCalendarPopup(true);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(170, 20, 61, 16));
        txtDrillNum = new QLineEdit(groupBox);
        txtDrillNum->setObjectName(QString::fromUtf8("txtDrillNum"));
        txtDrillNum->setGeometry(QRect(170, 40, 71, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 120, 61, 16));
        textEdit = new QTextEdit(groupBox);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 140, 231, 71));
        btnSaveDrill = new QPushButton(groupBox);
        btnSaveDrill->setObjectName(QString::fromUtf8("btnSaveDrill"));
        btnSaveDrill->setGeometry(QRect(170, 220, 75, 23));
        wndActiveDrill->setCentralWidget(centralwidget);

        retranslateUi(wndActiveDrill);
        QObject::connect(txtIDScan, SIGNAL(returnPressed()), wndActiveDrill, SLOT(txtSignIn_textEdited()));

        QMetaObject::connectSlotsByName(wndActiveDrill);
    } // setupUi

    void retranslateUi(QMainWindow *wndActiveDrill)
    {
        wndActiveDrill->setWindowTitle(QApplication::translate("wndActiveDrill", "Active Drill", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("wndActiveDrill", "Timesheet", 0, QApplication::UnicodeUTF8));
        btnSignIn->setText(QApplication::translate("wndActiveDrill", "Sign In / Out", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tblTimesheet->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("wndActiveDrill", "Name (ID)", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tblTimesheet->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("wndActiveDrill", "Time In", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tblTimesheet->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("wndActiveDrill", "Time Out", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = tblTimesheet->isSortingEnabled();
        tblTimesheet->setSortingEnabled(false);
        tblTimesheet->setSortingEnabled(__sortingEnabled);

        groupBox->setTitle(QApplication::translate("wndActiveDrill", "Drill Information", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("wndActiveDrill", "Start:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("wndActiveDrill", "End:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("wndActiveDrill", "Drill Number:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("wndActiveDrill", "Location:", 0, QApplication::UnicodeUTF8));
        btnSaveDrill->setText(QApplication::translate("wndActiveDrill", "Create Drill", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class wndActiveDrill: public Ui_wndActiveDrill {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WNDACTIVEDRILL_H

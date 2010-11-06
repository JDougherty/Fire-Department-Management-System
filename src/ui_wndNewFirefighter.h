/********************************************************************************
** Form generated from reading UI file 'wndNewFirefighter.ui'
**
** Created: Sat Nov 6 14:36:04 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WNDNEWFIREFIGHTER_H
#define UI_WNDNEWFIREFIGHTER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wndNewFirefighter
{
public:
    QWidget *centralwidget;
    QGroupBox *gbxNewFirefighter;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *txtFirstName;
    QLabel *label_3;
    QLineEdit *txtMiddleName;
    QLineEdit *txtLastName;
    QLabel *label_4;
    QDateEdit *dateDob;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *txtLocalID;
    QLineEdit *txtStateID;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *txtAddress;
    QLineEdit *txtCity;
    QComboBox *txtState;
    QLineEdit *txtZipCode;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLineEdit *txtStatus;
    QLineEdit *txtHphone;
    QLineEdit *txtWphone;
    QLineEdit *txtCphone;
    QLabel *label_16;
    QLabel *label_17;
    QLineEdit *txtDrvLic;
    QLineEdit *txtCDL;
    QDateEdit *dateJoin;
    QPushButton *btnAdd;

    void setupUi(QMainWindow *wndNewFirefighter)
    {
        if (wndNewFirefighter->objectName().isEmpty())
            wndNewFirefighter->setObjectName(QString::fromUtf8("wndNewFirefighter"));
        wndNewFirefighter->resize(432, 320);
        wndNewFirefighter->setMinimumSize(QSize(432, 320));
        wndNewFirefighter->setMaximumSize(QSize(432, 320));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/Logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        wndNewFirefighter->setWindowIcon(icon);
        centralwidget = new QWidget(wndNewFirefighter);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gbxNewFirefighter = new QGroupBox(centralwidget);
        gbxNewFirefighter->setObjectName(QString::fromUtf8("gbxNewFirefighter"));
        gbxNewFirefighter->setGeometry(QRect(10, 10, 411, 301));
        label = new QLabel(gbxNewFirefighter);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 61, 16));
        label_2 = new QLabel(gbxNewFirefighter);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 20, 61, 16));
        txtFirstName = new QLineEdit(gbxNewFirefighter);
        txtFirstName->setObjectName(QString::fromUtf8("txtFirstName"));
        txtFirstName->setGeometry(QRect(20, 40, 111, 20));
        label_3 = new QLabel(gbxNewFirefighter);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(280, 20, 61, 16));
        txtMiddleName = new QLineEdit(gbxNewFirefighter);
        txtMiddleName->setObjectName(QString::fromUtf8("txtMiddleName"));
        txtMiddleName->setGeometry(QRect(150, 40, 111, 20));
        txtLastName = new QLineEdit(gbxNewFirefighter);
        txtLastName->setObjectName(QString::fromUtf8("txtLastName"));
        txtLastName->setGeometry(QRect(280, 40, 111, 20));
        label_4 = new QLabel(gbxNewFirefighter);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 70, 71, 16));
        dateDob = new QDateEdit(gbxNewFirefighter);
        dateDob->setObjectName(QString::fromUtf8("dateDob"));
        dateDob->setGeometry(QRect(20, 90, 110, 20));
        dateDob->setDateTime(QDateTime(QDate(2010, 8, 20), QTime(0, 0, 0)));
        label_5 = new QLabel(gbxNewFirefighter);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(150, 70, 61, 16));
        label_6 = new QLabel(gbxNewFirefighter);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(280, 70, 61, 16));
        txtLocalID = new QLineEdit(gbxNewFirefighter);
        txtLocalID->setObjectName(QString::fromUtf8("txtLocalID"));
        txtLocalID->setGeometry(QRect(150, 90, 111, 20));
        txtStateID = new QLineEdit(gbxNewFirefighter);
        txtStateID->setObjectName(QString::fromUtf8("txtStateID"));
        txtStateID->setGeometry(QRect(280, 90, 111, 20));
        label_7 = new QLabel(gbxNewFirefighter);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 120, 71, 16));
        label_8 = new QLabel(gbxNewFirefighter);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(160, 120, 71, 16));
        label_9 = new QLabel(gbxNewFirefighter);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(260, 120, 41, 16));
        label_10 = new QLabel(gbxNewFirefighter);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(320, 120, 51, 16));
        txtAddress = new QLineEdit(gbxNewFirefighter);
        txtAddress->setObjectName(QString::fromUtf8("txtAddress"));
        txtAddress->setGeometry(QRect(20, 140, 131, 20));
        txtCity = new QLineEdit(gbxNewFirefighter);
        txtCity->setObjectName(QString::fromUtf8("txtCity"));
        txtCity->setGeometry(QRect(160, 140, 81, 20));
        txtState = new QComboBox(gbxNewFirefighter);
        txtState->setObjectName(QString::fromUtf8("txtState"));
        txtState->setGeometry(QRect(260, 140, 41, 20));
        txtState->setEditable(false);
        txtZipCode = new QLineEdit(gbxNewFirefighter);
        txtZipCode->setObjectName(QString::fromUtf8("txtZipCode"));
        txtZipCode->setGeometry(QRect(320, 140, 71, 20));
        label_11 = new QLabel(gbxNewFirefighter);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 170, 71, 16));
        label_12 = new QLabel(gbxNewFirefighter);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(100, 170, 41, 16));
        label_13 = new QLabel(gbxNewFirefighter);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(190, 170, 71, 16));
        label_14 = new QLabel(gbxNewFirefighter);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(300, 170, 71, 16));
        label_15 = new QLabel(gbxNewFirefighter);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(20, 220, 71, 16));
        txtStatus = new QLineEdit(gbxNewFirefighter);
        txtStatus->setObjectName(QString::fromUtf8("txtStatus"));
        txtStatus->setGeometry(QRect(100, 190, 71, 20));
        txtHphone = new QLineEdit(gbxNewFirefighter);
        txtHphone->setObjectName(QString::fromUtf8("txtHphone"));
        txtHphone->setGeometry(QRect(190, 190, 91, 20));
        txtWphone = new QLineEdit(gbxNewFirefighter);
        txtWphone->setObjectName(QString::fromUtf8("txtWphone"));
        txtWphone->setGeometry(QRect(300, 190, 91, 20));
        txtCphone = new QLineEdit(gbxNewFirefighter);
        txtCphone->setObjectName(QString::fromUtf8("txtCphone"));
        txtCphone->setGeometry(QRect(20, 240, 91, 20));
        label_16 = new QLabel(gbxNewFirefighter);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(130, 220, 91, 16));
        label_17 = new QLabel(gbxNewFirefighter);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(270, 220, 91, 16));
        txtDrvLic = new QLineEdit(gbxNewFirefighter);
        txtDrvLic->setObjectName(QString::fromUtf8("txtDrvLic"));
        txtDrvLic->setGeometry(QRect(130, 240, 121, 20));
        txtCDL = new QLineEdit(gbxNewFirefighter);
        txtCDL->setObjectName(QString::fromUtf8("txtCDL"));
        txtCDL->setGeometry(QRect(270, 240, 121, 20));
        dateJoin = new QDateEdit(gbxNewFirefighter);
        dateJoin->setObjectName(QString::fromUtf8("dateJoin"));
        dateJoin->setGeometry(QRect(20, 190, 71, 20));
        dateJoin->setDateTime(QDateTime(QDate(2010, 8, 20), QTime(0, 0, 0)));
        btnAdd = new QPushButton(gbxNewFirefighter);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));
        btnAdd->setGeometry(QRect(304, 270, 91, 23));
        wndNewFirefighter->setCentralWidget(centralwidget);
        QWidget::setTabOrder(txtFirstName, txtMiddleName);
        QWidget::setTabOrder(txtMiddleName, txtLastName);
        QWidget::setTabOrder(txtLastName, dateDob);
        QWidget::setTabOrder(dateDob, txtLocalID);
        QWidget::setTabOrder(txtLocalID, txtStateID);
        QWidget::setTabOrder(txtStateID, txtAddress);
        QWidget::setTabOrder(txtAddress, txtCity);
        QWidget::setTabOrder(txtCity, txtState);
        QWidget::setTabOrder(txtState, txtZipCode);
        QWidget::setTabOrder(txtZipCode, dateJoin);
        QWidget::setTabOrder(dateJoin, txtStatus);
        QWidget::setTabOrder(txtStatus, txtHphone);
        QWidget::setTabOrder(txtHphone, txtWphone);
        QWidget::setTabOrder(txtWphone, txtCphone);
        QWidget::setTabOrder(txtCphone, txtDrvLic);
        QWidget::setTabOrder(txtDrvLic, txtCDL);
        QWidget::setTabOrder(txtCDL, btnAdd);

        retranslateUi(wndNewFirefighter);
        QObject::connect(btnAdd, SIGNAL(clicked()), wndNewFirefighter, SLOT(btnAdd_Clicked()));

        txtState->setCurrentIndex(32);


        QMetaObject::connectSlotsByName(wndNewFirefighter);
    } // setupUi

    void retranslateUi(QMainWindow *wndNewFirefighter)
    {
        wndNewFirefighter->setWindowTitle(QApplication::translate("wndNewFirefighter", "Add New Firefighter", 0, QApplication::UnicodeUTF8));
        gbxNewFirefighter->setTitle(QApplication::translate("wndNewFirefighter", "Add New Firefighter", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("wndNewFirefighter", "First Name:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("wndNewFirefighter", "Middle Name:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("wndNewFirefighter", "Last Name:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("wndNewFirefighter", "Date of Birth:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("wndNewFirefighter", "Local ID:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("wndNewFirefighter", "State ID:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("wndNewFirefighter", "Address:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("wndNewFirefighter", "City:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("wndNewFirefighter", "State:", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("wndNewFirefighter", "Zip Code:", 0, QApplication::UnicodeUTF8));
        txtAddress->setText(QString());
        txtCity->setText(QString());
        txtState->clear();
        txtState->insertItems(0, QStringList()
         << QApplication::translate("wndNewFirefighter", "AL", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "AK", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "AZ", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "AR", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "CA", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "CO", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "CT", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "DE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "DC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "FL", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "GA", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "HI", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "ID", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "IL", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "IN", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "IA", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "KS", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "KY", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "LA", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "ME", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "MD", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "MA", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "MI", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "MN", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "MS", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "MO", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "MT", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "NE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "NV", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "NH", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "NJ", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "NM", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "NY", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "NC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "ND", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "OH", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "OK", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "OR", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "PA", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "RI", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "SC", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "SD", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "TN", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "TX", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "UT", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "VT", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "VA", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "WA", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "WV", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "WI", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("wndNewFirefighter", "WY", 0, QApplication::UnicodeUTF8)
        );
        txtZipCode->setText(QString());
        label_11->setText(QApplication::translate("wndNewFirefighter", "Join Date:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("wndNewFirefighter", "Status:", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("wndNewFirefighter", "Home Phone:", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("wndNewFirefighter", "Work Phone:", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("wndNewFirefighter", "Cell Phone:", 0, QApplication::UnicodeUTF8));
        txtStatus->setText(QString());
        txtHphone->setText(QString());
        txtWphone->setText(QString());
        txtCphone->setText(QString());
        label_16->setText(QApplication::translate("wndNewFirefighter", "Driver's License:", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("wndNewFirefighter", "CDL:", 0, QApplication::UnicodeUTF8));
        btnAdd->setText(QApplication::translate("wndNewFirefighter", "Add Firefighter", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class wndNewFirefighter: public Ui_wndNewFirefighter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WNDNEWFIREFIGHTER_H

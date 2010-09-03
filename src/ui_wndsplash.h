/********************************************************************************
** Form generated from reading UI file 'wndsplash.ui'
**
** Created: Tue Aug 31 03:14:09 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WNDSPLASH_H
#define UI_WNDSPLASH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wndSplash
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *wndSplash)
    {
        if (wndSplash->objectName().isEmpty())
            wndSplash->setObjectName(QString::fromUtf8("wndSplash"));
        wndSplash->resize(537, 218);
        centralwidget = new QWidget(wndSplash);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 80, 521, 41));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        wndSplash->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(wndSplash);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        wndSplash->setStatusBar(statusbar);

        retranslateUi(wndSplash);

        QMetaObject::connectSlotsByName(wndSplash);
    } // setupUi

    void retranslateUi(QMainWindow *wndSplash)
    {
        wndSplash->setWindowTitle(QApplication::translate("wndSplash", "MainWindow", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("wndSplash", "Loading FDMS...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class wndSplash: public Ui_wndSplash {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WNDSPLASH_H

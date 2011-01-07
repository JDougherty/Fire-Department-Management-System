#include "../headers/wndactivecall.h"
#include "ui_wndactivecall.h"

wndActiveCall::wndActiveCall(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wndActiveCall)
{
    ui->setupUi(this);
}

wndActiveCall::~wndActiveCall()
{
    delete ui;
}


// Test slot for the ordering of the input fields.
// Creates a list of the desired widgets.
// Uses the tab order for widget ordering.
// Will eventually be used to build the INSERT and UPDATE
//  SQL queries.
void wndActiveCall::on_pushButton_clicked()
{
    QList<QWidget*> edits;

    QWidget *tmpw = ui->tabWidget->nextInFocusChain();
    while(tmpw!=ui->tabWidget){
        if(tmpw->objectName().startsWith("txtarray")){
            edits+=tmpw;
        }
        tmpw=tmpw->nextInFocusChain();
    }

    for (int i = 0; i < edits.size(); ++i) {
        QWidget *tmp = edits.at(i);

        QLineEdit *tmplineedit = qobject_cast<QLineEdit *>(tmp);
        QDateTimeEdit *tmpdatetime = qobject_cast<QDateTimeEdit *>(tmp);
        QComboBox *tmpcombo = qobject_cast<QComboBox *>(tmp);

        if(tmplineedit){
            qDebug("%d %s",i,qPrintable(tmplineedit->text()));
        }
        else if(tmpdatetime){
            qDebug("%d %s",i,qPrintable(tmpdatetime->dateTime().toString()));
        }
        else if(tmpcombo){
            qDebug("%d %s",i,qPrintable(tmpcombo->currentText()));
        }
    }
}

#ifndef WNDACTIVECALL_H
#define WNDACTIVECALL_H

#include <QMainWindow>
#include <QMessageBox>
#include <QList>
#include "databasemanager.h"

namespace Ui
{
    class wndActiveCall;
}

//! GUI for adding a call and editing call data.
class wndActiveCall : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::wndActiveCall       *_pUI;
        DatabaseManager         *_pDB;

        int                     _iID;

    private slots:
        void                    btnSaveCallClicked( void );

    public:
                                wndActiveCall( QWidget *pParent, DatabaseManager *pDB );
                                wndActiveCall( QWidget *pParent, DatabaseManager *pDB, int iID );
                                ~wndActiveCall( void );
};

#endif // WNDACTIVECALL_H

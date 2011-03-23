#ifndef WNDACTIVECALL_H
#define WNDACTIVECALL_H

#include <QMainWindow>
#include <QMessageBox>
#include <QList>
#include "databaseitem.h"

namespace Ui
{
    class wndActiveCall;
}

//! GUI for adding a call and editing call data.
class wndActiveCall : public QMainWindow, public DatabaseItem
{
    Q_OBJECT

    private:
        Ui::wndActiveCall       *_pUI;

    private slots:
        void                    btnSaveCallClicked( void );

    public:
                                wndActiveCall( QWidget *pParent, DatabaseManager *pDB );
                                wndActiveCall( QWidget *pParent, DatabaseManager *pDB, int iID );

                                ~wndActiveCall( void );

        bool                    Create( void );
        bool                    Insert( void );
        bool                    Update( void );
        bool                    Select( void );
        bool                    Delete( void );

        static bool             Delete( DatabaseManager *pDB, int iID );
};

#endif // WNDACTIVECALL_H

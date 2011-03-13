#include "../headers/wndactivecall.h"
#include "ui_wndactivecall.h"

//! Constructor for adding a new call.
/*!
  Hide extra tabs and change the window and button names.
  \param pDB Pointer to the database manager.
*/
wndActiveCall::wndActiveCall( QWidget *pParent, DatabaseManager *pDB ) :
    QMainWindow( pParent ), _pUI( new Ui::wndActiveCall )
{
    _pUI->setupUi( this );
    _pDB = pDB;
    _iID = -1;
    pDB->buildQueries( "Calls", _pUI->tabWidget->nextInFocusChain() );
}

//! Constructor for editing a call.
/*!
  Load the call's data.
  \param pDB Pointer to the database manager.
  \param iID Call's DB id.
*/
wndActiveCall::wndActiveCall( QWidget *pParent, DatabaseManager *pDB, int iID ) :
    QMainWindow( pParent ), _pUI( new Ui::wndActiveCall )
{
    _pUI->setupUi( this );
    _pDB = pDB;
    _iID = iID;
    pDB->buildQueries( "Calls", _pUI->tabWidget->nextInFocusChain() );
    pDB->selectUI( _iID, "Calls", _pUI->tabWidget->nextInFocusChain() );
}

wndActiveCall::~wndActiveCall( void )
{
    delete _pUI;
}

//! Updates the calls's information in the database when the Save button is clicked.
void wndActiveCall::btnSaveCallClicked( void )
{
    if ( _iID <= 0 )
    {
        _iID = _pDB->insertUI( "Calls", _pUI->tabWidget->nextInFocusChain() );
        if ( _iID > 0 )
        {
            QMessageBox::information( this, "Call Information", "Call successfully added to database!" );
        }
        else
        {
            QMessageBox::warning( this, "Call Error", "Call could not be added to database! See log file for details." );
        }
    }
    else
    {
        if ( _pDB->updateUI( _iID, "Calls", _pUI->tabWidget->nextInFocusChain() ) )
        {
            QMessageBox::information( this, "Call Information: Update", "Call was successfully updated in database!" );
        }
        else
        {
            QMessageBox::warning( this, "Call Error: Update", "Call information failed to update! See log for more information." );
        }
    }
}

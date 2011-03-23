#include "../headers/wndactivecall.h"
#include "ui_wndactivecall.h"

//! Constructor for adding a new call.
/*!
  Hide extra tabs and change the window and button names.
  \param pDB Pointer to the database manager.
*/
wndActiveCall::wndActiveCall( QWidget *pParent, DatabaseManager *pDB ) :
    QMainWindow( pParent ), DatabaseItem( pDB, -1 )
{
    _pUI = new Ui::wndActiveCall;
    _pUI->setupUi( this );

    pDB->buildQueries( "Calls", _pUI->tabWidget->nextInFocusChain() );
}

//! Constructor for editing a call.
/*!
  Load the call's data.
  \param pDB Pointer to the database manager.
  \param iID Call's DB id.
*/
wndActiveCall::wndActiveCall( QWidget *pParent, DatabaseManager *pDB, int iID ) :
    QMainWindow( pParent ), DatabaseItem( pDB, iID )
{
    _pUI = new Ui::wndActiveCall;
    _pUI->setupUi( this );

    pDB->buildQueries( "Calls", _pUI->tabWidget->nextInFocusChain() );
    Select();
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
        if ( Insert() )
            QMessageBox::information( this, "Call Added", "Call has been added." );
        else
            QMessageBox::warning( this, "Call Error", "Call could not be added! See log file more information." );
    }
    else
    {
        if ( Update() )
            QMessageBox::information( this, "Call Updated", "Call has been updated." );
        else
            QMessageBox::warning( this, "Call Error", "Call could not be updated! See log for more information." );
    }
}

bool wndActiveCall::Create( void )
{
    return true;
}

bool wndActiveCall::Insert( void )
{
    _iID = _pDB->insertUI( "Calls", _pUI->tabWidget->nextInFocusChain() );
    return ( _iID > 0 ) ? true : false;
}

bool wndActiveCall::Update( void )
{
    return _pDB->updateUI( _iID, "Calls", _pUI->tabWidget->nextInFocusChain() );
}

bool wndActiveCall::Select( void )
{
    return _pDB->selectUI( _iID, "Calls", _pUI->tabWidget->nextInFocusChain() );
}

bool wndActiveCall::Delete( void )
{
    return true;
}

bool wndActiveCall::Delete( DatabaseManager *pDB, int iID )
{
    return pDB->deleteUI( iID, "Calls" );
}

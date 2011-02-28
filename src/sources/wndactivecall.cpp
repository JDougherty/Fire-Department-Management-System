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
    _iCallID = -1;
    _bAddCall = true;
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
    _iCallID = iID;
    _bAddCall = false;
}

wndActiveCall::~wndActiveCall( void )
{
    delete _pUI;
}

//! Create the initial call record in the database
bool wndActiveCall::insert( void )
{
    QSqlQuery selectQuery;
    selectQuery.prepare( "SELECT max(id)+1 FROM calls" );

    if ( _pDB->query( selectQuery ) )
    {
        selectQuery.first();
        _iCallID = selectQuery.value( 0 ).toInt();

        QSqlQuery insertQuery;
        insertQuery.prepare( "INSERT INTO calls (id) VALUES (?)" );
        insertQuery.addBindValue( selectQuery.value( _iCallID ) );

        if ( _pDB->query( insertQuery ) )
        {
            qDebug( "Call Information: Inserted new Call to database." );
            return true;
        }
        else
        {
            QMessageBox::warning( 0, "Call Error", "Could not insert new Call to database. See log for more information." );
            qWarning( "Call Error (%d): Could not insert new Call to database. Database Error: %s", _iCallID, qPrintable( insertQuery.lastError().text() ) );
            return false;
        }
    }
    else
    {
        QMessageBox::warning( 0, "Call Error", "Could not insert new Call to database. See log for more information." );
        qWarning( "Call Error: Could not retrieve new Call ID. Database Error: %s", qPrintable( selectQuery.lastError().text() ) );
        return false;
    }
}


//! Updates the call's information in the database when the Save button is clicked.
/*!
  Creates a list of the desired widgets. Uses the tab order for widget ordering.
*/
void wndActiveCall::btnSaveCallClicked( void )
{
    if ( _bAddCall )
    {
        insert();
        _bAddCall = false;
    }

    QList<QWidget*> edits;
    QWidget *tmpw = _pUI->tabWidget->nextInFocusChain();

    while ( tmpw != _pUI->tabWidget )
    {
        if ( tmpw->objectName().startsWith( "txtarray" ) )
        {
            edits += tmpw;
        }
        tmpw = tmpw->nextInFocusChain();
    }

    QSqlQuery updateQuery;
    updateQuery.prepare(
      "UPDATE calls SET incidentnumber=?,"
          "Location=?, TravelDirections=?, NumMile=?, StreetPrefix=?,"
          "Street=?, StreetType=?, StreetSuffix=?, AptSuiteRm=?,"
          "CityTown=?, State=?, ZipCode=?, IncidentType=?, MutualAid=?,"
          "MutualAidFDID=?, MutualAidState=?, MutualAidIncidentNumber=?,"
          "Alarm=?, Arrival=?, Clear=?, PrimaryAction=?,"
          "SecondaryAction=?, Apparatus=?, Personnel=?, ValueOfProperty=?,"
          "TotalLoss=?, InjuriesFireService=?, InjuriesOther=?,"
          "DeathsFireService=?, DeathsOther=?, HazMatType=?, HazMatClass=?,"
          "HazMatAmount=?, HazMatUnit=?, PropertyDetector=?,"
          "MixedUseProperty=?, PropertyUse=?, NumUnits=?,"
          "JuvenileInvolvement=?, InvolvedBusinessName1=?, InvolvedTitle1=?,"
          "InvolvedFirstName1=?, InvolvedMiddleInitial1=?,"
          "InvolvedLastName1=?, InvolvedSuffix1=?, InvolvedNumMile1=?,"
          "InvolvedStreetPrefix1=?, InvolvedStreet1=?, InvolvedStreetType1=?,"
          "InvolvedStreetSuffix1=?, InvolvedPOBox1=?, InvolvedAptSuiteRm1=?,"
          "InvolvedCityTown1=?, InvolvedState1=?, InvolvedZipCode1=?,"
          "InvolvedBusinessName2=?, InvolvedTitle2=?, InvolvedFirstName2=?,"
          "InvolvedMiddleInitial2=?, InvolvedLastName2=?, InvolvedSuffix2=?,"
          "InvolvedNumMile2=?, InvolvedStreetPrefix2=?, InvolvedStreet2=?,"
          "InvolvedStreetType2=?, InvolvedStreetSuffix2=?, InvolvedPOBox2=?,"
          "InvolvedAptSuiteRm2=?, InvolvedCityTown2=?, InvolvedState2=?,"
          "InvolvedZipCode2=?, AreaOfIgnition=?, HeatSource=?,"
          "ItemFirstIgnited=?, TypeMaterialFirstIgnited=?, CauseofIgnition=?,"
          "ContributingFactor=?, SpreadConfined=?, HumanFactors=?,"
          "HumanFactorsAge=?, HumanFactorsSex=?, EquipmentFactors=?,"
          "EquipmentFactorsPower=?, EquipmentFactorsPortability=?,"
          "MobilePropertyType=?, MobilePropertyMake=?, BuildingType=?,"
          "BuildingStatus=?, BuildingHeightStories=?, MainFloorSizeFtW=?,"
          "MainFloorSizeFtH=?, StoryFireOrigin=?, FireSpread=?,"
          "DetectorPresence=?, DetectorType=?, DetectorPower=?,"
          "DetectorOperation=?, DetectorEffectiveness=?,"
          "DetectorFailureReason=?, AESPresence=?, AESType=?,"
          "AESOperation=?, NumSprinklerHeadsOper=?, AESFailureReason=?"
          " WHERE id = ?");

    updateQuery.addBindValue( _pUI->txtCallNum->text() );

    for ( int i = 0; i < edits.size(); i++ )
    {
        QWidget *tmp = edits.at(i);
        QLineEdit *tmplineedit = qobject_cast<QLineEdit *>( tmp );
        QDateTimeEdit *tmpdatetime = qobject_cast<QDateTimeEdit *>( tmp );
        QComboBox *tmpcombo = qobject_cast<QComboBox *>( tmp );
        QCheckBox *tmpcheck = qobject_cast<QCheckBox *>( tmp );

        if ( tmplineedit )
        {
            updateQuery.addBindValue( tmplineedit->text() );
        }
        else if ( tmpdatetime )
        {
            updateQuery.addBindValue( tmpdatetime->dateTime().toString( "yyyy-MM-dd hh:mm:00.000" ) );
        }
        else if ( tmpcombo )
        {
            updateQuery.addBindValue( tmpcombo->currentText() );
        }
        else if ( tmpcheck )
        {
            updateQuery.addBindValue( tmpcheck->objectName() );
        }
    }

    updateQuery.addBindValue( _iCallID );

    if ( _pDB->query( updateQuery) )
    {
        qDebug( "Call Information (%d): Call information successfully updated in database.", _iCallID );
        QMessageBox::information( 0, "Call Information", "Call information successfully updated in database." );
    }
    else
    {
        qWarning( "Call Error (%d): Call information could not be updated in database. Database Error: %s", _iCallID, qPrintable( updateQuery.lastError().text() ) );
        QMessageBox::warning( 0, "Call Error", "Call information could not be updated in database. See log for more information." );
    }
}

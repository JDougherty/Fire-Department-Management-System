#include "../headers/wndactivecall.h"
#include "ui_wndactivecall.h"

wndActiveCall::wndActiveCall(QWidget *parent,DatabaseManager *newDb, int nid) :
    QMainWindow(parent),
    ui(new Ui::wndActiveCall)
{
    db=newDb;
    callid=nid;
    if(callid==0){
        if(!insert()){
            delete this;
        }

        ui->setupUi(this);

        ui->txtIDScan->setFocus();

    }
    else{
        ui->setupUi(this);
    }

    connect(ui->btnSave,SIGNAL(clicked()),this,SLOT(updateInformation()));
}

wndActiveCall::~wndActiveCall()
{
    delete ui;
}

// To create the initial record in the database
bool wndActiveCall::insert(){
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT max(id)+1 FROM calls");
    if(db->query(selectQuery)){
        selectQuery.first();
        callid=selectQuery.value(0).toInt();

        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO calls (id) VALUES (?)");
        insertQuery.addBindValue(selectQuery.value(callid));

        if(db->query(insertQuery)){
            qDebug("Call Information: Inserted new Call to database.");
            return true;
        }
        else{
            QMessageBox::warning(0,"Call Error","Could not insert new Call to database. See log for more information.");
            qWarning("Call Error (%d): Could not insert new Call to database. Database Error: %s",callid,qPrintable(insertQuery.lastError().text()));
            return false;
        }
    }
    else{
        QMessageBox::warning(0,"Call Error","Could not insert new Call to database. See log for more information.");
        qWarning("Call Error: Could not retrieve new Call ID. Database Error: %s",qPrintable(selectQuery.lastError().text()));
        return false;
    }
}

// Test slot for the ordering of the input fields.
// Creates a list of the desired widgets.
// Uses the tab order for widget ordering.
// Will eventually be used to build the INSERT and UPDATE
//  SQL queries.
void wndActiveCall::updateInformation()
{   QList<QWidget*> edits;

    QWidget *tmpw = ui->tabWidget->nextInFocusChain();
    while(tmpw!=ui->tabWidget){
        if(tmpw->objectName().startsWith("txtarray")){
            edits+=tmpw;
        }
        tmpw=tmpw->nextInFocusChain();
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

    updateQuery.addBindValue(ui->txtCallNum->text());

    for (int i = 0; i < edits.size(); ++i) {
        QWidget *tmp = edits.at(i);
        QLineEdit *tmplineedit = qobject_cast<QLineEdit *>(tmp);
        QDateTimeEdit *tmpdatetime = qobject_cast<QDateTimeEdit *>(tmp);
        QComboBox *tmpcombo = qobject_cast<QComboBox *>(tmp);
        QCheckBox *tmpcheck = qobject_cast<QCheckBox *>(tmp);

        if(tmplineedit){
            updateQuery.addBindValue(tmplineedit->text());
        }
        else if(tmpdatetime){
            updateQuery.addBindValue(tmpdatetime->dateTime().toString("yyyy-MM-dd hh:mm:00.000"));
        }
        else if(tmpcombo){
            updateQuery.addBindValue(tmpcombo->currentText());
        }
        else if(tmpcheck){
            updateQuery.addBindValue(tmpcheck->objectName());
        }
    }

    updateQuery.addBindValue(callid);

    if(db->query(updateQuery)){
        qDebug("Call Information (%d): Call information successfully updated in database.",callid);
        QMessageBox::information(0,"Call Information","Call information successfully updated in database.");
    }
    else{
        qWarning("Call Error (%d): Call information could not be updated in database. Database Error: %s",callid,qPrintable(updateQuery.lastError().text()));
        QMessageBox::warning(0,"Call Error","Call information could not be updated in database. See log for more information.");
    }
}

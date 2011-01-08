#include "../headers/wndactivecall.h"
#include "ui_wndactivecall.h"

wndActiveCall::wndActiveCall(QWidget *parent,DatabaseManager *newDb) :
    QMainWindow(parent),
    ui(new Ui::wndActiveCall)
{
    ui->setupUi(this);
    db=newDb;
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

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO Calls ("
                        "Location,"
                        "TravelDirections,"
                        "NumMile,"
                        "StreetPrefix,"
                        "Street,"
                        "StreetType,"
                        "StreetSuffix,"
                        "AptSuiteRm,"
                        "CityTown,"
                        "State,"
                        "ZipCode,"
                        "IncidentType,"
                        "MutualAid,"
                        "MutualAidFDID,"
                        "MutualAidState,"
                        "MutualAidIncidentNumber,"
                        "Alarm,"
                        "Arrival,"
                        "Clear,"
                        "PrimaryAction,"
                        "SecondaryAction,"
                        "Apparatus,"
                        "Personnel,"
                        "ValueOfProperty,"
                        "TotalLoss,"
                        "InjuriesFireService,"
                        "InjuriesOther,"
                        "DeathsFireService,"
                        "DeathsOther,"
                        "HazMatType,"
                        "HazMatClass,"
                        "HazMatAmount,"
                        "HazMatUnit,"
                        "PropertyDetector,"
                        "MixedUseProperty,"
                        "PropertyUse,"
                        "NumUnits,"
                        "JuvenileInvolvement,"
                        "InvolvedBusinessName1,"
                        "InvolvedTitle1,"
                        "InvolvedFirstName1,"
                        "InvolvedMiddleInitial1,"
                        "InvolvedLastName1,"
                        "InvolvedSuffix1,"
                        "InvolvedNumMile1,"
                        "InvolvedStreetPrefix1,"
                        "InvolvedStreet1,"
                        "InvolvedStreetType1,"
                        "InvolvedStreetSuffix1,"
                        "InvolvedPOBox1,"
                        "InvolvedAptSuiteRm1,"
                        "InvolvedCityTown1,"
                        "InvolvedState1,"
                        "InvolvedZipCode1,"
                        "InvolvedBusinessName2,"
                        "InvolvedTitle2,"
                        "InvolvedFirstName2,"
                        "InvolvedMiddleInitial2,"
                        "InvolvedLastName2,"
                        "InvolvedSuffix2,"
                        "InvolvedNumMile2,"
                        "InvolvedStreetPrefix2,"
                        "InvolvedStreet2,"
                        "InvolvedStreetType2,"
                        "InvolvedStreetSuffix2,"
                        "InvolvedPOBox2,"
                        "InvolvedAptSuiteRm2,"
                        "InvolvedCityTown2,"
                        "InvolvedState2,"
                        "InvolvedZipCode2,"
                        "AreaOfIgnition,"
                        "HeatSource,"
                        "ItemFirstIgnited,"
                        "TypeMaterialFirstIgnited,"
                        "CauseofIgnition,"
                        "ContributingFactor,"
                        "SpreadConfined,"
                        "HumanFactors,"
                        "HumanFactorsAge,"
                        "HumanFactorsSex,"
                        "EquipmentFactors,"
                        "EquipmentFactorsPower,"
                        "EquipmentFactorsPortability,"
                        "MobilePropertyType,"
                        "MobilePropertyMake,"
                        "BuildingType,"
                        "BuildingStatus,"
                        "BuildingHeightStories,"
                        "MainFloorSizeFtW,"
                        "MainFloorSizeFtH,"
                        "StoryFireOrigin,"
                        "FireSpread,"
                        "DetectorPresence,"
                        "DetectorType,"
                        "DetectorPower,"
                        "DetectorOperation,"
                        "DetectorEffectiveness,"
                        "DetectorFailureReason,"
                        "AESPresence,"
                        "AESType,"
                        "AESOperation,"
                        "NumSprinklerHeadsOper,"
                        "AESFailureReason"
                        ") VALUES (?,?,?,?,?,?,?,?,?,?,"
                          "?,?,?,?,?,?,?,?,?,?,"
                          "?,?,?,?,?,?,?,?,?,?,"
                          "?,?,?,?,?,?,?,?,?,?,"
                          "?,?,?,?,?,?,?,?,?,?,"
                          "?,?,?,?,?,?,?,?,?,?,"
                          "?,?,?,?,?,?,?,?,?,?,"
                          "?,?,?,?,?,?,?,?,?,?,"
                          "?,?,?,?,?,?,?,?,?,?,"
                          "?,?,?,?,?,?,?,?,?,?,"
                          "?,?,?)");

    insertQuery.addBindValue(ui->txtIDScan->text());

    for (int i = 0; i < edits.size(); ++i) {
        QWidget *tmp = edits.at(i);

        QLineEdit *tmplineedit = qobject_cast<QLineEdit *>(tmp);
        QDateTimeEdit *tmpdatetime = qobject_cast<QDateTimeEdit *>(tmp);
        QComboBox *tmpcombo = qobject_cast<QComboBox *>(tmp);
        QCheckBox *tmpcheck = qobject_cast<QCheckBox *>(tmp);

        if(tmplineedit){
            insertQuery.addBindValue(tmplineedit->text());
        }
        else if(tmpdatetime){
            insertQuery.addBindValue(tmpdatetime->dateTime().toString());
        }
        else if(tmpcombo){
            insertQuery.addBindValue(tmpcombo->currentText());
        }
        else if(tmpcheck){
           insertQuery.addBindValue(tmpcheck->objectName());
        }

    }
    if(db->query(insertQuery)){
        qDebug("Great!");
    }
    else{
        qDebug("Boo!");
    }
}

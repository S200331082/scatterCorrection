#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



DetectorMessenger::DetectorMessenger(DetectorConstruction * Det) : fDetector(Det)
{ 
  fGparameter = new G4UIdirectory("/GeometryParameter/");
  fGparameter->SetGuidance("Geometry parameter control.");

  fPhantomDir = new G4UIdirectory("/GeometryParameter/Phantom/");
  fPhantomDir->SetGuidance("Phantom subparameter control.");

  fDetectorDir = new G4UIdirectory("/GeometryParameter/Detector/");
  fDetectorDir->SetGuidance("Detector subparameter control.");
  
  fPhantomSizeCmd = new G4UIcmdWithADouble("/GeometryParameter/Phantom/setPhantomSize",this);
  fPhantomSizeCmd->SetGuidance("Set XYSize of Phantom.");
  fPhantomSizeCmd->SetParameterName("PhantomSize",false);
  fPhantomSizeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fPhantomThicknessCmd = new G4UIcmdWithADouble("/GeometryParameter/Phantom/setPhantomThickness",this);
  fPhantomThicknessCmd->SetGuidance("Set thickness of Phantom.");
  fPhantomThicknessCmd->SetParameterName("PhantomThickness",false);
  fPhantomThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  fDetectorSizeCmd = new G4UIcmdWithADouble("/GeometryParameter/Detector/setDetectorSize",this);
  fDetectorSizeCmd->SetGuidance("Set XYSize of Detector.");
  fDetectorSizeCmd->SetParameterName("DetectorSize",false);
  fDetectorSizeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fDetectorThicknessCmd = new G4UIcmdWithADouble("/GeometryParameter/Detector/setDetectorThickness",this);
  fDetectorThicknessCmd->SetGuidance("Set thickness of Detector.");
  fDetectorThicknessCmd->SetParameterName("DetectorThickness",false);
  fDetectorThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fPixelNumCmd = new G4UIcmdWithAnInteger("/GeometryParameter/Detector/setPixelNum",this);
  fPixelNumCmd->SetGuidance("Set length Num of Pixel.");
  fPixelNumCmd->SetParameterName("PixelNum",false);
  fPixelNumCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  delete fPhantomSizeCmd;
  delete fPhantomThicknessCmd;
  delete fDetectorSizeCmd;
  delete fDetectorThicknessCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
    if( command == fPhantomSizeCmd )
        { fDetector->setPhantomSize(fPhantomSizeCmd->GetNewDoubleValue(newValue));}

    if( command == fPhantomThicknessCmd )
        { fDetector->setPhantomThickness(fPhantomThicknessCmd->GetNewDoubleValue(newValue));}

    if( command == fDetectorSizeCmd )
        { fDetector->setDetectorSize(fDetectorSizeCmd->GetNewDoubleValue(newValue));}

    if( command == fDetectorThicknessCmd )
        { fDetector->setDetectorThickness(fDetectorThicknessCmd->GetNewDoubleValue(newValue));}

    if( command == fPixelNumCmd )
        { fDetector->setPixelNum(fPixelNumCmd->GetNewIntValue(newValue));}
}


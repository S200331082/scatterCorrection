#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "DetectorConstruction.hh"

using namespace scatterCorrection;


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorMessenger: public G4UImessenger
{
  public:
  
    DetectorMessenger(DetectorConstruction* );
   ~DetectorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);

  private:
  
    DetectorConstruction*   fDetector;
   
    G4UIdirectory* fGparameter;
    G4UIdirectory* fPhantomDir;   // 子目录指针声明
    G4UIdirectory* fDetectorDir;  
    G4UIcmdWithADouble* fPhantomSizeCmd;
    G4UIcmdWithADouble* fPhantomThicknessCmd;
    G4UIcmdWithADouble* fDetectorSizeCmd;
    G4UIcmdWithADouble* fDetectorThicknessCmd;
    G4UIcmdWithAnInteger* fPixelNumCmd;
};
#endif


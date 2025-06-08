//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file scatterCorrection/include/DetectorConstruction.hh
/// \brief Definition of the scatterCorrection::DetectorConstruction class

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"


class DetectorMessenger; 

class G4VPhysicalVolume;
class G4LogicalVolume;

namespace scatterCorrection
{

/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction() override;

    G4VPhysicalVolume* Construct() override;

    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

    void setPhantomSize(G4double);
    void setPhantomThickness(G4double);
    void setDetectorSize(G4double);
    void setDetectorThickness(G4double);
    void setPixelNum(G4int);
    G4double GetPhantomSize () {return PhantomSize;};
    G4double GetPhantomThickness () {return PhantomThickness;};
    G4double GetDetectorSize () {return DetectorSize;};
    G4double GetDetectorThickness () {return DetectorThickness;};
    G4int GetPixelNum () {return PixelNum;};
    G4double PhantomSize,PhantomThickness,DetectorSize,DetectorThickness;
    G4int PixelNum;

  protected:
    G4LogicalVolume* fScoringVolume = nullptr;
    DetectorMessenger* fDetectorMessenger;
};

}  // namespace scatterCorrection

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif





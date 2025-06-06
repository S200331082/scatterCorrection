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
/// \file scatterCorrection/src/DetectorConstruction.cc
/// \brief Implementation of the scatterCorrection::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Trd.hh"

namespace scatterCorrection
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




G4VPhysicalVolume* DetectorConstruction::Construct()
{





  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Envelope parameters
  //
  G4double env_sizeXY = 50 * cm, env_sizeZ = 100 * cm;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 1.2 * env_sizeXY;
  G4double world_sizeZ = 1.2 * env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  auto solidWorld =
    new G4Box("World",  // its name
              100 * cm, 100 * cm, 100 * cm);  // its size

  auto logicWorld = new G4LogicalVolume(solidWorld,  // its solid
                                        world_mat,  // its material
                                        "World");  // its name

  auto physWorld = new G4PVPlacement(nullptr,  // no rotation
                                     G4ThreeVector(),  // at (0,0,0)
                                     logicWorld,  // its logical volume
                                     "World",  // its name
                                     nullptr,  // its mother  volume
                                     false,  // no boolean operation
                                     0,  // copy number
                                     checkOverlaps);  // overlaps checking

  //
  // Envelope
  //
  auto solidEnv = new G4Box("Envelope",  // its name
                            99*cm, 99*cm, 99*cm);  // its size

  auto logicEnv = new G4LogicalVolume(solidEnv,  // its solid
                                      env_mat,  // its material
                                      "Envelope");  // its name

  new G4PVPlacement(nullptr,  // no rotation
                    G4ThreeVector(),  // at (0,0,0)
                    logicEnv,  // its logical volume
                    "Envelope",  // its name
                    logicWorld,  // its mother  volume
                    false,  // no boolean operation
                    0,  // copy number
                    checkOverlaps);  // overlaps checking




  // detector
    G4Material* pixelMat = nist->FindOrBuildMaterial("G4_Si");

    const G4int N = 768;
    const G4int Nx = N, Ny = N;

    const G4double detectorSize = 152.0 * mm;
    const G4double pixelSize = detectorSize / N;
    const G4double pixelThickness = 1.0 * mm;

    const G4double detectorZ = 335.0 * mm;

    auto pixelSolid = new G4Box("Pixel", pixelSize, pixelSize, pixelThickness);
    auto pixelLogic = new G4LogicalVolume(pixelSolid, pixelMat, "Pixel");

    G4double startPos = 0.0;

    startPos = (1 - N) * pixelSize;
  
    G4int flag = 0;
    for (G4int ix = 0; ix < Nx; ix++) {
      G4double x = startPos + ix * pixelSize * 2;
        for (G4int iy = 0; iy < Ny; iy++) {
            
            G4double y = startPos + iy * pixelSize * 2;
            G4double z = detectorZ;
            G4int copyNum = ix * Ny + iy;
            new G4PVPlacement(
              nullptr,
              G4ThreeVector(x, y, z),
              pixelLogic,
              "Pixel",
              logicEnv,
              false,
              copyNum, // Unique copy number
              false);
        }
    }

  // phantom

  auto solidShape2 =
    new G4Box("Phantom",  // its name
              152.0 * mm, 152.0 * mm, 10 * mm);  // its size

  auto logicPhantom = new G4LogicalVolume(solidShape2,  // its solid
                                         nist->FindOrBuildMaterial("G4_WATER"),  // its material
                                         "Phantom");  // its name

  new G4PVPlacement(nullptr,  // no rotation
                    G4ThreeVector(),  // at (0,0,0)
                    logicPhantom,  // its logical volume
                    "Phantom",  // its name
                    logicEnv,  // its mother  volume
                    false,  // no boolean operation
                    0,  // copy number
                    checkOverlaps);  // overlaps checking

  // Set Shape2 as scoring volume
  //
  fScoringVolume = pixelLogic;
  


  //
  // always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}  // namespace scatterCorrection

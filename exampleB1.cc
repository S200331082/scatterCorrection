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
/// \file exampleB1.cc
/// \brief Main program of the scatterCorrection example

#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "QBBC.hh"

#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "printProgressBar.hh"
#include <chrono>
#include <iomanip>
#include <ctime>
// #include "Randomize.hh"

using namespace scatterCorrection;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv)
{
  auto start = std::chrono::high_resolution_clock::now();
  // std::time_t start_time_t = std::chrono::system_clock::to_time_t(start);
  // // 转换为本地时间结构
  // std::tm* start_tm = std::localtime(&start_time_t);

  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = nullptr;
  if (argc == 1) {
    ui = new G4UIExecutive(argc, argv);
  }

  G4Random::setTheSeed(time(nullptr)); //随机数种子

  // Optionally: choose a different Random engine...
  // G4Random::setTheEngine(new CLHEP::MTwistEngine);

  // use G4SteppingVerboseWithUnits
  G4int precision = 4;
  G4SteppingVerbose::UseBestUnit(precision);

  // Construct the default run manager
  //
  auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  // Set mandatory initialization classes
  //
  // Detector construction
  runManager->SetUserInitialization(new DetectorConstruction());

  // Physics list
  auto physicsList = new QBBC;
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  // User action initialization
  runManager->SetUserInitialization(new ActionInitialization());

  // Initialize visualization with the default graphics system
  
  auto visManager = new G4VisExecutive(argc, argv);
  // Constructors can also take optional arguments:
  // - a graphics system of choice, eg. "OGL"
  // - and a verbosity argument - see /vis/verbose guidance.
  // auto visManager = new G4VisExecutive(argc, argv, "OGL", "Quiet");
  // auto visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager

  // Process macro or start UI session
  //
  auto* UImanager = G4UImanager::GetUIpointer();
  if (!ui) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

  delete visManager;
  delete runManager;

  auto end = std::chrono::high_resolution_clock::now();
  timeOutput(start, end);
  // std::time_t end_time_t = std::chrono::system_clock::to_time_t(end);
  // // 转换为本地时间结构
  // std::tm* end_tm = std::localtime(&end_time_t);
  // auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
  // long long total_seconds = duration.count();
  // // 转换为 h:m:s
  // int hours = total_seconds / 3600;
  // int minutes = (total_seconds % 3600) / 60;
  // int seconds = total_seconds % 60;
  // // 格式化输出
  
  // G4cout << "开始时间: " << std::put_time(start_tm, "%Y-%m-%d %H:%M:%S") << G4endl;
  // G4cout << "结束时间: " << std::put_time(end_tm, "%Y-%m-%d %H:%M:%S") << G4endl;

  // G4cout << "耗时: "
  //             << std::setw(2) << std::setfill('0') << hours << ":"
  //             << std::setw(2) << std::setfill('0') << minutes << ":"
  //             << std::setw(2) << std::setfill('0') << seconds << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

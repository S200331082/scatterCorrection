#include "RunAction.hh"
#include "PixelSD.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4HCofThisEvent.hh"
#include "G4AnalysisManager.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "printProgressBar.hh"
#include <iomanip>

using namespace scatterCorrection;

PixelSD::PixelSD(const G4String& name, const G4int PixelNum) : G4VSensitiveDetector(name) {
    pixelCount = PixelNum * PixelNum;
    Ip.resize(pixelCount, 0.0);
    Is.resize(pixelCount, 0.0);
    Np.resize(pixelCount, 0);
    Ns.resize(pixelCount, 0);
    numKnown = false;
    currentEventID = 0;

    static auto start_time = std::chrono::high_resolution_clock::now();
    
}

PixelSD::~PixelSD() {}

// void PixelSD::Initialize(G4HCofThisEvent*) {
//     std::fill(Ip.begin(), Ip.end(), 0.0);
//     std::fill(Is.begin(), Is.end(), 0.0);
//     std::fill(Np.begin(), Np.end(), 0);
//     std::fill(Ns.begin(), Ns.end(), 0);
// } // 每次用到该实例都会执行，鸡肋

G4bool PixelSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    G4Track* track = step->GetTrack();
    G4int copyNum = step->GetPreStepPoint()->GetTouchable()->GetCopyNumber();
    G4double edep = step->GetTotalEnergyDeposit();
    if (!numKnown)
    {
        nofEvents = G4RunManager::GetRunManager()->GetNumberOfEventsToBeProcessed();
    }
    
    
    

    if (track->GetCurrentStepNumber() == 1) {  // 主信号（未散射）
        Ip[copyNum] += edep;
        Np[copyNum]++;
    } else {  // 散射信号
        Is[copyNum] += edep;
        Ns[copyNum]++;
    }
    
    return true;
}

void PixelSD::EndOfEvent(G4HCofThisEvent*) {
    currentEventID++;

    printProgressBar(currentEventID, nofEvents);
    
}

void PixelSD::EndOfRun() {
    //非父类虚函数，EndofRunAction中调用
    auto analysisManager = G4AnalysisManager::Instance();
    for (G4int i = 0; i < pixelCount; i++) {
        analysisManager->FillNtupleDColumn(0, i % 10);      // x (pixel index)
        analysisManager->FillNtupleDColumn(1, i / 10);      // y (pixel index)
        analysisManager->FillNtupleDColumn(2, Ip[i]);        // Ip (MeV)
        analysisManager->FillNtupleDColumn(3, Is[i]);        // Is (MeV)
        analysisManager->FillNtupleIColumn(4, Np[i]);        // Np (counts)
        analysisManager->FillNtupleIColumn(5, Ns[i]);        // Ns (counts)
        analysisManager->AddNtupleRow();
    }
}
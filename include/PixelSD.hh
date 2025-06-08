#ifndef PixelSD_h
#define PixelSD_h 1

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"


class PixelSD : public G4VSensitiveDetector {
public:
    PixelSD(const G4String& name, const G4int PixelNum); // 像素尺寸
    virtual ~PixelSD();

    // virtual void Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void EndOfEvent(G4HCofThisEvent* hitCollection);
    void EndOfRun();

private:
    std::vector<G4double> Ip;  // 主信号能量（每个像素）
    std::vector<G4double> Is;  // 散射信号能量（每个像素）
    std::vector<G4int> Np;     // 主信号光子计数
    std::vector<G4int> Ns;     // 散射信号光子计数

    long long nofEvents;
    G4int pixelCount;
    G4int currentEventID;

    G4bool numKnown;

};

#endif
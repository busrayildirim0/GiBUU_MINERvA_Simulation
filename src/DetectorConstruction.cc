#include "DetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // World volume (20m x 20m x 20m)
    G4double world_size = 10*m;
    auto nist = G4NistManager::Instance();
    auto world_mat = nist->FindOrBuildMaterial("G4_AIR");
    
    auto solidWorld = new G4Box("World", world_size/2, world_size/2, world_size/2);
    auto logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
    auto physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0);
    
    // Dedektör volume (1m x 1m x 1m su)
    G4double detector_size = 1*m;
    auto detector_mat = nist->FindOrBuildMaterial("G4_WATER");
    auto solidDetector = new G4Box("Detector", detector_size/2, detector_size/2, detector_size/2);
    auto logicDetector = new G4LogicalVolume(solidDetector, detector_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(0,0,0), logicDetector, "Detector", logicWorld, false, 0, true);
    
    return physWorld;
}

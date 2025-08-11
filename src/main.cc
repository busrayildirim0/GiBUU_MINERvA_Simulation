#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"

int main(int argc, char** argv)
{
    auto* runManager = new G4RunManager;
    
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList());
    
    auto* generator = new PrimaryGeneratorAction();
    runManager->SetUserAction(generator);
    runManager->SetUserAction(new SteppingAction());
    
    runManager->Initialize();
    
    // Toplam event sayısı = CSV'den gelen + 10000 background
    G4int totalEvents = generator->GetNumberOfEvents() + 10000;
    runManager->BeamOn(totalEvents);
    
    delete runManager;
    return 0;
}

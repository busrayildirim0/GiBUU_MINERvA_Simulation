#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4EventManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

SteppingAction::SteppingAction()
{
    outFile.open("step_output.csv");
    outFile << "eventID,trackID,parentID,particleName,edep(MeV),x(cm),y(cm),z(cm)" << std::endl;
}

SteppingAction::~SteppingAction()
{
    outFile.close();
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    auto track = step->GetTrack();
    auto prePoint = step->GetPreStepPoint()->GetPosition();
    G4double edep = step->GetTotalEnergyDeposit();
    
    G4int eventID = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();

    outFile << eventID << ","
            << track->GetTrackID() << ","
            << track->GetParentID() << ","
            << track->GetDefinition()->GetParticleName() << ","
            << edep/MeV << ","
            << prePoint.x()/cm << ","
            << prePoint.y()/cm << ","
            << prePoint.z()/cm
            << std::endl;
}

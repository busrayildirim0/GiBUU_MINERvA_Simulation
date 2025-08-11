#ifndef PRIMARY_GENERATOR_ACTION_HH
#define PRIMARY_GENERATOR_ACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include <vector>

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event*);
    G4int GetNumberOfEvents() const { return fEventData.size(); }
    
private:
    G4ParticleGun* fParticleGun;
    std::vector<std::vector<G4double>> fEventData;
};

#endif

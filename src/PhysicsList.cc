#include "PhysicsList.hh"
#include "G4PhysListFactory.hh"
#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4NeutrinoPhysics.hh"

PhysicsList::PhysicsList()
{
    G4PhysListFactory factory;
    G4VModularPhysicsList* physList = factory.GetReferencePhysList("FTFP_BERT");
    
    for (G4int i = 0; ; ++i) {
        G4VPhysicsConstructor* physics = const_cast<G4VPhysicsConstructor*>(physList->GetPhysics(i));
        if (!physics) break;
        RegisterPhysics(physics);
    }
    
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4RadioactiveDecayPhysics());
    RegisterPhysics(new G4NeutrinoPhysics());
}

PhysicsList::~PhysicsList()
{}

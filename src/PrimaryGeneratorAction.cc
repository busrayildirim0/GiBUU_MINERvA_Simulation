#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "Randomize.hh"  // G4UniformRand için eklendi
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    fParticleGun = new G4ParticleGun(1);
    
    // CSV dosyasını oku
    std::ifstream file("events.csv");
    std::string line;
    
    // Başlık satırını atla
    if (file.good()) {
        std::getline(file, line);
    }
    
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string value;
        std::vector<G4double> row;
        
        while (std::getline(ss, value, ',')) {
            try {
                row.push_back(std::stod(value));
            } catch (...) {
                row.push_back(0.0);
            }
        }
        
        if (row.size() >= 3) {  // En az event_id, particle_type, energy
            fEventData.push_back(row);
        }
    }
    file.close();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4int eventID = anEvent->GetEventID();
    
    if (eventID < fEventData.size()) {
        // CSV'den okunan veriyi kullan
        std::vector<G4double> row = fEventData[eventID];
        G4String particleName;
        
        // Basit parçacık eşleme
        if (row[1] == 14) particleName = "nu_mu";
        else if (row[1] == 12) particleName = "nu_e";
        else if (row[1] == 13) particleName = "mu-";
        else if (row[1] == 11) particleName = "e-";
        else if (row[1] == 22) particleName = "gamma";
        else if (row[1] == 2212) particleName = "proton";
        else particleName = "mu-"; // Varsayılan

        G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
        if (!particle) {
            particle = particleTable->FindParticle("mu-");
        }

        fParticleGun->SetParticleDefinition(particle);
        fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, -10*m));
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
        fParticleGun->SetParticleEnergy(row[2]*MeV);
    } else {
        // Rastgele kozmik ışın oluştur
        G4ParticleDefinition* particle = particleTable->FindParticle("mu-");
        
        fParticleGun->SetParticleDefinition(particle);
        fParticleGun->SetParticlePosition(G4ThreeVector(
            CLHEP::RandFlat::shoot(-5., 5.)*m,
            CLHEP::RandFlat::shoot(-5., 5.)*m,
            -10*m
        ));
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(
            CLHEP::RandFlat::shoot(-0.5, 0.5),
            CLHEP::RandFlat::shoot(-0.5, 0.5),
            1
        ).unit());
        fParticleGun->SetParticleEnergy(CLHEP::RandFlat::shoot(100., 10000.)*MeV);
    }

    fParticleGun->GeneratePrimaryVertex(anEvent);
}

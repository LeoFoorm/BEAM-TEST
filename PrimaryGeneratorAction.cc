//-----------------------------------------
//    Primary Generator Action src 
//-----------------------------------------

//Author:   Carlos Leonardo Fernandez Luna

//Project: Beam test September 2024(.cc)



#include "PrimaryGeneratorAction.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
//cambiar a muon y también es foton de centelleo
 fParticleGun = new G4ParticleGun(1); //argument is particle per event

 //here we define what kind of prticle we want to creat
 G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
 //G4String particleName = "G4MuonPlus"; //maybe its name is "opticalphoton" //* se puso como comentario
 G4ParticleDefinition *particle = particleTable->FindParticle("pi+"); 

 G4ThreeVector position(0.,0.,2*m);
 G4ThreeVector momentum(0.,0.,-1.); //consistente con el momento total 
 fParticleGun->SetParticlePosition(position);
 fParticleGun->SetParticleMomentumDirection(momentum); //only direction
 fParticleGun->SetParticleMomentum(1.*GeV); //*
 fParticleGun->SetParticleDefinition(particle);

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
 delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
 fParticleGun->GeneratePrimaryVertex(anEvent);
}

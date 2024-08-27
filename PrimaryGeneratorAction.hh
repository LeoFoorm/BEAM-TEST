//-----------------------------------------
//     Primary Generator Action headers
//-----------------------------------------

//Author:   Carlos Leonardo Fernandez Luna

//Project: Beam test September 2024(.cc)



//aqui se va a definir el gun
#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"



class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
 public:
  PrimaryGeneratorAction();
  ~PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event*);
 private:
  G4ParticleGun *fParticleGun;

};

#endif

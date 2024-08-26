//-----------------------------------------
//         
//-----------------------------------------

//Author:   Carlos Leonardo Fernandez Luna

//Project: Beam test September 2024(.cc)


// En la parte de virtual void se define la función principal de la clase ActionInitialization corre la particle_gun y calcula los pasos. Es muy importante.

#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
//#include "RunAction.hh"
//#include "EventAction.hh" 
//#include "SteppingAction.hh"


class ActionInitialization : public G4VUserActionInitialization
{
 public:
 
  ActionInitialization();
  ~ActionInitialization();

 virtual void Build() const;

};   

#endif

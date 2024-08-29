//-----------------------------------------
//    Run Action header file
//-----------------------------------------

//Author:   Carlos Leonardo Fernandez Luna

//Project: Beam test September 2024(.cc)



#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"		//before g4root.hh
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"


class RunAction : public G4UserRunAction
{
 public:
  RunAction();
  ~RunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);

  void AddPhotonHit() { photonHits++;} 

private:
 int photonHits; 
};

#endif

//-----------------------------------------
//    Detector  header file
//-----------------------------------------

//Author:   Carlos Leonardo Fernandez Luna

//Project: Beam test September 2024(.cc)


#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
//#include "RunAction.hh"


class SensitiveDetector : public G4VSensitiveDetector
{
 public:
  SensitiveDetector(G4String);
  ~SensitiveDetector();

 private:
  virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};
#endif

//NOTES:
// The input parameters of this class is a String, that's why we should explicity declare
//The main function of the sensitive detector is the one from virtual, because it's needed to detect and process the hits. It has two parameters.

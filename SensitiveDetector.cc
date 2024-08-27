//-----------------------------------------
//    Detector  src file
//-----------------------------------------

//Author:   Carlos Leonardo Fernandez Luna

//Project: Beam test September 2024(.cc)


#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

SensitiveDetector::~ SensitiveDetector()
{}

G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    //Information about the position of the photon
    G4Track *track = aStep->GetTrack();

    track->SetTrackStatus(fStopAndKill);

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();
    //G4ThreeVector momentumphoton = preStepPoint->GetMomentum();
    //G4double wlen = (1.239841939*eV/momentumphoton.mag())*1E+03; //nanometros

    G4cout<<" PHOTON POSITION "<<posPhoton<<G4endl;
    //THIS TO PRINT THE DETECTOR THAT HAVE BEEN HIT. BUT I ONLY HAVE ONE DETECTOR. So what will I get?



    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int copyNo = touchable->GetCopyNumber();

    //G4cout<<" COPY NUMBER "<<copyNo<<G4endl;

    G4VPhysicalVolume *PhysVol = touchable->GetVolume();
  //G4ThreeVector posDetector = PhysVol->GetTranslation();  <--------

    //G4cout << " DETECTOR POSITION:  " << posDetector << G4endl;
    //G4cout << " PHOTON WAVELENGTH:  " << wlen << G4endl;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

     //#################################################<-- 27/05 7 pm NUMBER OF DETECTED PHOTONS
    //const RunAction *runaction = static_cast< const RunAction* >(G4RunManager::GetRunManager()->GetUserRunAction());
    //RunAction *runactionNonConst = const_cast<RunAction *>(runaction); //<--- linea que resuelve error
    //runactionNonConst->AddPhotonHit();
    //#################################################<-- 27/05 7 pm

    //G4AnalysisManager *man = G4AnalysisManager::Instance(); //<-- 20/05 1:15 am (y lo de abajo)

    //man->FillNtupleIColumn(0,0,evt); //<------------ 20/05 11 pm
    //man->FillNtupleDColumn(0,1,momentumphoton[0]);
    //man->FillNtupleDColumn(0,2,momentumphoton[1]);
    //man->FillNtupleDColumn(0,3,momentumphoton[2]);
    //man->FillNtupleDColumn(0,4,wlen);
    //man->AddNtupleRow(0);

    //man->FillNtupleIColumn(1,0,evt);
    //man->FillNtupleDColumn(1,1,posDetector[0]);
    //man->FillNtupleDColumn(1,2,posDetector[1]);
    //man->FillNtupleDColumn(1,3,posDetector[2]);
    //man->AddNtupleRow(1);
}

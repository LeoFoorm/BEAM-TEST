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
    //Information about the track

    G4Track *track = aStep->GetTrack();

    G4String particleName = track->GetDefinition()->GetParticleName();  // Get the particle type
    //track->SetTrackStatus(fStopAndKill);
    // Filter out optical photons
    if (particleName == "opticalphoton") {
        return false;  // Do not process optical photons
    }

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posParticle = preStepPoint->GetPosition();
    //G4ThreeVector momentumphoton = preStepPoint->GetMomentum();
    //G4double wlen = (1.239841939*eV/momentumphoton.mag())*1E+03; //nanometros

    //print the position of the photon detected by the square.
    G4cout << " PARTICLE TYPE: " << particleName << G4endl;  // Print particle name
    G4cout<< " PARTICLE POSITION: " << posParticle << G4endl; 
    
    //get evetn ID
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4VPhysicalVolume *PhysVol = touchable->GetVolume();
    G4ThreeVector posDetector = PhysVol->GetTranslation();  
    //G4cout << " DETECTOR POSITION:  " << posDetector << G4endl;
    
    
    //G4cout << " PHOTON WAVELENGTH:  " << wlen << G4endl;

     //################################################# NUMBER OF DETECTED PHOTONS

    const RunAction *runaction = static_cast< const RunAction* >(G4RunManager::GetRunManager()->GetUserRunAction());
    RunAction *runactionNonConst = const_cast<RunAction *>(runaction); 
    runactionNonConst->AddPhotonHit();

    //#################################################

    G4AnalysisManager *man = G4AnalysisManager::Instance(); 

    man->FillNtupleIColumn(0,0,evt); 
    man->FillNtupleDColumn(0,1,posParticle[0]);
    man->FillNtupleDColumn(0,2,posParticle[1]);
    man->FillNtupleDColumn(0,3,posParticle[2]);
    man->FillNtupleSColumn(0,4,particleName);
    //man->FillNtupleDColumn(0,4,wlen);
    man->AddNtupleRow(0);

    //man->FillNtupleIColumn(1,0,evt);
    //man->FillNtupleDColumn(1,1,posDetector[0]);
    //man->FillNtupleDColumn(1,2,posDetector[1]);
    //man->FillNtupleDColumn(1,3,posDetector[2]);
    //man->AddNtupleRow(1);
}

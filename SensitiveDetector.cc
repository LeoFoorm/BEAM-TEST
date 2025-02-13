//      SENSITIVE DETECTOR SORUCE

#include "SensitiveDetector.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}


SensitiveDetector::~ SensitiveDetector()
{}


G4bool SensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    G4Track *track = aStep->GetTrack();
    G4AnalysisManager *man = G4AnalysisManager::Instance(); 
    track->SetTrackStatus(fStopAndKill);


    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();


    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4VPhysicalVolume *PhysVol = touchable->GetVolume();
    G4ThreeVector posDetector = PhysVol->GetTranslation();

    G4int copynum = touchable->GetCopyNumber();


     // Retrieve of run and event action
    const RunAction *runaction = static_cast< const RunAction* >(G4RunManager::GetRunManager()->GetUserRunAction());
    RunAction *runactionNonConst = const_cast<RunAction *>(runaction); 
   
    const EventAction* constEventAction = static_cast<const EventAction*>(G4RunManager::GetRunManager()->GetUserEventAction());
    EventAction* eventAction = const_cast<EventAction*>(constEventAction); 
  
        
   if (copynum >= 0 && copynum < 2) {
        eventAction->Add_DetectedPhotons_event_A_SiPMs(copynum);
    } else if (copynum >= 2 && copynum < 5) {
        eventAction->Add_DetectedPhotons_event_B_SiPMs(copynum - 2); 
    }


    //man->FillNtupleIColumn(0,0,evt); 
   // man->AddNtupleRow(0); 
    
     G4String particleName = track->GetDefinition()->GetParticleName();  // Get the particle type
  
}


//-----------------------------------------
//    Run Action src file
//-----------------------------------------

//Author:   Carlos Leonardo Fernandez Luna

//Project: Beam test September 2024(.cc)



#include "RunAction.hh"

RunAction::RunAction()
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();


//The next is to define what kind of information we want to store

 man->CreateNtuple("Particles","Particles detected information; position and name");
 man->CreateNtupleIColumn("fEvent");
 man->CreateNtupleDColumn("fX");
 man->CreateNtupleDColumn("fY");
 man->CreateNtupleDColumn("fZ");
 man->CreateNtupleSColumn("PARTICLE_TYPE");
 //man->CreateNtupleDColumn("fwlen");
 //man->CreateNtupleDColumn("fTime"); 
 man->FinishNtuple(0);


 //man->CreateNtuple("hits","hits");
 //man->CreateNtupleIColumn("fEvent");
 //man->CreateNtupleDColumn("fZ_en_mm");
 //man->FinishNtuple(1);


 //man->CreateH1("Energy Deposition","Energy Deposition",101,0.,10.*MeV); 
 //man->CreateNtupleDColumn("fEdep");
 //man->FinishNtuple(2);
}

RunAction::~RunAction()
{}


void RunAction:: BeginOfRunAction(const G4Run* run)
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();   // IMPORTANTE

 G4int runID = run->GetRunID();

 std::stringstream strRunID;
 strRunID << runID;

 man->OpenFile("Output"+strRunID.str()+".root");

 photonHits = 0; 

}

void RunAction::EndOfRunAction(const G4Run*)
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();
 
 man->Write();
 man->CloseFile();

 G4cout << "NUMBER OF PARTICLES DETECTED: " << photonHits << G4endl; 
}

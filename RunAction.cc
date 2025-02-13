//    RUN ACTION SOURCE

#include "RunAction.hh"

RunAction::RunAction()
{
 G4AnalysisManager *man = G4AnalysisManager::Instance();


 man->CreateNtuple("Event","events number");
 man->CreateNtupleIColumn("fEvent");
 man->FinishNtuple(0);



  man->CreateNtuple("Edep","Data from each event");

  for (G4int i = 0; i < 5; i++) {
        std::stringstream columnName;
        columnName << "Energy_Deposition_MeV_On_Bar_" << i;
        man->CreateNtupleDColumn(columnName.str());
    }

  for (G4int j = 0; j < 5; j++){
      std::stringstream columnName;
      columnName << "dEdx_MeVmm_On_Bar_" << j;
      man->CreateNtupleDColumn(columnName.str());
  }

  for (G4int k = 0; k < 5; k++){
      std::stringstream columnName;
      columnName << "Photons_Detected_perEvent_by_SiPM_" << k;
      man->CreateNtupleDColumn(columnName.str());
  }

   for (G4int l = 0; l < 5; l++){
      std::stringstream columnName;
      columnName << "Photons_Generated_perEvent_on_Bar_" << l;
      man->CreateNtupleDColumn(columnName.str());
  }
  man->CreateNtupleDColumn("Particle_Momentum_MeV"); //20
  man->CreateNtupleDColumn("Particle_Momentum_GeV"); //21
  man->CreateNtupleDColumn("angle"); //22
  man->CreateNtupleIColumn("Copy_num_Bar_Traversed_A"); //23
  man->CreateNtupleIColumn("Copy_num_Bar_Traversed_B"); //24
  man->CreateNtupleIColumn("All_Triggers_Got_Activated");//25
  
  man->CreateNtupleDColumn("Position_x_Detected_On_Layer_A"); //26
  man->CreateNtupleDColumn("Position_y_Detected_On_Layer_A"); //27
  man->CreateNtupleDColumn("Position_z_Detected_On_Layer_A"); //28
  man->CreateNtupleDColumn("Position_x_Detected_On_Layer_B"); //29
  man->CreateNtupleDColumn("Position_y_Detected_On_Layer_B"); //30
  man->CreateNtupleDColumn("Position_z_Detected_On_Layer_B"); //31
  man->CreateNtupleSColumn("PARTICLE_TYPE");//32

  man->CreateNtupleDColumn("Total_Energy_Deposition");  //33
  man->CreateNtupleDColumn("Total_dEdx");   //34
  man->CreateNtupleDColumn("Total_Photons_Generated"); //35 
  man->CreateNtupleIColumn("Total_Photons_Detected"); //36

  man->CreateNtupleSColumn("PARTICLE_TYPE_B");//37

  man->CreateNtupleIColumn("HIT"); //38

  man->CreateNtupleDColumn("A_ANGLE_RAD_RESPEC_Y"); //39
  man->CreateNtupleDColumn("A_ANGLE_DEG_RESPEC_Y"); //40
  man->CreateNtupleDColumn("A_ANGLE_RAD_RESPEC_XZ"); //41
  man->CreateNtupleDColumn("A_ANGLE_DEG_RESPECT_XZ"); //42

  man->CreateNtupleDColumn("B_ANGLE_RAD_RESPEC_Y"); //43
  man->CreateNtupleDColumn("B_ANGLE_DEG_RESPEC_Y"); //44
  man->CreateNtupleDColumn("B_ANGLE_RAD_RESPEC_XZ"); //45
  man->CreateNtupleDColumn("B_ANGLE_DEG_RESPECT_XZ"); //46

  

  man->FinishNtuple(1);

}

RunAction::~RunAction()
{}


void RunAction:: BeginOfRunAction(const G4Run* run)
{
 G4AnalysisManager *man = G4AnalysisManager::Instance(); 

 G4int runID = run->GetRunID();

 std::stringstream strRunID;
 strRunID << runID;

 man->OpenFile("Output"+strRunID.str()+".root");

}


void RunAction::EndOfRunAction(const G4Run*)
{
G4AnalysisManager *man = G4AnalysisManager::Instance();

 man->Write();
 man->CloseFile();
}


//  STEPPING ACTION SOURCE

#include "SteppingAction.hh"
#include <map>
#include <vector>
#include <iomanip> // Para formatear la salida

using namespace std;

SteppingAction::SteppingAction( EventAction *eventaction)
{
 fEventAction = eventaction;
}


SteppingAction::~SteppingAction()
{}


void SteppingAction::UserSteppingAction(const G4Step *step)
{

const DetectorConstruction *detectorconstruction = static_cast < const DetectorConstruction* > (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
 
const std::vector<G4LogicalVolume*>& scoringVolumesA = detectorconstruction->GetScoringVolumesA();
const std::vector<G4LogicalVolume*>& scoringVolumesB = detectorconstruction->GetScoringVolumesB();

G4LogicalVolume *ScoringVolume_Trigger_1 = detectorconstruction->GetScoringVolumeT1();
G4LogicalVolume *ScoringVolume_Trigger_2 = detectorconstruction->GetScoringVolumeT2();
G4LogicalVolume *ScoringVolume_Trigger_3 = detectorconstruction->GetScoringVolumeT3();
G4LogicalVolume *ScoringVolume_Trigger_4 = detectorconstruction->GetScoringVolumeT4();
   

G4TouchableHandle touchedbar = step->GetPreStepPoint()->GetTouchableHandle(); 
 G4LogicalVolume* barvolume = touchedbar->GetVolume()->GetLogicalVolume();



 G4double stepLength = step->GetStepLength();
 G4ParticleDefinition* particle = step->GetTrack()->GetDefinition();
 
 
 G4Track* track = step->GetTrack();

  
  G4StepPoint *PreStep = step->GetPreStepPoint();
  G4double ltime = PreStep->GetLocalTime();  
  
 
if(particle->GetParticleName() == "mu+" ||  particle->GetParticleName() == "pi+" ){   

   G4double dEdxStep_A = 0.0; 
   G4double dEdxStep_B = 0.0;
   G4double generated_photons_A = 0.0;
   G4double generated_photons_B = 0.0;


         if (barvolume == ScoringVolume_Trigger_1) {
            G4int copyTrigger1 = touchedbar->GetCopyNumber(); 
            fEventAction->Trigger_1_pierced(copyTrigger1);

            //G4String p_name = step->GetTrack()->GetDefinition()->GetParticleName();
            //G4cout << "PARTICLE NAME ON TG1:    " << p_name << G4endl;
          }  

            

          if (barvolume == ScoringVolume_Trigger_2) {
            G4int copyTrigger2 = touchedbar->GetCopyNumber(); 
            fEventAction->Trigger_2_pierced(copyTrigger2);

            //G4String p_name = step->GetTrack()->GetDefinition()->GetParticleName();
            //G4cout << "PARTICLE NAME ON TG2:    " << p_name << G4endl;
          }   
        
           

          if (barvolume == ScoringVolume_Trigger_3) {
            G4int copyTrigger3 = touchedbar->GetCopyNumber(); 
            fEventAction->Trigger_3_pierced(copyTrigger3);

            //G4String p_name = step->GetTrack()->GetDefinition()->GetParticleName();
            //G4cout << "PARTICLE NAME ON TG3:    " << p_name << G4endl;
          } 

          

          if (barvolume == ScoringVolume_Trigger_4) {
            G4int copyTrigger4 = touchedbar->GetCopyNumber(); 
            fEventAction->Trigger_4_pierced(copyTrigger4);
            
            //G4String p_name = step->GetTrack()->GetDefinition()->GetParticleName();
           // G4cout << "PARTICLE NAME ON TG4:    " << p_name << G4endl;
          }  

         
         // ---------------------------------------------------------------------------------
         if (std::find(scoringVolumesA.begin(), scoringVolumesA.end(), barvolume) != scoringVolumesA.end())
        {
        
        G4int copyNumA = touchedbar->GetCopyNumber(); // Número de copia de la barra
        fEventAction->AddTraversedBar_A(copyNumA);


         G4String p_name = step->GetTrack()->GetDefinition()->GetParticleName();
       
        G4ThreeVector position_A = step->GetPostStepPoint()->GetPosition();
       
        G4double A_pos_x = position_A.x()/(cm);
        G4double A_pos_y = position_A.y()/(cm);
        G4double A_pos_z = position_A.z()/(cm);
        fEventAction->Add_Positions_Layer_A_x(A_pos_x);
        fEventAction->Add_Positions_Layer_A_y(A_pos_y);
        fEventAction->Add_Positions_Layer_A_z(A_pos_z);
      

        fEventAction->Particle_Name_Pierced_Layer_A(p_name);

   
   //---------------------------------------
      G4cout << "PARTICLE ON LAYER A |  "<<p_name << " | position: (" << position_A.x() /cm <<  ", " <<  position_A.y() / cm << ", "
               << position_A.z() / cm << ") cm "<< G4endl; 
   //---------------------------------------


         G4double edep_A = step->GetTotalEnergyDeposit();

         if (edep_A > 0.&& stepLength > 0.)
         {
            G4double dEdxStep_A = edep_A / stepLength ;

            G4Material *plastic_scin = step->GetPreStepPoint()->GetMaterial(); 
            G4MaterialPropertiesTable *Yield = plastic_scin->GetMaterialPropertiesTable(); 
            G4double Scintillation_Yield = Yield->GetConstProperty("SCINTILLATIONYIELD");

            generated_photons_A = edep_A * Scintillation_Yield; 
            generated_photons_A = G4Poisson(generated_photons_A); 

            size_t a = std::distance(scoringVolumesA.begin(),
                                              std::find(scoringVolumesA.begin(), scoringVolumesA.end(), barvolume));
            
            fEventAction->AddPhotonG_UsingEdep_A(a, generated_photons_A);
            fEventAction->AddEdepA(a, edep_A);
            fEventAction->AccumulatedEdx_A(a, dEdxStep_A);     
         }
        }
        

         if (std::find(scoringVolumesB.begin(), scoringVolumesB.end(), barvolume) != scoringVolumesB.end())
        {

        G4int copyNumB = touchedbar->GetCopyNumber(); 
        fEventAction->AddTraversedBar_B(copyNumB);

        G4String p_name = step->GetTrack()->GetDefinition()->GetParticleName();
  
        G4ThreeVector position_B = step->GetPostStepPoint()->GetPosition();

        G4double B_pos_x = position_B.x()/(cm);
        G4double B_pos_y = position_B.y()/(cm);
        G4double B_pos_z = position_B.z()/(cm);
        fEventAction->Add_Positions_Layer_B_x(B_pos_x);
        fEventAction->Add_Positions_Layer_B_y(B_pos_y);
        fEventAction->Add_Positions_Layer_B_z(B_pos_z);


       fEventAction->Particle_Name_Pierced_Layer_B(p_name);


        //---------------------------------------
        G4cout<< "PARTICLE ON LAYER B |  " << p_name << " | position: (" << position_B.x() /cm <<  ", " <<  position_B.y() / cm << ", "
               << position_B.z() / cm << ") cm "<< G4endl; 
        //---------------------------------------


         G4double edep_B = step->GetTotalEnergyDeposit();

         if (edep_B > 0.&& stepLength > 0.)
         {
            G4double dEdxStep_B = edep_B  / stepLength ;

            G4Material *plastic_scin = step->GetPreStepPoint()->GetMaterial(); 
            G4MaterialPropertiesTable *Yield = plastic_scin->GetMaterialPropertiesTable(); 
            G4double Scintillation_Yield = Yield->GetConstProperty("SCINTILLATIONYIELD");

            generated_photons_B = edep_B * Scintillation_Yield; 
            generated_photons_B = G4Poisson(generated_photons_B); 
            
            size_t b = std::distance(scoringVolumesB.begin(),
                                              std::find(scoringVolumesB.begin(), scoringVolumesB.end(), barvolume));
            
            fEventAction->AddPhotonG_UsingEdep_B(b, generated_photons_B); 
            fEventAction->AddEdepB(b, edep_B);
            fEventAction->AccumulatedEdx_B(b, dEdxStep_B);  
         }
         }    
    

}

}


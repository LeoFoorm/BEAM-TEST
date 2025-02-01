//   EVENT ACTION SOURCE

#include "EventAction.hh" 
using namespace std;


EventAction::EventAction(RunAction*) : photonHits_event_A(20, 0), photonHits_event_B(20, 0)
{
fEdepA.resize(20, 0.0); // Initialize with 20 bars, all values set to 0
fEdepB.resize(20, 0.0); // Initialize with 20 bars, all values set to 0

fTotaldEdx_A.resize(20, 0.0);
fTotaldEdx_B.resize(20, 0.0);

fGenerated_photons_A.resize(20, 0.0);
fGenerated_photons_B.resize(20, 0.0);

muonCount = 0;

    traversed_Bars_A.clear();
    traversed_Bars_B.clear();

   // Hit_particle_passed_two_layers = false;
    Sumcopies = 0;

    TOTAL_Edep = 0.0;
    TOTAL_dEdx = 0.0;
    TOTAL_Detected_photons = 0.0;
    TOTAL_Generated_photons = 0.0;

    Trig_1 = 0;
    Trig_2 = 0;
    Trig_3 = 0;
    Trig_4 = 0;
    all_triggers_work = false;

    pos_layer_A_x.clear();
    pos_layer_A_y.clear();
    pos_layer_A_z.clear();

    pos_layer_B_x.clear();
    pos_layer_B_y.clear();
    pos_layer_B_z.clear();

    particles_names_A.clear();
}


EventAction::~EventAction()
{}



void EventAction::BeginOfEventAction(const G4Event*) 
{
    photonHits_event_A.assign(20, 0);
    photonHits_event_B.assign(20, 0);
    
    fEdepA.assign(20, 0.0); 
    fEdepB.assign(20, 0.0); 

    fTotaldEdx_A.assign(20, 0.0);
    fTotaldEdx_B.assign(20, 0.0);

    fGenerated_photons_A.assign(20, 0.0);
    fGenerated_photons_B.assign(20, 0.0);

 muonCount++;
 G4cout << "EVENT ID: "  << muonCount << G4endl;
 G4cout << "------------------------------------------------------------" << G4endl;



    traversed_Bars_A.clear();
    traversed_Bars_B.clear();  

    //Hit_particle_passed_two_layers = false;
    Sumcopies = 0;    

    TOTAL_Edep = 0.0;
    TOTAL_dEdx = 0.0;
    TOTAL_Detected_photons = 0.0;
    TOTAL_Generated_photons = 0.0;

    Trig_1 = 0;
    Trig_2 = 0;
    Trig_3 = 0;
    Trig_4 = 0;
    all_triggers_work = false;

    pos_layer_A_x.clear();
    pos_layer_A_y.clear();
    pos_layer_A_z.clear();

    pos_layer_B_x.clear();
    pos_layer_B_y.clear();
    pos_layer_B_z.clear();

    particles_names_A.clear();
}



void EventAction::EndOfEventAction(const G4Event*)
{
G4AnalysisManager *man = G4AnalysisManager::Instance();  
//------------------------------------------------------------------------------------------
G4cout << "------------------------------------------------------------\n" << G4endl;
G4cout << "PARTICLES DETECTED PER TRIGGER:"<<G4endl;
G4cout << "TRIGGER 1: ";
    if(Trig_1 == 0){
        G4cout << "DID NOT PASSED";
    } else { 
        G4cout << "PASSED";
    }
G4cout << G4endl;

G4cout << "TRIGGER 2: ";
    if(Trig_2 == 0){
        G4cout << "DID NOT PASSED";
    } else { 
        G4cout << "PASSED";
    }
G4cout << G4endl;

G4cout << "TRIGGER 3: ";
    if(Trig_3 == 0){
        G4cout << "DID NOT PASSED";
    } else { 
        G4cout << "PASSED";
    }
G4cout << G4endl;

G4cout << "TRIGGER 4: ";
    if(Trig_4 == 0){
        G4cout << "DID NOT PASSED";
    } else { 
        G4cout << "PASSED";
    }
G4cout << "\n"<< G4endl;



        if(Trig_1 != 0){
            if(Trig_2 != 0){
                if(Trig_3 != 0){
                    if(Trig_4 != 0){
                        all_triggers_work = true;
                    }
                }   
            }
        } else {
          all_triggers_work = false;
        }  
    


    G4int ALL_TRIGGERS_INT = static_cast<G4int>(all_triggers_work );

    man->FillNtupleIColumn(1, 165, ALL_TRIGGERS_INT);


//------------------------------------------------------------------------------------------

G4cout << "------------------------------------------------------------\n" << G4endl;
G4cout << "ENERGY DEPOSITION ON BARS (MeV) :   \n" << G4endl;
for (size_t i = 0; i < fEdepA.size(); i++){
    if(fEdepA[i]>0){
        G4cout << "BAR A | " << "ID: "<< i << " |  Edep:  " << fEdepA[i] << "  MeV" << G4endl;
    } 
     man->FillNtupleDColumn(1, i, fEdepA[i]);  
}

for (size_t j = 0; j < fEdepA.size(); j++){
    if(fEdepB[j]>0){
       G4cout << "BAR B | " << "ID: "<< j + 2  << " |  Edep:  " << fEdepB[j] << "  MeV" << G4endl; 
    }
    man->FillNtupleDColumn(1, j + fEdepA.size(), fEdepB[j] );
    
}

    
//------------------------------------------------------------------------------------------
G4cout << "" << G4endl;
G4cout << "dE/dx (MeV/):   " << G4endl;

for (size_t k = 0; k < fTotaldEdx_A.size(); k++){
    if(fTotaldEdx_A[k]>0){
       G4cout << "BAR A | " << "ID: "<< k  << " |  dE/dx:  " << fTotaldEdx_A[k] << "  MeV/mm" << G4endl; 
    }
     man->FillNtupleDColumn(1, k + fEdepB.size() + fEdepA.size() , fTotaldEdx_A[k] );
}
   

for (size_t l = 0; l < fTotaldEdx_B.size(); l++){
    if(fTotaldEdx_B[l]>0){
       G4cout << "BAR B | " <<  "ID: "<< l + 2 << " |  dE/dx:  " << fTotaldEdx_B[l] << "  MeV/mm" << G4endl; 
    }
     man->FillNtupleDColumn(1, l + fTotaldEdx_A.size() + fEdepA.size() + fEdepB.size(), fTotaldEdx_B[l] );
}

//------------------------------------------------------------------------------------------
G4cout << "\n------------------------------------------------------------" << G4endl;
G4cout << "" << G4endl;
G4cout << "DETECTED PHOTONS ON SiPM's:   " << G4endl;
for (size_t m = 0; m < photonHits_event_A.size(); m++){
    if(photonHits_event_A[m]>0){
        G4cout << "SiPM A | " <<"ID: "<<  m  << " |  Detected photons:  " << photonHits_event_A[m] << "  photons" << G4endl;   
    }
    man->FillNtupleDColumn(1, m + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,  photonHits_event_A[m] ); 
}

for (size_t n = 0; n < photonHits_event_B.size(); n++){
    if(photonHits_event_B[n]>0){
        G4cout << "SiPM B | " <<"ID: "<< n +2   << " |  Detected photons:  " << photonHits_event_B[n] << "  photons" << G4endl; 
        }
     man->FillNtupleDColumn(1, n + photonHits_event_A.size() + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,  photonHits_event_B[n] );
}

//------------------------------------------------------------------------------------------
G4cout << "" << G4endl;
G4cout << "GENERATED PHOTONS:   " << G4endl;
for (size_t u = 0; u < fGenerated_photons_A.size(); ++u){
    if(fGenerated_photons_A[u]>0){
        G4cout << "BAR A | " <<"ID: "<<  u  << " |  Generated photons:  " << fGenerated_photons_A[u] << "  photons" << G4endl;   
        }
    man->FillNtupleDColumn(1, u + photonHits_event_B.size() + photonHits_event_A.size() + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,   fGenerated_photons_A[u] );   
}

for (size_t v = 0; v < fGenerated_photons_B.size(); v++){
    if(fGenerated_photons_B[v]>0){
        G4cout << "BAR B | " <<"ID: "<<  v + 2   << " |  Generated photons:  " << fGenerated_photons_B[v] << "  photons" << G4endl; 
        }
    man->FillNtupleDColumn(1, v + fGenerated_photons_A.size() + photonHits_event_B.size() + photonHits_event_A.size() + fTotaldEdx_B.size()+ fTotaldEdx_A.size() + fEdepB.size() + fEdepA.size() ,   fGenerated_photons_B[v] ); 
}
G4cout << "\n------------------------------------------------------------" << G4endl;

 //-------------------------------------------------------------------------------------------
G4cout << "" << G4endl;
G4cout << "LAYER A PIERCED BAR ID: ";
if (traversed_Bars_A.empty()) {
    G4cout << "-1  (-1 means no particle has passed.)";
    man->FillNtupleDColumn(1, 163, -1);
} else {
    for (auto bar_a : traversed_Bars_A) {
        G4cout << bar_a << " ";
        man->FillNtupleDColumn(1,163,bar_a);
    }
}
 G4cout <<"" <<G4endl;


G4cout << "LAYER B PIERCED BAR ID: ";
    for (auto bar_b : traversed_Bars_B) {
        G4cout << bar_b << " ";
        man->FillNtupleDColumn(1,164,bar_b);
    }
G4cout <<"" <<G4endl;

int Sumcopies = traversed_Bars_A.size() + traversed_Bars_B.size();
G4cout << "TOTAL AMOUNT OF PIERCED BARS:  " << Sumcopies << "  barras" << "\n" << G4endl; 



G4cout << G4endl;
G4cout << "PARTICLES ON LAYER A: " <<  G4endl;

if (particles_names_A.empty()) {
    G4cout << "**No particles pierced Layer A in this event." << G4endl;
} else {
    for (auto p_name : particles_names_A) {
        G4cout << p_name << ", ";
    }}



G4cout << G4endl;
G4cout << "\n------------------------------------------------------------" << G4endl;
G4cout << G4endl;

G4cout <<"(A) POSITION X : " << G4endl;
for(const auto& pos_x_A :pos_layer_A_x){
        G4cout << pos_x_A << " cm, ";
        man->FillNtupleDColumn(1, 166, pos_x_A);

}
G4cout << "" << G4endl;
G4cout <<"(A) POSITION Y: " << G4endl;
for(const auto& pos_y_A :pos_layer_A_y){
        G4cout << pos_y_A << " cm, ";
        man->FillNtupleDColumn(1, 167, pos_y_A);
}
G4cout << "" << G4endl;
G4cout <<"(A) POSITION Z: " << G4endl;
for(const auto& pos_z_A :pos_layer_A_z){
        G4cout << pos_z_A << " cm, ";
        man->FillNtupleDColumn(1, 168, pos_z_A);
}

G4cout << "" << G4endl;

G4cout <<"(B) POSITION X: "<< G4endl;
for(const auto& pos_x_B :pos_layer_B_x){
        G4cout << pos_x_B << " cm, ";
        man->FillNtupleDColumn(1, 169, pos_x_B);
}
G4cout << "" << G4endl;
G4cout <<"(B) POSITION Y: " << G4endl;
for(const auto& pos_y_B :pos_layer_B_y){
        G4cout << pos_y_B << " cm, ";
        man->FillNtupleDColumn(1, 170, pos_y_B);
}
G4cout << "" << G4endl;
G4cout <<"(B) POSITION Z: " << G4endl;
for(const auto& pos_z_B :pos_layer_B_z){
        G4cout << pos_z_B << " cm, ";
        man->FillNtupleDColumn(1, 171, pos_z_B);
}

G4cout << "\n" << G4endl;

/*
if (!pos_layer_A_x.empty() && !pos_layer_A_z.empty()) {
        G4double first_pos_x_a = pos_layer_A_x.front();
        G4double first_pos_z_a = pos_layer_A_z.front();

        G4cout << "XD (A) FIRST POSITION X: " << first_pos_x_a << " cm" << G4endl;
        G4cout << "XD (A) FIRST POSITION Z: " << first_pos_z_a << " cm" << G4endl;

        man->FillNtupleDColumn(1, 173, first_pos_x_a); // Columna fX_a
        man->FillNtupleDColumn(1, 174, first_pos_z_a); // Columna fZ_a
    } else {
        // Si no hay datos, llena con un valor de referencia (por ejemplo, -9999)
        man->FillNtupleDColumn(1, 173, 150);
        man->FillNtupleDColumn(1, 174,150);
    }

    // Guardar e imprimir la primera posición para la capa B
    if (!pos_layer_B_x.empty() && !pos_layer_B_z.empty()) {
        G4double first_pos_x_b = pos_layer_B_x.front();
        G4double first_pos_z_b = pos_layer_B_z.front();

        G4cout << "XD (B) FIRST POSITION X: " << first_pos_x_b << " cm" << G4endl;
        G4cout << "XD (B) FIRST POSITION Z: " << first_pos_z_b << " cm" << G4endl;

        man->FillNtupleDColumn(1, 175, first_pos_x_b); // Columna fX_b
        man->FillNtupleDColumn(1, 176, first_pos_z_b); // Columna fZ_b
    } else {
        // Si no hay datos, llena con un valor de referencia (por ejemplo, -9999)
        man->FillNtupleDColumn(1, 175, 150);
        man->FillNtupleDColumn(1, 176, 150);
    }
*/

//-------------------------------------------------------------------------------------------


if (fEdepA.size() != fEdepB.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden (EDEP)." << G4endl;
    return;
}

if (fTotaldEdx_A.size() != fTotaldEdx_A.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden (dEdx)." << G4endl;
    return;
}

if (photonHits_event_A.size() != photonHits_event_B.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden (Detected Photons)." << G4endl;
    return;
}

if (fGenerated_photons_A.size() != fGenerated_photons_B.size() ) {
    G4cerr << "Error: los tamaños de las listas no coinciden (Generated Photons)." << G4endl;
    return;
}


   for (size_t i = 0; i < fEdepA.size(); ++i) {
       TOTAL_Edep += fEdepA[i] + fEdepB[i];

    }

     for (size_t i = 0; i < fTotaldEdx_A.size(); ++i) {
        TOTAL_dEdx += fTotaldEdx_A[i] + fTotaldEdx_B[i];
    }

    for (size_t i = 0; i < photonHits_event_A.size(); ++i) {
        TOTAL_Detected_photons += photonHits_event_A[i] + photonHits_event_B[i];
    }

   for (size_t i = 0; i < fGenerated_photons_A.size(); ++i) {
        TOTAL_Generated_photons += fGenerated_photons_A[i] + fGenerated_photons_B[i];
    }



    // Guardar en el Ntuple
    //man->FillNtupleDColumn(1, 1, TOTAL_Edep);
     //man->FillNtupleDColumn(1, 1, TOTAL_dEdx);
     //man->FillNtupleDColumn(1, 1, TOTAL_Detected_photons);
     //man->FillNtupleDColumn(1, 1, TOTAL_Generated_photons);


   
man->AddNtupleRow(1);


}




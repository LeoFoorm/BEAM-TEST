//  DETECTOR CONSTRCTION SOURCE


#include "DetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>


DetectorConstruction::DetectorConstruction()
{
  fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");
  fMessenger->DeclareProperty("MID_Module", MID_Module, "Construct MID module detector");
  fMessenger->DeclareProperty("distance_modules", distance_modules, "The distance between both modules");
  
  DefineMaterials();

  env_sizeX = 4*m;
  env_sizeY = 4*m;
  env_sizeZ = 4*m;

  distance_modules = 10*cm + 1.04*cm;

  MID_Module = true; 
}


DetectorConstruction::~DetectorConstruction()
{}


void DetectorConstruction::DefineMaterials()
{
  
  std::vector<G4double> wavelength = {499.83,496.62,491.92,487.22,482.51,477.81,473.10,468.40,463.69,458.99,454.28,449.58,445.30,441.45,438.03,434.18,429.69,425.20,417.03,415.36,414.08,413.22,412.53,411.60,410.66,409.80, 408.53,405.80,402.75,400.18,399.32,397.27,396.33,395.48,394.62,394.28,392.91,392.27,391.41,390.34,389.70,388.42,386.63,384.57,381.58,380.31};
  std::vector<G4double> lightOutput = {2.55,2.56,2.97,3.59,4.40,5.49,6.93,8.52,10.68,13.38,17.07,21.41,26.21,31.27,36.04,40.53,45.23,49.04,53.41,58.78,63.62,68.61,73.05,78.28,83.01,88.07,92.45,96.07,99.46,96.00,91.32,86.66,80.18,73.98,69.53,64.76,58.40,50.56,44.59,38.14,33.28,29.14,23.55,17.68,12.13,6.27,4.06};
  std::vector<G4double> energy;
  std::vector<G4double> RI;
  std::vector<G4double> fraction;
  std::vector<G4double> absSC;
  std::vector<G4double> rindexWorld;
  std::vector<G4double> reflectivity;
  std::vector<G4double> rindexmylar;

  G4double RefIndex=1.58;
  G4double AbsSC = 160.*cm;
  G4double RIWorld = 1.0;
  G4double Reflectivity = 0.9999;
  G4double Rindexmylar = 1.655;


  for (size_t i = 0; i < wavelength.size(); ++i) {

    G4double Energy = 1.239841939 * eV / (wavelength[i] / 1000);

    G4double normalizedLightOutput = lightOutput[i] / 100;

    energy.push_back(Energy);

    fraction.push_back(normalizedLightOutput);

    RI.push_back(RefIndex);

    absSC.push_back(AbsSC);

    rindexWorld.push_back(RIWorld);

    reflectivity.push_back(Reflectivity);

    rindexmylar.push_back(Rindexmylar);
    }
  
  G4int numberOfEntries = energy.size();


 G4OpticalParameters::Instance()->SetScintFiniteRiseTime(true); 

 G4NistManager *nist = G4NistManager::Instance();
 worldMaterial = nist->FindOrBuildMaterial("G4_AIR");
 plastic = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
 mylarMaterial = nist->FindOrBuildMaterial("G4_MYLAR");
 steel = nist->FindOrBuildMaterial("G4_Fe");
 mirrorsurface = new G4OpticalSurface("mirrorsurface");

 mirrorsurface->SetType(dielectric_dielectric);
 mirrorsurface->SetFinish(polishedfrontpainted);
 mirrorsurface->SetModel(unified);

 G4MaterialPropertiesTable *mirror=new G4MaterialPropertiesTable();
 G4MaterialPropertiesTable *prop=new G4MaterialPropertiesTable();
 G4MaterialPropertiesTable *propworld=new G4MaterialPropertiesTable();
 G4MaterialPropertiesTable *propmylar=new G4MaterialPropertiesTable();
 

 propworld->AddProperty("RINDEX",energy, rindexWorld,numberOfEntries);
 prop->AddProperty("RINDEX",energy, RI,numberOfEntries);
 prop->AddProperty("SCINTILLATIONCOMPONENT1",energy,fraction,numberOfEntries);
 prop->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1.8*ns);
 prop->AddConstProperty("SCINTILLATIONRISETIME1", 0.7*ns); //decay time of the scintillator
 prop->AddConstProperty("SCINTILLATIONYIELD", 10.666666/keV);//amount of photons per (in this case) KeV        
 prop->AddConstProperty("RESOLUTIONSCALE", 1.);
 prop->AddProperty("ABSLENGTH",energy,absSC,numberOfEntries);
 mirror->AddProperty("REFLECTIVITY", energy, reflectivity);
 propmylar->AddProperty("RINDEX",energy, rindexmylar,numberOfEntries);


 worldMaterial->SetMaterialPropertiesTable(propworld);
 plastic->SetMaterialPropertiesTable(prop);
 mirrorsurface->SetMaterialPropertiesTable(mirror);
 mylarMaterial->SetMaterialPropertiesTable(propmylar);
}


void DetectorConstruction::ConstructMIDModule()
{
  //                     BAR 
  G4double bar_X = 2.5*cm;
  G4double bar_Y = 0.5*cm;
  G4double bar_Z = 50*cm;
  
  Solidbar = new G4Box("Solidbar", bar_X, bar_Y, bar_Z );


//                        SiPM 
  G4double sipm_X = 0.3*cm;
  G4double sipm_Y = 0.3*cm;
  G4double sipm_Z = 0.025*cm;
  
  Solidsipm = new G4Box("Solidsipm", sipm_X, sipm_Y, sipm_Z );


//                        MYLAR
  G4double mylar_x = 2.52*cm;
  G4double mylar_y = 0.52*cm;
  G4double mylar_z = 50.08*cm;
 Solidmylar = new G4Box("Solidmylar", mylar_x, mylar_y, mylar_z);
 SolidInnermylar = new G4Box("SolidInnermylar", mylar_x-0.01*cm, mylar_y-0.01*cm, mylar_z-0.01*cm);
 G4SubtractionSolid* hollowMylarBox = new G4SubtractionSolid("HollowMylarBox", Solidmylar, SolidInnermylar);
 Logicmylar = new G4LogicalVolume(hollowMylarBox, mylarMaterial, "Logicmylar");
 G4LogicalSkinSurface *skin= new G4LogicalSkinSurface("skin", Logicmylar, mirrorsurface); 



//----------------  2 SCINTILLATION BARS A  ---------------- 

  for (G4int i = 9; i < 11; i++)
  {

  Logicbar_A = new G4LogicalVolume(Solidbar, plastic, "Logicbar_A_"+std::to_string(i));
  LogicBars_A.push_back(Logicbar_A);
  fScoringVolumes_A.push_back(Logicbar_A);


  Physical_MID_A = new  G4PVPlacement(0, G4ThreeVector(-47.88 * cm + (5.04*i) * cm, 0, 0),
                                   Logicbar_A, "Physical_MID_A", LogicWorld, false, i-9, true);
  }


//             2 SiPM A 

 for (G4int j = 9; j<11; j++)
 {
  Logicsipm_A= new G4LogicalVolume(Solidsipm, worldMaterial, "Logicsipm_A_"+std::to_string(j));
  LogicSiPMs_A.push_back(Logicsipm_A);

  Physical_SiPM_MID_A = new  G4PVPlacement(0, G4ThreeVector(-47.88 * cm + (5.04*j) * cm, 0, 50.03*cm),
                                   Logicsipm_A, "Physical_SiPM_MID_A", LogicWorld, false, j-9, true);
 }


//             2 MYLAR A 
  for(G4int k = 9; k<11; k++)
  {
  Physical_Mylar_MID_A = new  G4PVPlacement(0, G4ThreeVector(-47.88 * cm + (5.04*k) * cm, 0, 0),
                                    Logicmylar, "Physical_Mylar_MID_A", LogicWorld, false, k-9, true);
  }


//---------------- 3 SCINTILLATION BARS B  -----------------------------
  G4RotationMatrix* rotationY = new G4RotationMatrix(); 
  rotationY->rotateY(90*deg);

  for (G4int l = 0; l <3; l++)
  {
  Logicbar_B = new G4LogicalVolume(Solidbar, plastic, "Logicbar_B_"+std::to_string(l));
  LogicBars_B.push_back(Logicbar_B);
  fScoringVolumes_B.push_back(Logicbar_B);

  Physical_MID_B = new  G4PVPlacement(rotationY, G4ThreeVector( 0, distance_modules, -5.04 * cm + (5.04*l) * cm),
                                   Logicbar_B, "Physical_MID_B", LogicWorld, false, l+2, true);
  }


//             3 SiPM B 
 for (G4int m = 0; m<3; m++)
 {
  Logicsipm_B= new G4LogicalVolume(Solidsipm, worldMaterial, "Logicsipm_B_"+std::to_string(m));
  LogicSiPMs_B.push_back(Logicsipm_B);
  
  Physical_SiPM_MID_B = new  G4PVPlacement(rotationY, G4ThreeVector(50.03*cm, distance_modules,  -5.04 * cm + (5.04*m) * cm),
                                   Logicsipm_B, "Physical_SiPM_MID_B", LogicWorld, false, m+2, true);
 }


//             3 MYLAR B  
  for(G4int n = 0; n<3; n++)
  {
  Physical_Mylar_MID_B = new  G4PVPlacement(rotationY, G4ThreeVector(0, distance_modules, -5.04 * cm + (5.04*n) * cm),
                                   Logicmylar, "Physical_Mylar_MID_B", LogicWorld, false, n+2, true);
  }


  //---------------  STEEL-ABSORBER  ---------------

  G4double SA_X = 50*cm;
  G4double SA_Y = 30*cm;
  G4double SA_Z = 50*cm;

  G4ThreeVector  positionSA = G4ThreeVector(0, 138.86*cm, 0);

  SolidSA = new G4Box("SolidSA", SA_X, SA_Y, SA_Z );
 LogicalSA = new G4LogicalVolume(SolidSA, steel, "LogicSA");
  PhysicalSA = new G4PVPlacement(0, positionSA, LogicalSA, "PhysicalSA", LogicWorld, false, 5, true);


  //---------------       TRIGGERS    --------------- 

   //                     SCINTILLATOR 1 & 2  
  G4double Finger_Trigger_X = 0.5*cm;
  G4double Finger_Trigger_Y = 0.5*cm;
  G4double Finger_Trigger_Z = 2.5*cm;
  
  SolidFingerTrigger = new G4Box("SolidFingerTrigger", Finger_Trigger_X, Finger_Trigger_Y, Finger_Trigger_Z );
  LogicFingerTrigger1 = new G4LogicalVolume(SolidFingerTrigger, plastic, "LogicFingerTrigger1");
  ScoringVolume_Trigger_1 = LogicFingerTrigger1;

  LogicFingerTrigger2 = new G4LogicalVolume(SolidFingerTrigger, plastic, "LogicFingerTrigger2");
  ScoringVolume_Trigger_2 = LogicFingerTrigger2;



//                        MYLAR 1 & 2 
 G4double mylarTrigger_x = 0.52*cm;
 G4double mylarTrigger_y = 0.52*cm;
 G4double mylarTrigger_z = 2.52*cm;
 SolidMylarTrigger1_2 = new G4Box("SolidMylarTrigger1_2", mylarTrigger_x, mylarTrigger_y, mylarTrigger_z);
 SolidMylarTrigger1_2_Inner = new G4Box("SolidMylarTrigger1_2_Inner", mylarTrigger_x-0.01*cm, mylarTrigger_y-0.01*cm, mylarTrigger_z-0.01*cm);
 G4SubtractionSolid* hollowMylarTrigger = new G4SubtractionSolid("HollowMylarTrigger", SolidMylarTrigger1_2, SolidMylarTrigger1_2_Inner);

 Logicmylar_Trigger_1_2 = new G4LogicalVolume(hollowMylarTrigger, mylarMaterial, "Logicmylar_Trigger_1_2");
 G4LogicalSkinSurface *skin2= new G4LogicalSkinSurface("skin2", Logicmylar_Trigger_1_2, mirrorsurface); 


//                        POSITION 1 & 2 

G4ThreeVector PosTrigger1 = G4ThreeVector(0, 280*cm, 0);
PhysicalTrigger1 = new G4PVPlacement(0, PosTrigger1, LogicFingerTrigger1, "PhysicalTrigger1", LogicWorld, false, 6, true);

G4ThreeVector PosTrigger2 = G4ThreeVector(0, 277*cm, 0);
PhysicalTrigger2 = new G4PVPlacement(rotationY, PosTrigger2, LogicFingerTrigger2, "PhysicalTrigger2", LogicWorld, false, 7, true);


Physical_Mylar_Trigger1 = new  G4PVPlacement(0, PosTrigger1,
                                    Logicmylar_Trigger_1_2, "Physical_Mylar_Trigger1", LogicWorld, false, 6, true);
                                    
Physical_Mylar_Trigger2 = new  G4PVPlacement(rotationY, PosTrigger2,
                                    Logicmylar_Trigger_1_2, "Physical_Mylar_Trigger2", LogicWorld, false, 7, true);


//                     SCINTILLATOR 3
  G4double Trigger_3_X = 3.5*cm;
  G4double Trigger_3_Y = 0.5*cm;
  G4double Trigger_3_Z = 2.5*cm;
  
  SolidTrigger_3 = new G4Box("SolidTrigger_3", Trigger_3_X, Trigger_3_Y, Trigger_3_Z );
  LogicTrigger_3 = new G4LogicalVolume(SolidTrigger_3, plastic, "LogicTrigger_3");
  ScoringVolume_Trigger_3 = LogicTrigger_3;

//                        MYLAR 3 
 G4double mylarTrigger_x3 = 3.52*cm;
 G4double mylarTrigger_y3 = 0.52*cm;
 G4double mylarTrigger_z3 = 2.52*cm;
 SolidMylarTrigger_3 = new G4Box("SolidMylarTrigger_3", mylarTrigger_x3, mylarTrigger_y3, mylarTrigger_z3);
 SolidMylarTrigger_3_Inner = new G4Box("SolidMylarTrigger_3_Inner", mylarTrigger_x3-0.01*cm, mylarTrigger_y3-0.01*cm, mylarTrigger_z3-0.01*cm);
 G4SubtractionSolid* hollowMylarTrigger_3 = new G4SubtractionSolid("HollowMylarTrigger_3", SolidMylarTrigger_3, SolidMylarTrigger_3_Inner);

 Logicmylar_Trigger_3 = new G4LogicalVolume(hollowMylarTrigger_3, mylarMaterial, "Logicmylar_Trigger_3");
 G4LogicalSkinSurface *skin3= new G4LogicalSkinSurface("skin3", Logicmylar_Trigger_3, mirrorsurface); 

//                        POSITION 3 

G4ThreeVector PosTrigger3 = G4ThreeVector(0, 274*cm, 0);
PhysicalTrigger3 = new G4PVPlacement(0, PosTrigger3, LogicTrigger_3, "PhysicalTrigger3", LogicWorld, false, 8, true);

Physical_Mylar_Trigger3 = new  G4PVPlacement(0, PosTrigger3,
                                    Logicmylar_Trigger_3, "Physical_Mylar_Trigger3", LogicWorld, false, 8, true);
                                    


//                     SCINTILLATOR 4
  G4double Trigger_4_X = 1*cm;
  G4double Trigger_4_Y = 1*cm;
  G4double Trigger_4_Z = 1*cm;
  
  SolidTrigger_4 = new G4Box("SolidTrigger_4", Trigger_4_X, Trigger_4_Y, Trigger_4_Z );
  LogicTrigger_4 = new G4LogicalVolume(SolidTrigger_4, plastic, "LogicTrigger_4");

   ScoringVolume_Trigger_4 = LogicTrigger_4;

//                        MYLAR 4 
 G4double mylarTrigger_x4 = 1.02*cm;
 G4double mylarTrigger_y4 = 1.02*cm;
 G4double mylarTrigger_z4 = 1.02*cm;
 SolidMylarTrigger_4 = new G4Box("SolidMylarTrigger_4", mylarTrigger_x4, mylarTrigger_y4, mylarTrigger_z4);
 SolidMylarTrigger_4_Inner = new G4Box("SolidMylarTrigger_4_Inner", mylarTrigger_x4-0.01*cm, mylarTrigger_y4-0.01*cm, mylarTrigger_z4-0.01*cm);
 G4SubtractionSolid* hollowMylarTrigger_4 = new G4SubtractionSolid("HollowMylarTrigger_4", SolidMylarTrigger_4, SolidMylarTrigger_4_Inner);

 Logicmylar_Trigger_4 = new G4LogicalVolume(hollowMylarTrigger_4, mylarMaterial, "Logicmylar_Trigger_4");
 G4LogicalSkinSurface *skin4= new G4LogicalSkinSurface("skin4", Logicmylar_Trigger_4, mirrorsurface); 

//                        POSITION 4 

G4ThreeVector PosTrigger4 = G4ThreeVector(0, 217.36*cm, 0);
PhysicalTrigger4 = new G4PVPlacement(0, PosTrigger4, LogicTrigger_4, "PhysicalTrigger4", LogicWorld, false, 9, true);

Physical_Mylar_Trigger4= new  G4PVPlacement(0, PosTrigger4,
                                    Logicmylar_Trigger_4, "Physical_Mylar_Trigger4", LogicWorld, false, 9, true);



//              CUBE TO B FIELD
  G4double BcubeX = 4.9 * m;
  G4double BcubeY = 1.9921 * m;
  G4double BcubeZ = 4.9 * m;

  G4ThreeVector positioncube = G4ThreeVector(0, 3.0077 * m, 0);
  SolidCube = new G4Box("SolidCube", BcubeX, BcubeY, BcubeZ);
  //LogicCube = new G4LogicalVolume(SolidCube, worldMaterial, "LogicCube");
 //PhysicalCube = new G4PVPlacement(0, positioncube, LogicCube, "PhysicalCube", LogicWorld, false, 0, true);

}



G4VPhysicalVolume *DetectorConstruction::Construct()
{
  // Solid world
  SolidWorld = new G4Box("SolidWorld", env_sizeX, env_sizeY, env_sizeZ);
  
  //logical
  LogicWorld = new G4LogicalVolume(SolidWorld, worldMaterial, "LogicWorld");

  //Physical
  PhysicalWorld = new G4PVPlacement(0, G4ThreeVector(), LogicWorld, "PhysicalWorld", 0, false, 0, true);


  if (MID_Module)
   ConstructMIDModule(); 

  return PhysicalWorld; 
}


void DetectorConstruction::ConstructSDandField()
{
 SensitiveDetector *sensDet = new SensitiveDetector("SensitiveDetector");
 // Assign sensitive detector to all SiPMs in Set A
    for (auto& logicSiPM_aasignment_a : LogicSiPMs_A) {
        logicSiPM_aasignment_a->SetSensitiveDetector(sensDet);
    }

    // Assign sensitive detector to all SiPMs in Set B
    for (auto& logicSiPM_aasignment_b : LogicSiPMs_B) {
        logicSiPM_aasignment_b->SetSensitiveDetector(sensDet);
    }
  

  G4MagneticField *magField;
  G4ThreeVector BField = G4ThreeVector(0., 0., 5.0 *kilogauss);
  magField = new G4UniformMagField(BField);

  G4FieldManager* FieldMngr = new G4FieldManager(magField);
  //FieldMngr->SetDetectorField(magField);
  //FieldMngr->CreateChordFinder(magField);
  //LogicCube->SetFieldManager(FieldMngr,true); 
  
}


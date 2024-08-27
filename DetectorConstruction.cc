//-----------------------------------------
//    Detector Construction src files
//-----------------------------------------

//Author:   Carlos Leonardo Fernandez Luna

//Project: Beam test September 2024(.cc)



#include "DetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>
#include <vector>
#include <iostream>
#include <tuple>



DetectorConstruction::DetectorConstruction()
{
 DefineMaterials();

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


 G4NistManager *nist = G4NistManager::Instance();
 G4OpticalParameters::Instance()->SetScintFiniteRiseTime(true);


 worldMaterial = nist->FindOrBuildMaterial("G4_AIR");
 plastic = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
 mylarMaterial = nist->FindOrBuildMaterial("G4_MYLAR");
 steel = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
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
 prop->AddConstProperty("SCINTILLATIONYIELD", 10./keV);//amount of photons per (in this case) KeV
 prop->AddConstProperty("RESOLUTIONSCALE", 1.);
 prop->AddProperty("ABSLENGTH",energy,absSC,numberOfEntries);
 mirror->AddProperty("REFLECTIVITY", energy, reflectivity);
 propmylar->AddProperty("RINDEX",energy, rindexmylar,numberOfEntries);


 worldMaterial->SetMaterialPropertiesTable(propworld);
 plastic->SetMaterialPropertiesTable(prop);
 mirrorsurface->SetMaterialPropertiesTable(mirror);
 mylarMaterial->SetMaterialPropertiesTable(propmylar);

}



//void DetectorConstruction::ConstructProtoDetector()

//{


//}



//all the important information to Construct() to construct the detector

G4VPhysicalVolume *DetectorConstruction::Construct()
{
    //####################################################################

  env_sizeX = 5*m;
  env_sizeY = 5*m;
  env_sizeZ = 5*m;

  //world
  SolidWorld = new G4Box("SolidWorld", env_sizeX, env_sizeY, env_sizeZ);

  //logical
  LogicWorld = new G4LogicalVolume(SolidWorld, worldMaterial, "LogicWorld");

  //Physical
  //parametros: rotation, origen (0,0,0), el logical volume, su nombre, si va a estar dentro de otro volumen, copias, check overlaps
  PhysicalWorld = new G4PVPlacement(0, G4ThreeVector(), LogicWorld, "PhysicalWorld", 0, false, 0, true);



  //############################ SQUARE ###########################

  G4double bar_X = 100*cm;
  G4double bar_Y = 100*cm;
  G4double bar_Z = 1*cm;

  G4ThreeVector  positionsquare = G4ThreeVector(0, 0, 100*cm);

  Solidsquare = new G4Box("Solidsquare", bar_X, bar_Y, bar_Z );
  Logicsquare = new G4LogicalVolume(Solidsquare, plastic, "Logicsquare"); //<-----

  //fScoringVolume = Logicsquare;

  Physicalsquare = new G4PVPlacement(0, positionsquare, Logicsquare, "Physicalsquare", LogicWorld, false, 0, true);


//############################ STEEL-ABSORBER  ###########################

  G4double SA_X = 100*cm;
  G4double SA_Y = 100*cm;
  G4double SA_Z =70*cm;

  G4ThreeVector  positionSA = G4ThreeVector(0, 0, -100*cm);

  SolidSA = new G4Box("SolidSA", SA_X, SA_Y, SA_Z );
  LogicalSA = new G4LogicalVolume(SolidSA, steel, "LogicSA");

  //fScoringVolume = Logicsquare;

  PhysicalSA = new G4PVPlacement(0, positionSA, LogicalSA, "PhysicalSA", LogicWorld, false, 0, true);


//############################ DETECTOR (SiPM) ###########################

  //G4double sipm_X = 0.6*cm;
  //G4double sipm_Y = 0.6*cm;
  //G4double sipm_Z = 0.01*cm;

  //G4ThreeVector possipm = G4ThreeVector(0, 0, 100.0051*cm);

  //Solidsipm = new G4Box("Solidsipm", sipm_X, sipm_Y, sipm_Z );
  //Logicsipm = new G4LogicalVolume(Solidsipm, worldMaterial, "Logicsipm");

  //fScoringVolume = Logicsipm;

  //Physicalsipm = new G4PVPlacement(0, possipm, Logicsipm, "Physicalsipm", LogicWorld, false, 0, true);


 //############################# MYLAR ###############################

 //G4double mylar_x = 100.001*cm;
 //G4double mylar_y = 100.001*cm;
 //G4double mylar_z = 1.0011*cm;

 //G4ThreeVector  positionmylar = G4ThreeVector(0, 0, 100*cm);

 //Solidmylar = new G4Box("Solidmylar", mylar_x, mylar_y, mylar_z);
 //Logicmylar = new G4LogicalVolume(Solidmylar,mylarMaterial,"Logicmylar");

 //fScoringVolume = Logicmylar;

 //G4LogicalSkinSurface *skin= new G4LogicalSkinSurface("skin", Logicmylar, mirrorsurface);
 //Physicalmylar = new G4PVPlacement(0,positionmylar,Logicmylar,"Physicalmylar",LogicWorld,false,0,true);




  //the mother volume always needs this return
  return PhysicalWorld;
}


void DetectorConstruction::ConstructSDandField()
{
 SensitiveDetector *sensDet = new SensitiveDetector("SensitiveDetector");

 Logicsquare->SetSensitiveDetector(sensDet);
}

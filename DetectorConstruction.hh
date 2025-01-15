//    DETECTOR CONSTRUCTION HEADER

#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalPhysics.hh"
#include "SensitiveDetector.hh"
#include "G4GenericMessenger.hh" 
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh" 
#include "G4SubtractionSolid.hh"

#include "G4FieldManager.hh"
#include "G4UniformMagField.hh"
#include "G4TransportationManager.hh"
#include "G4MagneticField.hh"


class G4VPhysicalVolume;
class G4LogicalVolume;




class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction();
    ~DetectorConstruction();
  
    virtual G4VPhysicalVolume *Construct(); 

    void ConstructMIDModule();     
   

    // TO RETRIEVE THE fScoringVolumes TO GET THE EDEP
    const std::vector<G4LogicalVolume*>& GetScoringVolumesA() const {
    return fScoringVolumes_A;
    }

    const std::vector<G4LogicalVolume*>& GetScoringVolumesB() const {
    return fScoringVolumes_B;
    }

    G4LogicalVolume *GetScoringVolumeT1() const {return ScoringVolume_Trigger_1;} 
    G4LogicalVolume *GetScoringVolumeT2() const {return ScoringVolume_Trigger_2;} 
    G4LogicalVolume *GetScoringVolumeT3() const {return ScoringVolume_Trigger_3;} 
    G4LogicalVolume *GetScoringVolumeT4() const {return ScoringVolume_Trigger_4;} 


   std::vector<G4LogicalVolume*> LogicBars_A;
   std::vector<G4LogicalVolume*> LogicSiPMs_A;
   std::vector<G4LogicalVolume*> fScoringVolumes_A;

   std::vector<G4LogicalVolume*> LogicBars_B; 
   std::vector<G4LogicalVolume*> LogicSiPMs_B;
   std::vector<G4LogicalVolume*> fScoringVolumes_B;



    G4double wavelength, lightOutput;
    G4bool MID_Module; 
    G4double distance_modules; 
    
  
  private: 

    virtual void ConstructSDandField();

    G4double env_sizeX, env_sizeY, env_sizeZ; 

    G4GenericMessenger *fMessenger;  


    G4Box  *SolidWorld, *Solidbar, *Solidsipm, *SolidCube,
           *SolidSA, *Solidmylar, *SolidInnermylar,
           *SolidFingerTrigger, *SolidMylarTrigger1_2, *SolidMylarTrigger1_2_Inner,
           *SolidTrigger_3, *SolidMylarTrigger_3, *SolidMylarTrigger_3_Inner,
           *SolidTrigger_4, *SolidMylarTrigger_4, *SolidMylarTrigger_4_Inner;


    G4LogicalVolume *LogicWorld, *Logicbar, *Logicmylar, *Logicsipm, *LogicalSA,
                    *LogicCube, *Logicbar_A, *Logicbar_B, *Logicsipm_A, *Logicsipm_B,
                    *LogicFingerTrigger1, *LogicFingerTrigger2, *Logicmylar_Trigger_1_2,
                    *LogicTrigger_3, *Logicmylar_Trigger_3,
                    *LogicTrigger_4, *Logicmylar_Trigger_4;

    G4VPhysicalVolume *PhysicalWorld, *Physicalbar, *Physicalsipm, *Physicalmylar, *PhysicalSA, *PhysicalCube,
                      *Physical_MID_A, *Physical_SiPM_MID_A, *Physical_Mylar_MID_A, 
                      *Physical_MID_B, *Physical_SiPM_MID_B, *Physical_Mylar_MID_B,
                      *PhysicalTrigger1, *PhysicalTrigger2, *Physical_Mylar_Trigger1, *Physical_Mylar_Trigger2,
                      *PhysicalTrigger3, *Physical_Mylar_Trigger3,
                      *PhysicalTrigger4, *Physical_Mylar_Trigger4;


      G4LogicalVolume *ScoringVolume_Trigger_1, *ScoringVolume_Trigger_2, 
                      *ScoringVolume_Trigger_3, *ScoringVolume_Trigger_4;
    
    void DefineMaterials();

    G4Material *plastic, *worldMaterial, *steel, *mylarMaterial;
   
    G4OpticalSurface *mirrorsurface; 
  
};

#endif


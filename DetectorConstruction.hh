//-----------------------------------------
//         Detector Construction headers files
//-----------------------------------------

//Author:   Carlos Leonardo Fernandez Luna

//Project: Beam test September 2024(.cc)




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
//#include "detector.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh" 


class G4VPhysicalVolume;
class G4LogicalVolume;



/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    

    DetectorConstruction();
    ~DetectorConstruction();
  
    virtual G4VPhysicalVolume *Construct(); 


    //void ConstructProtoDetector();
    

    G4LogicalVolume *GetScoringVolume() const {return fScoringVolume;}  


    G4double wavelength, lightOutput;


  private: 

    //In order to give the sensitivity characteristic to the detector, we have to references to this object outsid. That's why we create this private
    virtual void ConstructSDandField();//here I define this function in order to give th detector characteristics. Private means that this function is previously define on Geant4.


    G4double env_sizeX, env_sizeY, env_sizeZ; 

    

    G4Box  *SolidWorld, *Solidsquare, *SolidSA, *Solidsipm, *Solidmylar;
    G4LogicalVolume *LogicWorld, *Logicsipm, *LogicalSA, *Logicsquare, *Logicmylar; 
    G4VPhysicalVolume *PhysicalWorld, *Physicalsquare, *PhysicalSA, *Physicalsipm,*Physicalmylar;

    
    void DefineMaterials();


    G4Material *plastic, *worldMaterial, *steel, *mylarMaterial;
   
    
    
   // G4bool ProtoDetector; 


    G4OpticalSurface *mirrorsurface; //based on the PET video 13/05 1:46 pm
    

    G4LogicalVolume *fScoringVolume;


};

#endif

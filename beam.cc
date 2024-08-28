//-----------------------------------------
//         main file
//-----------------------------------------

//Author:   Carlos Leonardo Fernandez Luna

//Project: Beam test September 2024(.cc)

#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "DetectorConstruction.hh"
#include "Physics.hh"
#include "ActionInitialization.hh"
#include "G4OpticalPhysics.hh"



int main(int argc,char** argv)
{
    G4RunManager *runManager = new G4RunManager;

    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new ActionInitialization());
    //runManager->SetUserInitialization(Physics);
    //Physics-> RegisterPhysics(new G4OpticalPhysics());
    runManager->Initialize();

    G4UIExecutive *ui = new G4UIExecutive(argc,argv);

    G4VisManager * visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/ViewpointVector 1 1 1");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");//update everytime it creates a new event
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");//to show the particle
    UImanager->ApplyCommand("/vis/scene/endofEventAction accumulate");//to show the particle
    UImanager->ApplyCommand("/vis/scene/add/axes 0 0 0 1 m");
    UImanager->ApplyCommand("/vis/scene/add/hits");
    UImanager->ApplyCommand("/vis/scene/add/eventID");
    UImanager->ApplyCommand("/vis/scene/add/date");
    //UImanager->ApplyCommand("/vis/scene/");

    ui->SessionStart();

    return 0;
}

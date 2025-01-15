READ THIS!

If you are about to start a new project, first you have to write the 
CMakeLists.txt. It will tell to CMake how to compile your project.

Then, you have to make the source. In order to  “ACTIVATE GEANT4” ON  TERMINAL:

  
source /usr/local/bin/geant4.sh  (PARA SIMULACION  *si haces esto, no es necesario hacer GANT4 DIR blabla*)


Now, If the instruction above didn't work, you should try:


(in this macbook: cmake -DGeant4_DIR=/../../../../../../usr/local/lib/Geant4-11.2.0/ ../YOUR PROJECT)


El primer problema se resolvió solamente añaiendo la función DefineMaterials(); al constructor de 
DetectorConstruction.cc

El problema con la visualización se resolvió solo añadiendo a runManager->Initialize()

-------------------------------------------------------------------------------------------

Here we have 5 plastic scintillators divided in two layers. Layer A has three bars and layer B two. Layer A is above layer B. 

At 97.3 cm from layer A there is a steel absobers with thickness of 60 cm and it will change to 100 cm in 10 cm steps. 

Between the steel absorber there is 4 triggers with differents geometries. 

The particle gun just shoot one particle per event between muons and pions.

The traverse momentum of the particles will be 2, 3 and 6 GeV/c.

This simulations prints on the terminal the next data per event: (example)

------------------------------------------------------------
MOMENTUM FOR THIS EVENT: 2 GeV/c 

EVENT ID: 3
------------------------------------------------------------
PARTICLE NAME ON TG1:    mu+
PARTICLE NAME ON TG1:    e-
PARTICLE NAME ON TG1:    e-
PARTICLE NAME ON TG1:    e-
PARTICLE NAME ON TG1:    e-
PARTICLE NAME ON TG1:    e-
PARTICLE NAME ON TG1:    e-
PARTICLE NAME ON TG1:    e-
PARTICLE NAME ON TG1:    e-
PARTICLE NAME ON TG1:    e-
PARTICLE NAME ON TG1:    mu+
PARTICLE NAME ON TG2:    mu+
PARTICLE NAME ON TG2:    mu+
PARTICLE NAME ON TG3:    mu+
PARTICLE NAME ON TG3:    mu+
PARTICLE NAME ON TG4:    mu+
PARTICLE NAME ON TG4:    e-
PARTICLE NAME ON TG4:    e-
PARTICLE NAME ON TG4:    e-
PARTICLE NAME ON TG4:    e-
PARTICLE NAME ON TG4:    e-
PARTICLE NAME ON TG4:    e-
PARTICLE NAME ON TG4:    e-
PARTICLE NAME ON TG4:    mu+
PARTICLE NAME ON TG4:    mu+
PARTICLE NAME ON TG4:    mu+
PARTICLE ON LAYER B |  mu+ | position: (-1.32904, 10.9584, 0.263143) cm 
PARTICLE ON LAYER B |  mu+ | position: (-1.33657, 10.54, 0.264063) cm 
PARTICLE ON LAYER A |  mu+ | position: (-1.5357, -0.0816102, 0.28689) cm 
PARTICLE ON LAYER A |  mu+ | position: (-1.54331, -0.5, 0.28788) cm 
------------------------------------------------------------

PARTICLES DETECTED PER TRIGGER:
TRIGGER 1: PASSED
TRIGGER 2: PASSED
TRIGGER 3: PASSED
TRIGGER 4: PASSED

------------------------------------------------------------

ENERGY DEPOSITION ON BARS (MeV) :   

BAR A | ID: 0 |  Edep:  2.06707  MeV
BAR B | ID: 3 |  Edep:  1.89045  MeV

dE/dx (MeV/):   
BAR A | ID: 0 |  dE/dx:  0.399683  MeV/mm
BAR B | ID: 3 |  dE/dx:  0.371842  MeV/mm

------------------------------------------------------------

DETECTED PHOTONS ON SiPM's:   
SiPM A | ID: 0 |  Detected photons:  308  photons
SiPM A | ID: 3 |  Detected photons:  269  photons

GENERATED PHOTONS:   
BAR A | ID: 0 |  Generated photons:  22216  photons
BAR B | ID: 3 |  Generated photons:  20296  photons

------------------------------------------------------------

LAYER A PIERCED BAR ID: 0 
LAYER B PIERCED BAR ID: 3 
TOTAL AMOUNT OF PIERCED BARS:  2  barras

------------------------------------------------------------

bars are 0, 1, 2, 3 and 4.

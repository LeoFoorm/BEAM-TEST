#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"

void Aceptance()
{
    Tfile *file_1 = TFile::Open("test_1.root", "READ");

    TTree *tree = (TTree *) file_1->Get("Edep");

    Edep->Draw("Position_x_Detected_On_Layer_A:Position_z_Detected_On_Layer_A", "", "colz");
    
    Edep->Draw("Position_x_Detected_On_Layer_B:Position_z_Detected_On_Layer_B", "", "colz");
}

    
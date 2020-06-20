#include <iomanip>
#include "TFile.h"
#include "RooWorkspace.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLorentzVector.h"
#include "TSystem.h"
#include "TCut.h"
#include "TString.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TChain.h"
#include "TGraphAsymmErrors.h"
#include "iostream"
#include "/afs/ihep.ac.cn/users/z/zhouyx/cc/boot.h"


using namespace std;
using namespace RooFit;
  
void how_to_get_mphi_shape_pdf_match()
{
     setStyle();
      
     TChain *tr_data = new TChain("tree");
     tr_data->Add("/scratchfs/bes/lincx/6.6.4.p02/DptoPhiPi/job_ana/root/truth_match3.root");    
     // Tcut!!!!
     TCut cut_data ="anglekplus*180/3.14<5&&anglekminus*180/3.14<5&&anglepion*180/3.14<5";
     // get data!!!
     TTree *tr_fit = tr_data->CopyTree(cut_data);
     RooRealVar M_phi("M_phi", "M_phi", 0.987354, 1.085);
     RooDataSet *data = new RooDataSet("data","M_phi(GeV)",tr_fit, RooArgSet(M_phi));

     // generate pdf!!!
     RooKeysPdf *pdf1 = new RooKeysPdf("pdf1","", M_phi, *data, RooKeysPdf::NoMirror,2);
     pdf1->SetName("pdf1");
     pdf1->Print();
    
     //store the pdf in RooWorkspace
     RooWorkspace *w1 = new RooWorkspace("w1","workspace");
     w1->import(*pdf1);
     w1->writeToFile("pdf_mphi_match_05.root");    // rename your output file !!!!!!!!!!!!!!!!!!!!!!

     // Workspace will remain in memory after macro finishes
     gDirectory->Add(w1) ;

}





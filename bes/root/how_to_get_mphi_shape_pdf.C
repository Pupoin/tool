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
  
void how_to_get_mphi_shape_pdf()
{
     setStyle();
      
     TChain *tr_data = new TChain("TDphipi");
     tr_data->Add("/scratchfs/bes/lincx/6.6.4.p02/DptoPhiPi/job_ana/root/cut_MC.root");    
     // Tcut!!!!
     TCut cut_data ="(dE_min>-0.020&&dE_min<0.019)&&(M_phi>0.987354&&M_phi<1.085)&&(mbc_1>1.83&&mbc_1<1.8865)";
     // get data!!!
     TTree *tr_fit = tr_data->CopyTree(cut_data,"",1000000000,0);
     RooRealVar M_phi("M_phi", "M_phi", 0.987354, 1.085);
     RooDataSet *data = new RooDataSet("data","Mphi(GeV)",tr_fit, RooArgSet(M_phi));

     // generate pdf!!!
     RooKeysPdf *pdf1 = new RooKeysPdf("pdf1","", M_phi, *data, RooKeysPdf::NoMirror,2);
     pdf1->SetName("pdf1");
     pdf1->Print();
    
     //store the pdf in RooWorkspace
     RooWorkspace *w1 = new RooWorkspace("w1","workspace");
     w1->import(*pdf1);
     w1->writeToFile("pdf_mphi.root");    // rename your output file !!!!!!!!!!!!!!!!!!!!!!

     // Workspace will remain in memory after macro finishes
     gDirectory->Add(w1) ;

}





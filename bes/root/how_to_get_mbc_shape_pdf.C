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
  
void how_to_get_mbc_shape_pdf()
{
     setStyle();
      
     TChain *tr_data = new TChain("TDphipi");
     tr_data->Add("/scratchfs/bes/lincx/6.6.4.p02/DptoPhiPi/job_ana/root/cut_MC.root");    
     // Tcut!!!!
     TCut cut_data ="(dE_min>-0.020&&dE_min<0.019)&&(M_phi>0.987354&&M_phi<1.085)&&(mbc_1>1.83&&mbc_1<1.8865)";
     // get data!!!
     TTree *tr_fit = tr_data->CopyTree(cut_data,"",1000000000,0);
     RooRealVar mbc_1("mbc_1", "mbc_1", 1.83, 1.8865);
     RooDataSet *data = new RooDataSet("data","mBC(GeV)",tr_fit, RooArgSet(mbc_1));

     // generate pdf!!!
     RooKeysPdf *pdf = new RooKeysPdf("pdf","", mbc_1, *data, RooKeysPdf::NoMirror,2);
     pdf->SetName("pdf");
     pdf->Print();
    
     //store the pdf in RooWorkspace
     RooWorkspace *w = new RooWorkspace("w","workspace");
     w->import(*pdf);
     w->writeToFile("pdf_mbc.root");    // rename your output file !!!!!!!!!!!!!!!!!!!!!!

     // Workspace will remain in memory after macro finishes
     gDirectory->Add(w) ;

}






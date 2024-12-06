#include "TChain.h"
#include "TGraphAsymmErrors.h"
#include "iostream"
// #include "/afs/ihep.ac.cn/users/z/zhouyx/cc/boot.h"
#include <iomanip>



using namespace std;
using namespace RooFit;

void a()
{
        RooRealVar *chi2_min_r3c;
		// setStyle();


		TChain *tr_data = new TChain("tree");
		tr_data->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/hadron/cutmassroot/tightcut_r3c_minchi2/hadron.root");
		//tcut!!!!
		TCut cut_data="((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919)) && (  np!=0 && npbar !=0 ) && (dipim<0.44 || dipim>0.52)";
		//get data!!!
		TTree *tr_fit =tr_data->CopyTree(cut_data,"",1000000000,0);
        chi2_min_r3c= new RooRealVar("chi2_min_r3c", "chi2_min_r3c", 0, 150);
		RooDataSet *data=new RooDataSet("data","mBC(GeV)",tr_fit, RooArgSet(*chi2_min_r3c));


// generate pdf!!!
		RooKeysPdf *pdf = new RooKeysPdf("pdf","", *chi2_min_r3c, *data, RooKeysPdf::MirrorLeft,2);
		pdf->SetName("pdf");
		pdf->Print();
//store the pdf in RooWorkspace

		// RooWorkspace *w = new RooWorkspace("w","workspace") ;
		// w->import(*pdf) ;
		// w->writeToFile("pdfkkright.root") ;    //rename your output file !!!!!!!!!!!!!!!!!!!!!!

		// Workspace will remain in memory after macro finishes
		// gDirectory->Add(w) ;

        
          TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
            c2->cd();
            RooPlot *frame2 = chi2_min_r3c->frame();
            // bkgPdf->plotOn(frame) ;
            pdf->plotOn(frame2, LineWidth(2));
            frame2->Draw();
            c2->Update();

}
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooPolynomial.h"
#include "RooAddPdf.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1.h"
using namespace RooFit;
 
void plot_fit()
{
   TCanvas *canv1 = new TCanvas("canv1", "mBC", 700, 600);
   canv1->SetFillColor(0);
   canv1->SetFrameFillColor(0);
   canv1->SetTopMargin(0.1);
   canv1->SetBottomMargin(0.15);
   canv1->SetLeftMargin(0.15);
   canv1->SetRightMargin(0.03);
   gStyle->SetOptStat(0);
   gStyle->SetPadColor(0);
   gStyle->SetCanvasColor(0);

   gStyle->SetOptFit(1);
   // S e t u p   m o d e l
   // ---------------------
 
   // Construct observables x
   RooRealVar x("Costheta_sigma", "cos#theta_{#Sigma^{+}}", -1, 1);
   x.setBins(5);
 

    // Construct gaussx(x,mx,1)
    // RooRealVar mean("mean", "mean", 5.7821e-01, -1, 1);
    // RooRealVar sigma("sigma", "sigma", 1, 0, 3);
    // RooGaussian gauss("gauss", "gauss", x, mean, sigma);

    // RooRealVar poly_c1("poly_c1", "coefficient of x^1 term", 0, ­-2, 2);
    // RooPolyVar poly_c1("poly_c1", "coefficient of x^1 term", 0, ­-2, 2);

    // RooRealVar x(“x”,”x”,0.,1.) ;
    RooRealVar p0("p0","p0",0.5, -2, 2) ;
    RooRealVar p1("p1","p1",-20, -1000000, 10000) ;
    // // RooRealVar p2("p2","p2",3.0) ;
    // RooFormulaVar funcpol("f","polynomial",x,RooArgList(p0,p1)) ;
    // RooFormulaVar funcpol("f","exp(foo)*sqrt(bar)", RooArgList(foo,bar)) ;
    RooPolynomial poly("poly", "cubic polynomial", x, RooArgList(p0) );


    TChain *chain_data = new TChain("tree");
    chain_data->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/decay_asymmetry/total_Costheta_sigma.root");
    chain_data->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2_eta3pi/decay_asymmetry/total_Costheta_sigma.root");
    TTree *tree_cut = chain_data->CopyTree("M_BC_r3c>2.276 && M_BC_r3c<2.3", "", 100000000, 0);
    RooDataSet *data = new RooDataSet("data", "data", tree_cut, RooArgSet(x));


    TChain *chain_sd1 = new TChain("tree");
    TChain *chain_sd2 = new TChain("tree");
    chain_sd1->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/decay_asymmetry/total_Costheta_sigma.root");
    chain_sd2->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2_eta3pi/decay_asymmetry/total_Costheta_sigma.root");

    TTree *tree_sd1 = chain_sd1->CopyTree("(M_BC_r3c>2.25 && M_BC_r3c<2.27) || (M_BC_r3c>2.31 && M_BC_r3c<2.33)", "", 100000000, 0);
    TTree *tree_sd2 = chain_sd2->CopyTree("(M_BC_r3c>2.25 && M_BC_r3c<2.27) || (M_BC_r3c>2.31 && M_BC_r3c<2.33)", "", 100000000, 0);

    RooDataSet *data_sideband1 = new RooDataSet("data_sideband1", "data_sideban1", tree_sd1, RooArgSet(x));
    RooDataSet *data_sideband2 = new RooDataSet("data_sideband2", "data_sideban2", tree_sd1, RooArgSet(x));

   RooDataHist dh("dh","binned version of d",RooArgSet(x),data) ;
   RooDataHist dh_sd1("dh_sd1","binned version of dh_sd2",RooArgSet(x),data_sideband1) ;
   RooDataHist dh_sd2("dh_sd2","binned version of dh_sd2",RooArgSet(x),data_sideband2) ;

   RooDataHist* dh2 = (RooDataHist*) dh.reduce(y,"x>0") ;

 
   // F i t   p a r t i a l   r a n g e
   // ---------------------------------- 
   // x.setRange("signal", -3, 4);

   // Fit pdf to all data
   RooFitResult *r_full = poly.fitTo(*data, Save(kTRUE), Range("signal"));
 
   // P l o t   /   p r i n t   r e s u l t s
   // ---------------------------------------
 
   // Make plot frame in x and add data and fitted model
   RooPlot *frame = x.frame(Title( " "), Bins(5));
   data->plotOn(frame);
   poly.plotOn(frame, LineStyle(kDashed), LineColor(kRed)); // Add shape in full ranged dashed
   poly.plotOn(frame);                                                     // By default only fitted range is shown
 
   // Print fit results
   cout << "result of fit on all data " << endl;
   r_full->Print();


 
   // Draw frame on canvas
   // TCanvas *c = new TCanvas("rf203_ranges", "rf203_ranges", 800, 600);
   // gPad->SetLeftMargin(0.15);
   // frame->GetYaxis()->SetTitleOffset(1.);
   // frame->GetXaxis()->SetTitleOffset(0.8);
   frame->GetYaxis()->SetTitleSize(0.06);
   frame->GetXaxis()->SetTitleSize(0.06);
   frame->SetLabelSize(0.045, "xy");
   
   frame->Draw();



   TPaveText *pt = new TPaveText(0.16, 0.62, 0.45, 0.87, "blNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   // pt->SetLineColor(5);
   // pt->SetTextColor(5);
   pt->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta");
   pt->InsertText(TString::Format("slop  = %.3f #pm %.3f",  p0.getVal(), p0.getError()));
//    pt->InsertText(TString::Format("#sigma = %.3f #pm %.3f", p1.getVal(), p1.getError()));
   pt->InsertText(TString::Format("#chi^{2}/ndf = %.2f", frame->chiSquare()/2.0));
   pt->SetTextAlign(12);
   pt->SetTextSize(0.04);
   

   pt->Draw();
   canv1->Update();


   canv1->SaveAs("pullfit.png");
   canv1->SaveAs("pullfit.pdf");


    
 
   return;
}
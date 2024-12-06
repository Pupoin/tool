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
   // x.setBins(10);
   int bin=5;
 

    // Construct gaussx(x,mx,1)
    // RooRealVar mean("mean", "mean", 5.7821e-01, -1, 1);
    // RooRealVar sigma("sigma", "sigma", 1, 0, 3);
    // RooGaussian gauss("gauss", "gauss", x, mean, sigma);

    // RooRealVar poly_c1("poly_c1", "coefficient of x^1 term", 0, ­-2, 2);
    // RooPolyVar poly_c1("poly_c1", "coefficient of x^1 term", 0, ­-2, 2);

    // RooRealVar x(“x”,”x”,0.,1.) ;
    RooRealVar p0("p0","p0",1) ;
    RooRealVar p1("p1","p1",-20, -1000000, 10000) ;
    // // RooRealVar p2("p2","p2",3.0) ;
    // RooFormulaVar funcpol("f","polynomial",x,RooArgList(p0,p1)) ;
    // RooFormulaVar funcpol("f","exp(foo)*sqrt(bar)", RooArgList(foo,bar)) ;
   //  RooPolynomial poly("poly", "cubic polynomial", x, RooArgList(p0,p1) );


   // RooRealVar x("x", "x", -15, 15);
  RooRealVar a1("a1", "a1", -0.5, -10., 20.);
//   RooRealVar a2("a2", "a2", 0.2, -10., 20.);
//   RooRealVar a3("a3", "a3", 0.01);
  RooPolynomial poly("pol3", "c + a1 * x ", x, RooArgSet(a1));


    TChain *chain_data = new TChain("tree");
    chain_data->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/decay_asymmetry/total_Costheta_sigma.root");
    chain_data->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2_eta3pi/decay_asymmetry/total_Costheta_sigma.root");
    TH1F *histo = new TH1F("histo","histo", bin, -1, 1);
    chain_data->Project("histo", "Costheta_sigma", "M_BC_r3c>2.276 && M_BC_r3c<2.3");
    
    // sideband 
    TChain *chain_sd1 = new TChain("tree");
    TChain *chain_sd2 = new TChain("tree");
    chain_sd1->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/decay_asymmetry/total_Costheta_sigma.root");
    chain_sd2->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2_eta3pi/decay_asymmetry/total_Costheta_sigma.root");
    TH1F *histo_sideband1 = new TH1F("histo_sideband1","histo_sideband1", bin, -1, 1);
    TH1F *histo_sideband2 = new TH1F("histo_sideband2","histo_sideband2", bin, -1, 1);
    chain_sd1->Project("histo_sideband1", "Costheta_sigma", "(M_BC_r3c>2.25 && M_BC_r3c<2.27) || (M_BC_r3c>2.30 && M_BC_r3c<2.32)");
    chain_sd2->Project("histo_sideband2", "Costheta_sigma", "(M_BC_r3c>2.25 && M_BC_r3c<2.27) || (M_BC_r3c>2.30 && M_BC_r3c<2.32)");

    histo_sideband1->Scale(0.667968);
    histo_sideband2->Scale(0.57683);

    histo->Add(histo_sideband1);
    histo->Add(histo_sideband2);

    RooDataHist *dh = new RooDataHist("dh","binned version of d",RooArgSet(x),Import(*histo)) ;

 
   // F i t   p a r t i a l   r a n g e
   // ---------------------------------- 
   x.setRange("signal", -1, 1);

   // Fit pdf to all data
   RooFitResult *r_full = poly.fitTo(*dh, Save(kTRUE), Range("signal"));
 
   // P l o t   /   p r i n t   r e s u l t s
   // ---------------------------------------
 
   // Make plot frame in x and add data and fitted model
   RooPlot *frame = x.frame(Title( " "));
   dh->plotOn(frame);
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
   pt->InsertText(TString::Format("#alpha_{#Sigma^{+}#eta}#alpha_{p#pi^{0}} = %.3f #pm %.3f",  a1.getVal(), a1.getError()));
//    pt->InsertText(TString::Format("#sigma = %.3f #pm %.3f", p1.getVal(), p1.getError()));
   // pt->InsertText(TString::Format("#chi^{2}/ndf = %.2f", frame->chiSquare()/2.0));
   pt->SetTextAlign(12);
   pt->SetTextSize(0.04);
   
   // cout << 

   pt->Draw();
   canv1->Update();


   canv1->SaveAs("pullfit.png");
   canv1->SaveAs("pullfit.pdf");


    
 
   return;
}
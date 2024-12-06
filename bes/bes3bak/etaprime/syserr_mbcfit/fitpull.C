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
 
void fitpull()
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
   // S e t u p   m o d e l
   // ---------------------
 
   // Construct observables x
   RooRealVar x("pull", "pull", -6, 6);
 

    // Construct gaussx(x,mx,1)
    RooRealVar mean("mean", "mean", 5.7821e-02, -1, 1);
    RooRealVar sigma("sigma", "sigma", 1, 0, 3);
    RooGaussian gauss("gauss", "gauss", x, mean, sigma);


    TChain *chain_data = new TChain("tree");
    chain_data->Add("ratio.root");
   //  TTree *tree_cut = chain_data->CopyTree("kind==4 || kind==5", "", 100000000, 0);
    TTree *tree_cut = chain_data->CopyTree("", "", 100000000, 0);

    // --- Retrieve Data ---
    RooDataSet *data = new RooDataSet("data", "data", tree_cut, RooArgSet(x));


 
   // F i t   p a r t i a l   r a n g e
   // ---------------------------------- 
   // x.setRange("signal", -3, 4);

   // Fit pdf to all data
   RooFitResult *r_full = gauss.fitTo(*data, Save(kTRUE), Range("signal"));
 
   // P l o t   /   p r i n t   r e s u l t s
   // ---------------------------------------
 
   // Make plot frame in x and add data and fitted model
   RooPlot *frame = x.frame(Title(" "), Bins(15));
   data->plotOn(frame);
   gauss.plotOn(frame, LineStyle(kDashed), LineColor(kRed)); // Add shape in full ranged dashed
   gauss.plotOn(frame);                                                     // By default only fitted range is shown
 
   // Print fit results
   cout << "result of fit on all data " << endl;
   r_full->Print();


 
   // Draw frame on canvas
   // TCanvas *c = new TCanvas("rf203_ranges", "rf203_ranges", 800, 600);
   gPad->SetLeftMargin(0.15);
   // frame->GetYaxis()->SetTitleOffset(1.);
   // frame->GetXaxis()->SetTitleOffset(0.8);
   frame->GetYaxis()->SetTitleSize(0.06);
   frame->GetXaxis()->SetTitleSize(0.06);
   frame->SetLabelSize(0.045, "xy");
   frame->GetYaxis()->SetMaxDigits(3);
   frame->Draw();



   TPaveText *pt = new TPaveText(0.16, 0.62, 0.45, 0.87, "blNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   // pt->SetLineColor(5);
   // pt->SetTextColor(5);
   pt->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta'");
   pt->InsertText(TString::Format("#mu  = %.3f #pm %.3f",  mean.getVal(), sigma.getError()));
   pt->InsertText(TString::Format("#sigma = %.3f #pm %.3f", sigma.getVal(), sigma.getError()));
   pt->InsertText(TString::Format("#chi^{2}/ndf = %.2f", frame->chiSquare()/2.0));
   pt->SetTextAlign(12);
   pt->SetTextSize(0.04);
   

   pt->Draw();
   canv1->Update();


   canv1->SaveAs("pullfit.png");
   canv1->SaveAs("pullfit.pdf");


    
 
   return;
}
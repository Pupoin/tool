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
   gStyle->SetOptFit(1);
   // S e t u p   m o d e l
   // ---------------------
 
   // Construct observables x
   RooRealVar x("pull", "pull", -5, 5);
 

    // Construct gaussx(x,mx,1)
    RooRealVar mean("mean", "mean", 5.7821e-01, -1, 1);
    RooRealVar sigma("sigma", "sigma", 1, 0, 3);
    RooGaussian gauss("gauss", "gauss", x, mean, sigma);


    TChain *chain_data = new TChain("tree");
    chain_data->Add("ratio.root");
    // --- Retrieve Data ---
    RooDataSet *data = new RooDataSet("data", "data", chain_data, RooArgSet(x));


 
   // F i t   p a r t i a l   r a n g e
   // ---------------------------------- 
   // x.setRange("signal", -3, 4);

   // Fit pdf to all data
   RooFitResult *r_full = gauss.fitTo(*data, Save(kTRUE), Range("signal"));
 
   // P l o t   /   p r i n t   r e s u l t s
   // ---------------------------------------
 
   // Make plot frame in x and add data and fitted model
   RooPlot *frame = x.frame(Title("Fitting a sub range"), Bins(20));
   data->plotOn(frame);
   gauss.plotOn(frame, LineStyle(kDashed), LineColor(kRed)); // Add shape in full ranged dashed
   gauss.plotOn(frame);                                                     // By default only fitted range is shown
 
   // Print fit results
   cout << "result of fit on all data " << endl;
   r_full->Print();


 
   // Draw frame on canvas
   TCanvas *c = new TCanvas("rf203_ranges", "rf203_ranges", 800, 600);
   gPad->SetLeftMargin(0.15);
   frame->GetYaxis()->SetTitleOffset(1.);
   frame->GetXaxis()->SetTitleOffset(0.8);
   frame->GetYaxis()->SetTitleSize(0.05);
   frame->GetXaxis()->SetTitleSize(0.05);
   frame->Draw();



   TPaveText *pt = new TPaveText(0.16, 0.72, 0.45, 0.87, "blNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   // pt->SetLineColor(5);
   // pt->SetTextColor(5);
   pt->InsertText(TString::Format("mean  = %.3f #pm %.3f",  mean.getVal(), sigma.getError()));
   pt->InsertText(TString::Format("sigma = %.3f #pm %.3f", sigma.getVal(), sigma.getError()));
   pt->InsertText(TString::Format("#chi^{2}/ndf = %.2f", frame->chiSquare()/2.0));
   pt->SetTextAlign(12);

   pt->Draw();
   c->Update();


   c->SaveAs("pullfit.png");


    
 
   return;
}
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

void singleFit(int index);

string energy[] = {"4600", "4612", "4620", "4640", "4660", "4680", "4700"};
string energy2[] = {"4600", "4612", "4626", "4640", "4660", "4680", "4700"};
double endpoint[]={ 2.299765, 2.30579 , 2.31387, 2.320255 , 2.33046 , 2.34079, 2.34919 };

void fiteffic()
{

   for(int i=0; i<7 ; i++)
   {
      singleFit(i);
      
   }
   

   

}


void singleFit(int index)
{
   gStyle->SetOptFit(1);
   // S e t u p   m o d e l
   // ---------------------
 
   // Construct observables x
   // RooRealVar x("eff_norm4600", "eff_norm4600", -0.005, 0.004);

   string name = "eff_norm"+ energy[index];
   RooRealVar x(name.c_str(), name.c_str(), -0.006, 0.006);

    // Construct gaussx(x,mx,1)
    RooRealVar mean("mean", "mean", 5.7821e-04, -0.005, 0.005);
    RooRealVar sigma("sigma", "sigma", 0.001, 0, 0.01);
    RooGaussian gauss("gauss", "gauss", x, mean, sigma);


   TChain *chain_data = new TChain("tree");
   chain_data->Add("effic_addBr.root");
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
   RooPlot *frame = x.frame(Title(" "), Bins(15));
   data->plotOn(frame);
   gauss.plotOn(frame, LineStyle(kDashed), LineColor(kRed)); // Add shape in full ranged dashed
   gauss.plotOn(frame);                                                     // By default only fitted range is shown
   frame->SetXTitle("#varepsilon - #varepsilon_{normal}");

   // Print fit results
   cout << "result of fit on all data " << endl;
   r_full->Print();


 
   // Draw frame on canvas
   TCanvas *c = new TCanvas("rf203_ranges", "rf203_ranges", 700, 600);
   gPad->SetMargin(0.15, 0.05, 0.15, 0.1);
   // frame->GetYaxis()->SetTitleOffset(1.);
   // frame->GetXaxis()->SetTitleOffset(0.8);
   frame->SetTitleSize(0.06, "xy");
   frame->SetLabelSize(0.045, "xy");
   frame->GetYaxis()->SetMaxDigits(3);
   // frame->GetXaxis()->SetMaxDigits(1);
   frame->Draw();



   TPaveText *pt = new TPaveText(0.16, 0.62, 0.4, 0.87, "blNDC");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   // pt->SetLineColor(5);
   // pt->SetTextColor(5);
   pt->InsertText(TString::Format("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta, #sqrt{s}=%.3f GeV", endpoint[index]*2));
   // pt->InsertText(TString::Format("#mu  = %.6f #pm %.6f",  mean.getVal(), sigma.getError()));
   // pt->InsertText(TString::Format("#sigma = %.6f #pm %.6f", sigma.getVal(), sigma.getError()));
   pt->InsertText(TString::Format("#mu  = %.1e ",  mean.getVal()));
   pt->InsertText(TString::Format("#sigma = %.1e", sigma.getVal()));
   // pt->InsertText(TString::Format("#chi^{2}/ndf = %.2f", frame->chiSquare()/2.0));
   pt->SetTextAlign(12);
   pt->SetTextSize(0.035);

   pt->Draw();
   c->Update();


   c->SaveAs(("eff_norm" + energy[index] +  "fit.png").c_str());


    
 
   return;
}
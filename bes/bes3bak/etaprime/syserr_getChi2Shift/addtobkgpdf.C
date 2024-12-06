#include "RooAbsPdf.h"
#include "TSystem.h"
#include "TTree.h"
#include "iostream"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <vector>
using namespace RooFit;
using namespace ROOT;
void DrawModelPdf(RooRealVar *var, RooAbsPdf *pdf)
{
  RooPlot *frame = var->frame(
      Title("Adaptive kernel estimation pdf with and w/o mirroring"), Bins(25));
  pdf->plotOn(frame, LineStyle(kDashed), LineColor(kRed));
  // //   data->plotOn(frame);
  frame->Draw();
}


int addtobkgpdf()
{
  // gROOT->SetBatch(kTRUE); // same to root -b  

  RooRealVar *chi2_min_r3c = new RooRealVar("chi2_min_r3c", "chi2_min_r3c", 0, 150, "");

  // bkg pdf ______________________________________
  TFile *file_LL_pdf = TFile::Open("allchi2_LLbkgpdf.root");
  RooWorkspace *wspace1 = (RooWorkspace *)file_LL_pdf->Get("wspace");
  chi2_min_r3c = wspace1->var("chi2_min_r3c");
  RooAbsPdf *LLPdf = wspace1->pdf("modelPdf");
  LLPdf->SetName("LLpdf");


  TFile *file_hadron_pdf = TFile::Open("allchi2_hadronbkgpdf.root");
  RooWorkspace *wspace2 = (RooWorkspace *)file_hadron_pdf->Get("wspace");
  chi2_min_r3c = wspace2->var("chi2_min_r3c");
  RooAbsPdf *hadronPdf = wspace2->pdf("modelPdf");
  hadronPdf->SetName("hadronpdf");
  //    double factor[2] = {0.030, 0.045}; 2:3
  RooRealVar frLL("frLL", "frLL", 41.477);
  RooRealVar frhardon("frhardon", "frhardon", 261.144);
  RooAddPdf *bkgPdf = new RooAddPdf("bkgPdf", "bkgPdf", RooArgList(*LLPdf, *hadronPdf), RooArgList(frLL,frhardon));

  // save new bkg pdf 
  RooWorkspace *wspace_s = new RooWorkspace("wspace", "wspace title");
  wspace_s->import(*bkgPdf) ;
  // getattr(wspace,'import')(shapepdf)
  wspace_s->writeToFile("allchi2_bkgpdf.root");



  //////---------------------------------------------------------
  //////// ------------------- draw --------------------
  // draw 1-=----------------------------
  // ----------=----------------------------
  TCanvas *canv1 = new TCanvas("canv1", "mBC", 800, 600);
  canv1->SetFillColor(0);
  canv1->SetFrameFillColor(0);
  canv1->SetTopMargin(0.13);
  canv1->SetBottomMargin(0.13);
  canv1->SetLeftMargin(0.13);
  canv1->SetRightMargin(0.13);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);  RooPlot *frame = chi2_min_r3c->frame();
  double xmin = 0, xmax = 100;
  Int_t xbins = 100;
  TH1::SetDefaultSumw2(1);
  TString a("Events/");
  char b[100];
  sprintf(b, "(%g", (xmax - xmin) / xbins ); 
  TString c(")");
  TString ytitle = a + b + c;

  // bkgPdf->plotOn(frame) ;
  bkgPdf->plotOn(frame, LineColor(kRed),LineWidth(6));
  bkgPdf->plotOn(frame, Components("hadronpdf"), LineStyle(2), LineWidth(6), LineColor(kBlue));
  bkgPdf->plotOn(frame, Components("LLpdf"),  LineStyle(2), LineWidth(6), LineColor(kGreen));
    
  frame->GetYaxis()->SetTitle(ytitle);
  // hStack->GetYaxis()->SetTitleOffset(0.75);
  frame->GetYaxis()->SetTitleSize(0.05);
  // hStack->GetYaxis()->SetRange(0, 100);
  frame->SetMinimum(0.);
  // double hist_max = hStack->GetMaximum() > hist_data->GetMaximum() ? hStack->GetMaximum():hist_data->GetMaximum();
  frame->GetXaxis()->SetTitle("#chi^{2}");
  // hStack->GetXaxis()->SetTitleOffset(1.0);
  frame->GetXaxis()->SetTitleSize(0.05);


  canv1->cd();
  frame->Draw("AP");
  canv1->Update();
  canv1->SaveAs("bkg.png");

  // draw 2 -=----------------------------
  // ----------=----------------------------
  TCanvas *c2 = new TCanvas("c2", "c2", 800, 600);
  c2->cd();
  TFile *file_bkg_pdf = TFile::Open("allchi2_bkgpdf.root");
  RooWorkspace *wspacea = (RooWorkspace *)file_bkg_pdf->Get("wspace");
  chi2_min_r3c = wspacea->var("chi2_min_r3c");
  RooAbsPdf *bkgPdfa = wspacea->pdf("bkgPdf");


  RooPlot *frame2 = chi2_min_r3c->frame();
  // bkgPdf->plotOn(frame) ;
  bkgPdfa->plotOn(frame2, LineWidth(2));
  frame2->Draw();
  c2->Update();

  return 0;
}



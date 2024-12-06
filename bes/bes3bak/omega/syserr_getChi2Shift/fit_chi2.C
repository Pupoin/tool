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

void DrawModelPdf(RooRealVar *var, RooAbsPdf *pdf);

Double_t xmin = 0;
Double_t xmax = 100;
Double_t xbins = 40;
Double_t mbcmin = 2.25;
Double_t mbcmax = 2.34919;
RooRealVar *chi2_min_r3c = new RooRealVar("chi2_min_r3c", "chi2_min_r3c", xmin, xmax, "");

int fit_chi2()
{
  gROOT->SetBatch(kTRUE); // same to root -b

  TH1::SetDefaultSumw2(1);
  TString a("Events/");
  char b[20];
  sprintf(b, "(%1.0f", (xmax - xmin) / xbins );
  TString d(")");
  TString ytitle = a + b + d;

  // __________________ cut _________________________
  TCut cut_np = "(np !=0 && npbar != 0)";
  // TCut cut = "(refm>=0.115&&refm<=0.15) && (refmORsigm1m>=0.115&&refmORsigm1m<=0.15) && (sigmam>=1.174 && sigmam<=1.2) && (dipim<0.48 || dipim>0.52)";
  TCut cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919))";
  // TCut cut_deltaE_ref = "((deltaE_min>-0.033) && (deltaE_min<0.022))";
  // TCut cut_deltaE_sig = "((deltaE_min>-0.021) && (deltaE_min<0.015))";
  // TCut cut_chi2 = "(chi2_min_r3c< 29)";
  // TCut cut_ref = (cut_mbc && "(chi2_min_r3c<100) && (dipim<0.44 || dipim>0.52)" && cut_np);
  TCut cut_sig = (cut_mbc && cut_np);
  // RooRealVar *chi2_min_r3c = new RooRealVar("chi2_min_r3c", "chi2_min_r3c", mbcmin, mbcmax);  


  // get the data ___________________________________
  TChain *chain_data = new TChain("tree");
  //chain_data->Add("4600data_mass.root");
  chain_data->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/tightcut_r3c_minomega/data.root");
  TTree *tree_cut = chain_data->CopyTree(cut_sig, "", 100000000, 0);
  Int_t nentries = (Int_t)tree_cut->GetEntries();
  // --- Retrieve Data ---
  RooDataSet *data = new RooDataSet("data", "data", tree_cut, RooArgSet(*chi2_min_r3c));

  // get the shape pdf_______________________________
  // TChain *chain_shape = new TChain("tree");
  // chain_shape->Add("../shape/cutmassroot/zhou/4600shape_mass.root");
  // TTree *tr_fit = chain_shape->CopyTree(cut_sum1, "");
  // RooRealVar *chi2_min_r3c = new RooRealVar("chi2_min_r3c", "chi2_min_r3c", 2.25, 2.299765, "");
  // RooDataSet *shape = new RooDataSet("shape", "mBC(GeV)", tr_fit, RooArgSet(*chi2_min_r3c));
  // RooKeysPdf *modelPdf = new RooKeysPdf("modelPdf", "", *chi2_min_r3c, *shape, RooKeysPdf::NoMirror);
  TFile *file_sig_pdf = TFile::Open("allchi2_shapepdf.root");
  RooWorkspace *wspace = (RooWorkspace *)file_sig_pdf->Get("wspace");
  chi2_min_r3c = wspace->var("chi2_min_r3c");
  RooAbsPdf *modelPdf = wspace->pdf("modelPdf");
  // modelPdf->SetName("sig")

  // Gauss definition________________________________
  RooRealVar mean("mean", "mean", 7.8313e-02, -1, 1);
  RooRealVar sigma("sigma", "sigma", 3.4895e-02, 0, 0.5);
  RooGaussian gauss("gauss", "gauss", *chi2_min_r3c, mean, sigma);

  // convoluted shapePdf with gauss__________________
  RooAbsPdf *SignalPdf = new RooFFTConvPdf("SignalPdf", "modelPdf (X) gauss", *chi2_min_r3c, *modelPdf, gauss);
  

  // bkg pdf ______________________________________
  // TFile *file_bkg_pdf = TFile::Open("allchi2_bkgpdf.root");
  // RooWorkspace *wspace2 = (RooWorkspace *)file_bkg_pdf->Get("wspace");
  // chi2_min_r3c = wspace2->var("chi2_min_r3c");
  // RooAbsPdf *bkgPdf = wspace2->pdf("bkgPdf");

  TFile *file_LL_pdf = TFile::Open("allchi2_LLbkgpdf.root");
  RooWorkspace *wspace1 = (RooWorkspace *)file_LL_pdf->Get("wspace");
  chi2_min_r3c = wspace1->var("chi2_min_r3c");
  RooAbsPdf *LLPdf = wspace1->pdf("modelPdf"); LLPdf->SetName("LLBKGpdf");

  TFile *file_hadron_pdf = TFile::Open("allchi2_hadronbkgpdf.root");
  RooWorkspace *wspace2 = (RooWorkspace *)file_hadron_pdf->Get("wspace");
  chi2_min_r3c = wspace2->var("chi2_min_r3c");
  RooAbsPdf *hadronPdf = wspace2->pdf("modelPdf"); hadronPdf->SetName("hadronBKGpdf");

  RooRealVar frLL("frLL", "frLL", 0.1, 0, 1);
  RooRealVar frhardon("frhardon", "frhardon", 0.3, 0,1);
  RooAddPdf *bkgPdf = new RooAddPdf("bkgPdf", "bkgPdf", RooArgList(*LLPdf, *hadronPdf), RooArgList(frLL,frhardon));


  //  Signal + Background Pdf _______________________
  RooRealVar nsig("nsig", "#sig events", 0.05 * nentries, 0.0, 1.2 * nentries);
  //RooRealVar nsig("nsig", "#sig events", 0);
  RooRealVar nbkg("nbkg", "#bkg events", 0.05 * nentries, 0.0, 1.2 * nentries);
  RooAddPdf sumpdf("sumpdf", "sumpdf", RooArgList(*SignalPdf, *bkgPdf), RooArgList(nsig, nbkg));
  
  
  //  Fit ___________________________________________
  chi2_min_r3c->setRange("fitrange", xmin, xmax);
  RooFitResult *m_fitres(0);
  m_fitres = sumpdf.fitTo(*data, Save(kTRUE), Extended(kTRUE));
  m_fitres->Print("v");

  //   Draw _________________________________________
  RooPlot *frame = chi2_min_r3c->frame(xmin, xmax, xbins);
  data->plotOn(frame, LineWidth(2));
  sumpdf.plotOn(frame, LineColor(kRed),LineWidth(6));
  sumpdf.plotOn(frame, Components("SignalPdf"), LineStyle(2), LineWidth(6), LineColor(kBlue));
  sumpdf.plotOn(frame, Components("hadronBKGpdf"),  LineStyle(2), LineWidth(6), LineColor(kGreen));
  sumpdf.plotOn(frame, Components("LLBKGpdf"),  LineStyle(2), LineWidth(6), LineColor(kOrange));

  // sumpdf.paramOn(frame, Parameters(RooArgList(nsig, nbkg)),
  //  Layout(0.15, 0.4, 0.9));

  frame->GetYaxis()->SetTitle(ytitle);
  // hStack->GetYaxis()->SetTitleOffset(0.75);
  frame->SetTitleSize(0.06, "xy");
  frame->SetLabelSize(0.045, "xy");
  // hStack->GetYaxis()->SetRange(0, 100);
  frame->SetMinimum(0.);
  // double hist_max = hStack->GetMaximum() > hist_data->GetMaximum() ? hStack->GetMaximum():hist_data->GetMaximum();
  frame->GetXaxis()->SetTitle("#chi^{2}");
  // hStack->GetXaxis()->SetTitleOffset(1.0);
  frame->GetXaxis()->SetTitleSize(0.05);


  frame->SetTitle("");

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
      // setPad();

  frame->Draw();
  TPaveText *pt = new TPaveText(0.55, 0.65, 0.84, 0.84, "blNDC");
  pt->SetBorderSize(0);
  pt->SetFillColor(0);
  // pt->SetLineColor(5);
  // pt->SetTextColor(5);
  TText *text = pt->AddText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #omega");
  pt->Draw();
  canv1->Update();

  sumpdf.Print("t");
  cout << "chi2/ndf = " << frame->chiSquare()/2.0 << endl;


  canv1->SaveAs("fitresult.png");
  canv1->SaveAs("fitresult.pdf");
  return 0;
}

void DrawModelPdf(RooRealVar *var, RooAbsPdf *pdf)
{
  RooPlot *frame = var->frame(
      Title("Adaptive kernel estimation pdf with and w/o mirroring"), Bins(25));
  pdf->plotOn(frame, LineStyle(kDashed), LineColor(kRed));
  // //   data->plotOn(frame);
  frame->Draw();
}

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

void DrawModelPdf(RooRealVar *var, RooAbsPdf *pdf);

RooRealVar *M_BC = new RooRealVar("M_BC", "M_BC", 2.25, 2.34919, "");

int fitInclusive4680()
{
  Double_t xmin = 2.25, xmax = 2.34079;
  Double_t   xbins = 100;
  TH1::SetDefaultSumw2(1);
  TString a("Events/");
  char b[20];
  sprintf(b, "(%5.1f", (xmax - xmin) / xbins * 1000);
  TString d(" MeV/c^{2})");
  TString ytitle = a + b + d;

  // __________________ cut _________________________
  // TCut cut_np = "(np !=0 && npbar != 0)";
  TCut cut_deltaE = "((deltaE_min>-0.02) && (deltaE_min<0.015))";
  //TCut cut_chi2 = "(chi2_min_r1c<13)";
  TCut cut_mbc = "((M_BC>=2.25) && (M_BC<=2.34079))";
  TCut cut_sum1 = (cut_deltaE && cut_mbc);
  

  // get the data _______________________________
  TChain *chain_data = new TChain("tree");
  chain_data->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/signal/cutmassroot/tightcut_zhou2me/4680signal_removedouble.root");
  TTree *tree_cut = chain_data->CopyTree(cut_sum1, "", 100000000, 0);
  Int_t nentries = (Int_t)tree_cut->GetEntries();
  // --- Retrieve Data ---
  RooDataSet *data = new RooDataSet("data", "data", tree_cut, RooArgSet(*M_BC));

  // get the shape pdf_______________________________
  // TChain *chain_shape = new TChain("tree");
  // chain_shape->Add("../shape/cutmassroot/tightcut_zhou2me/4680shape_removedouble.root");
  // TTree *tr_fit = chain_shape->CopyTree(cut_sum1, "");
  // RooRealVar *M_BC = new RooRealVar("M_BC", "M_BC", 2.25, 2.34079, "");
  // RooDataSet *shape = new RooDataSet("shape", "mBC(GeV)", tr_fit, RooArgSet(*M_BC));
  // RooKeysPdf *modelPdf = new RooKeysPdf("modelPdf", "", *M_BC, *shape, RooKeysPdf::NoMirror);
  TFile *file_sig_pdf = TFile::Open("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_zhou2me/4680_ref_shapepdf.root");
  RooWorkspace *wspace = (RooWorkspace *)file_sig_pdf->Get("wspace");
  M_BC = wspace->var("M_BC");
  RooAbsPdf *modelPdf = wspace->pdf("modelPdf");

  // Gauss definition_______________________________
  RooRealVar sigma("sigma", "sigma", 0.0003076298, -0.00, 0.003);
  RooRealVar mean("mean", "mean", 0, -0.001, 0.001);
  RooGaussian gauss("gauss", "gauss", *M_BC, mean, sigma);

  // convoluted shapePdf with gauss_________________
  RooAbsPdf *SignalPdf = new RooFFTConvPdf("SignalPdf", "modelPdf (X) gauss", *M_BC, *modelPdf, gauss);
  

  // argus pdf _______________________________
  RooRealVar m0("m0", "m0", 2.34079);
  RooRealVar p("p", "p", 1);
  RooRealVar c("c", "c", -10, -100, 100);
  RooAbsPdf *argus = new RooArgusBG("argus", "argus", *M_BC, m0, c, p);

  //  Signal + Background Pdf _______________________________
  RooRealVar nsig("nsig", "#sig events", 0.05 * nentries, 0.0, 1.2 * nentries);
  RooRealVar nbkg("nbkg", "#bkg events", 0.05 * nentries, 0.0, 1.2 * nentries);
  RooAddPdf sumpdf("sumpdf", "sumpdf", RooArgList(*SignalPdf, *argus), RooArgList(nsig, nbkg));
  
  
  //  Fit _______________________________
  RooFitResult *m_fitres(0);
  m_fitres = sumpdf.fitTo(*data, Save(kTRUE), Extended(kTRUE));
  m_fitres->Print("v");

  //   Draw _______________________________
  RooPlot *frame = M_BC->frame(xmin, xmax, xbins);
  data->plotOn(frame, LineWidth(2));
  sumpdf.plotOn(frame, LineColor(kRed), LineWidth(6));
  sumpdf.plotOn(frame, Components("SignalPdf"), LineStyle(2), LineWidth(6), LineColor(kBlue));
  sumpdf.plotOn(frame, Components("*argus"), LineStyle(2), LineWidth(6), LineColor(kGreen));


  frame->GetXaxis()->SetTitle("M_{BC} (GeV/c^{2})");
  frame->GetYaxis()->SetTitle(ytitle);
  frame->SetTitle("");
  TCanvas *c1 = new TCanvas("c1", "c1", 1024, 768);
  frame->Draw();


  sumpdf.Print("t");
  M_BC->setRange("signal", 2.25, 2.34079);
  RooAbsReal *isig = SignalPdf->createIntegral(*M_BC, NormSet(*M_BC), Range("signal"));
  RooAbsReal *ibkg = argus->createIntegral(*M_BC, NormSet(*M_BC), Range("signal"));

  double ISIG = isig->getVal() * nsig.getVal();
  double ISIGerr = isig->getVal() * nsig.getError();
  double IBKG = ibkg->getVal() * nbkg.getVal();
  double IBKGerr = ibkg->getVal() * nbkg.getError();
  double par1 = sigma.getVal();
  double par2 = mean.getVal();
  std::cout << " nsignal " << ISIG << " +- " << ISIGerr <<  " nsig " << nsig.getVal() << " isig->getVal()" << isig->getVal() << std::endl;
  std::cout << " nbg " << IBKG << " +- " << IBKGerr << std::endl;
  cout << " chain_data->GetEntries(cut_sum1) "  << chain_data->GetEntries(cut_sum1)  <<endl;
  cout << "m_fitres->minNll(): " <<m_fitres->minNll() << endl;


  TChain *chain_datatruth = new TChain("tree_truth");
  chain_datatruth->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/signal/cutmassroot/tightcut_zhou2me/4680signal.root");
  Double_t all = chain_datatruth->GetEntries();

  TPaveText *pt = new TPaveText(0.15, 0.75, 0.38, 0.88, "blNDC");
  pt->SetBorderSize(0);
  pt->SetFillColor(0);
  // pt->SetLineColor(5);
  // pt->SetTextColor(5);
  pt->InsertText("#sqrt{s}=4682 GeV");
  pt->InsertText(TString::Format("effic = %.2f %%", ISIG/all*100.));
	pt->SetTextAlign(12);

  pt->Draw();
  c1->Update();
  c1->SaveAs("effic4682.pdf");
  c1->SaveAs("effic4682.png");

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
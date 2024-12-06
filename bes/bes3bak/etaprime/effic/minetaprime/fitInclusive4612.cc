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

RooRealVar *M_BC_1c = new RooRealVar("M_BC_1c", "M_BC_1c", 2.25, 2.34919, "");

int fitInclusive4612()
{
  Double_t xmin = 2.25, xmax = 2.30579;
  Double_t   xbins = 200;
  TH1::SetDefaultSumw2(1);
  TString a("Events/");
  char b[20];
  sprintf(b, "(%5.1f", (xmax - xmin) / xbins * 1000);
  TString d(" MeV/c^{2})");
  TString ytitle = a + b + d;

  // __________________ cut _________________________
  // TCut cut_np = "(np !=0 && npbar != 0)";
  TCut cut_deltaE = "((deltaE_min_1c>-0.023) && (deltaE_min_1c<0.02))";
  //TCut cut_chi2 = "(chi2_min_r1c<13)";
  TCut cut_mbc = "((M_BC_1c>=2.25) && (M_BC_1c<=2.30579))";
  TCut cut_sum1 = (cut_deltaE && cut_mbc);
  

  // get the data _______________________________
  TChain *chain_data = new TChain("tree");
  chain_data->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/signal/cutmassroot/minetaprime/4612signal_mass.root");
  TTree *tree_cut = chain_data->CopyTree(cut_sum1, "", 100000000, 0);
  Int_t nentries = (Int_t)tree_cut->GetEntries();
  // --- Retrieve Data ---
  RooDataSet *data = new RooDataSet("data", "data", tree_cut, RooArgSet(*M_BC_1c));

  // get the shape pdf_______________________________
  // TChain *chain_shape = new TChain("tree");
  // chain_shape->Add("../shape/cutmassroot/minetaprime/4612shape_mass.root");
  // TTree *tr_fit = chain_shape->CopyTree(cut_sum1, "");
  // RooRealVar *M_BC_1c = new RooRealVar("M_BC_1c", "M_BC_1c", 2.25, 2.30579, "");
  // RooDataSet *shape = new RooDataSet("shape", "mBC(GeV)", tr_fit, RooArgSet(*M_BC_1c));
  // RooKeysPdf *modelPdf = new RooKeysPdf("modelPdf", "", *M_BC_1c, *shape, RooKeysPdf::NoMirror);
  TFile *file_sig_pdf = TFile::Open("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/minetaprime/4612_sig_shapepdf.root");
  RooWorkspace *wspace = (RooWorkspace *)file_sig_pdf->Get("wspace");
  M_BC_1c = wspace->var("M_BC_1c");
  RooAbsPdf *modelPdf = wspace->pdf("modelPdf");

  // Gauss definition_______________________________
  RooRealVar sigma("sigma", "sigma", 1.1913e-05);//, -0.0, 0.001);
  RooRealVar mean("mean", "mean", -2.6278e-05);//, -0.001, 0.0001);
  RooGaussian gauss("gauss", "gauss", *M_BC_1c, mean, sigma);

  // convoluted shapePdf with gauss_________________
  RooAbsPdf *SignalPdf = new RooFFTConvPdf("SignalPdf", "modelPdf (X) gauss", *M_BC_1c, *modelPdf, gauss);
  

  // argus pdf _______________________________
  RooRealVar m0("m0", "m0", 2.30579);
  RooRealVar p("p", "p", 1);
  RooRealVar c("c", "c", -8.5210e+01, -200, 100);
  RooAbsPdf *argus = new RooArgusBG("argus", "argus", *M_BC_1c, m0, c, p);

  //  Signal + Background Pdf _______________________________
  RooRealVar nsig("nsig", "#sig events", 0.05 * nentries, 0.0, 1.2 * nentries);
  RooRealVar nbkg("nbkg", "#bkg events", 0.05 * nentries, 0.0, 1.2 * nentries);
  RooAddPdf sumpdf("sumpdf", "sumpdf", RooArgList(*SignalPdf, *argus), RooArgList(nsig, nbkg));
  
  
  //  Fit _______________________________
  RooFitResult *m_fitres(0);
  m_fitres = sumpdf.fitTo(*data, Save(kTRUE), Extended(kTRUE));
  m_fitres->Print("v");

  //   Draw _______________________________
  RooPlot *frame = M_BC_1c->frame(xmin, xmax, xbins);
  data->plotOn(frame, LineWidth(2));
  sumpdf.plotOn(frame, LineColor(kRed), LineWidth(4));
  sumpdf.plotOn(frame, Components("SignalPdf"), LineStyle(2), LineWidth(2), LineColor(kBlue));
  sumpdf.plotOn(frame, Components("*argus"), LineStyle(2), LineWidth(2), LineColor(kGreen));


  frame->GetXaxis()->SetTitle("M_{BC} (GeV/c^{2})");
  frame->GetYaxis()->SetTitle(ytitle);
  frame->SetTitle("");
  TCanvas *c1 = new TCanvas("c1", "c1", 1024, 768);
  frame->Draw();


  sumpdf.Print("t");
  M_BC_1c->setRange("signal", 2.25, 2.30579);
  RooAbsReal *isig = SignalPdf->createIntegral(*M_BC_1c, NormSet(*M_BC_1c), Range("signal"));
  RooAbsReal *ibkg = argus->createIntegral(*M_BC_1c, NormSet(*M_BC_1c), Range("signal"));

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
  chain_datatruth->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/signal/cutmassroot/minetaprime/4612signal.root");
  Double_t all = chain_datatruth->GetEntries();

  TPaveText *pt = new TPaveText(0.15, 0.75, 0.38, 0.88, "blNDC");
  pt->SetBorderSize(0);
  pt->SetFillColor(0);
  // pt->SetLineColor(5);
  // pt->SetTextColor(5);
  pt->InsertText("#sqrt{s}=4612 GeV");
  pt->InsertText(TString::Format("effic = %.2f %%", ISIG/all*100.));
	pt->SetTextAlign(12);

  pt->Draw();
  c1->Update();
  c1->SaveAs("effic4612.pdf");
  c1->SaveAs("effic4612.png");
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

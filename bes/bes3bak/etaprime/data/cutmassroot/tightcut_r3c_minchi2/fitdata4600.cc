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

RooRealVar *M_BC_r3c = new RooRealVar("M_BC_r3c", "M_BC_r3c", 2.25, 2.34919, "");

int fitdata4600()
{
  Double_t xmin = 2.25, xmax = 2.35;
  Double_t   xbins = 40;
  TH1::SetDefaultSumw2(1);
  TString a("Events/");
  char b[20];
  sprintf(b, "(%5.1f", (xmax - xmin) / xbins * 1000);
  TString d(" MeV/c^{2})");
  TString ytitle = a + b + d;

  // __________________ cut _________________________
  // TCut cut_np = "(np !=0 && npbar != 0)";
  TCut cut_deltaE = "(chi2_min_r3c<32)";
  // TCut cut_mass = "(etam>0.5&&etam<0.56 && pi0m>0.115&&pi0m<0.15 && sigmam>1.174&&sigmam<1.2 && etaprimem>0.946 && etaprimem<0.968)";
  //TCut cut_chi2 = "(chi2_min_r1c<13)";
  TCut cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.35))";
  TCut cut_sum1 = (cut_deltaE && cut_mbc && "np==npbar");
  

  // get the data ___________________________________
  TChain *chain_data = new TChain("tree");
  //chain_data->Add("4600data.root");
  chain_data->Add("data.root");
  TTree *tree_cut = chain_data->CopyTree(cut_sum1, "", 100000000, 0);
  Int_t nentries = (Int_t)tree_cut->GetEntries();
  // --- Retrieve Data ---
  RooDataSet *data = new RooDataSet("data", "data", tree_cut, RooArgSet(*M_BC_r3c));

  // get the shape pdf_______________________________
  // TChain *chain_shape = new TChain("tree");
  // chain_shape->Add("../shape/cutmassroot/zhou/4600shape_mass.root");
  // TTree *tr_fit = chain_shape->CopyTree(cut_sum1, "");
  // RooRealVar *M_BC_r3c = new RooRealVar("M_BC_r3c", "M_BC_r3c", 2.25, 2.35, "");
  // RooDataSet *shape = new RooDataSet("shape", "mBC(GeV)", tr_fit, RooArgSet(*M_BC_r3c));
  // RooKeysPdf *modelPdf = new RooKeysPdf("modelPdf", "", *M_BC_r3c, *shape, RooKeysPdf::NoMirror);
  TFile *file_sig_pdf = TFile::Open("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c/4600_sig_shapepdf.root");
  RooWorkspace *wspace = (RooWorkspace *)file_sig_pdf->Get("wspace");
  M_BC_r3c = wspace->var("M_BC_r3c");
  RooAbsPdf *modelPdf = wspace->pdf("modelPdf");

  // Gauss definition________________________________
  RooRealVar sigma("sigma", "sigma", 8.4505e-06, -0.0, 0.003);
  RooRealVar mean("mean", "mean", 0, -0.003, 0.003);
  RooGaussian gauss("gauss", "gauss", *M_BC_r3c, mean, sigma);

  // convoluted shapePdf with gauss__________________
  RooAbsPdf *SignalPdf = new RooFFTConvPdf("SignalPdf", "modelPdf (X) gauss", *M_BC_r3c, *modelPdf, gauss);
  

  // argus pdf ______________________________________
  RooRealVar m0("m0", "m0", 2.35);
  RooRealVar p("p", "p", 1);
  RooRealVar c("c", "c", -10, -100, 100);
  RooAbsPdf *argus = new RooArgusBG("argus", "argus", *M_BC_r3c, m0, c, p);

  //  Signal + Background Pdf _______________________
  RooRealVar nsig("nsig", "#sig events", 0.05 * nentries, 0.0, 1.2 * nentries);
  //RooRealVar nsig("nsig", "#sig events", 0);
  RooRealVar nbkg("nbkg", "#bkg events", 0.05 * nentries, 0.0, 1.2 * nentries);
  RooAddPdf sumpdf("sumpdf", "sumpdf", RooArgList(*SignalPdf, *argus), RooArgList(nsig, nbkg));
  
  
  //  Fit ___________________________________________
  RooFitResult *m_fitres(0);
  m_fitres = sumpdf.fitTo(*data, Save(kTRUE), Extended(kTRUE));
  m_fitres->Print("v");

  //   Draw _________________________________________
  RooPlot *frame = M_BC_r3c->frame(xmin, xmax, xbins);
  data->plotOn(frame, LineWidth(2));
  sumpdf.plotOn(frame, LineColor(kRed), LineWidth(6));
  sumpdf.plotOn(frame, Components("SignalPdf"), LineStyle(2), LineWidth(6), LineColor(kBlue));
  sumpdf.plotOn(frame, Components("*argus"), LineStyle(2), LineWidth(6), LineColor(kGreen));

  // sumpdf.paramOn(frame, Parameters(RooArgList(nsig, nbkg)),
  //  Layout(0.15, 0.4, 0.9));

  frame->GetXaxis()->SetTitle("M_{BC} (GeV/c^{2})");
  frame->GetYaxis()->SetTitle(ytitle);
  frame->SetTitle("");
  TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    // setPad();

  frame->Draw();
  TPaveText *pt = new TPaveText(0.15, 0.75, 0.38, 0.88, "blNDC");
  pt->SetBorderSize(0);
  pt->SetFillColor(0);
  // pt->SetLineColor(5);
  // pt->SetTextColor(5);
  TText *text = pt->AddText("E=4.600 GeV");
  pt->Draw();
  c1->Update();

  sumpdf.Print("t");

  double LOWER, UPPER;
  LOWER = 2.25;
  UPPER = 2.35;
  M_BC_r3c->setRange("signal", LOWER, UPPER);

  RooAbsReal *isig = SignalPdf->createIntegral(*M_BC_r3c, NormSet(*M_BC_r3c), Range("signal"));
  RooAbsReal *ibkg = argus->createIntegral(*M_BC_r3c, NormSet(*M_BC_r3c), Range("signal"));

  double ISIG = isig->getVal() * nsig.getVal();
  double ISIGerr = isig->getVal() * nsig.getError();
  double IBKG = ibkg->getVal() * nbkg.getVal();
  double IBKGerr = ibkg->getVal() * nbkg.getError();
  double par1 = sigma.getVal();
  double par2 = mean.getVal();
  std::cout << "nsignal " << ISIG << " +- " << ISIGerr << std::endl;
  std::cout << "nbg " << IBKG << " +- " << IBKGerr << std::endl;
  // std::cout << " sigma =" << par1 << "   " << par2 << " = mH" << std::endl;


  cout << "cut_sum1->GetEntries(cut_sum1) "  << chain_data->GetEntries(cut_sum1) << endl;
  cout << "m_fitres->minNll(): " <<m_fitres->minNll() << endl;

  // Double_t chi2 = frame->chiSquare("sumpdf","data",2);
  // cout << "chi2: " << chi2 <<endl;

  c1->SaveAs("pic_fitInclusive4600.svg");
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

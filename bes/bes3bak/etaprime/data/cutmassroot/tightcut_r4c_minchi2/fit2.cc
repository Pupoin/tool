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

int fit2()
{
  Double_t xmin = 2.25, xmax = 2.35;
  Double_t   xbins = 20;
  TH1::SetDefaultSumw2(1);
  TString a("Events/");
  char b[20];
  sprintf(b, "(%5.1f", (xmax - xmin) / xbins * 1000);
  TString d(" MeV/c^{2})");
  TString ytitle = a + b + d;

  // __________________ cut _________________________
  // TCut cut_np = "(np !=0 && npbar != 0)";
  // TCut cut_chi2 = "(chi2_min_r3c<15)";
  // TCut cut_mbc = "((M_BC_r3c_>=2.25) && (M_BC_r3c_<=2.35))";
  // // TCut cut_sum1 = (cut_chi2 && cut_mbc && cut_np && "etaprimemr_>0.91 && etaprimemr_<0.968");
  // TCut cut_sum1 = (cut_chi2 && cut_mbc && cut_np);
  

  TCut cut_np_ = "(np_ !=0 && npbar_ != 0)";
  TCut cut_chi2_ = "(chi2_min_r3c_<15)";
  TCut cut_mbc_ = "((M_BC_r3c_>=2.25) && (M_BC_r3c_<=2.35))";
  TCut cut_sum1_ = (cut_chi2_ && cut_mbc_ && cut_np_ && "etaprimemr_>0.91 && etaprimemr_<0.968");

  // get the shape pdf_______________________________
  TChain *chain_shape = new TChain("tree");
  chain_shape->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/shape/cutmassroot/tightcut_r4c_minchi2/4700shape_selB_addetap1c.root");
  TTree *tr_fit = chain_shape->CopyTree(cut_sum1_, "");
  RooRealVar *M_BC_r3c_ = new RooRealVar("M_BC_r3c_", "M_BC_r3c_", 2.25, 2.35, "");
  RooDataSet *shape = new RooDataSet("shape", "mBC(GeV)", tr_fit, RooArgSet(*M_BC_r3c_));
  RooKeysPdf *modelPdf = new RooKeysPdf("modelPdf", "", *M_BC_r3c_, *shape, RooKeysPdf::NoMirror);

  // Gauss definition_______________________________
  RooRealVar sigma("sigma", "sigma", 9.2790e-06, 0, 0.001);
  RooRealVar mean("mean", "mean", 1.1911e-03, -0.0, 0.002);
  RooGaussian gauss("gauss", "gauss", *M_BC_r3c_, mean, sigma);

  // convoluted shapePdf with gauss_________________
  RooAbsPdf *SignalPdf = new RooFFTConvPdf("sig", "modelPdf (X) gauss", *M_BC_r3c_, *modelPdf, gauss);
  
  // get the data _______________________________
  TChain *chain_data = new TChain("tree");
  chain_data->Add("data.root");

  TTree *tree_cut = chain_data->CopyTree(cut_sum1_, "");
  Int_t nentries = (Int_t)tree_cut->GetEntries();
  // --- Retrieve Data ---
  RooDataSet *data = new RooDataSet("data", "data", tree_cut, RooArgSet(*M_BC_r3c_));

  // argus pdf _______________________________
  RooRealVar m0("m0", "m0", 2.35);
  RooRealVar p("p", "p", 1);
  RooRealVar c("c", "c", -1.5449e+01, -50, 10);
  RooAbsPdf *argus = new RooArgusBG("argus", "argus", *M_BC_r3c_, m0, c, p);

  //  Signal + Background Pdf _______________________________
  RooRealVar nsig("nsig", "#sig events", 0.05 * nentries, 0.0, 1.2 * nentries);
  // RooRealVar nsig("nsig", "#sig events", 0);
  RooRealVar nbkg("nbkg", "#bkg events", 0.05 * nentries, 0.0, 1.2 * nentries);
  RooAddPdf sumpdf("sumpdf", "sumpdf", RooArgList(*SignalPdf, *argus), RooArgList(nsig, nbkg));
  
  
  //  Fit _______________________________
  RooFitResult *m_fitres(0);
  m_fitres = sumpdf.fitTo(*data, Save(kTRUE), Extended(kTRUE));
  m_fitres->Print("v");

  //   Draw _______________________________
  RooPlot *frame = M_BC_r3c_->frame();
  data->plotOn(frame, LineWidth(4), Binning(xbins));
  sumpdf.plotOn(frame, LineColor(kRed), LineWidth(6));
  sumpdf.plotOn(frame, Components("sig"), LineStyle(2), LineWidth(6), LineColor(kBlue));
  sumpdf.plotOn(frame, Components("*argus"), LineStyle(2), LineWidth(6), LineColor(kGreen));

  // sumpdf.paramOn(frame, Parameters(RooArgList(nsig, nbkg)),
  //  Layout(0.15, 0.4, 0.9));

  frame->GetXaxis()->SetTitle("M_{BC} (GeV/c^{2})");
  frame->GetYaxis()->SetTitle(ytitle);
  frame->SetTitle("");
  TCanvas *c1 = new TCanvas("c1", "c1", 1024, 768);
    // setPad();

  frame->Draw();
  TPaveText *pt = new TPaveText(0.65, 0.75, 0.88, 0.88, "blNDC");
  pt->SetBorderSize(0);
  pt->SetFillColor(0);
  // pt->SetLineColor(5);
  // pt->SetTextColor(5);
  TText *text = pt->AddText("all data");
  pt->Draw();
  c1->Update();

  //sumpdf.Print("t");

  double LOWER, UPPER;
  LOWER = 2.25;
  UPPER = 2.35;
  M_BC_r3c_->setRange("signal", LOWER, UPPER);

  RooAbsReal *isig = SignalPdf->createIntegral(*M_BC_r3c_, NormSet(*M_BC_r3c_), Range("signal"));
  RooAbsReal *ibkg = argus->createIntegral(*M_BC_r3c_, NormSet(*M_BC_r3c_), Range("signal"));

  double ISIG = isig->getVal() * nsig.getVal();
  double ISIGerr = isig->getVal() * nsig.getError();
  double IBKG = ibkg->getVal() * nbkg.getVal();
  double IBKGerr = ibkg->getVal() * nbkg.getError();
  double par1 = sigma.getVal();
  double par2 = mean.getVal();
  std::cout << " nsignal " << ISIG << " +- " << ISIGerr << std::endl;
  std::cout << " nbg " << IBKG << " +- " << IBKGerr << std::endl;
  // std::cout << " sigma =" << par1 << "   " << par2 << " = mH" << std::endl;

  cout << "m_fitres->minNll(): " <<m_fitres->minNll() << endl;
    
    // -756.454
    double sb = m_fitres->minNll(), bbb = -190.919;
    Double_t DeltaLL = 2 * fabs(sb - bbb);
    Double_t prob = TMath::Prob(DeltaLL, 1);              
    Double_t significance = sqrt(2) * TMath::ErfcInverse(prob); // ErfcInverse(x) = 1 - ErfInverse(x)
    cout << " 2ln(L) = " << DeltaLL << endl;
    cout << " significance : " << significance << endl;

  c1->SaveAs("pic_fit2.svg");
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

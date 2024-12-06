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

RooRealVar *etaprimemr3c = new RooRealVar("etaprimemr3c", "etaprimemr3c", 0.72, 0.86, "");
// double endpoint[]={2.299765, 2.30579, 2.31387, 2.320255, 2.33046,  2.34079, 2.34919 };
// string energy[] = {"4600","4612","4620","4640","4660","4680", "4700"};
// const int myindex = 0;


Double_t xmin = 0.72, xmax = 0.86;
int   xbins = 25;
int fit_omega_mc()
{
  TH1::SetDefaultSumw2(1);
  TString a("Events/");
  char b[20];
  sprintf(b, "(%5.1f", (xmax - xmin) / xbins * 1000);
  TString d(" MeV/c^{2})");
  TString ytitle = a + b + d;

  // __________________ cut _________________________
  TCut cut_np = "(np !=0 && npbar != 0)";
  // TCut cut = "(refm>=0.115&&refm<=0.15) && (refmORsigm1m>=0.115&&refmORsigm1m<=0.15) && (sigmam>=1.174 && sigmam<=1.2) && (dipim<0.48 || dipim>0.52)";
  // TCut cut_mbc = "((etaprimemr3c>=2.25) && (etaprimemr3c<=2.34919))";
  // TCut cut_deltaE_ref = "((deltaE_min>-0.033) && (deltaE_min<0.022))";
  // TCut cut_deltaE_sig = "((deltaE_min>-0.021) && (deltaE_min<0.015))";
  // TCut cut_chi2 = "(chi2_min_r3c< 29)";
  // TCut cut_ref = (cut_mbc && "(chi2_min_r3c< 30)" && cut_np);
  TCut cut_sum1 = ("(chi2_min_r3c< 30) " && cut_np );
  

  // get the data ___________________________________
  TChain *chain_data = new TChain("tree");
  //chain_data->Add("4600data.root");
  chain_data->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/hadron/cutmassroot/tightcut_r3c_minomega/4*hadron.root");
  chain_data->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/LL/cutmassroot/tightcut_r3c_minomega/4*LL.root");
  TTree *tree_cut = chain_data->CopyTree(cut_sum1 && "(signal!=1 && signal!=-1)", "", 10000000000, 0);
  Int_t nentries = (Int_t)tree_cut->GetEntries();
  // --- Retrieve Data ---
  RooDataSet *data = new RooDataSet("data", "data", tree_cut, RooArgSet(*etaprimemr3c));

  // get the shape pdf_______________________________
  // TChain *chain_shape = new TChain("tree");
  // chain_shape->Add("../shape/cutmassroot/zhou/4600shape_mass.root");
  // TTree *tr_fit = chain_shape->CopyTree(cut_sum1, "");
  // RooRealVar *etaprimemr3c = new RooRealVar("etaprimemr3c", "etaprimemr3c", 2.25, endpoint[6], "");
  // RooDataSet *shape = new RooDataSet("shape", "mBC(GeV)", tr_fit, RooArgSet(*etaprimemr3c));
  // RooKeysPdf *modelPdf = new RooKeysPdf("modelPdf", "", *etaprimemr3c, *shape, RooKeysPdf::NoMirror);
  TFile *file_sig_pdf = TFile::Open("/publicfs/ucas/user/yuanchy8/7.0.6/omega/fit/tightcut_r3c_minomega/omega_shapepdf.root");
  RooWorkspace *wspace = (RooWorkspace *)file_sig_pdf->Get("wspace");
  etaprimemr3c = wspace->var("etaprimemr3c");
  RooAbsPdf *modelPdf = wspace->pdf("modelPdf");

  // Gauss definition________________________________
  RooRealVar sigma("sigma", "sigma", 1.7419e-03, 0, 0.02);
  RooRealVar mean("mean", "mean", 1.8434e-04, -0.002, 0.002);
  RooGaussian gauss("gauss", "gauss", *etaprimemr3c, mean, sigma);

  // convoluted shapePdf with gauss__________________
  // RooAbsPdf SignalPdf("SignalPdf", "modelPdf (X) gauss", *etaprimemr3c, *modelPdf, gauss);
  RooAbsPdf *SignalPdf = new RooFFTConvPdf("SignalPdf", "modelPdf (X) gauss", *etaprimemr3c, *modelPdf, gauss);

  

  // argus pdf ______________________________________
  // RooRealVar m0("m0", "m0", 0.72);
  // RooRealVar p("p", "p", 1);
  RooRealVar c0("c0", "c0", 0.01, -0.5, 0.5);
  RooRealVar c2("c2", "c2", 0.01, -0.5, 0.5);
  RooRealVar c3("c3", "c3", 0.01, -0.5, 0.5);
  RooRealVar c4("c4", "c4", 0.01, -0.5, 0.5);
  RooRealVar c5("c5", "c5", 0.01, -0.5, 0.5);
  // RooAbsPdf *argus = new RooArgusBG("argus", "argus", *etaprimemr3c, m0, c, p);
  RooAbsPdf *argus = new RooChebychev("argus", "argus", *etaprimemr3c, 
    RooArgList(c0));
   

  //  Signal + Background Pdf _______________________
  RooRealVar nsig("nsig", "#sig events", 0.05 * nentries, 0.0, 1.2 * nentries);
  // RooRealVar nsig("nsig", "#sig events", 0);
  RooRealVar nbkg("nbkg", "#bkg events", 0.05 * nentries, 0.0, 1.2 * nentries);
  RooAddPdf sumpdf("sumpdf", "sumpdf", RooArgList(*SignalPdf, *argus), RooArgList(nsig, nbkg));
  
  
  //  Fit ___________________________________________
  RooFitResult *m_fitres(0);
  m_fitres = sumpdf.fitTo(*data, Save(kTRUE), Extended(kTRUE));
  m_fitres->Print("v");

  //   Draw _________________________________________
  RooPlot *frame = etaprimemr3c->frame(xmin, xmax, xbins);
  data->plotOn(frame, LineWidth(2));
  sumpdf.plotOn(frame, LineColor(kRed), LineWidth(6));
  sumpdf.plotOn(frame, Components("argus"), LineStyle(2), LineWidth(6), LineColor(kBlue));
  sumpdf.plotOn(frame, Components("SignalPdf"), LineStyle(2), LineWidth(6), LineColor(kGreen));

  // sumpdf.paramOn(frame, Parameters(RooArgList(nsig, nbkg)),
  //  Layout(0.15, 0.4, 0.9));

  frame->GetXaxis()->SetTitle("M_{BC} (GeV/c^{2})");
  frame->GetYaxis()->SetTitle(ytitle);
  frame->SetTitle("");
  TCanvas *c1 = new TCanvas("c1", "c1", 800, 600);
    // setPad();

  frame->Draw();
  TPaveText *pt = new TPaveText(0.56, 0.62, 0.8, 0.87, "blNDC");
  pt->SetBorderSize(0);
  pt->SetFillColor(0);
  // pt->SetLineColor(5);
  // pt->SetTextColor(5);
  // pt->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta'");
  pt->InsertText(TString::Format("#mu  = %.4f #pm %.4f MeV/c^{2}",  mean.getVal(), mean.getError()));
  pt->InsertText(TString::Format("#sigma = %.4f #pm %.4f MeV/c^{2}", sigma.getVal(), sigma.getError()));
  // pt->InsertText(TString::Format("#chi^{2}/ndf = %.2f", frame->chiSquare()/2.0));
  pt->SetTextAlign(12);
  pt->SetTextSize(0.04);

  pt->Draw();
  c1->Update();

  sumpdf.Print("t");

  // double LOWER, UPPER;
  // LOWER = 2.25;
  // UPPER = endpoint[myindex];
  // etaprimemr3c->setRange("signal", LOWER, UPPER);

  // RooAbsReal *isig = sumpdf.createIntegral(*etaprimemr3c, NormSet(*etaprimemr3c), Range("signal"));
  // RooAbsReal *ibkg = argus->createIntegral(*etaprimemr3c, NormSet(*etaprimemr3c), Range("signal"));

  // double ISIG = isig->getVal() * nsig.getVal();
  // double ISIGerr = isig->getVal() * nsig.getError();
  // double IBKG = ibkg->getVal() * nbkg.getVal();
  // double IBKGerr = ibkg->getVal() * nbkg.getError();
  // double par1 = sigma.getVal();
  // double par2 = mean.getVal();
  // std::cout << "nsignal " << ISIG << " +- " << ISIGerr << std::endl;
  // std::cout << "nbg " << IBKG << " +- " << IBKGerr << std::endl;
  // std::cout << " sigma =" << par1 << "   " << par2 << " = mH" << std::endl;


  // cout << "cut_sum1->GetEntries(cut_sum1) "  << chain_data->GetEntries(cut_sum1) << endl;
  // cout << "m_fitres->minNll(): " <<m_fitres->minNll() << endl;

  // Double_t chi2 = frame->chiSquare("sumpdf","data",2);
  // cout << "chi2: " << chi2 <<endl;

  // c1->SaveAs((energy[myindex]  + "sig.png").c_str());
  c1->SaveAs("mc.png");
  return 0;
}

void DrawModelPdf(RooRealVar *var, RooAbsPdf *pdf)
{
  RooPlot *frame = var->frame(
      Title("Adaptive kernel estimation pdf with and w/o mirroring"), Bins(xbins));
  pdf->plotOn(frame, LineStyle(kDashed), LineColor(kRed));
  // //   data->plotOn(frame);
  frame->Draw();
}

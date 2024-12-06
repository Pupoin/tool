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
double endpoint[]={2.299765, 2.30579, 2.31387, 2.320255, 2.33046,  2.34079, 2.34919 };
string energy[] = {"4600","4612","4620","4640","4660","4680", "4700"};
const int myindex = 6;


int fit_add()
{
  Double_t xmin = 2.25, xmax = endpoint[myindex];
  Double_t   xbins = 30;
  TH1::SetDefaultSumw2(1);
  TString a("Events/");
  char b[20];
  sprintf(b, "(%5.1f", (xmax - xmin) / xbins * 1000);
  TString d(" MeV/c^{2})");
  TString ytitle = a + b + d;

  // __________________ cut _________________________
  TCut cut_np = "(np !=0 && npbar != 0)";
  // TCut cut = "(refm>=0.115&&refm<=0.15) && (refmORsigm1m>=0.115&&refmORsigm1m<=0.15) && (sigmam>=1.174 && sigmam<=1.2) && (dipim<0.48 || dipim>0.52)";
  TCut cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919))";
  // TCut cut_deltaE_ref = "((deltaE_min>-0.033) && (deltaE_min<0.022))";
  // TCut cut_deltaE_sig = "((deltaE_min>-0.021) && (deltaE_min<0.015))";
  // TCut cut_chi2 = "(chi2_min_r3c< 29)";
  // TCut cut_ref = (cut_mbc && "(chi2_min_r3c< 30)" && cut_np);
  TCut cut_sum1 = (cut_mbc && "(chi2_min_r3c< 30) " && cut_np );
  

  // get the data ___________________________________
  TChain *chain_data = new TChain("tree");
  //chain_data->Add("4600data.root");
  // chain_data->Add(("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/tightcut_r3c_minetap/" + energy[myindex] + "data_selB.root").c_str());
  chain_data->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/tightcut_r3c_minetap_eta2pipipi0/*selB.root");
  TTree *tree_cut = chain_data->CopyTree(cut_sum1, "", 100000000, 0);
    
  TChain *chain_data_nominal = new TChain("tree");
  chain_data_nominal->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/tightcut_r3c_minetap/4*selB.root");
  TTree *tree_cut_nominal = chain_data_nominal->CopyTree(cut_sum1 , "", 100000000, 0);
  
  TList *list = new TList;
  list->Add(tree_cut);
  list->Add(tree_cut_nominal);
  TTree *newtree = TTree::MergeTrees(list);
  newtree->SetName("tree");

  Int_t nentries = (Int_t)newtree->GetEntries();
  // --- Retrieve Data ---
  RooDataSet *data = new RooDataSet("data", "data", newtree, RooArgSet(*M_BC_r3c));

  // get the shape pdf_______________________________
  // TChain *chain_shape = new TChain("tree");
  // chain_shape->Add("../shape/cutmassroot/zhou/4600shape_mass.root");
  // TTree *tr_fit = chain_shape->CopyTree(cut_sum1, "");
  // RooRealVar *M_BC_r3c = new RooRealVar("M_BC_r3c", "M_BC_r3c", 2.25, endpoint[6], "");
  // RooDataSet *shape = new RooDataSet("shape", "mBC(GeV)", tr_fit, RooArgSet(*M_BC_r3c));
  // RooKeysPdf *modelPdf = new RooKeysPdf("modelPdf", "", *M_BC_r3c, *shape, RooKeysPdf::NoMirror);
  // TFile *file_sig_pdf = TFile::Open(("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/"+ energy[myindex] + "_sig_shapepdf.root").c_str());
  TFile *file_sig_pdf = TFile::Open("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/4700_sig_shapepdf.root");
  RooWorkspace *wspace = (RooWorkspace *)file_sig_pdf->Get("wspace");
  M_BC_r3c = wspace->var("M_BC_r3c");
  RooAbsPdf *modelPdf = wspace->pdf("modelPdf");

  // Gauss definition________________________________
  RooRealVar sigma("sigma", "sigma", 1.7419e-05, 0, 0.0001);
  RooRealVar mean("mean", "mean", 1.8434e-04, -0.001, 0.001);
  RooGaussian gauss("gauss", "gauss", *M_BC_r3c, mean, sigma);

  // convoluted shapePdf with gauss__________________
  RooAbsPdf *SignalPdf = new RooFFTConvPdf("SignalPdf", "modelPdf (X) gauss", *M_BC_r3c, *modelPdf, gauss);
  

  // argus pdf ______________________________________
  RooRealVar m0("m0", "m0", endpoint[myindex]);
  RooRealVar p("p", "p", 1);
  RooRealVar c("c", "c", -10, -100, 100);
  RooAbsPdf *argus = new RooArgusBG("argus", "argus", *M_BC_r3c, m0, c, p);

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

  sumpdf.Print("t");

  double LOWER, UPPER;
  LOWER = 2.276;
  // UPPER = endpoint[myindex];
  UPPER = 2.293;
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
  
  // cout << "cut_sum1->GetEntries(cut_sum1) "  << chain->GetEntries(cut_sum1) << endl;
  cout << "m_fitres->minNll(): " <<m_fitres->minNll() << endl;
  
  Double_t FCN_bkg = -974.254;
  Double_t DeltaLL = 2 * fabs(m_fitres->minNll() - FCN_bkg);
  Double_t prob = TMath::Prob(DeltaLL, 1);
  Double_t nSigma = sqrt(2) * TMath::ErfcInverse(prob);
  cout << "result->minNll() " << m_fitres->minNll() << " " << "|FCN_single - FCN_bkg| = " << DeltaLL << endl;
  cout << " Sigma: " << nSigma << endl;


  TPaveText *pt = new TPaveText(0.65, 0.65, 0.88, 0.88, "blNDC");
  pt->SetBorderSize(0);
  pt->SetFillColor(0);
  // pt->SetLineColor(5);
  // pt->SetTextColor(5);
  pt->InsertText(TString::Format("signal: %.1f#pm%.1f",ISIG, ISIGerr) );
  pt->InsertText(TString::Format("bkg: %.1f#pm%.1f", IBKG, IBKGerr) );
  pt->InsertText(TString::Format("significance: %.1f #sigma" , nSigma) );


  pt->Draw();
  c1->Update();


  // c1->SaveAs((energy[myindex]  + "sig.png").c_str());
  c1->SaveAs("fit_add.png");







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

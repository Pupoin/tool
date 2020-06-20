#include "TCanvas.h"
#include "TChain.h"
#include "TCut.h"
#include "TH1D.h"
#include "THStack.h"
#include "TLegend.h"
#include "TString.h"
#include "TStyle.h"
#include <iostream>
// #include "boot.h"

using namespace std;
int plot_mode()
{

  // setStyle();
  // setPad();
  // //********************plot the mBC distributions*********************//
  TCanvas *w = new TCanvas("w", "mBC", 800, 600);
  w->SetFillColor(0);
  w->SetFrameFillColor(0);
  w->SetTopMargin(0.13);
  w->SetBottomMargin(0.13);
  w->SetLeftMargin(0.13);
  w->SetRightMargin(0.13);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);

  double xmin = 2.25, xmax = 2.3;
  double xbins = 25;
  // TH1::SetDefaultSumw2(1);
  TString a("Events/");
  char b[100];
  sprintf(b, "(%g", (xmax - xmin) / xbins * 1000);
  TString c(" MeV)");
  TString ytitle = a + b + c;

  TChain *chain_inclusive = new TChain("STag");

  chain_inclusive->Add("yinclusive_selected.root");

  TH1D *hist_inclusive_sig =
      new TH1D("hist_inclusive_sig", "m_{BC} Distribution", xbins, xmin, xmax);
  TH1D *hist_inclusive_bkg =
      new TH1D("hist_inclusive_bkg", "m_{BC} Distribution", xbins, xmin, xmax);

  TCut cut_deltaE = "((deltaE_min>-0.01) && (deltaE_min<0.01))";
  TCut cut_mbc = ""; //"((M_BC>2.282) && (M_BC<2.294))";
  TCut cut_sum1 = (cut_deltaE && cut_mbc);

  TCut cut_inclusive_sig =
      "(charge==1 && mode2==34 && Ap_id[0]==3222 && Ap_id[1]==221 && "
      "Ap_id[2]==2212 && Ap_id[3]==111 && Ap_id[4]==22 && Ap_id[5]==22 && "
      "Ap_id[6]==22 && Ap_id[7]==22) || "
      "(charge==-1 && mode2==34 && Ap_id[0]==-3222 && Ap_id[1]==221 && "
      "Ap_id[2]==-2212 && Ap_id[3]==111 && Ap_id[4]==22 && Ap_id[5]==22 &&"
      "Ap_id[6]==22 && Ap_id[7]==22)";
  TCut cut_inclusive_bkg = !cut_inclusive_sig;

  chain_inclusive->Project("hist_inclusive_bkg", "M_BC",
                           cut_inclusive_bkg && cut_sum1);
  chain_inclusive->Project("hist_inclusive_sig", "M_BC",
                           cut_inclusive_sig && cut_sum1);

  hist_inclusive_sig->SetLineColor(2);
  hist_inclusive_bkg->SetLineColor(3);

  hist_inclusive_sig->SetLineWidth(3);

  hist_inclusive_bkg->SetFillColor(3);

  w->cd();
  THStack *hs = new THStack("his", "test");
  // hs->SetMaximum(2);

  hs->Add(hist_inclusive_bkg);
  hs->Add(hist_inclusive_sig);

  // ll 199 0010, dd 1000 0000, ditau 995 0000, ISR 1000 0000, DsDSS 999 0000,
  // qqbar 10000 00000, lambdacPair ;
  //   double base = 1990010.0;
  // hist_signal->Scale(base / 1990010);
  // hist_signal->Scale(base / 1990010);
  // hist_DD->Scale(base / 20000000);
  // hist_ditau->Scale(base / 9950000);
  // hist_ISR->Scale(base / 10000000);
  // hist_qqbar->Scale(base / 10000000);

  hist_inclusive_sig->Scale(0.051);
  hist_inclusive_bkg->Scale(0.051);

  hs->Draw("HIST ");

  hs->GetYaxis()->SetTitle(ytitle);
  hs->GetYaxis()->SetTitleOffset(0.75);
  hs->GetYaxis()->SetTitleSize(0.05);
  hs->GetYaxis()->SetRange(0, 100);
  hs->SetMinimum(0.);
  hs->GetXaxis()->SetTitle("m_{BC} (GeV)");
  hs->GetXaxis()->SetTitleOffset(1.0);
  hs->GetXaxis()->SetTitleSize(0.05);

  TLegend *legend = new TLegend(0.2, 0.5, 0.45, 0.8);
  legend->SetHeader("m_{BC} Distribution");
  legend->AddEntry("hist_inclusive_sig", "signal", "f");
  legend->AddEntry("hist_inclusive_bkg", "#Lambda_{c}#bar{#Lambda_{c}} bkg",
                   "f");
  //   legend->AddEntry("hist_ISR", "ISR", "f");
  //   legend->AddEntry("hist_DD", "D_{(s)}D_{(s)}(#pi)", "f");
  //   legend->AddEntry("hist_ditau", "#tau#tau", "f");
  //   legend->AddEntry("hist_qqbar", "q#bar{q}", "f");

  legend->SetBorderSize(2);
  legend->SetFillColor(0);
  legend->Draw();

  w->Update();
  w->SaveAs("tmp_mode.svg");
  return 0;
}

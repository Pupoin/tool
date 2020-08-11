#include "TCanvas.h"
#include "TChain.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TRatioPlot.h"
#include "TString.h"
#include "TStyle.h"
#include <iostream>

using namespace std;

int plot2_wpt()
{

  TCanvas *canv = new TCanvas("canv", "", 800, 600);
  canv->SetFillColor(0);
  canv->SetFrameFillColor(0);
  canv->SetTopMargin(0.13);
  canv->SetBottomMargin(0.13);
  canv->SetLeftMargin(0.13);
  canv->SetRightMargin(0.13);
  gStyle->SetOptStat(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  canv->Divide(1, 2);

  TH1::SetDefaultSumw2(kTRUE);

  double xmin = 0, xmax = 2000;
  int xbins = 40;
  TString a("Events/");
  char b[100];
  sprintf(b, "(%g", (xmax - xmin) / xbins);
  TString c(" GeV)");
  TString ytitle = a + b + c;

  // double bins[9] = {0, 100, 200, 400, 600, 800, 1200, 2500, 5000};
  double bins[xbins + 1];
  for (int i = 0; i < xbins + 1; i++)
  {
    bins[i] = (xmax - xmin) / xbins * i;
    // cout << bins[i] << " ";
  }

  TChain *chain_70 = new TChain("test");
  TChain *chain_100 = new TChain("test");
  TChain *chain_200 = new TChain("test");
  TChain *chain_400 = new TChain("test");
  TChain *chain_600 = new TChain("test");
  TChain *chain_800 = new TChain("test");
  TChain *chain_1200 = new TChain("test");
  TChain *chain_2500 = new TChain("test");
  TChain *chain_inclusive = new TChain("test");

  chain_70->Add("../outputRoot/70to100_*ana.root");
  chain_100->Add("../outputRoot/100to200_*.root");
  chain_200->Add("../outputRoot/200to400_*ana.root");
  chain_400->Add("../outputRoot/400to600_*ana.root");
  chain_600->Add("../outputRoot/600to800_*ana.root");
  chain_800->Add("../outputRoot/800to1200_*ana.root");
  chain_1200->Add("..//outputRoot/1200to2500_*ana.root");
  chain_2500->Add("../outputRoot/2500toInf_*ana.root");
  chain_inclusive->Add("../outputRoot/inclusive_*ana.root");

  // int binWidth = 10;
  // TH1D *hist_70 = new TH1D("hist_70", "", 30/10, 70, 100);
  // TH1D *hist_100 = new TH1D("hist_100", "", 10, 100, 200);
  // TH1D *hist_200 = new TH1D("hist_200", "", 200/binWidth, 200, 400);
  // TH1D *hist_400 = new TH1D("hist_400", "", 200/binWidth, 400, 600);
  // TH1D *hist_600 = new TH1D("hist_600", "", 200/binWidth, 600, 800);
  // TH1D *hist_800 = new TH1D("hist_800", "", 400/binWidth, 800, 1200);
  // TH1D *hist_1200 = new TH1D("hist_1200", "", 1300/binWidth, 1200, 2500);
  // TH1D *hist_2500 = new TH1D("hist_2500", "", (xmax - 2500)/binWidth, 2500,
  // xmax); TH1D *hist_inclusive =
  //     new TH1D("hist_inclusive", "", (xmax - xmin) / binWidth, xmin, xmax);

  TH1D *hist_70 = new TH1D("hist_70", "", xbins, bins);
  TH1D *hist_100 = new TH1D("hist_100", "", xbins, bins);
  TH1D *hist_200 = new TH1D("hist_200", "", xbins, bins);
  TH1D *hist_400 = new TH1D("hist_400", "", xbins, bins);
  TH1D *hist_600 = new TH1D("hist_600", "", xbins, bins);
  TH1D *hist_800 = new TH1D("hist_800", "", xbins, bins);
  TH1D *hist_1200 = new TH1D("hist_1200", "", xbins, bins);
  TH1D *hist_2500 = new TH1D("hist_2500", "", xbins, bins);
  TH1D *hist_inclusive = new TH1D("hist_inclusive", "", xbins, bins);

  chain_70->Project("hist_70", "wpt");
  chain_100->Project("hist_100", "wpt");
  chain_200->Project("hist_200", "wpt");
  chain_400->Project("hist_400", "wpt");
  chain_600->Project("hist_600", "wpt");
  chain_800->Project("hist_800", "wpt");
  chain_1200->Project("hist_1200", "wpt");
  chain_2500->Project("hist_2500", "wpt");
  chain_inclusive->Project("hist_inclusive", "wpt");

  //double factor[9] = {1271.225652, 1413.463788, 417.830929, 61.446034, 14.864938, 6.813988, 1.713687, 0.042489, 3326.410892};
double factor[9] = {1314.157819 , 1411.051147 , 414.652901 , 58.93422 , 15.348104 , 7.016852 , 1.738243 , 0.041597 , 3344.844953 };
  // double factor[9] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

  cout << "70 " << hist_70->Integral() << " " << hist_70->GetEntries() << endl;
  cout << "100 " << hist_100->Integral() << " " << hist_100->GetEntries()
       << endl;
  cout << "200 " << hist_200->Integral() << " " << hist_200->GetEntries()
       << endl;
  cout << "400 " << hist_400->Integral() << " " << hist_400->GetEntries()
       << endl;
  cout << "600 " << hist_600->Integral() << " " << hist_600->GetEntries()
       << endl;
  cout << "800 " << hist_800->Integral() << " " << hist_800->GetEntries()
       << endl;
  cout << "1200 " << hist_1200->Integral() << " " << hist_1200->GetEntries()
       << endl;
  cout << "2500 " << hist_2500->Integral() << " " << hist_2500->GetEntries()
       << endl;
  cout << "inlcusive " << hist_inclusive->Integral() << " "
       << hist_inclusive->GetEntries() << endl;

  hist_70->Scale(factor[0] / hist_70->Integral());
  hist_100->Scale(factor[1] / hist_100->Integral());
  hist_200->Scale(factor[2] / hist_200->Integral());
  hist_400->Scale(factor[3] / hist_400->Integral());
  hist_600->Scale(factor[4] / hist_600->Integral());
  hist_800->Scale(factor[5] / hist_800->Integral());
  hist_1200->Scale(factor[6] / hist_1200->Integral());
  hist_2500->Scale(factor[7] / hist_2500->Integral());
  hist_inclusive->Scale(factor[8] / hist_inclusive->Integral());

  cout << "70 " << hist_70->Integral() << " " << hist_70->GetEntries() << endl;
  cout << "100 " << hist_100->Integral() << " " << hist_100->GetEntries()
       << endl;
  cout << "200 " << hist_200->Integral() << " " << hist_200->GetEntries()
       << endl;
  cout << "400 " << hist_400->Integral() << " " << hist_400->GetEntries()
       << endl;
  cout << "600 " << hist_600->Integral() << " " << hist_600->GetEntries()
       << endl;
  cout << "800 " << hist_800->Integral() << " " << hist_800->GetEntries()
       << endl;
  cout << "1200 " << hist_1200->Integral() << " " << hist_1200->GetEntries()
       << endl;
  cout << "2500 " << hist_2500->Integral() << " " << hist_2500->GetEntries()
       << endl;
  cout << "inlcusive " << hist_inclusive->Integral() << " "
       << hist_inclusive->GetEntries() << endl;

  // hist_100->Scale(factor[1] / hist_100->GetEntries());
  // hist_200->Scale(factor[2] / hist_200->GetEntries());
  // hist_400->Scale(factor[3] / hist_400->GetEntries());
  // hist_600->Scale(factor[4] / hist_600->GetEntries());
  // hist_800->Scale(factor[5] / hist_800->GetEntries());
  // hist_1200->Scale(factor[6] / hist_1200->GetEntries());
  // hist_2500->Scale(factor[7] / hist_2500->GetEntries());
  // hist_inclusive->Scale(factor[8] / hist_inclusive->GetEntries());

  TH1D *hist_binned = (TH1D *)hist_1200->Clone("hist_binned");

  hist_binned->Reset();
  TList *list = new TList;
  list->Add(hist_70);
  list->Add(hist_100);
  list->Add(hist_200);
  list->Add(hist_400);
  list->Add(hist_600);
  list->Add(hist_800);
  list->Add(hist_1200);
  list->Add(hist_2500);

  hist_binned->Merge(list);

  // hist_100->Draw();
  // hist_binned->Add(hist_70);
  // hist_binned->Add(hist_100);
  // hist_binned->Add(hist_200);
  // hist_binned->Add(hist_400);
  // hist_binned->Add(hist_600);
  // hist_binned->Add(hist_800);
  // hist_binned->Add(hist_1200);
  // hist_binned->Add(hist_2500);

  // -------------- draw --------------------
  // canv->cd(1);
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(1);
  pad1->Draw();
  pad1->cd();
  gPad->SetLogy(1);

  hist_binned->SetMinimum(0.00001);
  hist_binned->SetMaximum(50000);
  hist_binned->GetYaxis()->SetTitleSize(0.055);
  hist_binned->GetYaxis()->SetTitleOffset(0.46);

  hist_binned->GetYaxis()->SetTitle(ytitle);
  hist_binned->GetXaxis()->SetTitle("HT(GeV)");

  hist_binned->SetLineColor(1);
  // hist_binned->SetFillColor(2);
  hist_binned->SetLineWidth(1);

  hist_inclusive->SetLineColor(2);
  // hist_inclusive->SetFillColor(8);
  hist_inclusive->SetLineWidth(1);

  hist_binned->Draw("e");
  hist_inclusive->Draw("e same");
  // hist_inclusive->SetMarkerStyle(kFullCircle);

  // hist_70->Draw("HIST same");
  // hist_100->Draw("HIST same");
  // hist_200->Draw("wpt>>hist_200 same");
  // hist_400->Draw("wpt>>hist_400 same");
  // hist_600->Draw("wpt>>hist_600 same");
  // hist_800->Draw("wpt>>hist_800 same");
  // hist_1200->Draw("wpt>>hist_1200 same");
  // hist_2500->Draw("wpt>>hist_2500 same");
  // hist_inclusive->SetMinimum(0.0001);
  // hist_inclusive->GetXaxis()->SetTitle();

  // hist_70->SetFillColor(10);
  // hist_100->SetFillColor(9);
  // hist_200->SetFillColor(3);
  // hist_400->SetFillColor(12);
  // hist_600->SetFillColor(5);
  // hist_800->SetFillColor(6);
  // hist_1200->SetFillColor(7);
  // hist_2500->SetFillColor(8);

  hist_70->SetLineColor(4);
  hist_100->SetLineColor(9);
  hist_200->SetLineColor(3);
  hist_400->SetLineColor(13);
  hist_600->SetLineColor(2);
  hist_800->SetLineColor(6);
  hist_1200->SetLineColor(7);
  hist_2500->SetLineColor(8);

  hist_70->SetLineWidth(2);
  hist_100->SetLineWidth(2);
  hist_200->SetLineWidth(2);
  hist_400->SetLineWidth(2);
  hist_600->SetLineWidth(2);
  hist_800->SetLineWidth(2);
  hist_1200->SetLineWidth(2);
  hist_2500->SetLineWidth(2);

  TLegend *legend = new TLegend(0.65, 0.46, 0.85, 0.8);
  //   legend->SetHeader("m_{BC} Distribution");
  legend->AddEntry("hist_inclusive", "inclusive", "l");
  legend->AddEntry("hist_binned", "binned", "l");

  // legend->AddEntry("hist_70", "HT_70to100", "l");
  // legend->AddEntry("hist_100", "HT_100to200", "l");
  // legend->AddEntry("hist_200", "HT_200to400", "l");
  // legend->AddEntry("hist_400", "HT_400to600", "l");
  // legend->AddEntry("hist_600", "HT_600to800", "l");
  // legend->AddEntry("hist_800", "HT_800to1200", "l");
  // legend->AddEntry("hist_1200", "HT_1200to2500", "l");
  // legend->AddEntry("hist_2500", "HT_2500toInf", "l");

  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->Draw();

  //--------------------------- ratio -----------------------
  //--- Ensure no overflow events are left out of scale factor calculation
  TH1D *Hratio = (TH1D *)hist_inclusive->Clone("Hratio");
  TH1D *Hdenom = (TH1D *)hist_binned->Clone("Hdenom");

  int nbins = Hratio->GetNbinsX();
  double addoverflow =
      Hratio->GetBinContent(nbins) + Hratio->GetBinContent(nbins + 1);
  double erroverflow = sqrt(pow(Hratio->GetBinError(nbins), 2) +
                            pow(Hratio->GetBinError(nbins + 1), 2));
  Hratio->SetBinContent(nbins, addoverflow);
  Hratio->SetBinError(nbins, erroverflow);

  nbins = hist_binned->GetNbinsX();
  addoverflow =
      hist_binned->GetBinContent(nbins) + hist_binned->GetBinContent(nbins + 1);
  erroverflow = sqrt(pow(hist_binned->GetBinError(nbins), 2) +
                     pow(hist_binned->GetBinError(nbins + 1), 2));
  hist_binned->SetBinContent(nbins, addoverflow);
  hist_binned->SetBinError(nbins, erroverflow);

  Hratio->Divide(Hdenom);

  // ------ Draw ratio --------
  canv->cd();
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(1);
  pad2->SetBottomMargin(0.1);
  pad2->SetGridy(); // horizon grid
  pad2->Draw();
  pad2->cd();
  gPad->SetLogy(0);
  Hratio->SetLineColor(kBlack);
  Hratio->Draw("e");

  // Y axis ratio plot settings
  Hratio->GetYaxis()->SetTitle("#frac{inclusive}{binned}");
  Hratio->GetYaxis()->SetNdivisions(405);
  Hratio->GetYaxis()->SetTitleSize(20);
  Hratio->GetYaxis()->SetTitleFont(43);
  Hratio->GetYaxis()->SetTitleOffset(0.98);
  // Absolute font size in pixel (precision 3)
  Hratio->GetYaxis()->SetLabelFont(43);
  Hratio->GetYaxis()->SetLabelSize(15);

  // X axis ratio plot settings
  Hratio->GetXaxis()->SetTitleSize(20);
  Hratio->GetXaxis()->SetTitleFont(43);
  Hratio->GetXaxis()->SetTitleOffset(4.);
  // Absolute font size in pixel (precision 3)
  Hratio->GetXaxis()->SetLabelFont(43);
  Hratio->GetXaxis()->SetLabelSize(15);
  Hratio->SetAxisRange(0, 2, "Y");
  Hratio->SetLineColor(kAzure+1);
  // Hratio->SetErrorLineStyle

  // print scale factors
  // (makes sense when the sample-binned histograms are used)
  cout << "Ratio Inclusive/Binned" << endl;
  for (int ibin = 1; ibin <= nbins; ibin++)
  {
    printf("%f +/- %f\n", Hratio->GetBinContent(ibin),
           Hratio->GetBinError(ibin));
  }

  // w->SaveAs("pic_date_Mbc.eps");
  canv->SaveAs("/stash/user/zhyuan/public/svg/stiching_inclusive2_265_wjet_wpt.svg");

  return 0;
}

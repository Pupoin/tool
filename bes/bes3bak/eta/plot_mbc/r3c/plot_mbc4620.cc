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
int plot_mbc4620()
{

    // setStyle();
    // setPad();
    double factor[2] = {0.01250, 0.01250};

    // //********************plot the mBC distributions*********************//
    TCanvas *canv1 = new TCanvas("canv1", "mBC", 800, 600);
    canv1->SetFillColor(0);
    canv1->SetFrameFillColor(0);
    canv1->SetTopMargin(0.13);
    canv1->SetBottomMargin(0.13);
    canv1->SetLeftMargin(0.13);
    canv1->SetRightMargin(0.13);
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    double xmin = 2.25, xmax = 2.31387;
    double xbins = 20;
    TH1::SetDefaultSumw2(1);
    TString a("Events/");
    char b[100];
    sprintf(b, "(%g", (xmax - xmin) / xbins * 1000);
    TString c(" MeV)");
    TString ytitle = a + b + c;

    TChain *chain_data = new TChain("tree");
    TChain *chain_hardon = new TChain("tree");
    TChain *chain_inclusive = new TChain("tree");

    chain_inclusive->Add("../LL/cutmassroot/4620LL_mass.root");
    chain_data->Add("../data/cutmassroot/4620data_mass.root");
    chain_hardon->Add("../hadron/cutmassroot/4620hadron_mass.root");

    TH1D *hist_data = new TH1D("hist_data", "m_{BC} Distribution", xbins, xmin, xmax);
    TH1D *hist_hardon = new TH1D("hist_hardon", "m_{BC} Distribution", xbins, xmin, xmax);
    TH1D *hist_inclusive_sig =
        new TH1D("hist_inclusive_sig", "m_{BC} Distribution", xbins, xmin, xmax);
    TH1D *hist_inclusive_bkg =
        new TH1D("hist_inclusive_bkg", "m_{BC} Distribution", xbins, xmin, xmax);

    //TCut cut_deltaE = "((deltaE_min>-0.03) && (deltaE_min<0.02))";
    TCut cut_np = "(np!=0 && npbar != 0)";
    TCut cut_chi2 = "(chi2_min_r1c<13)";
    TCut cut_mbc = "((M_BC>=2.25) && (M_BC<=2.31387))";

    TCut cut_sum1 = (cut_mbc && cut_chi2 && cut_np);

    TCut cut_inclusive_sig = "signal==1 || signal == -1";
    TCut cut_inclusive_bkg = !cut_inclusive_sig;

    chain_data->Project("hist_data", "M_BC", cut_sum1);
    //chain_hardon->Project("hist_hardon", "M_BC", cut_sum1 && "indexmc==0");
    chain_hardon->Project("hist_hardon", "M_BC", cut_sum1 && "flag1!=96");

    auto chain_inclusive_bkg = chain_inclusive;
    auto chain_inclusive_sig = chain_inclusive;
    chain_inclusive_bkg->Project("hist_inclusive_bkg", "M_BC",
                                 cut_inclusive_bkg && cut_sum1);
    chain_inclusive_sig->Project("hist_inclusive_sig", "M_BC",
                                 cut_inclusive_sig && cut_sum1);

    hist_inclusive_sig->SetLineColor(2);
    hist_inclusive_bkg->SetLineColor(3);
    hist_hardon->SetLineColor(4);

    hist_inclusive_sig->SetLineWidth(3);

    hist_inclusive_bkg->SetFillColor(3);
    hist_hardon->SetFillColor(5);

    canv1->cd();
    THStack *hStack = new THStack("his", "");
    // hs->SetMaximum(2);
    hStack->Add(hist_hardon);
    hStack->Add(hist_inclusive_bkg);
    hStack->Add(hist_inclusive_sig);

    double fac = 1;
    hist_inclusive_sig->Scale(factor[0] * fac);
    hist_inclusive_bkg->Scale(factor[0] * fac);
    hist_hardon->Scale(factor[1] * fac);

    //hist_data->Draw("e ");
    hStack->Draw("HIST");
    hist_data->Draw("e same");

    hStack->GetYaxis()->SetTitle(ytitle);
    hStack->GetYaxis()->SetTitleOffset(0.75);
    hStack->GetYaxis()->SetTitleSize(0.05);
    hStack->GetYaxis()->SetRange(0, 100);
    hStack->SetMinimum(0.);
    //hStack->SetMaximum(14);
    hStack->GetXaxis()->SetTitle("m_{BC} (GeV)");
    hStack->GetXaxis()->SetTitleOffset(1.0);
    hStack->GetXaxis()->SetTitleSize(0.05);

    TLegend *legend = new TLegend(0.75, 0.6, 0.95, 0.9);
    //   legend->SetHeader("m_{BC} Distribution");
    legend->AddEntry("hist_data", "data", "f");
    legend->AddEntry("hist_inclusive_sig", "signal", "f");
    legend->AddEntry("hist_inclusive_bkg", "#Lambda_{c}#bar{#Lambda_{c}} bkg",
                     "f");
    legend->AddEntry("hist_hardon", "hardon", "f");

    //   legend->SetBorderSize(0);
    //   legend->SetFillColor(0);
    legend->Draw();

    canv1->Update();
    // canv1->SaveAs("combined_Mbc.svg");
    return 0;
}

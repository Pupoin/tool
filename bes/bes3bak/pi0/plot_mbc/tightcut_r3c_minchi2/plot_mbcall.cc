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
int plot_mbcall()
{

    // setStyle();
    // setPad();
    double factor[2] = {0.0230, 0.05};

    // //********************plot the mBC distributions*********************//
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

    double xmin = 2.25, xmax = 2.34919;
    double width=0.006;
    Int_t xbins = (xmax-xmin)/width + 1;
    xmax = xmin+xbins*width;
    TH1::SetDefaultSumw2(1);
    TString a("Events / ");
    char b[100];
    sprintf(b, "(%g", (xmax - xmin) / xbins * 1000);
    TString c("MeV/#font[12]{c^{2}})");
    TString ytitle = a + b + c;

    TChain *chain_data = new TChain("tree");
    TChain *chain_hardon = new TChain("tree");
    TChain *chain_inclusive = new TChain("tree");

    chain_inclusive->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/LL/cutmassroot/tightcut_r3c_minchi2/LL.root"); 
    chain_hardon->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/hadron/cutmassroot/tightcut_r3c_minchi2/hadron.root"); 
    chain_data->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/data/cutmassroot/tightcut_r3c_minchi2/data.root");

    TH1D *hist_data = new TH1D("hist_data", "m_{BC} Distribution", xbins, xmin, xmax);
    TH1D *hist_hardon = new TH1D("hist_hardon", "m_{BC} Distribution", xbins, xmin, xmax);
    TH1D *hist_inclusive_sig = new TH1D("hist_inclusive_sig", "m_{BC} Distribution", xbins, xmin, xmax);
    TH1D *hist_inclusive_bkg = new TH1D("hist_inclusive_bkg", "m_{BC} Distribution", xbins, xmin, xmax);

    // TCut cut_deltaE = "((deltaE_min>-0.020) && (deltaE_min<0.015))";
    TCut cut_np = "(np!=0 && npbar != 0)";
    TCut cut_chi2 = "(chi2_min_r3c<17)";
    TCut cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919))";
    TCut cut_sum1 = (cut_mbc && cut_chi2 && cut_np && "(dipim<0.44 || dipim>0.52)");

    // TCut cut_inclusive_sig = (cut_inclusive_sigp || cut_inclusive_sigm);
    TCut cut_inclusive_sig = "(signal==1 || signal == -1)";
    TCut cut_inclusive_bkg = !cut_inclusive_sig;

    chain_data->Project("hist_data", "M_BC_r3c", cut_sum1);
    //TCut cut_mode = ("mode1==0 && mode2==0 && mode3==96");
    //chain_hardon->Project("hist_hardon", "M_BC_r3c", cut_sum1 && "indexmc==0");
    chain_hardon->Project("hist_hardon", "M_BC_r3c", cut_sum1);

    auto chain_inclusive_bkg = chain_inclusive;
    auto chain_inclusive_sig = chain_inclusive;
    chain_inclusive_bkg->Project("hist_inclusive_bkg", "M_BC_r3c", cut_inclusive_bkg && cut_sum1);
    chain_inclusive_sig->Project("hist_inclusive_sig", "M_BC_r3c", cut_inclusive_sig && cut_sum1);

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
    hist_data->SetMarkerStyle(20);
    hist_data->SetLineWidth(2);
    hist_data->Draw("e1 same");
    // hStack->GetYaxis()->SetRange(0, 100);
    // hStack->GetYaxis()->SetTitleOffset(0.75);
    // double hist_max = hStack->GetMaximum() > hist_data->GetMaximum() ? hStack->GetMaximum():hist_data->GetMaximum();
    // hStack->GetXaxis()->SetTitleOffset(1.0);

    hStack->GetYaxis()->SetTitle(ytitle);
    hStack->GetYaxis()->SetTitleSize(0.06);
    hStack->GetYaxis()->SetLabelSize(0.045);
    hStack->GetXaxis()->SetLabelSize(0.045);
    hStack->SetMinimum(0.);
    hStack->SetMaximum(hStack->GetMaximum() > hist_data->GetMaximum() ? 1.2*hStack->GetMaximum(): 1.2*hist_data->GetMaximum());
    hStack->GetXaxis()->SetTitle("M_{BC} (GeV/#font[12]{c^{2}})");
    hStack->GetXaxis()->SetTitleSize(0.06);
    hStack->GetXaxis()->SetNdivisions(410);


    TLegend *legend = new TLegend(0.67, 0.58, 0.96, 0.84);
    // legend->SetHeader("all data");
    legend->AddEntry("hist_data", "data", "le");
    legend->AddEntry("hist_inclusive_sig", "signal", "f");
    legend->AddEntry("hist_inclusive_bkg", "#Lambda_{c}#bar{#Lambda}_{c} background", "f");
    legend->AddEntry("hist_hardon", "other background", "f");
    legend->SetBorderSize(0);
    legend->SetFillColor(0);
    legend->Draw();

    canv1->Update();
    canv1->SaveAs("stackall.pdf");
    canv1->SaveAs("stackall.png");
    return 0;
}

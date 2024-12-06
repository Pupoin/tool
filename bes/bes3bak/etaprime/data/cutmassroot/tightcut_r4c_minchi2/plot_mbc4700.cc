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
int plot_mbc4700()
{
    // //********************plot the mBC distributions*********************//
    TCanvas *canv1 = new TCanvas("canv1", "mBC", 800, 600);
    // canv1->SetFillColor(0);
    // canv1->SetFrameFillColor(0);
    // canv1->SetTopMargin(0.13);
    // canv1->SetBottomMargin(0.13);
    // canv1->SetLeftMargin(0.13);
    // canv1->SetRightMargin(0.13);
    // gStyle->SetOptStat(0);
    // gStyle->SetPadColor(0);
    // gStyle->SetCanvasColor(0);

    TChain *chain_hardon = new TChain("tree");
    chain_hardon->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/hadron/cutmassroot/tightcut_r3c_minchi2/4700hadron_mode.root");
    TH1D *hist_hardon = new TH1D("hist_hardon", "m_{BC} Distribution", 20, 2.25, 2.35);

    chain_hardon->Project("hist_hardon", "M_BC_r3c");
    canv1->cd();
    hist_hardon->Draw("HIST");

    canv1->Update();

    return 0;
}

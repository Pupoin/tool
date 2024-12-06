#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"
#include "TChain.h"
#include <iostream>
#include "TH1D.h"
#include "TLegend.h"

using namespace std;
int mbc()
{

    // //********************plot the mbc distributions*********************//
    TCanvas *canva1 = new TCanvas("canva1", "mbc", 800, 600);
    canva1->SetFillColor(0);
    canva1->SetFrameFillColor(0);
    canva1->SetTopMargin(0.13);
    canva1->SetBottomMargin(0.13);
    canva1->SetLeftMargin(0.13);
    canva1->SetRightMargin(0.13);
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);


    double xmin = 2.25, xmax = 2.313;
    double xbins = 100;
    // TH1::SetDefaultSumw2(1);
    TString a("Events/");
    char b[100];
    sprintf(b, "(%g", (xmax - xmin) / xbins * 1000);
    TString c(" MeV)");
    TString ytitle = a + b + c;

    TChain *chain_mbc = new TChain("tree");
    chain_mbc->Add("../root/shape.root");
    
    double mbc;
    // chain_mbc->SetBranchAddress("M_BC", &mbc);
    TH1D *hist_mbc = new TH1D("hist_mbc", "", xbins, xmin, xmax);
    // cout << chain_mbc->GetEntries();
    // for(int i = 0; i < chain_mbc->GetEntries(); i++)
    // {
    //     chain_mbc->GetEntry(i);
    //     hist_mbc->Fill(mbc);
    // }

    hist_mbc->SetLineColor(kRed);
    hist_mbc->SetFillColor(0);
    hist_mbc->SetLineWidth(3);

    // TCut cut_np = "(np !=0 && npbar != 0)";
    TCut cut_mass = "(etam>=0.5&&etam<=0.56 ) && (pi0m>=0.115&&pi0m<=0.15) && (sigmam>=1.174&&sigmam<=1.2)";
    TCut cut_deltaE = "((deltaE_min>-0.1) && (deltaE_min<0.1))";

    chain_mbc->Project("hist_mbc", "M_BC",cut_mass && cut_deltaE);


    hist_mbc->Scale(1);
    hist_mbc->Sumw2();
    hist_mbc->SetMinimum(0);
    //  w->cd();
    // Signal_MC->SetMaximum(22000);
    // Signal_MC->Draw("M_BC");
    hist_mbc->GetYaxis()->SetTitle(ytitle);
    hist_mbc->GetYaxis()->SetTitleOffset(1.1);
    hist_mbc->GetYaxis()->SetTitleSize(0.05);
    hist_mbc->GetXaxis()->SetTitle("m_bc (GeV)");
    hist_mbc->GetXaxis()->SetTitleOffset(1.0);
    hist_mbc->GetXaxis()->SetTitleSize(0.05);
    
    hist_mbc->Draw();

    TLegend *legend = new TLegend(0.2, 0.65, 0.45, 0.8);
    legend->SetHeader("m_bc Distribution");
    legend->AddEntry("hist_mbc", "m_bc", "f");
    legend->SetBorderSize(2);
    legend->SetFillColor(0);
    // legend->Draw();

    // w->SaveAs("pic_shape_Mbc.eps");
    canva1->SaveAs("pic_mbc.svg");
    
    return 0;
}

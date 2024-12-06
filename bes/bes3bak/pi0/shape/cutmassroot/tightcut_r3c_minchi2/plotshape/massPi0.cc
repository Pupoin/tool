#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"
#include "TChain.h"
#include <iostream>
#include "TH1D.h"
#include "TLegend.h"

using namespace std;
int massPi0()
{

    // //********************plot the massPi0 distributions*********************//
    TCanvas *canva1 = new TCanvas("canva1", "massPi0", 800, 600);
    canva1->SetFillColor(0);
    canva1->SetFrameFillColor(0);
    canva1->SetTopMargin(0.13);
    canva1->SetBottomMargin(0.13);
    canva1->SetLeftMargin(0.13);
    canva1->SetRightMargin(0.13);
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);


    double xmin = 0.08, xmax = 0.18;
    double xbins = 100;
    // TH1::SetDefaultSumw2(1);
    TString a("Events/");
    char b[100];
    sprintf(b, "(%g", (xmax - xmin) / xbins * 1000);
    TString c(" MeV)");
    TString ytitle = a + b + c;

    TChain *chain_massPi0 = new TChain("tree");
    chain_massPi0->Add("../4600shape.root");
    
    double massPi0;
    // chain_massPi0->SetBranchAddress("pi0m", &massPi0);
    TH1D *hist_massPi0 = new TH1D("hist_massPi0", "", xbins, xmin, xmax);
    // cout << chain_massPi0->GetEntries();
    // for(int i = 0; i < chain_massPi0->GetEntries(); i++)
    // {
    //     chain_massPi0->GetEntry(i);
    //     hist_massPi0->Fill(massPi0);
    // }

    hist_massPi0->SetLineColor(kRed);
    hist_massPi0->SetFillColor(0);
    hist_massPi0->SetLineWidth(3);

    // TCut cut_np = "(np !=0 && npbar != 0)";
    TCut cut_mass = "(etam>=0.5&&etam<=0.56 ) && (sigmam>=1.174&&sigmam<=1.2)";
    TCut cut_deltaE = "((deltaE_min>-0.1) && (deltaE_min<0.1))";
    TCut cut_mbc = "((M_BC>=2.25) && (M_BC<=2.313))";

    chain_massPi0->Project("hist_massPi0", "pi0m", cut_deltaE && cut_mass && cut_mbc);

    hist_massPi0->Scale(1);
    hist_massPi0->SetMinimum(0);
    hist_massPi0->Sumw2();

    //  w->cd();
    // Signal_MC->SetMaximum(22000);
    // Signal_MC->Draw("M_BC");
    hist_massPi0->GetYaxis()->SetTitle(ytitle);
    hist_massPi0->GetYaxis()->SetTitleOffset(1);
    hist_massPi0->GetYaxis()->SetTitleSize(0.05);
    hist_massPi0->GetXaxis()->SetTitle("m_{#pi^{0}(#gamma#gamma)} (GeV)");
    hist_massPi0->GetXaxis()->SetTitleOffset(1.0);
    hist_massPi0->GetXaxis()->SetTitleSize(0.05);
    
    hist_massPi0->Draw();

    TArrow *ar2 = new TArrow(0.1150,5000,0.1150,30000,0.02,"<|");
    ar2->SetAngle(40);
    ar2->SetLineWidth(2);
    ar2->SetLineColor(4);
    ar2->SetFillColor(4);
    ar2->Draw();

    TArrow *ar3 = new TArrow(0.15,5000,0.15,30000,0.02,"<|");
    ar3->SetAngle(40);
    ar3->SetLineWidth(2);
    ar3->SetLineColor(4);
    ar3->SetFillColor(4);
    ar3->Draw();

    TLegend *legend = new TLegend(0.2, 0.65, 0.45, 0.8);
    legend->SetHeader("m_{#pi^{0}(#gamma#gamma)} Distribution");
    legend->AddEntry("hist_massPi0", "mass #pi^{0}(#gamma#gamma)", "f");
    legend->SetBorderSize(2);
    legend->SetFillColor(0);
    // legend->Draw();

    // w->SaveAs("pic_shape_Mbc.eps");
    canva1->SaveAs("pic_massPi0.svg");
    
    return 0;
}

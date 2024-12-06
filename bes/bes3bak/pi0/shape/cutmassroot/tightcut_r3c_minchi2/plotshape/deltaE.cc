#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"
#include "TChain.h"
#include <iostream>
#include "TH1D.h"
#include "TLegend.h"

using namespace std;
int deltaE()
{

    // //********************plot the massDeltaE distributions*********************//
    TCanvas *canva1 = new TCanvas("canva1", "massDeltaE", 800, 600);
    canva1->SetFillColor(0);
    canva1->SetFrameFillColor(0);
    canva1->SetTopMargin(0.13);
    canva1->SetBottomMargin(0.13);
    canva1->SetLeftMargin(0.13);
    canva1->SetRightMargin(0.13);
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);


    double xmin = -0.1, xmax = 0.1;
    double xbins = 100;
    // TH1::SetDefaultSumw2(1);
    TString a("Events/");
    char b[100];
    sprintf(b, "(%g", (xmax - xmin) / xbins * 1000);
    TString c(" MeV)");
    TString ytitle = a + b + c;

    TChain *chain_massDeltaE = new TChain("tree");
    chain_massDeltaE->Add("../root/shape.root");
    
    double massDeltaE;
    // chain_massDeltaE->SetBranchAddress("deltaE_min", &massDeltaE);
    TH1D *hist_massDeltaE = new TH1D("hist_massDeltaE", "", xbins, xmin, xmax);
    // cout << chain_massDeltaE->GetEntries();
    // for(int i = 0; i < chain_massDeltaE->GetEntries(); i++)
    // {
    //     chain_massDeltaE->GetEntry(i);
    //     hist_massDeltaE->Fill(massDeltaE);
    // }

    hist_massDeltaE->SetLineColor(kRed);
    hist_massDeltaE->SetFillColor(0);
    hist_massDeltaE->SetLineWidth(3);

    // TCut cut_np = "(np !=0 && npbar != 0)";
    TCut cut_mass = "(etam>=0.5&&etam<=0.56 ) && (pi0m>=0.115&&pi0m<=0.15) && (sigmam>=1.174&&sigmam<=1.2)";
    TCut cut_deltaE = "((deltaE_min>-0.1) && (deltaE_min<0.1))";
    TCut cut_mbc = "((M_BC>=2.25) && (M_BC<=2.313))";

    chain_massDeltaE->Project("hist_massDeltaE", "deltaE_min",cut_deltaE && cut_mass && cut_mbc );

    hist_massDeltaE->Scale(1);
    hist_massDeltaE->Sumw2();
    hist_massDeltaE->SetMinimum(0);
    //  w->cd();
    // Signal_MC->SetMaximum(22000);
    // Signal_MC->Draw("M_BC");
    hist_massDeltaE->GetYaxis()->SetTitle(ytitle);
    hist_massDeltaE->GetYaxis()->SetTitleOffset(1.1);
    hist_massDeltaE->GetYaxis()->SetTitleSize(0.05);
    hist_massDeltaE->GetXaxis()->SetTitle("#Delta E (GeV)");
    hist_massDeltaE->GetXaxis()->SetTitleOffset(1.0);
    hist_massDeltaE->GetXaxis()->SetTitleSize(0.05);
    
    hist_massDeltaE->Draw();

    TArrow *ar2 = new TArrow(-0.03,5000,-0.03,25000,0.02,"<|");
    ar2->SetAngle(40);
    ar2->SetLineWidth(2);
    ar2->SetLineColor(4);
    ar2->SetFillColor(4);
    // ar2->Draw();

    TArrow *ar3 = new TArrow(0.02,5000,0.02,25000,0.02,"<|");
    ar3->SetAngle(40);
    ar3->SetLineWidth(2);
    ar3->SetLineColor(4);
    ar3->SetFillColor(4);
    // ar3->Draw();

    TLegend *legend = new TLegend(0.2, 0.65, 0.45, 0.8);
    legend->SetHeader("#Delta E distribution");
    // legend->AddEntry("hist_massDeltaE", "", "f");
    legend->SetBorderSize(2);
    legend->SetFillColor(0);
    // legend->Draw();

    // w->SaveAs("pic_shape_Mbc.eps");
    canva1->SaveAs("pic_massDeltaE.svg");
    
    return 0;
}

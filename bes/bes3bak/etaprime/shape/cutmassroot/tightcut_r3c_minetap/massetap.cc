#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"
#include "TChain.h"
#include <iostream>
#include "TH1D.h"
#include "TLegend.h"

using namespace std;
int massetap()
{

    // //********************plot the massetap distributions*********************//
    TCanvas *canva1 = new TCanvas("canva1", "massEta", 700, 600);
    canva1->SetFillColor(0);
    canva1->SetFrameFillColor(0);
    canva1->SetTopMargin(0.1);
    canva1->SetBottomMargin(0.15);
    canva1->SetLeftMargin(0.15);
    canva1->SetRightMargin(0.05);
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);


    double xmin = 0.93, xmax = 0.99;
    double xbins = 100;
    // TH1::SetDefaultSumw2(1);
    TString a("Events/");
    char b[100];
    sprintf(b, "(%g", (xmax - xmin) / xbins * 1000);
    TString c(" MeV/c^{2})");
    TString ytitle = a + b + c;

    TChain *chain_massetap = new TChain("tree");
    chain_massetap->Add("4600shape.root");
    
    double massetap;
    // chain_massetap->SetBranchAddress("pi0m", &massetap);
    TH1D *hist_massetap = new TH1D("hist_massetap", "", xbins, xmin, xmax);
    // cout << chain_massetap->GetEntries();
    // for(int i = 0; i < chain_massetap->GetEntries(); i++)
    // {
    //     chain_massetap->GetEntry(i);
    //     hist_massetap->Fill(massetap);
    // }

    hist_massetap->SetLineColor(kRed);
    hist_massetap->SetFillColor(0);
    hist_massetap->SetLineWidth(3);

    // TCut cut_np = "(np !=0 && npbar != 0)";
    // TCut cut_mass = "(etam>=0.5&&etam<=0.56 ) && (sigmam>=1.174&&sigmam<=1.2)";
    // TCut cut_deltaE = "((deltaE_min>-0.1) && (deltaE_min<0.1))";
    // TCut cut_mbc = "((M_BC>=2.25) && (M_BC<=2.3))";

    chain_massetap->Project("hist_massetap", "etaprimemr3c", "");

    hist_massetap->Scale(1);
    hist_massetap->SetMinimum(0);
    hist_massetap->Sumw2();

    //  w->cd();
    // Signal_MC->SetMaximum(22000);
    // Signal_MC->Draw("M_BC");
    hist_massetap->GetYaxis()->SetTitle(ytitle);
    // hist_massetap->GetYaxis()->SetTitleOffset(1);
    // hist_massetap->GetYaxis()->SetTitleSize(0.05);
    hist_massetap->GetXaxis()->SetTitle(" m_{#eta'(#pi^{+}#pi^{-}#eta)} (GeV/c^{2})");
    // hist_massetap->GetXaxis()->SetTitleOffset(1.0);
    // hist_massetap->GetXaxis()->SetTitleSize(0.05);
    hist_massetap->SetTitleSize(0.06, "xy");
    hist_massetap->SetLabelSize(0.045, "xy");
    hist_massetap->GetYaxis()->SetMaxDigits(3); 
    hist_massetap->GetXaxis()->SetNdivisions(205); 


    
    hist_massetap->Draw();

    TArrow *ar2 = new TArrow(0.9460,500,0.9460,5000,0.02,"<|");
    ar2->SetAngle(40);
    ar2->SetLineWidth(2);
    ar2->SetLineColor(4);
    ar2->SetFillColor(4);
    ar2->Draw();

    TArrow *ar3 = new TArrow(0.968,500,0.968,5000,0.02,"<|");
    ar3->SetAngle(40);
    ar3->SetLineWidth(2);
    ar3->SetLineColor(4);
    ar3->SetFillColor(4);
    ar3->Draw();

    TLegend *legend = new TLegend(0.2, 0.65, 0.45, 0.8);
    // legend->SetHeader("m_{#eta'(#gamma#gamma)} Distribution");
    legend->AddEntry("hist_massetap", "mass #eta'(#pi^{+}#pi^{-}#eta)", "f");
    legend->SetBorderSize(2);
    legend->SetFillColor(0);
    // legend->Draw();

    // w->SaveAs("pic_shape_Mbc.eps");
    canva1->SaveAs("pic_massetap.png");
    canva1->SaveAs("pic_massetap.pdf");
    
    return 0;
}

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

    // //********************plot the massEta distributions*********************//
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


    double xmin = 0.11, xmax = 0.17;
    double xbins = 100;
    // TH1::SetDefaultSumw2(1);
    TString a("Events/");
    char b[100];
    sprintf(b, "(%g", (xmax - xmin) / xbins * 1000);
    TString c(" MeV/#font[12]{c^{2}})");
    TString ytitle = a + b + c;

    TChain *chain_massEta = new TChain("tree");
    chain_massEta->Add("./shape.root");
    
    double massEta;
    // chain_massEta->SetBranchAddress("etam", &massEta);
    TH1F *hist_massEta = new TH1F("hist_massEta", "", xbins, xmin, xmax);
    // cout << chain_massEta->GetEntries();
    // for(int i = 0; i < chain_massEta->GetEntries(); i++)
    // {
    //     chain_massEta->GetEntry(i);
    //     hist_massEta->Fill(massEta);
    // }

    hist_massEta->SetLineColor(kRed);
    hist_massEta->SetFillColor(0);
    hist_massEta->SetLineWidth(3);

    // TCut cut_np = "(np !=0 && npbar != 0)";
    TCut cut_mass = "(etam>=0.45&&etam<=0.58) && (sigmam>=1.174&&sigmam<=1.2)";
    // TCut cut_deltaE = "((deltaE_min>-0.1) && (deltaE_min<0.1))";
    TCut cut_deltaE = "(chi2_min_r3c<17)";
    TCut cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.313))";

    chain_massEta->Project("hist_massEta", "pi0m",cut_mbc && cut_mass );

    hist_massEta->Scale(1);
    hist_massEta->Sumw2();
    hist_massEta->SetMinimum(0);
    //  w->cd();
    // Signal_MC->SetMaximum(22000);
    // Signal_MC->Draw("chi2_min_r1c");
    hist_massEta->GetYaxis()->SetTitle(ytitle);
    // hist_massEta->GetYaxis()->SetTitleOffset(1.1);
    // hist_massEta->GetYaxis()->SetTitleSize(0.05);
    hist_massEta->GetXaxis()->SetTitle("m_{#pi^{0}(#gamma#gamma)} (GeV/#font[12]{c^{2}})");
    // hist_massEta->GetXaxis()->SetTitleOffset(1.0);
    hist_massEta->SetTitleSize(0.06, "xy");
    hist_massEta->SetLabelSize(0.045, "xy");
    hist_massEta->GetYaxis()->SetMaxDigits(3); 
    
    hist_massEta->Draw();
    

    TArrow *ar2 = new TArrow(0.1150,1000,0.1150,8000,0.02,"<|");
    ar2->SetAngle(40);
    ar2->SetLineWidth(2);
    ar2->SetLineColor(4);
    ar2->SetFillColor(4);
    ar2->Draw();

    TArrow *ar3 = new TArrow(0.15,1000,0.15,8000,0.02,"<|");
    ar3->SetAngle(40);
    ar3->SetLineWidth(2);
    ar3->SetLineColor(4);
    ar3->SetFillColor(4);
    ar3->Draw();

    TLegend *legend = new TLegend(0.2, 0.65, 0.45, 0.8);
    // legend->SetHeader("m_{#eta(#gamma#gamma)} Distribution");
    legend->AddEntry("hist_massEta", "mass #eta(#gamma#gamma)", "l");
    legend->SetBorderSize(2);
    legend->SetFillColor(0);
    // legend->Draw();

    // w->SaveAs("pic_shape_Mbc.eps");
    canva1->SaveAs("m_pi0.png");
    canva1->SaveAs("m_pi0.pdf");
    
    return 0;
}

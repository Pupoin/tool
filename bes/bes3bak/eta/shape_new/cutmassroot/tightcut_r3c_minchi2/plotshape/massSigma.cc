#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"
#include "TChain.h"
#include <iostream>
#include "TH1D.h"
#include "TLegend.h"

using namespace std;
int massSigma()
{

    // //********************plot the massSigma distributions*********************//
    TCanvas *canva1 = new TCanvas("canva1", "massSigma", 800, 600);
    canva1->SetFillColor(0);
    canva1->SetFrameFillColor(0);
    canva1->SetTopMargin(0.13);
    canva1->SetBottomMargin(0.13);
    canva1->SetLeftMargin(0.13);
    canva1->SetRightMargin(0.13);
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);


    double xmin = 1.15, xmax = 1.21;
    double xbins = 100;
    // TH1::SetDefaultSumw2(1);
    TString a("Events/");
    char b[100];
    sprintf(b, "(%g", (xmax - xmin) / xbins * 1000);
    TString c(" MeV)");
    TString ytitle = a + b + c;

    TChain *chain_massSigma = new TChain("tree");
    chain_massSigma->Add("../root/shape.root");
    
    double massSigma;
    // chain_massSigma->SetBranchAddress("mass_Sigma", &massSigma);
    TH1D *hist_massSigma = new TH1D("hist_massSigma", "", xbins, xmin, xmax);
    // cout << chain_massSigma->GetEntries();
    // for(int i = 0; i < chain_massSigma->GetEntries(); i++)
    // {
    //     chain_massSigma->GetEntry(i);
    //     hist_massSigma->Fill(massSigma);
    // }

    hist_massSigma->SetLineColor(kRed);
    hist_massSigma->SetFillColor(0);
    hist_massSigma->SetLineWidth(3);

    // TCut cut_np = "(np !=0 && npbar != 0)";
    TCut cut_mass = "(etam>=0.5&&etam<=0.56 ) && (pi0m>=0.115&&pi0m<=0.15)";
    TCut cut_deltaE = "((deltaE_min>-0.1) && (deltaE_min<0.1))";
    TCut cut_mbc = "((M_BC>=2.25) && (M_BC<=2.313))";
    
    chain_massSigma->Project("hist_massSigma", "sigmam",cut_deltaE && cut_mass && cut_mbc);

    hist_massSigma->Scale(1);
    hist_massSigma->Sumw2();
    hist_massSigma->SetMinimum(0);

    hist_massSigma->GetYaxis()->SetTitle(ytitle);
    hist_massSigma->GetYaxis()->SetTitleOffset(1.1);
    hist_massSigma->GetYaxis()->SetTitleSize(0.05);
    hist_massSigma->GetXaxis()->SetTitle("m_{#Sigma^{+}(p#pi^{0})} (GeV)");
    hist_massSigma->GetXaxis()->SetTitleOffset(1.0);
    hist_massSigma->GetXaxis()->SetTitleSize(0.05);
    
    hist_massSigma->Draw();

    TArrow *ar2 = new TArrow(1.174, 4000, 1.174, 26000, 0.02, "<|");
    ar2->SetAngle(40);
    ar2->SetLineWidth(2);
    ar2->SetLineColor(4);
    ar2->SetFillColor(4);
    ar2->Draw();

    TArrow *ar3 = new TArrow(1.2, 4000, 1.2, 26000, 0.02, "<|");
    ar3->SetAngle(40);
    ar3->SetLineWidth(2);
    ar3->SetLineColor(4);
    ar3->SetFillColor(4);
    ar3->Draw();

    TLegend *legend = new TLegend(0.2, 0.65, 0.45, 0.8);
    legend->SetHeader("m_{#Sigma^{+}(p#pi^{0})} Distribution");
    legend->AddEntry("hist_massSigma", "mass #Sigma^{+}(p#pi^{0})", "f");
    // Signal_MC->Draw("M_BC");
    legend->SetBorderSize(2);
    legend->SetFillColor(0);
    // legend->Draw();

    // w->SaveAs("pic_shape_Mbc.eps");
    canva1->SaveAs("pic_massSigma.svg");
    
    return 0;
}

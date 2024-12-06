#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"
#include "TChain.h"
#include <iostream>
#include "TH1D.h"
#include "TLegend.h"

using namespace std;
int plot_fom2()
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

    double xmin = 0, xmax = 30;
    double xbins = 30;
    TH1::SetDefaultSumw2(1);
    // TString a("Events/");
    // char b[100];
    // sprintf(b, "(%g", (xmax - xmin) / xbins * 1000);
    // TString c(" MeV)");
    // TString ytitle = a + b + c;

    TChain *chain = new TChain("tree");
    chain->Add("fom.root");

    double m_nsig, m_nbkg, m_fom, m_chi2;
    chain->SetBranchAddress("chi2", &m_chi2);
    chain->SetBranchAddress("nsig", &m_nsig);
    chain->SetBranchAddress("nbkg", &m_nbkg);
    chain->SetBranchAddress("s_sb", &m_fom);

    TH1D *hist = new TH1D("hist", "", xbins, xmin, xmax);
    TH1D *hist2 = new TH1D("hist2", "", xbins, xmin, xmax);
    for (int i = 0; i < chain->GetEntries(); i++)
    {
        chain->GetEvent(i);

        hist->Fill(m_chi2, m_nsig);
        hist2->Fill(m_chi2, m_nbkg);
    }

    hist->SetLineColor(kRed);
    hist2->SetLineColor(4);
    hist->SetFillColor(0);
    hist->SetLineWidth(3);

    hist->Draw("HIST");
    hist2->Draw("HIST same");

    hist->GetXaxis()->SetTitle("chi2");
    hist->GetYaxis()->SetTitle("Events");

    TLegend *legend = new TLegend(0.6, 0.35, 0.85, 0.5);
    //legend->SetHeader("s/sqrt(s+b)");
    legend->AddEntry("hist", "sig", "f");
    legend->AddEntry("hist2", "bkg", "f");
    legend->SetBorderSize(0);
    legend->SetFillColor(0);
    legend->Draw();

    canva1->SaveAs("pic_fom2.svg");

    return 0;
}

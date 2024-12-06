#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"
#include "TChain.h"
#include <iostream>
#include "TH2D.h"
#include "TLegend.h"

using namespace std;
int plot_fom2()
{

    // //********************plot the mbc distributions*********************//
    TCanvas *canva1 = new TCanvas("canva1", "mbc", 720, 600);
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

    double m_nsig, m_nbkg, m_fom, m_deltaE_up, m_deltaE_down;
    chain->SetBranchAddress("deltaE_up", &m_deltaE_up);
    chain->SetBranchAddress("deltaE_down", &m_deltaE_down);
    chain->SetBranchAddress("nsig", &m_nsig);
    chain->SetBranchAddress("nbkg", &m_nbkg);
    chain->SetBranchAddress("s_sb", &m_fom);

    auto *hist = new TH2D("hist", "", 100, 0.00999, 0.11 , 100, -0.11000, -0.00999001000);
    for (int i = 0; i < chain->GetEntries(); i++)
    {
        chain->GetEvent(i);

        // cout << m_deltaE_up << "  " <<  m_deltaE_down << " " << m_fom << endl;
        hist->Fill(m_deltaE_up, m_deltaE_down, m_fom);
    }

    // hist->SetLineColor(kRed);
    // hist2->SetLineColor(4);
    // hist->SetFillColor(0);
    // hist->SetLineWidth(3);
    hist->GetZaxis()->SetRangeUser(90, 106);
    gStyle->SetPalette(kBird);
    hist->Draw("colz");
    hist->SetNdivisions(120, "xy");
    // hist2->Draw("HIST same");

    hist->GetXaxis()->SetTitle("deltaE_up");
    hist->GetYaxis()->SetTitle("deltaE_down");

    // TLegend *legend = new TLegend(0.6, 0.35, 0.85, 0.5);
    //legend->SetHeader("s/sqrt(s+b)");
    // legend->AddEntry("hist", "sig", "f");
    // legend->AddEntry("hist2", "bkg", "f");
    // legend->SetBorderSize(0);
    // legend->SetFillColor(0);
    // legend->Draw();

    // canva1->SaveAs("pic_fom.svg");

    return 0;
}
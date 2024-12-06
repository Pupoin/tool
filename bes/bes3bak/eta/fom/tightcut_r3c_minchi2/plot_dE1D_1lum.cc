#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"
#include "TChain.h"
#include <iostream>
#include "TH2D.h"
#include "TLegend.h"

using namespace std;
int plot_dE1D_1lum()
{

    // //********************plot the mbc distributions*********************//
    TCanvas *canv1 = new TCanvas("canv1", "mBC", 700, 600);
    canv1->SetFillColor(0);
    canv1->SetFrameFillColor(0);
    canv1->SetTopMargin(0.15);
    canv1->SetBottomMargin(0.15);
    canv1->SetLeftMargin(0.15);
    canv1->SetRightMargin(0.03);
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
    chain->Add("fom_1lum.root");

    double m_nsig, m_nbkg, m_fom, m_deltaE_up, m_deltaE_down;
    // chain->SetBranchAddress("deltaE_up", &m_deltaE_up);
    chain->SetBranchAddress("deltaE_down", &m_deltaE_down);
    chain->SetBranchAddress("nsig", &m_nsig);
    chain->SetBranchAddress("nbkg", &m_nbkg);
    chain->SetBranchAddress("s_sb", &m_fom);

    auto *hist = new TH1F("hist", "", 100, 0, 101);
    for (int i = 0; i < chain->GetEntries(); i++)
    {
        chain->GetEvent(i);

        // cout << m_deltaE_up << "  " <<  m_deltaE_down << " " << m_fom << endl;
        hist->Fill(m_deltaE_down, m_fom);
    }

    // hist->SetLineColor(kRed);
    // hist2->SetLineColor(4);
    // hist->SetFillColor(0);
    // hist->SetLineWidth(3);
    // hist->GetZaxis()->SetRangeUser(45, 56);
    // gStyle->SetPalette(kBird);
    hist->Draw("HIST");
    hist->SetLineColor(4);
    hist->SetLineWidth(3);
    // hist->SetLineWidth(3);
    // hist->SetNdivisions(120, "xy");
    // hist2->Draw("HIST same");

    hist->GetXaxis()->SetTitle("#chi^{2}");
    hist->GetYaxis()->SetTitle("s/#sqrt{s+b}");
    hist->SetTitleSize(0.06,"xy");
    hist->GetYaxis()->SetLabelSize(0.045);
    hist->GetXaxis()->SetLabelSize(0.045);

    TArrow *ar2 = new TArrow(26 , 69, 26, 30 ,0.025,"|>");
    ar2->SetAngle(40);
    ar2->SetLineWidth(2);
    ar2->Draw();

    // TLegend *legend = new TLegend(0.6, 0.35, 0.85, 0.5);
    //legend->SetHeader("s/sqrt(s+b)");
    // legend->AddEntry("hist", "sig", "f");
    // legend->AddEntry("hist2", "bkg", "f");
    // legend->SetBorderSize(0);
    // legend->SetFillColor(0);
    // legend->Draw();

//    canv1->SaveAs("pic_fom.png");
    canv1->SaveAs("pic_fom.pdf");

    return 0;
}

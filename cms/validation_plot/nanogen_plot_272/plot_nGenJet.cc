#include "TCanvas.h"
#include "TChain.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TRatioPlot.h"
#include "TString.h"
#include "TStyle.h"
#include <iostream>
#include <Riostream.h>
#include "THStack.h"
#include "TThread.h"

using namespace std;
// void MyFill(TChain *chain_0j, TH1D *hist_0j)
// {
//     Float_t genWeight;
//     Double_t LHE_Njets[20];
//     Int_t GenPart_pdgId[20], GenPart_status[20];
//     // UChar_t LHE_NpNLO;
//     chain_0j->SetBranchAddress("genWeight", &genWeight);
//     // chain_0j->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId);
//     chain_0j->SetBranchAddress("LHE_Njets", LHE_Njets);
//     // chain_0j->SetBranchAddress("GenPart_status", &GenPart_status);
//     // chain_0j->SetBranchAddress("LHE_NpNLO", &LHE_NpNLO);
//     int weight_p = 0, weight_m = 0;
//     cout << __LINE__ << " entries:" << chain_0j->GetEntries() << endl;

//     for (int i = 0; i < chain_0j->GetEntries(); i++)
//     {
//         if (i % 2000 == 0 && i != 0)
//             cout << __LINE__ << " i:" << i << endl;
//         chain_0j->GetEvent(i);

        // for (int j = 0; j < 20; j++)
        // {
        // int flag = 0, index = -1;
        // if (GenPart_pdgId[j] == 23)
        // {
        //     flag = 1;
        //     index = j;
        // }

        // if (flag == 0)
        //     continue;
        // cout << __LINE__ << " " << endl;
        // if (genWeight > 0)
        // {
        //     weight_p++;
        //     hist_0j->Fill(LHE_Njets[index], 1);
        // }
        // else
        // {
        //     weight_m++;
        //     hist_0j->Fill(LHE_Njets[index], -1);
        // }
        // }
    // }

    // hist_0j->Scale(1.0 / (weight_p - weight_m));
//     cout << __LINE__ << endl;
// }
int plot_nGenJet()
{
    const char param[] = "nGenJet";
    TCanvas *canv = new TCanvas("canv", "", 800, 700);
    canv->SetFillColor(0);
    canv->SetFrameFillColor(0);
    canv->SetTopMargin(0.13);
    canv->SetBottomMargin(0.13);
    canv->SetLeftMargin(0.13);
    canv->SetRightMargin(0.13);
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    canv->Divide(1, 2);

    TH1::SetDefaultSumw2(kTRUE);

    double xmin = 0, xmax = 12;
    int xbins = 12;    
    // double xmin = 10, xmax = 500;
    // int xbins = 10;
    TString a("Events/");
    char b[100];
    sprintf(b, "(%g", (xmax - xmin) / xbins);
    TString c(" GeV)");
    TString ytitle = a + b + c;

    TChain *chain_0j = new TChain("Events");
    TChain *chain_1j = new TChain("Events");
    TChain *chain_2j = new TChain("Events");
    TChain *chain_inclusive = new TChain("Events");

    chain_0j->Add("../root/0j_*root");
    chain_1j->Add("../root/1j_*root");
    chain_2j->Add("../root/2j_*root");
    chain_inclusive->Add("../root/012j_*root");

    TH1D *hist_0j = new TH1D("hist_0j", "", xbins, xmin, xmax);
    TH1D *hist_1j = new TH1D("hist_1j", "", xbins, xmin, xmax);
    TH1D *hist_2j = new TH1D("hist_2j", "", xbins, xmin, xmax);
    TH1D *hist_inclusive = new TH1D("hist_inclusive", "", xbins, xmin, xmax);

    TString selkt = "genWeight/fabs(genWeight)";
    // const char param[] = "LHE_HT*LHEWeight_originalXWGTUP/fabs(LHEWeight_originalXWGTUP)";
    // const char param[] = "LHE_Njets*LHEScaleWeight/fabs(LHEScaleWeight)";

    chain_0j->Project("hist_0j", param, selkt);
    chain_1j->Project("hist_1j", param, selkt);
    chain_2j->Project("hist_2j", param, selkt);
    chain_inclusive->Project("hist_inclusive", param, selkt);
    chain_inclusive->Project("hist_inclusive", param, selkt);

    // MyFill(chain_0j, hist_0j);
    // MyFill(chain_1j, hist_1j);
    // MyFill(chain_2j, hist_2j);
    // MyFill(chain_inclusive, hist_inclusive);

    cout << "0j " << hist_0j->Integral() << " " << hist_0j->GetEntries() << endl;
    cout << "1j " << hist_1j->Integral() << " " << hist_1j->GetEntries() << endl;
    cout << "2j " << hist_2j->Integral() << " " << hist_2j->GetEntries() << endl;
    cout << "inlcusive " << hist_inclusive->Integral() << " " << hist_inclusive->GetEntries() << endl;

    double factor[4] = {5688.025158 , 681.463411 , 212.307003 , 6540.333596 };

    hist_0j->Scale(factor[0] / (chain_0j->GetEntries("genWeight>0") - chain_0j->GetEntries("genWeight<0")));
    hist_1j->Scale(factor[1] / (chain_1j->GetEntries("genWeight>0") - chain_1j->GetEntries("genWeight<0")));
    hist_2j->Scale(factor[2] / (chain_2j->GetEntries("genWeight>0") - chain_2j->GetEntries("genWeight<0")));
    hist_inclusive->Scale(factor[3] / (chain_inclusive->GetEntries("genWeight>0") - chain_inclusive->GetEntries("genWeight<0")));

    cout << "_________________  after scale ___________________" << endl;
    cout << "0j intergral " << hist_0j->Integral() << "  allentries " << hist_0j->GetEntries() << "  p-n "<< chain_0j->GetEntries("genWeight>0") - chain_0j->GetEntries("genWeight<0") << endl;
    cout << "1j intergral " << hist_1j->Integral() << "  allentries " << hist_1j->GetEntries() << "  p-n "<< chain_1j->GetEntries("genWeight>0") - chain_1j->GetEntries("genWeight<0") << endl;
    cout << "2j intergral " << hist_2j->Integral() << "  allentries" << hist_2j->GetEntries() << "  p-n "<< chain_2j->GetEntries("genWeight>0") - chain_2j->GetEntries("genWeight<0") << endl;
    cout << "inlcusive intergral " << hist_inclusive->Integral() << " allentries " << hist_inclusive->GetEntries() << "  p-n "<< chain_inclusive->GetEntries("genWeight>0") - chain_inclusive->GetEntries("genWeight<0") << endl;

    TH1D *hist_binned = (TH1D *)hist_2j->Clone("hist_binned");
    hist_binned->Reset();
    TList *list = new TList;
    list->Add(hist_0j);
    list->Add(hist_1j);
    list->Add(hist_2j);
    hist_binned->Merge(list);

    THStack *hstack = new THStack("hstack", "");
    // hs->SetMaximum(2);
    hstack->Add(hist_0j);
    hstack->Add(hist_1j);
    hstack->Add(hist_2j);

    // -------------- draw --------------------
    // canv->cd(1);
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.235, 1, 1.0);
    pad1->SetBottomMargin(1);
    pad1->Draw();
    pad1->cd();
    gPad->SetLogy(1);

    hstack->Draw("HIST  ");
    hist_inclusive->Draw("e same");
    hist_binned->Draw("HIST same");
    // hist_0j->Draw("HIST same");
    // hist_1j->Draw("HIST same");
    // hist_2j->Draw("hist same");
    // hist_inclusive->SetMinimum(0.0001);
    // hist_inclusive->GetXaxis()->SetTitle();

    // _____________________ for line style ______________________________
    hist_0j->SetFillColor(18);
    hist_1j->SetFillColor(17);
    hist_2j->SetFillColor(15);

    hist_0j->SetLineColor(18);
    hist_1j->SetLineColor(17);
    hist_2j->SetLineColor(15);

    hist_0j->SetLineWidth(1);
    hist_1j->SetLineWidth(1);
    hist_2j->SetLineWidth(1);

    hist_inclusive->SetLineColor(2);
    hist_inclusive->SetLineWidth(2);

    hist_binned->SetLineColor(1);
    hist_binned->SetLineWidth(2);
    // _____________________________________________________________

    // _____________________ for axis ______________________________
    hstack->GetYaxis()->SetTitle("Events");
    hstack->GetXaxis()->SetNdivisions(105);
    // hstack->GetXaxis()->SetTitle("HT(GeV)");
    hstack->SetMinimum(0.1);
    //hstack->SetMaximum(50000);
    hstack->GetXaxis()->SetLabelSize(0);
    // hstack->SetFillColor(8);
    hstack->GetYaxis()->SetTitleSize(0.045);
    hstack->GetYaxis()->SetTitleOffset(0.96);
    // ______________________________________________________________

    TLegend *legend = new TLegend(0.65, 0.65, 0.85, 0.85);
    legend->SetHeader("MG v2.7.2");
    legend->AddEntry("hist_inclusive", "DY NLO inclusive", "f");
    legend->AddEntry("hist_binned", "DY NLO binned", "f");
    legend->AddEntry("hist_0j", "DY NLO 0j", "f");
    legend->AddEntry("hist_1j", "DY NLO 1j", "f");
    legend->AddEntry("hist_2j", "DY NLO 2j", "f");

    legend->SetBorderSize(0);
    // legend->SetFillColor(0);
    legend->Draw();

    //--------------------------- ratio -----------------------
    //--- Ensure no overflow events are left out of scale factor calculation
    TH1D *Hratio = (TH1D *)hist_inclusive->Clone("Hratio");
    TH1D *Hdenom = (TH1D *)hist_binned->Clone("Hdenom");

    int nbins = Hratio->GetNbinsX();
    double addoverflow = Hratio->GetBinContent(nbins) + Hratio->GetBinContent(nbins + 1);
    double erroverflow = sqrt(pow(Hratio->GetBinError(nbins), 2) + pow(Hratio->GetBinError(nbins + 1), 2));
    Hratio->SetBinContent(nbins, addoverflow);
    Hratio->SetBinError(nbins, erroverflow);

    nbins = hist_binned->GetNbinsX();
    addoverflow = hist_binned->GetBinContent(nbins) + hist_binned->GetBinContent(nbins + 1);
    erroverflow = sqrt(pow(hist_binned->GetBinError(nbins), 2) + pow(hist_binned->GetBinError(nbins + 1), 2));
    hist_binned->SetBinContent(nbins, addoverflow);
    hist_binned->SetBinError(nbins, erroverflow);

    Hratio->Divide(Hdenom);

    // ------ Draw ratio --------
    canv->cd();
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.08, 1, 0.3);
    pad2->SetTopMargin(1);
    pad2->SetBottomMargin(0.1);
    pad2->SetGridy(); // horizon grid
    pad2->Draw();
    pad2->cd();
    //gPad->SetLogy(0);
    Hratio->SetLineColor(kBlack);
    Hratio->Draw("e");

    // _____________________ for axis ______________________________
    // Y axis ratio plot settings
    Hratio->GetYaxis()->SetTitle("inclusive / bin");
    Hratio->GetYaxis()->SetNdivisions(405);
    Hratio->GetYaxis()->SetTitleSize(20);
    Hratio->GetYaxis()->SetTitleFont(43);
    Hratio->GetYaxis()->SetTitleOffset(0.98);
    // Absolute font size in pixel (precision 3)
    Hratio->GetYaxis()->SetLabelFont(43);
    Hratio->GetYaxis()->SetLabelSize(15);
    // X axis ratio plot settings
    Hratio->GetXaxis()->SetTitleSize(20);
    Hratio->GetXaxis()->SetTitle(param);
    Hratio->GetXaxis()->SetTitleFont(43);
    Hratio->GetXaxis()->SetTitleOffset(4.);
    Hratio->GetXaxis()->SetNdivisions(105);
    // Absolute font size in pixel (precision 3)
    Hratio->GetXaxis()->SetLabelFont(43);
    Hratio->GetXaxis()->SetLabelSize(18);
    Hratio->SetAxisRange(0.5, 1.5, "Y");
    Hratio->SetLineColor(kAzure + 1);
    // Hratio->SetErrorLineStyle
    pad2->Update();
    // _____________________________________________________________

    // print scale factors
    // (makes sense when the sample-binned histograms are used)
    cout << "\nRatio Inclusive/Binned" << endl;
    for (int ibin = 1; ibin <= nbins; ibin++)
    {
        printf("%f +/- %f\n", Hratio->GetBinContent(ibin), Hratio->GetBinError(ibin));
    }

    // w->SaveAs("pic_date_Mbc.eps");
    canv->SaveAs("/stash/user/zhyuan/public/svg/nanogen_272_nGenJet.svg");

    return 0;
}

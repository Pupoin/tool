#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"
void Mphi_plot()
{
//********************plot the Mphi distributions*********************//
TCanvas *w1 = new TCanvas("w1","Mphi",800,600);
w1->SetFillColor(0);
w1->SetFrameFillColor(0);
w1->SetTopMargin(0.13);
w1->SetBottomMargin(0.13);
w1->SetLeftMargin(0.13);
w1->SetRightMargin(0.13);
gStyle->SetOptStat(0);
gStyle->SetPadColor(0);
gStyle->SetCanvasColor(0);

double xmin=0.98, xmax=1.10; double xbins=100;
TH1::SetDefaultSumw2(1);
TString a("Events/"); char b[100]; sprintf(b, "(%g",(xmax-xmin)/xbins  *1000); TString c(" MeV)");
TString ytitle = a + b + c;

TChain *Mphi=new TChain("TDphipi");
Mphi->Add("/scratchfs/bes/lincx/job_ana/root/all_deltaE.root");

TH1D *Signal_MC=new TH1D("Signal_MC","M_{#phi} Distribution",100,0.98,1.10);
Signal_MC->SetLineColor(kRed);
Signal_MC->SetFillColor(0);
Signal_MC->SetLineWidth(3);

Mphi->Project("Signal_MC","M_phi","((dE_min>-0.020&&dE_min<0.019)&&(M_phi>0.98&&M_phi<1.10)&&(mbc_1>1.80&&mbc_1<1.89))");

cout << "Entries = " << Signal_MC->GetEntries() << endl;
cout << "RMS(Signal_MC) = " << Signal_MC->GetMean() << " +- " << Signal_MC->GetMeanError() <<endl;

Signal_MC->Scale(1);

w1->cd();
Signal_MC->SetMaximum(11000);
Signal_MC->Draw("HIST");
Signal_MC->GetXaxis()->SetTitle("M_{#phi} (GeV)");
Signal_MC->GetYaxis()->SetTitle(ytitle);
Signal_MC->GetYaxis()->SetTitleOffset(1.37);

TLegend *legend = new TLegend(0.5,0.65,0.75,0.8);
legend->SetHeader("M_{#phi} Distribution");
legend->AddEntry("Signal_MC","Signal MC","f");

legend->SetBorderSize(2);
legend->SetFillColor(0);
legend->Draw();


}










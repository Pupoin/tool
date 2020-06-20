#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"
void mBC_plot()
{
//********************plot the mBC distributions*********************//
TCanvas *w = new TCanvas("w","mBC",800,600);
w->SetFillColor(0);
w->SetFrameFillColor(0);
w->SetTopMargin(0.13);
w->SetBottomMargin(0.13);
w->SetLeftMargin(0.13);
w->SetRightMargin(0.13);
gStyle->SetOptStat(0);
gStyle->SetPadColor(0);
gStyle->SetCanvasColor(0);

double xmin=1.80, xmax=1.89; double xbins=100;
TH1::SetDefaultSumw2(1);
TString a("Events/"); char b[100]; sprintf(b, "(%g",(xmax-xmin)/xbins  *1000); TString c(" MeV)");
TString ytitle = a + b + c;

TChain *mBC=new TChain("TDphipi");
mBC->Add("/scratchfs/bes/lincx/job_ana/root/all_deltaE.root");

TH1D *Signal_MC=new TH1D("Signal_MC","m_{BC} Distribution",100,1.80,1.89);
Signal_MC->SetLineColor(kRed);
Signal_MC->SetFillColor(0);
Signal_MC->SetLineWidth(3);

mBC->Project("Signal_MC","mbc_1","((dE_min>-0.020&&dE_min<0.019)&&(M_phi>0.98&&M_phi<1.10)&&(mbc_1>1.80&&mbc_1<1.89))");

cout << "Entries = " << Signal_MC->GetEntries() << endl;
cout << "RMS(Signal_MC) = " << Signal_MC->GetMean() << " +- " << Signal_MC->GetMeanError() <<endl;

Signal_MC->Scale(1);

w->cd();
Signal_MC->SetMaximum(22000);
Signal_MC->Draw("HIST");
Signal_MC->GetXaxis()->SetTitle("m_{BC} (GeV)");
Signal_MC->GetYaxis()->SetTitle(ytitle);
Signal_MC->GetYaxis()->SetTitleOffset(1.37);

TLegend *legend = new TLegend(0.2,0.65,0.45,0.8);
legend->SetHeader("m_{BC} Distribution");
legend->AddEntry("Signal_MC","Signal MC","f");

legend->SetBorderSize(2);
legend->SetFillColor(0);
legend->Draw();


}










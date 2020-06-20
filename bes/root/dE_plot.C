#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"
void dE_plot()
{
//********************plot the deltaE distributions*********************//
TCanvas *can = new TCanvas("can","dEmin",800,600);
can->SetFillColor(0);
can->SetFrameFillColor(0);
can->SetTopMargin(0.13);
can->SetBottomMargin(0.13);
can->SetLeftMargin(0.13);
can->SetRightMargin(0.13);
gStyle->SetOptStat(0);
gStyle->SetPadColor(0);
gStyle->SetCanvasColor(0);

double xmin=-0.1, xmax=0.1; double xbins=100;
TH1::SetDefaultSumw2(1);
TString a("Events/"); char b[100]; sprintf(b, "(%g",(xmax-xmin)/xbins  *1000); TString c(" MeV)");
TString ytitle = a + b + c;

TChain *deltaE=new TChain("TDphipi");
deltaE->Add("/scratchfs/bes/lincx/job_ana/root/all_deltaE.root");

TH1D *Signal_MC=new TH1D("Signal_MC","#DeltaE Distribution",100,-0.1,0.1);
Signal_MC->SetLineColor(kRed);
Signal_MC->SetFillColor(0);
Signal_MC->SetLineWidth(3);

deltaE->Project("Signal_MC","dE_min","((dE_min>-0.1&&dE_min<0.1)&&(M_phi>0.98&&M_phi<1.10)&&(mbc_1>1.8&&mbc_1<1.89))");

cout << "Entries = " << Signal_MC->GetEntries() << endl;
cout << "RMS(Signal_MC) = " << Signal_MC->GetMean() << " +- " << Signal_MC->GetMeanError() <<endl;

Signal_MC->Scale(1);

can->cd();
Signal_MC->SetMaximum(16000);
Signal_MC->Draw("HIST");
Signal_MC->GetXaxis()->SetTitle("#DeltaE (GeV)");
Signal_MC->GetYaxis()->SetTitle(ytitle);
Signal_MC->GetYaxis()->SetTitleOffset(1.37);

TLegend *legend = new TLegend(0.2,0.65,0.43,0.8);
legend->SetHeader("#DeltaE Distribution");
legend->AddEntry("Signal_MC","Signal MC","f");

legend->SetBorderSize(2);
legend->SetFillColor(0);
legend->Draw();


}












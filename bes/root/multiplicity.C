#include "TCanvas.h"
#include "TStyle.h"
#include "TString.h"
#include "/afs/ihep.ac.cn/users/l/lincx/useful/boot.h"
void multiplicity()
{
//********************plot the mBC distributions*********************//
setStyle();myStyle->SetTitleXSize(0.06);
myStyle->SetTitleYSize(0.05);
TCanvas *can = new TCanvas("can","Multiplicity",800,600);
can->SetFillColor(0);
can->SetFrameFillColor(0);
can->SetTopMargin(0.13);
can->SetBottomMargin(0.13);
can->SetLeftMargin(0.13);
can->SetRightMargin(0.13);
gStyle->SetOptStat(1);
gStyle->SetPadColor(0);
gStyle->SetCanvasColor(0);

double xmin=0, xmax=20; double xbins=20;
TH1::SetDefaultSumw2(1);
TString a("Events/"); char b[100]; sprintf(b, "(%.1f)",(xmax-xmin)/xbins);
TString ytitle = a + b;

TChain *Multip=new TChain("TDphipi");
Multip->Add("/afs/ihep.ac.cn/users/l/lincx/scratchfs/job_ana/root/all.root");

TH1D *sigMC=new TH1D("sigMC","",20,0,20);
sigMC->SetLineColor(kBlack);
sigMC->SetFillColor(0);
sigMC->SetLineWidth(2);

Multip->Project("sigMC","deltaE_index","");

cout << "Entries = " << sigMC->GetEntries() << endl;
cout << "RMS(sigMC) = " << sigMC->GetMean() << " +- " << sigMC->GetMeanError() <<endl;

//sigMC->Scale(1);

can->cd();
//sigMC->SetMaximum(300);
sigMC->Draw("HIST");
sigMC->GetXaxis()->SetTitle("Multiplicity");
sigMC->GetYaxis()->SetTitle(ytitle);
sigMC->GetYaxis()->SetTitleOffset(1.2);

TLegend *legend = new TLegend(0.5,0.5,0.75,0.7);
//legend->SetHeader("Dang Distribution");
legend->AddEntry("sigMC","D^{+}#rightarrow#phi#pi^{+}","");

legend->SetBorderSize(0);
legend->SetFillColor(0);
legend->Draw();
//can->SaveAs("/afs/ihep.ac.cn/users/l/lincx/picture/phipi_SigMC_multip.eps");

}










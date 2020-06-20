#include "TStyle.h"
#include "TCanvas.h"
#include "/afs/ihep.ac.cn/users/l/lincx/useful/boot.h"
void multip_sigMC_data()
{
    setStyle();myStyle->SetTitleXSize(0.06);//myStyle->SetTitleXOffset(1.2);
    myStyle->SetTitleYSize(0.05);//myStyle->SetTitleYOffset(1.2);
    TCanvas *mul=new TCanvas("mul","mul",800,600);
    mul->SetFillColor(0);
    mul->SetFrameFillColor(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    gStyle->SetOptStat(0);
    mul->SetLeftMargin(0.15);
    mul->SetTopMargin(0.1);
    mul->SetRightMargin(0.1);
    mul->SetBottomMargin(0.15);
   
    // set ytitle
    Double_t xmin=0, xmax=20;  Double_t xbins=20;
    TH1::SetDefaultSumw2(1);
    TString a("Events/"); char b[100];  sprintf(b, "(%.1f)",(xmax-xmin)/xbins);
    TString ytitle = a + b;
 
    TChain *data=new TChain("TDphipi");
    data->Add("/afs/ihep.ac.cn/users/l/lincx/scratchfs/6.6.4.p02/DptoPhiPi/data/root/same_deltaE.root");
    TChain *sigMC=new TChain("TDphipi");
    sigMC->Add("/afs/ihep.ac.cn/users/l/lincx/scratchfs/6.6.4.p02/DptoPhiPi/job_ana/root/same_deltaE.root");
    
    TH1D *data_multip=new TH1D("data_multip","",20, 0, 20);
    data_multip->SetLineColor(kBlue);
    TH1D *sigMC_multip=new TH1D("sigMC_multip","",20, 0, 20);
    sigMC_multip->SetLineColor(kRed);
    
    data->Project("data_multip","index_deltaE","");
    sigMC->Project("sigMC_multip","index_deltaE","");

    cout << "RMS(data_multip) = " << data_multip->GetMean() << " +- " << data_multip->GetMeanError() << endl;
    cout << "RMS(sigMC_multip) = " << sigMC_multip->GetMean() << " +- " << sigMC_multip->GetMeanError() << endl;
    
    //data_multip->Scale(1);
    sigMC_multip->Scale(50);
    
    mul->cd();
    //data_multip->SetMaximum(9000);
    data_multip->Draw("FHIST");
    sigMC_multip->Draw("HISTsame");
    data_multip->GetXaxis()->SetTitle("Multiplicity");
    data_multip->GetYaxis()->SetTitle(ytitle);
    data_multip->GetYaxis()->SetTitleOffset(1.3);
    
    TLegend *legend = new TLegend(0.55,0.6,0.8,0.86);
    legend->SetHeader("D^{+}#rightarrow#phi#pi^{+}");
    legend->AddEntry("data_multip","data","f");
    legend->AddEntry("sigMC_multip","sigMC","f");
    
    legend->SetBorderSize(0);
    legend->SetFillColor(0);
    legend->Draw();
    mul->SaveAs("/afs/ihep.ac.cn/users/l/lincx/picture/phipi_SigMC_data_multip.eps");
}

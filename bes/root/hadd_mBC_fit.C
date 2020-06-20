#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include "TMath.h"
#include "TAxis.h"
#include "TCut.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TFrame.h"
#include "TNtuple.h"
#include "TPostScript.h"
#include "RooFit.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooNovosibirsk.h"
#include "RooCBShape.h"
#include "RooChebychev.h"
#include "RooBreitWigner.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooArgusBG.h"
#include "RooArgList.h"
#include "RooAddPdf.h"
#include "RooAbsPdf.h"
#include "RooKeysPdf.h"
#include "RooPlot.h"
#include "RooWorkspace.h"
#include "/afs/ihep.ac.cn/users/l/lincx/useful/boot.h"

using namespace RooFit;

void hadd_mBC_fit()
{
     // **************** Global Settings *****************
     setStyle();myStyle->SetTitleXSize(0.06);myStyle->SetTitleXOffset(1.2);
     myStyle->SetTitleYSize(0.05);myStyle->SetTitleYOffset(1.2);
     // set ytitle
     Double_t xmin=1.83, xmax=1.8865;  Double_t xbins=100;
     TH1::SetDefaultSumw2(1);
     TString a("Events/"); char b[20];  sprintf(b, "(%5.1f",(xmax-xmin)/xbins  *1000); TString d(" MeV/c^{2})");
     TString ytitle = a + b + d;
     //define variables
     RooRealVar mbc_1("mbc_1", "mbc_1", 1.83, 1.8865);
     TString BranName("mbc_1");
    
     // ***************** Cut ******************
     TCut cut_Mphi = "((M_phi>0.987354)&&(M_phi<1.085))";
     TCut cut_deltaE = "((dE_min>-0.020)&&(dE_min<0.019))";
     TCut cut_mBC = "((mbc_1>1.83)&&(mbc_1<1.8865))";
     TCut cut = cut_deltaE;
     TCut cut_sum =(cut_deltaE&&cut_Mphi&&cut_mBC);

     // ******************** Retrieve Data ***********************
     // ************ Input ***************
     TString FILENAME_I_1 = "cut_MC.root";  // fit file
     TFile *FILE_I_1 = new TFile(FILENAME_I_1);

     // ************* Output ***************	
     //TString FILENAME_O_1 = "/afs/ihep.ac.cn/users/l/lincx/fit_data.root";   // output file
     //TFile *FILE_O_1 = new TFile(FILENAME_O_1, "recreate");
	
     TString TREENAME_I_1 = "TDphipi";   // input tree
     TTree *TREE_I_1 = FILE_I_1->Get(TREENAME_I_1);
     //TTree *TREE_O_1 = TREE_I_1->CopyTree(cut_sum);  //output tree
     Int_t nentries = (Int_t)TREE_I_1->GetEntries();  // all entries
     cout << "************!!!!!!!!!!**************    Entries are:  = " << nentries << endl;
     RooDataSet *data = new RooDataSet("data", "data", TREE_I_1, RooArgSet(mbc_1));

     // *************************** mBC signal pdf ****************************
     //TFile *mcfile = new TFile("/scratchfs/bes/lincx/job_ana/root/cut_MC.root");
     //TTree *sg = (TTree*)mcfile->Get("TDphipi");
     //TTree *sg = si->CopyTree(cut_deltaE&&cut_Mphi); 
     //RooDataSet *sig = new RooDataSet("sig","sig",sg,RooArgSet(mbc_1));
     //RooKeysPdf sig("sig", "sig", mbc_1, *sig, RooKeysPdf::NoMirror, 2);
     //RooAbsPdf   *SignalPdf = 0;
     RooRealVar sigma("sigma", "sigma", 0.0001, 0, 0.001);
     RooRealVar mean("mean","mean",0.0, -0.0001, 0.001) ;
     RooGaussModel gauss("gauss","gauss", mbc_1, mean, sigma);
     TFile *file_sig_pdf  = TFile::Open("/scratchfs/bes/lincx/6.6.4.p02/DptoPhiPi/job_ana/root/pdf_mbc_match_30.root");  // mBC distribution pdf
     RooWorkspace* w = (RooWorkspace*) file_sig_pdf->Get("w");
     cout << "debug1: " << "33333333333333333" << endl;
     w->Print();  // debug in here!!!
     cout << "debug2: " << "99999999999999999" << endl;
     mbc_1= w->var("mbc_1");
     RooAbsPdf *sig = w->pdf("pdf");
     //mbc_1.setBins(10000, "fft");
     RooAbsPdf *SignalPdf=new RooFFTConvPdf("SignalPdf","sig (X) gauss", mbc_1, *sig, gauss);
     //sig->SetName("sig");	 
     
     // *************************** mbc bg pdf *******************************
     RooRealVar edp("edp", "edp", 1.8865);
     RooRealVar k("k", "k", -5, -200, 0);
     RooAbsPdf* BkgPdf = new RooArgusBG("BkgPdf", "BkgPdf", mbc_1, edp, k);

     // *************************** all product pdf ***************************
     //sigmbc = new RooProdPdf("sigmbc","sigmbc",RooArgList(*SignalPdf));
     //totalbg = new RooProdPdf("totalbg","totalbg",RooArgList(*BkgPdf));

     // ******************************* total pdf *****************************
     //RooRealVar nsig("nsig", "#sig events", 0.46*nentries, 0.4*nentries, 0.48*nentries);
     //RooRealVar nbkg("nbkg", "#bkg events", 0.54*nentries, 0.52*nentries, 0.6*nentries);
     //RooRealVar nsig("nsig", "#sig events", 7400, 5000, 9000 );
     //RooRealVar nbkg("nbkg", "#bkg events", 9100, 7000, 11000 );
     //RooAddPdf sum("sum", "sum", RooArgList(*sigmbc,*totalbg), RooArgList(nsig,nbkg));
     
     
     RooRealVar nsig("nsig", "#sig events", 70000, 50000, 90000);
     RooRealVar nbkg("nbkg", "#bkg events", 1000, 100, 8000);
     RooAddPdf sum("sum", "sum", RooArgList(*SignalPdf,*BkgPdf), RooArgList(nsig,nbkg));

     // ************************************* Fit and Draw *******************************************
     // ******************* Fit **********************
     sum.fitTo(*data, Extended(kTRUE));
     //sum.fitTo(*data);  

     // ******************* Draw *********************
     RooPlot* frame = mbc_1.frame();
     data->plotOn(frame, RooFit::Name("data"), LineWidth(3));
     sum.plotOn(frame, RooFit::Name("fit"), LineColor(kRed), LineWidth(5));
     sum.plotOn(frame, RooFit::Name("sig"), Components("SignalPdf"), LineStyle(2), LineColor(kBlue),LineWidth(4));
     sum.plotOn(frame, RooFit::Name("bkg"), Components("BkgPdf"), LineStyle(2), LineColor(kGreen),LineWidth(4));

     //sum.paramOn(frame, Parameters(RooArgList(nsig, nbkg)), Layout(0.2330872, 0.5451678, 0.7205085));
     frame->GetXaxis()->SetTitle("m_{BC} (GeV/c^{2})");
     frame->GetYaxis()->SetTitle(ytitle);
     frame->GetYaxis()->SetTitleOffset(1.23);
     TCanvas *can = new TCanvas("can","mBC",800,600);
     setPad();
     frame->Draw();
     //TPaveText *pt = new TPaveText(0.2130872,0.8305085,0.5251678,0.9491525,"blNDC");
     //TPaveText *pt = new TPaveText(0.2330872,0.7205085,0.5451678,0.8291525,"blNDC");
     //pt->SetBorderSize(0);
     //pt->SetFillColor(4);
     //pt->SetLineColor(5);
     //pt->SetTextColor(5);
     //TText *text = pt->AddText("D^{+}#rightarrow#phi#pi^{+}");
     //pt->Draw();
     //TString t("D^{+}#rightarrow#phi#pi^{+}"); 
     TLegend *legend = new TLegend(0.29,0.55,0.57,0.85,NULL,"brNDC");
     //legend->SetHeader(t);
     //legend->AddEntry("", "D^{+}#rightarrow#phi#pi^{+}","");
     legend->AddEntry(frame->findObject("data"), "Real data","lp");
     legend->AddEntry(frame->findObject("fit"), "Fit result","lp");
     legend->AddEntry(frame->findObject("sig"), "Signal","lp");
     legend->AddEntry(frame->findObject("bkg"), "Background","lp");
     legend->SetFillColor(0);
     legend->SetBorderSize(0);
     legend->SetLineColor(1);
     legend->SetLineStyle(1);
     legend->SetLineWidth(1);
     legend->SetFillStyle(1001);
     legend->Draw();

     //hist->Draw();
     can->SetLeftMargin(0.18);
     can->SetRightMargin(0.15);
     can->Update();
     //can1->SaveAs("kkmbc.eps");

			


}

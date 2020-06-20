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

void hadd_mBC_MKK_2Dfit_OK()
{
     // **************** Global Settings *****************
     setStyle();myStyle->SetTitleXSize(0.06);myStyle->SetTitleXOffset(1.2);
     myStyle->SetTitleYSize(0.05);myStyle->SetTitleYOffset(1.2);
     // set ytitle
     Double_t xmin=1.83, xmax=1.8865;  Double_t xbins=100;
     TH1::SetDefaultSumw2(1);
     TString a("Events/"); char b[20];  sprintf(b, "(%5.1f",(xmax-xmin)/xbins  *1000); TString d(" MeV/c^{2})");
     TString ytitle = a + b + d;
     // set ytitle2
     Double_t xmin1=0.987354, xmax1=1.085;  Double_t xbins1=100;
     TString ap("Events/"); char bp[20];  sprintf(bp, "(%5.1f",(xmax1-xmin1)/xbins1  *1000); TString dp(" MeV/c^{2})");
     TString ytitle2 = ap + bp + dp;
     
     //define variables
     RooRealVar mbc_1("mbc_1", "mbc_1", 1.83, 1.8865);
     TString  BranName("mbc_1");
     RooRealVar M_phi("M_phi", "M_phi", 0.987354, 1.085);
     TString BranName("M_phi");
    
     // ***************** Cut ******************
     TCut cut_Mphi = "((M_phi>0.987354)&&(M_phi<1.085))";
     TCut cut_deltaE = "((dE_min>-0.020)&&(dE_min<0.019))";
     TCut cut_mBC = "((mbc_1>1.83)&&(mbc_1<1.8865))";
     TCut cut = cut_deltaE;
     TCut cut_sum =(cut_deltaE&&cut_Mphi&&cut_mBC);

     // ******************** Retrieve Data ***********************
     // ************ Input ***************
     TString FILENAME_I_1 = "cut_MC.root";  // data root file
     TFile *FILE_I_1 = new TFile(FILENAME_I_1);

     // ************* Output ***************	
     //TString FILENAME_O_1 = "/afs/ihep.ac.cn/users/l/lincx/fit_data.root";   // output file
     //TFile *FILE_O_1 = new TFile(FILENAME_O_1, "recreate");
	
     TString TREENAME_I_1 = "TDphipi";   // input tree
     TTree *TREE_I_1 = FILE_I_1->Get(TREENAME_I_1);
     //TTree *TREE_O_1 = TREE_I_1->CopyTree(cut_sum);  //output tree
     Int_t nentries = (Int_t)TREE_I_1->GetEntries();  // all entries
     cout << "************!!!!!!!!!!**************    Entries are:  = " << nentries << endl;
     RooDataSet *data = new RooDataSet("data", "data", TREE_I_1, RooArgSet(mbc_1,M_phi));

     // *************************** mBC peak signal(phipi) pdf ****************************
     RooAbsPdf   *SignalPdf = 0;
     //RooRealVar sigma1("sigma1", "sigma1", 0.0001, 0, 0.001);
     //RooRealVar mean1("mean1","mean1",0.0, -0.0001, 0.001);
     //RooRealVar sigma1("sigma1", "sigma1", 0.000117746);//angle<10
     //RooRealVar sigma1("sigma1", "sigma1", 0.000114826);//angle<20
     RooRealVar sigma1("sigma1", "sigma1", 0.000114009);//angle<30
     //RooRealVar mean1("mean1", "mean1", 0.0000559155);//angle<10
     //RooRealVar mean1("mean1", "mean1", 0.0000594367);//angle<20
     RooRealVar mean1("mean1", "mean1", 0.0000606450);//angle<30
     RooGaussModel gauss1("gauss1","gauss1",mbc_1, mean1, sigma1);
     TFile *file_sig1_pdf  = TFile::Open("/scratchfs/bes/lincx/6.6.4.p02/DptoPhiPi/job_ana/root/pdf_mbc_match_30.root");  // mBC distribution pdf
     //TFile *file_sig_pdf  = TFile::Open("/afs/ihep.ac.cn/users/l/lincx/scratchfs/DpDm/root/pdf_mbc.root"); // mBC distribution pdf
     RooWorkspace* w = (RooWorkspace*) file_sig1_pdf->Get("w");
     w->Print();  // debug in here!!!
     mbc_1= w->var("mbc_1");
     RooAbsPdf *sig1 = w->pdf("pdf");
     mbc_1.setBins(10000, "fft");
     RooAbsPdf *SignalPdf1=new RooFFTConvPdf("SignalPdf1","sig1 (X) gauss1", mbc_1, *sig1, gauss1);
     //SignalPdf1->SetName("SignalPdf1");	 
     
     // *************************** mBC peak background(kkpi) pdf ****************************
     //RooRealVar sigma1("sigma1", "sigma1", 0.0000263, 0.0,  0.0001);
     //RooRealVar mean1("mean1", "mean1", 0.0000, -0.0001, 0.0001);
     //RooGaussModel gauss1("gauss1","gauss1",mbc_1, mean1, sigma1);
     //TFile *file_peak_pdf  = TFile::Open("/scratchfs/bes/lincx/DpDm/root/pdf_mbc_peakbkg_kkpi.root"); // mBC peaking pdf
     //RooWorkspace* w3 = (RooWorkspace*) file_peak_pdf->Get("w3");
     //w3->Print();  // debug in here!!!
     //mbc_1= w3->var("mbc_1");
     //RooAbsPdf *mckkpi = w3->pdf("pdf3");
     //RooAbsPdf *kkpiPdf=new RooFFTConvPdf("kkpiPdf","mcsig (X) gauss", mbc_1, *mcsig, gauss);
     //kkpiPdf->SetName("bkg_kkpi");  

     // ************************** phi peak signal(phipi or qqbar...) pdf *****************************
     //RooRealVar sigma2("sigma2", "sigma2", 0.0001, 0, 0.001);
     //RooRealVar mean2("mean2", "mean2", 0.0, -0.0001, 0.001); 
     //RooRealVar sigma2("sigma2", "sigma2", 0.0000866634);//angle<10
     //RooRealVar sigma2("sigma2", "sigma2", 0.0000899302);
     RooRealVar sigma2("sigma2", "sigma2", 0.0000900844);
     //RooRealVar mean2("mean2", "mean2", 0.0000310281);//angle<10
     //RooRealVar mean2("mean2", "mean2", 0.0000339837);
     RooRealVar mean2("mean2", "mean2", 0.0000338979);
     RooGaussModel gauss2("gauss2","gauss2",M_phi, mean2, sigma2);
     TFile *file_sig2_pdf  = TFile::Open("/scratchfs/bes/lincx/6.6.4.p02/DptoPhiPi/job_ana/root/pdf_mphi_match_30.root");  // Mphi distribution pdf
     //TFile *file_sig1_pdf  = TFile::Open("/afs/ihep.ac.cn/users/l/lincx/scratchfs/DpDm/root/pdf_mphi.root");  // Mphi distribution pdf
     RooWorkspace* w1 = (RooWorkspace*) file_sig2_pdf->Get("w1");
     w1->Print();
     M_phi= w1->var("M_phi");
     RooAbsPdf *sig2 = w1->pdf("pdf1");
     //RooAbsPdf *mcsig1 = w1->pdf("pdf1");
     M_phi.setBins(10000, "fft");
     RooAbsPdf *SignalPdf2=new RooFFTConvPdf("SignalPdf2","sig2 (X) gauss2", M_phi, *sig2, gauss2) ;
     //SignalPdf2->SetName("SignalPdf2");     

     // ************************** phi peak bg pdf *****************************
     //TFile *file_peak1_pdf  = TFile::Open("/scratchfs/bes/lincx/temp/pdf_mphi_peakbkg1.root"); // mphi peaking pdf
     //RooWorkspace* w2 = (RooWorkspace*) file_peak1_pdf->Get("w2");
     //w2->Print();  // debug in here!!!
     //M_phi= w2->var("M_phi");
     //RooAbsPdf *PeakPdf1 = w2->pdf("pdf2"); 
     
     // *************************** mbc Argus backgrounds(qqbar... or random) pdf *******************************
     //	RooRealVar edp1("edp1", "edp1", 0,-1000,1000);
     //	RooRealVar c("c", "c", 0, -1000, 1000);
     //	RooPolynomial poly("poly", "poly", M_BC, RooArgSet(edp1,c,0));
     RooRealVar edp1("edp1", "edp1", 1.8865);
     //RooRealVar k1("k1", "k1", -5, -20, 0);
     //RooRealVar k1("k1", "k1", -56.2038);//angle<10
     //RooRealVar k1("k1", "k1", -46.4177);
     RooRealVar k1("k1", "k1", -38.5993);
     RooAbsPdf* bkg1 = new RooArgusBG("bkg1", "bkg1", mbc_1, edp1, k1);

     // *************************** phi inverse Argus backgrounds(kkpi or random->a part of qqbar..) pdf ************************
     RooRealVar edp2("edp2", "edp2", 1.085);
     //RooRealVar k2("k2", "k2", -5, -20, 0);
     //RooRealVar k2("k2", "k2", -4.93196);//angle<10
     //RooRealVar k2("k2", "k2", -2.12206);
     RooRealVar k2("k2", "k2", -1.34462e-05);
     RooFormulaVar shifted("shifted", "-1*M_phi+0.987354+1.085", RooArgSet(M_phi));
     RooAbsPdf* bkg2 = new RooArgusBG("bkg2", "bkg2", shifted, edp2, k2);

     // *************************** four components product pdf ***************************
     phipi     = new RooProdPdf("phipi","phipi",RooArgList(*SignalPdf1,*SignalPdf2)); // all phipi signals(Mphi and mBC peak)
     kkpi      = new RooProdPdf("kkpi","kkpi",RooArgList(*SignalPdf1,*bkg2)); // kkpi bkgs(Mphi inver-Argus and mBC peak)
     qqbaretc  = new RooProdPdf("qqbaretc","qqbaretc",RooArgList(*bkg1,*SignalPdf2)); // qqbar etc bkgs(Mphi peak mBC Argus) 
     random    = new RooProdPdf("random","random",RooArgList(*bkg1,*bkg2)); // random backgrounds(Mphi inver-Argus mBC Argus)

     // ******************************* total pdf *****************************
     //RooRealVar nphipi("nphipi", "#sig events", 0.35*nentries, 0.2*nentries, 0.5*nentries);
     //RooRealVar nkkpi("nkkpi", "#kkpi events",  0.1*nentries, 0.05*nentries, 0.2*nentries);
     //RooRealVar nqqbaretc("nqqbaretc", "#qqbaretc events", 0.15*nentries, 0.05*nentries, 0.25*nentries); // mphi peak bg
     //RooRealVar nrandom("nrandom", "#random events", 0.4*nentries, 0.2*nentries, 0.6*nentries);
     //RooAddPdf sum("sum", "sum", RooArgList(*phipi,*kkpi,*qqbaretc,*random), RooArgList(nphipi,nkkpi,nqqbaretc,nrandom));
     RooRealVar nphipi("nphipi", "#sig events", 70000, 20000, 90000);
     RooRealVar nkkpi("nkkpi", "#kkpi events",  100, 0, 500);
     RooRealVar nqqbaretc("nqqbaretc", "#qqbar.etc events", 300, 10, 1000); // mphi peak bg
     RooRealVar nrandom("nrandom", "#random events", 1000, 500, 3000);
     RooAddPdf sum("sum", "sum", RooArgList(*phipi,*kkpi,*qqbaretc,*random), RooArgList(nphipi,nkkpi,nqqbaretc,nrandom));


     // ************************************* Fit and Draw *******************************************
     // ******************* Fit **********************
     sum.fitTo(*data, Extended(kTRUE));

     // ******************* Draw *********************
     TCanvas* can = new TCanvas("can","MKK v.s. mBC",1300,500);
     can->SetFillColor(0);
     can->SetFrameFillColor(0);
     //can->SetLeftMargin(0.1);
     //can->SetRightMargin(0.1);
     can->Divide(2,1);
     setPad();
     
     can->cd(1);
     RooPlot* frame1 = mbc_1.frame();
     data->plotOn(frame1, RooFit::Name("Data"), Binning(100),LineWidth(2));
     sum.plotOn(frame1, RooFit::Name("Fit"), LineColor(kRed), LineStyle(1), LineWidth(3));
     sum.plotOn(frame1, RooFit::Name("phipi"), Components("phipi"), LineStyle(2), LineColor(kBlue),LineWidth(2));
     sum.plotOn(frame1, RooFit::Name("KKpi"), Components("kkpi"), LineStyle(2), LineColor(kGreen),LineWidth(2));
     sum.plotOn(frame1, RooFit::Name("qqbar"), Components("qqbaretc"), LineStyle(2), LineColor(kViolet),LineWidth(2));
     sum.plotOn(frame1, RooFit::Name("Random"), Components("random"), LineStyle(2), LineColor(kGray),LineWidth(2)); 

     //sum.paramOn(frame1, Parameters(RooArgList(nphipi,nkkpi,nqqbaretc,nrandom)), Layout(0.515, 0.9, 0.8491525));
     frame1->GetXaxis()->SetTitle("M_{BC} (GeV/c^{2})");
     frame1->GetYaxis()->SetTitle(ytitle);
     frame1->GetYaxis()->SetTitleOffset(1.25);
     setPad();
     //RooCurve *curve = (RooCurve*)frame1->getObject(1);
     //RooHist *histo = (RooHist*)frame1->getHist("data");
     //TString Par = Form("#chi^{2}/ndf = %.0f/%.0d", curve->chiSquare(*histo,4)*(histo->GetN()-4),histo->GetN()-4);
     //cout<< Par <<endl;
     frame1->Draw();
     
     //TString t("D^{+}#rightarrow#phi#pi^{+}");
     TLegend *legend = new TLegend(0.18,0.56,0.38,0.86,NULL,"brNDC");
     //legend->SetHeader(t);
     //legend->AddEntry("", "D^{+}#rightarrow#phi#pi^{+}","");
     legend->AddEntry(frame1->findObject("Data"), "Real data","lp");
     legend->AddEntry(frame1->findObject("Fit"), "Fit result","lp");
     legend->AddEntry(frame1->findObject("phipi"), "D^{#pm}#rightarrow#phi#pi^{#pm}","lp");
     legend->AddEntry(frame1->findObject("KKpi"), "D^{#pm}#rightarrowK^{#pm}K^{#bar{+}}#pi^{#pm}","lp");
     legend->AddEntry(frame1->findObject("qqbar"), "non-D#bar{D} #phi","lp");
     legend->AddEntry(frame1->findObject("Random"), "Random bkg","lp");
     legend->SetFillColor(0);
     legend->SetBorderSize(0);
     legend->SetLineColor(1);
     legend->SetLineStyle(1);
     legend->SetLineWidth(1);
     legend->SetFillStyle(1001);
     legend->Draw();

     can->cd(2);
     RooPlot* frame2 = M_phi.frame();
     data->plotOn(frame2, Binning(100),LineWidth(2));
     sum.plotOn(frame2,LineColor(kRed), LineStyle(1), LineWidth(3));
     sum.plotOn(frame2, Components("phipi"), LineStyle(2), LineColor(kBlue),LineWidth(2));
     sum.plotOn(frame2, Components("kkpi"), LineStyle(2), LineColor(kGreen),LineWidth(2));
     sum.plotOn(frame2, Components("qqbaretc"), LineStyle(2), LineColor(kViolet),LineWidth(2));
     sum.plotOn(frame2, Components("random"), LineStyle(2), LineColor(kGray),LineWidth(2));     

     frame2->GetXaxis()->SetTitle("M_{K^{+}K^{-}} (GeV/c^{2})");
     frame2->GetYaxis()->SetTitle(ytitle2);
     frame2->GetYaxis()->SetTitleOffset(1.25);
     //TCanvas *can1 = new TCanvas("can1","mBC",900,600);
     setPad();
     frame2->Draw();
     //TPaveText *pt = new TPaveText(0.2130872,0.8305085,0.5251678,0.9491525,"blNDC");
     //TPaveText *pt = new TPaveText(0.2830872,0.7305085,0.5651678,0.8491525,"blNDC");
     //pt->SetBorderSize(2);
     //pt->SetFillColor(0);
     //pt->SetLineColor(5);
     //pt->SetTextColor(5);
     //TText *text = pt->AddText("D^{+}#rightarrow#phi#pi^{+}");
     //pt->Draw();
     //hist->Draw();
     can->Update();
    // can->SaveAs("/afs/ihep.ac.cn/users/l/lincx/picture/phipi_input_output_2Dfit.eps");


     /*TPaveText *pt1 = new TPaveText(0.5,0.7705085,0.8,0.8791525,"blNDC");
     pt1->SetBorderSize(2);
     pt1->SetFillColor(0);
     //pt1->SetLineColor(5);
     //pt1->SetTextColor(5);
     TText *text = pt1->AddText("D^{+}#rightarrow#phi#pi^{+}");
     pt1->Draw();
   //hist->Draw();
     can2->SetLeftMargin(0.18);
     can2->SetRightMargin(0.15);
     can2->Update();
    */ //can2->SaveAs("phi.eps");




}

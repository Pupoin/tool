#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooCBShape.h"
#include "RooConstVar.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "RooWorkspace.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TAxis.h"
#include <iostream>
#include "/afs/ihep.ac.cn/users/z/zhulinx/useful/boot.h"
using namespace std;
using namespace RooFit;

void fitOmega(){
	
	TCanvas *can = new TCanvas("can","can",700,600);
	
	double xmin = 0.67, xmax = 0.9;
    int xbins = 80;
    TString a("#bf{Events/}");
    char b[20];  sprintf(b, "#bf{(%5.1f}",(xmax - xmin)/xbins  *1000);
    TString d("#bf{ MeV/c^{#it{2}})}");
    TString ytitle = a+b+d;
	
	TChain chain("tree");
    chain.Add("4*data.root");
    TTree *myTree = chain.CopyTree("M_BC_r3c>2.25 && etaprimemr3c>0.6&&etaprimemr3c<0.92 && (chi2_min_r3c<30 && np!=0 && npbar !=0 )", "", 1000000000, 0); 
	
	RooRealVar* etaprimemr3c = new RooRealVar("etaprimemr3c", "etaprimemr3c", xmin, xmax);
	RooDataSet* dataSet = new RooDataSet("dataSet", "dataSet", RooArgSet(*etaprimemr3c), Import(*myTree));
	
	RooRealVar* mean_1 = new RooRealVar("mean_1", "mean_1", 0.782, 0.7, 0.85);
	RooRealVar* sigma_1 = new RooRealVar("sigma_1", "sigma_1", 0.011, 0., 1.);
	RooRealVar* mean_2 = new RooRealVar("mean_2", "mean_2", 0.55, 0.5, 0.6);
	RooRealVar* sigma_2 = new RooRealVar("sigma_2", "sigam_2", 0.001, 0., 1.);
	RooRealVar* a_1 = new RooRealVar("a_1", "a_1", -0.6, -1., 1.);
	RooRealVar* a_2 = new RooRealVar("a_2", "a_2", 0., -1., 1.);
	
	RooRealVar* frac_1 = new RooRealVar("frac_1", "frac_1", 0.5, 0., 1.);
	RooRealVar* nsig = new RooRealVar("nsig", "nsig", 5000., 0., 10000.);
	RooRealVar* nbkg = new RooRealVar("nbkg", "nbkg", 10000., 0., 50000.);
	
	RooGaussian* gauss_1 = new RooGaussian("gauss_1", "gauss_1", *etaprimemr3c, *mean_1, *sigma_1);
	RooGaussian* gauss_2 = new RooGaussian("gauss_2", "gauss_2", *etaprimemr3c, *mean_2, *sigma_2);
	// RooAddPdf* sig = new RooAddPdf("sig", "sig", RooArgList(*gauss_1, *gauss_2), RooArgList(*frac_1));
	
	TFile* f = TFile::Open("./omegashape.root");
	RooWorkspace* w = (RooWorkspace*)f -> Get("wspace");
	RooAbsPdf* simuPdf = w -> pdf("modelPdf"); simuPdf->SetName("simuPdf");
	
	RooRealVar* mean = new RooRealVar("mean", "mean", 0.001, 0.00001, 0.01);
	RooRealVar* sigma = new RooRealVar("sigma", "sigma", 0.0001, 0.00001, 0.01);
	RooGaussian* gauss = new RooGaussian("gauss", "gauss", *etaprimemr3c, *mean, *sigma);
	RooFFTConvPdf* sig = new RooFFTConvPdf("sig", "simuPdf (*) gauss", *etaprimemr3c, *simuPdf, *gauss);
    sig->setBufferFraction(0);
    sig->setBufferStrategy(RooFFTConvPdf::Flat);

	//RooPolynomial* bkg = new RooPolynomial("poly1", "poly1", *etaprimemr3c, RooArgList(*a_1), lowestOrder = 1);
	
	RooChebychev* bkg = new RooChebychev("bkg", "bkg", *etaprimemr3c, RooArgList(*a_1, *a_2));
	
	RooAddPdf* pdf = new RooAddPdf("pdf", "pdf", RooArgList(*sig, *bkg), RooArgList(*nsig, *nbkg));
	//RooAddPdf* pdf = new RooAddPdf("pdf", "pdf", RooArgList(*bkg), RooArgList(*nbkg));
	pdf -> fitTo(*dataSet, Extended(kTRUE));
	RooPlot* xframe = etaprimemr3c->frame(Title(" "), Bins(xbins));
	dataSet -> plotOn(xframe);
	xframe->Draw();
	pdf -> plotOn(xframe, LineColor(kRed));
	pdf -> plotOn(xframe, Components(*sig), LineColor(kGreen), LineStyle(kDashed));
	//pdf -> plotOn(xframe, Components(*gauss_2),LineColor(kRed), LineStyle(kDashed));
	//pdf -> plotOn(xframe, Components(*sig), LineColor(kViolet), LineStyle(kDashed));
	pdf -> plotOn(xframe, Components(*bkg),LineColor(kBlue), LineStyle(kDashed));
	xframe -> GetXaxis()->SetTitle("M_{#pi^{+}#pi^{-}#pi^{0}} (GeV/#font[12]{c^{2}})");
    xframe -> GetYaxis()->SetTitle(ytitle);
    xframe->Draw();
	//arrows
    TArrow *arrow1 = new TArrow(0.68, 150., 0.68, 0., 0.05, ">");
    arrow1 -> SetLineWidth(4);
    arrow1 -> SetLineColor(4);
    //arrow1 -> SetAngle(40);
    TArrow *arrow2 = new TArrow(0.72, 150., 0.72, 0., 0.05, ">");
    arrow2 -> SetLineWidth(4);
    arrow2 -> SetLineColor(4);
	arrow1 -> Draw();
	arrow2 -> Draw();
	TArrow *arrow3 = new TArrow(0.84, 150., 0.84, 0., 0.05, ">");
    arrow3 -> SetLineWidth(4);
    arrow3 -> SetLineColor(4);
    TArrow *arrow4 = new TArrow(0.89, 150., 0.89, 0., 0.05, ">");
    arrow4 -> SetLineWidth(4);
    arrow4 -> SetLineColor(4);
	arrow3 -> Draw();
	arrow4 -> Draw();
	TArrow *arrow5 = new TArrow(0.76, 150., 0.76, 0., 0.05, ">");
    arrow5 -> SetLineWidth(4);
    arrow5 -> SetLineColor(2);
    TArrow *arrow6 = new TArrow(0.8, 150., 0.8, 0., 0.05, ">");
    arrow6 -> SetLineWidth(4);
    arrow6 -> SetLineColor(2);
	arrow5 -> Draw();
	arrow6 -> Draw();

    can->SetLeftMargin(0.18);
    can->SetRightMargin(0.15);
    can->Update();
	can->SaveAs("fitOmega_sideband.png");
	can->SaveAs("fitOmega_sideband.pdf");
	
	Double_t sb_1(0.68), sb_2(0.72), sb_3(0.84), sb_4(0.89);
	// Double_t sb_5(0.84), sb_6(0.89);
	Double_t sig_1(0.76), sig_2(0.8);
    etaprimemr3c->setRange("sigwindow",sig_1,sig_2);
	etaprimemr3c->setRange("sbwindow1", sb_1, sb_2);
	etaprimemr3c->setRange("sbwindow2", sb_3, sb_4);
	// etaprimemr3c->setRange("sbwindow3", sb_5, sb_6);
    RooAbsReal *sigInte = bkg->createIntegral(*etaprimemr3c, NormSet(*etaprimemr3c), Range("sigwindow"));
	RooAbsReal *sbInte1 = bkg->createIntegral(*etaprimemr3c, NormSet(*etaprimemr3c), Range("sbwindow1"));
	RooAbsReal *sbInte2 = bkg->createIntegral(*etaprimemr3c, NormSet(*etaprimemr3c), Range("sbwindow2"));
	//RooAbsReal *sbInte3 = bkg->createIntegral(*etaprimemr3c, NormSet(*etaprimemr3c), Range("sbwindow3"));
    Double_t Nsig = sigInte->getVal()*nbkg->getVal();
    Double_t Nsigerr = sigInte->getVal()*nbkg->getError();
	Double_t Nbkg1 = sbInte1->getVal()*nbkg->getVal();
	Double_t Nbkgerr1 = sbInte1->getVal()*nbkg->getError();
	Double_t Nbkg2 = sbInte2->getVal()*nbkg->getVal();
	Double_t Nbkgerr2 = sbInte2->getVal()*nbkg->getError();
	//Double_t Nbkg3 = sbInte3->getVal()*nbkg->getVal();
	//Double_t Nbkgerr3 = sbInte3->getVal()*nbkg->getError();


    cout << "The number of signal is " << Nsig << endl;
    cout << "The error is " << Nsigerr << endl;
	cout << "The number of bkg1 is " << Nbkg1 << endl;
	cout << "The error1 is " << Nbkgerr1 << endl;
	cout << "The number of bkg2 is " << Nbkg2 << endl;
	cout << "The error2 is " << Nbkgerr2 << endl;
	//cout << "The number of bkg3 is " << Nbkg3 << endl;
	//cout << "The error3 is " << Nbkgerr3 << endl;

	cout << "The ratio between signal and background is " << (Nsig)/(Nbkg1+Nbkg2) << endl;
	//The ratio between signal and background is 0.582975
}

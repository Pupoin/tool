#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include "TStyle.h"
#include "TDirectory.h"
#include "TCut.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "TTree.h"
#include "TPostScript.h"
#include "TCanvas.h"
#include "TNtuple.h"
#include "RooRealVar.h"
#include "RooNovosibirsk.h"
#include "RooCBShape.h"
#include "RooChebychev.h"
#include "RooArgusBG.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooArgList.h"
#include "RooAddPdf.h"
#include "RooPlot.h"
#include "RooMCStudy.h"
//#include "PlotDataMC.h"
#include "RooGaussian.h"
#include "RooKeysPdf.h"
#include "RooGaussian.h"
#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "/afs/ihep.ac.cn/users/l/lincx/useful/boot.h"

const double MBC = 1.86961;
//const double MBC = 1.8648;
using namespace RooFit;

int dEFit() {
	gStyle->SetFrameBorderMode(0);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadColor(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetStatColor(0);
	gStyle->SetTitleFillColor(0);

	// set the paper & margin sizes
	gStyle->SetPaperSize(20,26);
	gStyle->SetPadTopMargin(0.05);
	gStyle->SetPadRightMargin(0.05);
	gStyle->SetPadBottomMargin(0.16);
	gStyle->SetPadLeftMargin(0.15);

	// use large Times-Roman fonts
	gStyle->SetTitleFont(132,"xyz");  // set the all 3 axes title font
	gStyle->SetTitleFont(132," ");    // set the pad title font
	gStyle->SetTitleSize(0.06,"xyz"); // set the 3 axes title size
	gStyle->SetTitleSize(0.06," ");   // set the pad title size
	gStyle->SetLabelFont(132,"xyz");
	gStyle->SetLabelSize(0.06,"xyz");
	gStyle->SetTextFont(132);
	gStyle->SetTextSize(0.08);
	gStyle->SetStatFont(132);

	// use bold lines and markers
	gStyle->SetMarkerStyle(8);
	gStyle->SetMarkerSize(0.8);
	gStyle->SetHistLineWidth(1.85);
	gStyle->SetLineStyleString(2,"[12 12]");// postscript dashes

	//..Get rid of X error bars
	gStyle->SetErrorX(0.001);

	// do not display any of the standard histogram decorations
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);

	// put tick marks on top and RHS of plots
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);
        
        //*******************Add the two lines below***********************
        setStyle();myStyle->SetTitleXSize(0.08);//myStyle->SetTitleXOffset(1.2);
        myStyle->SetTitleYSize(0.07);//myStyle->SetTitleYOffset(1.2);

	gSystem->Load("libRooFit");

	bool   IsNuBinned(0), m_IsFloat(1);
	int    m_bkg(1);
	Int_t  WhichPdf(2);
	Double_t  Nbin(100), up(-0.1), lo(0.1);
	//Double_t  Nbin(275), up(1.83), lo(1.885);

	TString  BranName("dE_min"), McHist(">>McHknew"), InHist(">>InHknew"), DaHist(">>DaHknew");
	TString  McName = BranName + McHist;
	TString  InName = BranName + InHist;
	TString  DaName = BranName + DaHist;

	TFile *Mcf, *Inf, *Daf; 
	TH1F  *McHknew, *InHknew, *DaHknew, *FitHist;
	TTree *McOutTree, *DaOutTree, *InOutTree, *FitTree;

	//TCut cut_per="passflag==1";
	TCut cut_per="";
	//cut_per+="mks>0.484&&mks<0.512";
	//cut_per+="(dcyL/dcyLdE)>2.";
	//cut_per+="pichi<20";

	//	TTree *pdfT;
	//
	//	pdfT=Tree->CopyTree(cut_per1,"",100000000,0);

	//Mcf       = new TFile("data_merge.root");
	//Mcf       = new TFile("gen_merge.root");
	//Mcf       = new TFile("gen_merge.root");
	Mcf       = new TFile("/scratchfs/bes/lincx/job_ana/root/all_deltaE.root");
	//Mcf       = new TFile("D0_S.root");
	McHknew   = new TH1F("McHknew", "McHknew", Nbin, up, lo);
	McOutTree = (TTree*)Mcf->Get("TDphipi");
        McOutTree->Draw(McName,cut_per);
	//McOutTree->Draw(McName,"abs(deltaE)<0.03&&Mode==104&&CosVeto==0&&minangle>10&&(Ntrks>0||Nshower>0)");
	cout<<" Mc signal "<<McHknew->GetEntries()<<endl;
	//RooRealVar deltaE("deltaE","",-0.1,0.1);
	//RooRealVar bardE("bardE","",-0.1,0.1);
	//RooRealVar CosVeto("CosVeto","",-1,2);
	//RooRealVar Nshower("Nshower","",-1,2);
	//RooRealVar Ntrks("Ntrks","",-1,2);
	//RooRealVar Mode("Mode","",103,106);
	//RooRealVar minangle("minangle","",0,1001);

	//RooArgSet ntupleVarSet1(x, deltaE, CosVeto, Nshower, Ntrks, Mode, minangle);
	//RooDataSet *data1 = new RooDataSet("data1","", McOutTree, ntupleVarSet1);
	//RooDataSet data = (RooDataSet)data1->reduce( cut_per );

	FitHist   = McHknew;

	// Parameters
	//	RooRealVar m0("m0","m0",1.8865,1.88,1.89);
	RooRealVar k("k","k",-9,-100,100);
	//RooRealVar k("k","k",-13.321);
	//RooRealVar k("k","k",-10);

	RooRealVar Pi0(BranName, "Pi0", up, lo);

	//Hispdf
	TH1F *a = new TH1F("a", "a", Nbin, up, lo);
	//TFile *F1 = new TFile("../eff/Pdf.root");
	//a =(TH1F*)F1->Get("pdf__deltaE");

	//RooDataHist* sigHist = new RooDataHist("sigHist", "sigHist", Pi0, a);
	//RooHistPdf sigPdf("sigPdf","",Pi0, *sigHist, 2);

	//Keyspdf
	//Data = new RooDataSet("data", "KnewMass", pdfT, Pi0);
	//RooKeysPdf sigPdf("pdf", "", Pi0, *Data);

	//TFile* f_pdf = new TFile("Pdf.root","recreate");
	//sigPdf->Write();
	//f_pdf->Close();

	//TFile *F = new TFile("../mc_out/PiPi_Pdf.root");
	//TFile *F = new TFile("../mc_out/KK_Pdf.root");
	//TH1F *b;
	//b =(TH1F*)F->Get("pdf__mbc");
	//RooDataHist* bgHist = new RooDataHist("bgHist", "bgHist", Pi0, b);
	//RooHistPdf bgPdf("bgPdf","bgPdf",Pi0, *bgHist, 2);

	//RooRealVar m0("m0","m0",0,-0.007,0.007);
	//RooRealVar m0("m0","m0",0.0024);
	//RooRealVar covsigma("covsigma", "covsigma", 0.001, 0.00, 0.01);
	//RooRealVar covsigma1("covsigma1", "covsigma1", 0.001, 0.00, 0.01);
	//RooRealVar covsigma("covsigma", "covsigma", 0.003);
	//RooRealVar covsigma1("covsigma1", "covsigma1", 0.003);
	//RooBifurGauss gauss("gauss","gauss",Pi0,m0,covsigma,covsigma1) ;
	//RooGaussModel gauss("gauss", "gauss", Pi0, m0, covsigma);

	//**niv
	RooRealVar *D0, *sigma, *asym, *amp, *sigmatail,*frac;
	D0 = new RooRealVar("D0", "D0", 0,-0.05,0.05);
	sigma = new RooRealVar("sigma", "sigma", 0.001,0.0000,0.3);
	RooRealVar mH("mH","mean",0,-0.05,0.05) ;
	sigmatail = new RooRealVar("sigmatail", "sigmatail", 0.001,0.00,0.3);
	frac  = new RooRealVar("frac", "fraction", 0.5, 0, 1.0);
	//RooRealVar mH("mH","meln",1.87,1.86,1.875) ;
	asym  = new RooRealVar("asym", "asymmetry", 1.81, 0, 9000.0);
	//asym  = new RooRealVar("asym", "asymmetry", 1.28186);

	//**niv
	//amp   = new RooRealVar("amp", "amplitude", 5);
	amp   = new RooRealVar("amp", "amplitude", 5, 0,50);
	//**niv
	RooRealVar tail("tail", "tail of Novosibirsk", -0.5, -3, 3);

	RooRealVar mean(*D0);

	RooAbsPdf   *sig = 0;

	if(WhichPdf==1) {
		sig = new RooNovosibirsk("Seberia", "Seberia0", Pi0, mean, *sigma, tail); //asymetry tail of guass
	}else if(WhichPdf==2) {
		//			sig = new RooGaussian("gauss", "gauss", Pi0, mean, *sigma);
		RooGaussModel gaussmcore("gaussmcore","coregauss",Pi0,mean,*sigma);
		RooGaussModel gaussmtail("gaussmtail","tailgauss",Pi0,mH,*sigmatail);
		sig = new RooAddModel("sig","gaussm",RooArgList(gaussmcore,gaussmtail),*frac);

	}else if(WhichPdf==3) {
		TString shiftvar("");
		shiftvar += MBC*2;
		shiftvar += " - " + BranName;
		RooFormulaVar mean_shifted("mean_shifted", shiftvar, RooArgSet(Pi0));
		sig = new RooCBShape("CB", "CB", mean_shifted, mean, *sigma, *asym, *amp);//crystal ball 
	}else if(WhichPdf==4) {
		sig = new RooFFTConvPdf("sig", "MC (X) gauss", Pi0, sigPdf, gauss, 2) ;//fx X gx
		//sig = new RooFFTConvPdf("sig", "MC (X) gauss", Pi0, *sigPdf, gauss, 2) ;
	}

	RooRealVar c0("c0", "coefficient #0", -100000,100000);
	RooRealVar c1("c1", "coefficient #1", -100000,100000);
	RooRealVar c2("c2", "coefficient #2", -100000,100000);
	//RooRealVar c0("c0", "coefficient #0", -0.367);
	//RooRealVar c1("c1", "coefficient #1", 0.1007);
	//RooRealVar c2("c2", "coefficient #2", 0.03);
	RooRealVar c3("c3", "coefficient #3", -100000,100000);
	RooRealVar c4("c4", "coefficient #4", -100000,100000);

	RooKeysPdf *kestOffSet = 0;

	//RooRealVar nsig("nsig", "signal fraction", 70000,0,500000);
	RooRealVar nsig("nsig", "signal fraction", 100000,0,200000);
	//RooRealVar nbkg("nbkg", "bg fraction", 50000,0,500000);
	RooRealVar nbkg("nbkg", "bg fraction", 70000,0,200000);
	RooRealVar nbkg1("nbkg1", "bg fraction", 0,100000);
	RooRealVar nbkg2("nbkg2", "bg fraction", 0,100000);

	//RooAbsPdf *bkg_poly = kestOffSet;
	RooAbsPdf  *bkg_poly = new RooChebychev("bkg_poly", "background pdf", Pi0, RooArgList(c0));

	RooRealVar  bkg_D0("bkg_D0", "bkg_D0", 1.87,1.84,1.98);
	RooRealVar  bkg_sigma("bkg_sigma", "bkg_sigma",  0.01,0.0000,0.30);

	RooAbsPdf  *bkg_gaus = new RooGaussian("bkg_gauss", "bkg_gauss", Pi0, bkg_D0, bkg_sigma);

	RooAbsPdf  *bkg = 0;
	if(m_bkg==0) {
		RooRealVar mt("mt","",1.885,1.89);
		bkg = new RooArgusBG("argus","argus",Pi0,mt,k) ;
		//bkg = new RooArgusBG("argus","argus",Pi0,RooConst(1.8866),k) ;
	}
	else if(m_bkg==1) {
		bkg = bkg_poly;
	}
	else if(m_bkg==2) {
		bkg = bkg_gaus;
	}

	RooAbsData*  rHKnew = 0;
	RooDataSet*  data = 0;

	if(IsNuBinned==0) {
		rHKnew  = new RooDataHist("rHKnew", "Knew mass(GeV)", Pi0, FitHist);
	}else {
		//RooRealVar* pi0chi = new RooRealVar("pi0chi", "", 0,20);
		//RooRealVar* mpi0 = new RooRealVar("mpi0", "", 0.107,0.163);
		//RooRealVar* mks = new RooRealVar("mks", "", 0.484,0.512);
		//RooRealVar* deltaE = new RooRealVar("deltaE", "", -0.1,0.1);
		//RooRealVar* dcyL = new RooRealVar("dcyL", "", -100,100);
		//RooRealVar* dcyLdE = new RooRealVar("dcyLdE", "", -100,100);
		////TCut cut1 = "mpi0<0.15&&mpi0>0.112&&chisq<20";
		//TCut cut1 = "deltaE<0.045&&deltaE>-0.071&&mks<0.512&&mks>0.484&&pi0chi<20&&mpi0<0.15&&mpi0>0.112&&dcyL/dcyLdE>2";
		////TCut cut1 = "deltaE<0.06&&deltaE>-0.089&&mks<0.512&&mks>0.484&&pi0chi<20&&mpi0<0.15&&mpi0>0.112&&dcyL/dcyLdE>2";
		//RooArgSet ntupleVarSet(Pi0, *pi0chi, *mpi0, *deltaE, *dcyL, *dcyLdE, *mks);
		//data = new RooDataSet("data", "KnewMass", FitTree, ntupleVarSet);
		//RooDataSet reducedata = (RooDataSet)data->reduce( cut1 );
		rHKnew = new RooDataSet("rHKnew", "KnewMass", FitTree, Pi0);
	}

	RooPlot* frame5 = Pi0.frame();
	RooPlot* frame6 = Pi0.frame();
	frame5->SetXTitle("#DeltaE(GeV)");
        frame5->SetYTitle("Events/(2 MeV)");
	rHKnew->plotOn(frame5, Binning(Nbin));
	//rHKnew->plotOn(frame5);
	//reducedata.plotOn(frame5,Binning(Nbin));

	RooAddPdf *model = 0;
	model = new RooAddPdf("model", "model", RooArgList(*sig, *bkg), RooArgList(nsig, nbkg));
	//model = new RooAddPdf("model", "model", RooArgList(*sig, bgPdf), RooArgList(nsig, nbkg));
	//model = new RooAddPdf("model", "model", RooArgList(sigPdf, *bkg), RooArgList(nsig, nbkg));
	//model = new RooAddPdf("model", "model", RooArgList(*bkg), RooArgList(nbkg));

	//cout<<" "<<rHKnew<<endl;
	RooFitResult *res=model->fitTo(*rHKnew, Extended(kTRUE), Save());
	res->Print("v");
	//model->fitTo(reducedata, Extended(kTRUE));

	Pi0.setRange("McHknew",-0.1,0.1);

	RooAbsReal *inteSignal=sig->createIntegral(Pi0,NormSet(Pi0),Range("McHknew"));
	cout<<"*********************************************************"<<endl;
	cout<<"*********************************************************"<<endl;
	cout<<"Pi0: "<<inteSignal->getVal()<<endl;
	cout<<"sig number:  "<<inteSignal->getVal()*nsig.getVal()<<"+-"<<nsig.getError()*inteSignal->getVal()<<endl;
	cout<<"*********************************************************"<<endl;
	cout<<"*********************************************************"<<endl;

	//model->paramOn(frame5);
	model->plotOn(frame5, RooFit::LineColor(kRed));
	//model->plotOn(frame5, Components("CB"), LineColor(kGreen), LineStyle(kDashed));
	model->plotOn(frame5, Components("sig"), LineColor(kRed), LineStyle(kDashed));
	//model->plotOn(frame5, Components("sigPdf"), LineColor(kGreen), LineStyle(kDashed));
	//model->plotOn(frame5, Components("gauss"), LineColor(kRed), LineStyle(kDashed)); 
	//model->plotOn(frame5, Components("gaussmtail"), LineColor(kBlue+2), LineStyle(kDashed)); 
	//model->plotOn(frame5, Components("gaussmcore"), LineColor(kRed), LineStyle(kDashed));
	//model->plotOn(frame5, Components("bgPdf"), LineColor(kBlue), LineStyle(kDashed));
	//model->plotOn(frame5, Components("argus"), LineColor(kBlue), LineStyle(kDashed));
	model->plotOn(frame5, Components("bkg_poly"), LineColor(kBlue), LineStyle(kDashed));
	//model->plotOn(frame5, Components("bkg_gauss"), LineColor(kBlack));
	TCanvas* Canvas = new  TCanvas( "Canvas", "beam constraint mass" ) ;

        //*******************Add the two lines below***********************
        //setStyle();myStyle->SetTitleXSize(0.08);//myStyle->SetTitleXOffset(1.2);
        //myStyle->SetTitleYSize(0.07);//myStyle->SetTitleYOffset(1.2);
        Canvas->SetFillColor(0);
        Canvas->SetFrameFillColor(0);

	cout<<" #### "<<nsig.getVal()<<endl;
	cout<<" #### "<<nbkg.getVal()<<endl;

	//frame5->SetTitle("D+");
        frame5->GetYaxis()->SetTitleOffset(1.15);
	frame5->Draw();
	//rHKnew->->SaveAs("Fit.gif");


	//calculate chisq for check the fit quality 
	RooCurve *curve = (RooCurve*)frame5->getObject(1);
	RooHist *histo = (RooHist*)frame5->getHist("h_rHKnew");

	cout << histo->GetN() << endl;
	cout << "chisquare==" << curve->chiSquare(*histo, 4) <<endl;

	//	double x[1000] = {0}; 
	//	double y[1000] = {0};
	//	double xa[1000] = {0}; 
	//	double ya[1000] = {0};
	//	double y_fit[1000] = {0};
	//	double x_fit[1000] = {0};
	//	double tmp_y = 0;
	//	double eyl[1000] = {0}; 
	//	double eyh[1000] = {0}; 
	//	double exl[1000] = {0};
	//	double exh[1000] = {0};
	//	int ndf = 0;
	//
	//	//the value of each variable for histo gram
	//	for (int i = 0; i<histo->GetN(); i++) {
	//		histo->GetPoint(i,x[i],y[i]);
	//		eyl[i] = histo->GetEYlow()[i];
	//		eyh[i] = histo->GetEYhigh()[i];
	//		exl[i] = histo->GetEXlow()[i];
	//		exh[i] = histo->GetEXhigh()[i];
	//	}
	//
	//	for (int i = 0; i<histo->GetN(); i++) {
	//		tmp_y += y[i];
	//		if ( tmp_y < 10 ) continue;
	//		xa[ndf] = x[i];
	//		ya[ndf] = tmp_y;
	//		tmp_y = 0;
	//		ndf++;
	//	}
	//	if ( tmp_y != 0 ) {
	//		xa[ndf] = x[histo->GetN()-1];
	//		ya[ndf] = tmp_y;
	//	}
	//	double xstart(0), xstop(0), ystart(0), ystop(0);
	//	curve->GetPoint(0,xstart,ystart);
	//	curve->GetPoint(curve->GetN()-1,xstop,ystop);
	//	for (int i = 0; i<histo->GetN(); i++) {
	//		if (x[i] > xstop || x[i] < xstart ) continue;
	//		x_fit[i] = x[i];
	//		y_fit[i] = curve->average(x[i]-exl[i],x[i]+exh[i]);
	//	}
	//	double y_fb[1000] = {0};
	//	int num = 0;
	//	for (int i=0; i<histo->GetN(); i++) {
	//		if ( y[i] < 1 ) continue;
	//		if ( x[i] <= xa[num] ) {
	//			y_fb[num] += y_fit[i];
	//		}
	//		else {
	//			num++;
	//			y_fb[num] += y_fit[i];
	//		}
	//	}
	//	float tx[1000]={0};
	//	float tx_err[1000]={0};
	//	float ty[1000]={0};
	//	float chi_err[1000]={0};
	//	float chisq = 0;
	//	for ( int tk = 0; tk != ndf; tk++){
	//		tx[tk]=xa[tk];
	//		ty[tk]=(ya[tk] - y_fb[tk])/sqrt(y_fb[tk]);
	//		chi_err[tk]=sqrt(ya[tk])/sqrt(y_fb[tk]);
	//		chisq += ty[tk] * ty[tk];
	//	}

	//TPaveText *pt = new TPaveText(0.15,0.55,0.48,0.95,"BRNDC");
	TPaveText *pt = new TPaveText(0.20,0.54,0.47,0.94,"BRNDC"); //************Change the TPave Param********************
	pt->SetBorderSize(1);
	pt->SetFillColor(10);
	pt->SetTextAlign(12);
	pt->SetTextSize(0.03);
	TString Par0  = "D^{+}#rightarrow#phi#pi^{+}(Signal MC)" ;
	//TString Par5  = "K^{+} K^{-}(data)" ;
	//TString Par5  = "D^{0} #rightarrow K_{S} #pi^{0} " ;
	TString Par1V = Form("%5.0f", nbkg.getVal() );
	TString Par1E = Form("%3.0f", nbkg.getError() );
	TString Par1  = "N_{bkg} = " + Par1V + " #pm " + Par1E;
	TString Par2V = Form("%5.0f", nsig.getVal() );
	TString Par2E = Form("%3.0f", nsig.getError() );
	TString Par2  = "N_{sig} = " + Par2V + " #pm " + Par2E;
	
	TString Par3V = Form("%7.2f", (mean.getVal())*1000 );
	//TString Par3V = Form("%7.2f", (2*MBC-mean.getVal())*1000.00 );	
	//TString Par3E = Form("%3.2f", mean.getError()*1000.00 );
	TString Par3E = Form("%3.2f", mean.getError()*1000 );
	TString Par3  = "m_{1} = " + Par3V + " #pm " + Par3E + " MeV" ;
	TString Par4V = Form("%4.2f", sigma->getVal()*1000.00 );
	TString Par4E = Form("%4.2f", sigma->getError()*1000.00 );
	TString Par4  = "sigma_{1} = " + Par4V + " #pm " + Par4E + " MeV" ;
	TString Par5V = Form("%7.2f", mH.getVal()*1000.00 );
	TString Par5E = Form("%3.2f", mH.getError()*1000.00 );
	TString Par5  = "m_{2} = " + Par5V + " #pm " + Par5E + " MeV" ;
	TString Par6V = Form("%4.2f", sigmatail->getVal()*1000.00 );
	TString Par6E = Form("%4.2f", sigmatail->getError()*1000.00 );
	TString Par6  = "sigma_{2} = " + Par6V + " #pm " + Par6E + " MeV" ;
        TString Par7V = Form("%5.4f", frac->getVal() );
        TString Par7E = Form("%5.4f", frac->getError() );
        TString Par7  = "sig1frac = " + Par7V + " #pm " + Par7E;
	TString Par8  = Form("#chi^{2}/ndf = %.0f/%.0d", curve->chiSquare(*histo, 4)*(histo->GetN()-4),histo->GetN()-4 );
	TText *text;
	text = pt->AddText(Par0);
	text = pt->AddText(Par1);
	text = pt->AddText(Par2);
	text = pt->AddText(Par3);
	text = pt->AddText(Par4);
	text = pt->AddText(Par5);
	text = pt->AddText(Par6);
	text = pt->AddText(Par7);
        text = pt->AddText(Par8);
	TArrow xy1(-0.0195,0.0,-0.0195,3500.0,0.015,"<");
	xy1.SetLineColor(kGreen);
	xy1.SetLineWidth(2);
	xy1.Draw();
	TArrow xy2(0.0195,0.0,0.0195,3500.0,0.015,"<");
	xy2.SetLineColor(kGreen);
	xy2.SetLineWidth(2);
	xy2.Draw();

	pt->Draw();
	Canvas->Print("dE.pdf");
//        Canvas->SaveAs("/afs/ihep.ac.cn/users/l/lincx/picture/dEFit.eps");


	//	TCanvas* Canvas1 = new  TCanvas( "Canvas1", "beam constraint mass" ) ;
	//	bgHist->plotOn(frame6);
	//	bgPdf->plotOn(frame6, LineColor(kGreen));
	//	frame6->Draw();
}

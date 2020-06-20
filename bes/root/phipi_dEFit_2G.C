#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooChebychev.h"
#include "RooAddPdf.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "RooFit.h"
#include "RooCurve.h"
#include "RooHist.h"
#include "/afs/ihep.ac.cn/users/l/lincx/useful/boot.h"
using namespace RooFit ;

void phipi_dEFit_2G()
{
		//Set up component  pdfs 
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

		gStyle->SetOptFit(0);                                                                                              

		// put tick marks on top and RHS of plots
		gStyle->SetPadTickX(1);
		gStyle->SetPadTickY(1);

		setStyle();myStyle->SetTitleXSize(0.08);
		myStyle->SetTitleYSize(0.07);
		// ---------------------------------------

		// Declare observable x
		RooRealVar *dE_min=new RooRealVar("dE_min","dE_min",-0.1,0.1) ;
		TFile *datafile = new TFile("/afs/ihep.ac.cn/users/l/lincx/scratchfs/6.6.4.p02/DptoPhiPi/job_ana/root/all_deltaE.root");
		TTree *datatree = (TTree*)datafile->Get("TDphipi");
		RooDataSet *data = new RooDataSet("data","data",datatree,*dE_min);
		// Create two Gaussian PDFs g1(x,mean1,sigma) anf g2(x,mean2,sigma) and their parameters
		RooRealVar *mean1=new RooRealVar("mean1","mean of gauss1",0,-0.008,0.008) ;
		RooRealVar *sigma1=new RooRealVar("sigma1","width of gaussians",0.0003,0.00,0.03) ;
    RooRealVar *mean2=new RooRealVar("mean2","",0,-0.05,10);
    RooRealVar *sigma2=new RooRealVar("sigma2","",0.3,0.02,10);
    RooRealVar *sig1frac= new RooRealVar("sig1frac", "fraction", 0.5, 0, 1.0);
    RooGaussian *gaus1=new RooGaussian("gaus1","Signal component 1",*dE_min,*mean1,*sigma1) ;
    RooGaussian *gaus2=new RooGaussian("gaus2","Signal component 2",*dE_min,*mean2,*sigma2) ;
		RooAddModel  *sig=new RooAddModel("sig","",RooArgList(*gaus1,*gaus2),*sig1frac) ;
    //rxs=new RooFFTConvPdf("rxs","signal x resolution",*dE_min,*sig,*res);
		//RooRealVar *alpha=new RooRealVar("alpha","alpha",1.0, 0, 10);
		//RooRealVar *n = new RooRealVar("n","n",10, 0,160);
    //RooRealVar *c0= new RooRealVar("c0", "coefficient #0", 0,-10,10);
    //RooRealVar *c1= new RooRealVar("c1", "coefficient #1", 0,-300,10);
    //RooRealVar *c2= new RooRealVar("c2", "coefficient #1", 0,-300,10);
		//RooCBShape *cb=new RooCBShape("cb","cb", *dE_min, *mean1, *sigma1, *alpha, *n);
		RooPolynomial *bkg=new RooPolynomial("bkg","background component",*dE_min);//, RooArgList(*c0,*c1));//,*c2));
		RooRealVar nsig("nsig","nsig",80000,50000,100000);
		RooRealVar nbkg("nbkg","nbkg",10000,5000,20000);
    RooRealVar nsig2("ngaus","ngaus",10000,0,100000);
		

		// Sum the composite signal and background 
		RooAddPdf  *model=new RooAddPdf("model","",RooArgList(*bkg,*gaus1,*gaus2),RooArgList(nbkg,nsig,nsig2)) ;
		//RooAddPdf  *model=new RooAddPdf("model","",RooArgList(*bkg,*rxs),RooArgList(nbkg,nsig)) ;


		// Fit model to data
		model->fitTo(*data,Extended(kTRUE)) ;

		// Plot data and PDF overlaid
		RooPlot* xframe = dE_min->frame(-0.1,0.1,100) ;
		data->plotOn(xframe) ;
		model->plotOn(xframe,RooFit::LineColor(kRed)) ;

		// Overlay the background component of model with a dashed line
		model->plotOn(xframe,Components(*bkg),LineColor(kBlue),LineStyle(kDashed)) ;

		// Overlay the background+sig2 components of model with a dotted line
		//model->plotOn(xframe,Components(RooArgSet(*bkg,*sig2)),LineStyle(kDotted)) ;

		model->plotOn(xframe,Components(RooArgSet(*gaus1)),LineStyle(kDashed),LineColor(kRed));
		model->plotOn(xframe,Components(RooArgSet(*gaus2)),LineStyle(kDashed),LineColor(kViolet));

		// Print structure of composite p.d.f.
		model->Print("t") ;

		xframe->SetXTitle("#DeltaE (GeV)");
                xframe->SetYTitle("Event/(2 MeV)");

		RooCurve *curve = (RooCurve*)xframe->getObject(1);
		RooHist *histo = (RooHist*)xframe->getHist("h_data");
		
                TPaveText *pt = new TPaveText(0.20,0.54,0.48,0.94,"BRNDC");
		pt->SetBorderSize(1);
		pt->SetFillColor(10);
		pt->SetTextAlign(12);
		pt->SetTextSize(0.03);
		TString Par0  = "D^{+}#rightarrow#phi#pi^{+}(Signal MC)" ;
		TString Par1V = Form("%5.0f", nbkg.getVal() );
		TString Par1E = Form("%3.0f", nbkg.getError() );
		TString Par1  = "N_{bkg} = " + Par1V + " #pm " + Par1E;
		TString Par2V = Form("%5.0f", nsig.getVal()+nsig2.getVal());
		TString Par2E = Form("%3.0f", sqrt(nsig.getError()*nsig.getError()+nsig2.getError()*nsig2.getError()));
		TString Par2  = "N_{sig} = " + Par2V + " #pm " + Par2E;

		TString Par3V = Form("%7.2f", (mean1->getVal())*1000 );
		TString Par3E = Form("%3.2f", mean1->getError()*1000 );
		TString Par3  = "mean_{1} = " + Par3V + " #pm " + Par3E + " MeV" ;
		TString Par4V = Form("%4.2f", sigma1->getVal()*1000.00 );
		TString Par4E = Form("%4.2f", sigma1->getError()*1000.00 );
		TString Par4  = "sigma_{1} = " + Par4V + " #pm " + Par4E + " MeV" ;
		//TString Par5V = Form("%7.4f", alpha->getVal() );
		//TString Par5E = Form("%3.4f", alpha->getError() );
		//TString Par5  = "#alpha = " + Par5V + " #pm " + Par5E  ;
		//TString Par6V = Form("%4.2f", n->getVal() );
		//TString Par6E = Form("%4.2f", n->getError() );
		//TString Par6  = "n = " + Par6V + " #pm " + Par6E;
                TString Par7V = Form("%7.2f", (mean2->getVal())*1000 );
                TString Par7E = Form("%3.2f", mean2->getError()*1000 );
                TString Par7  = "mean_{2} = " + Par7V + " #pm " + Par7E + " MeV" ;
                TString Par8V = Form("%4.2f", sigma2->getVal()*1000.00 );
                TString Par8E = Form("%4.2f", sigma2->getError()*1000.00 );
                TString Par8  = "sigma_{2} = " + Par8V + " #pm " + Par8E + " MeV" ;
                TString Par9V = Form("%4.2f", sig1frac->getVal());
                TString Par9E = Form("%4.2f",sig1frac->getError());
                TString Par9  = "sig1frac = " + Par9V + " #pm " + Par9E;
		TString Par10 = Form("#chi^{2}/ndf = %.0f/%.0d", curve->chiSquare(*histo,8)*(histo->GetN()-8),histo->GetN()-8);
		//TString Par9 = Form("#chi^{2}/ndf = %.3f", curve->chiSquare(*histo,100-9));
		TText *text;
		text = pt->AddText(Par0);
		text = pt->AddText(Par1);
		text = pt->AddText(Par2);
		text = pt->AddText(Par3);
		text = pt->AddText(Par4);
		//text = pt->AddText(Par5);
		//text = pt->AddText(Par6);
		text = pt->AddText(Par7);
		text = pt->AddText(Par8); 
		text = pt->AddText(Par9);
		text = pt->AddText(Par10);
		TArrow *xy1 = new TArrow(-0.020,0.0,-0.020,3500.0,0.015,"<");
		xy1->SetLineColor(kGreen);
		xy1->SetLineWidth(2);
		TArrow *xy2 = new TArrow(0.019,0.0,0.019,3500.0,0.015,"<");
		xy2->SetLineColor(kGreen);
		xy2->SetLineWidth(2);

		TCanvas* Canvas = new  TCanvas( "Canvas", "delta E" );
		Canvas->SetFillColor(0);
		Canvas->SetFrameFillColor(0);
		xframe->Draw();
		pt->Draw();
		xy1->Draw();
		xy2->Draw();
		Canvas->Update();
  //  Canvas->SaveAs("/afs/ihep.ac.cn/users/l/lincx/picture/dEFit.eps");
}


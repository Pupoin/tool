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
#include "/afs/ihep.ac.cn/users/l/lincx/useful/boot.h"
using namespace RooFit ;


void deltaefit()
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
		TFile *datafile = new TFile("/publicfs/ucas/user/yuanchy8/job/6.6.4p01/root/signal_shape.root");
		TTree *datatree = (TTree*)datafile->Get("tree");
		RooDataSet *data = new RooDataSet("data","data",datatree,*dE_min);

		// Create CB PDF and Gaussian PDF cb(x,mean1,sigma2,alpha,n) anf g2(x,mean2,sigma2) and their parameters
		RooRealVar *mean1=new RooRealVar("mean1","mean of gauss1",-9.51368e-05,-9.51368e-05-1.87103e-05,-9.51368e-05+1.87103e-05) ;
		RooRealVar *sigma1=new RooRealVar("sigma1","width of gaussians",0.00356598,0.00356598-1.97054e-05,0.00356598+1.97054e-05) ;
		RooRealVar *alpha=new RooRealVar("alpha","alpha",1.25258, 1.25258-0.0211074, 1.25258+0.0211074);
		RooRealVar *n = new RooRealVar("n","n",133.897, 133.897-82.609,133.897+82.609);
		RooCBShape *cb=new RooCBShape("cb","cb", *dE_min, *mean1, *sigma1, *alpha, *n);
                RooRealVar *mean2=new RooRealVar("mean2","",0.000178383,0.000178383-0.000266241,0.000178383+0.000266241);
                RooRealVar *sigma2=new RooRealVar("sigma2","",0.0172772,0.0172772-0.00047412,0.0172772+0.00047412);
                RooGaussian *gaus=new RooGaussian("gaus","gaus",*dE_min,*mean2,*sigma2) ;
                
                RooPolynomial *bkg=new RooPolynomial("bkg","background component",*dE_min);
		
                RooRealVar nsig("nsig","nsig",70000,0,100000);
		RooRealVar nbkg("nbkg","nbkg",10000,0,20000);
                RooRealVar nsig2("nsig2","nsig2",10000,0,100000);
		
                //RooAddPdf *sig=new RooAddPdf("sig","sig",RooArgList(*cb,*gaus),RooArgList(nsig,nsig2));
// Build Chebychev polynomial p.d.f.  
		//RooRealVar a0("a0","a0",0.5,0.,1.) ;
		//RooRealVar a1("a1","a1",-0.2,0.,1.) ;
		//RooChebychev bkg("bkg","Background",x,RooArgSet(a0,a1)) ;


		////////////////////////////////////////////////////
		// M E T H O D   1 - T w o   R o o A d d P d f s  //
		////////////////////////////////////////////////////


		// A d d   s i g n a l   c o m p o n e n t s 
		// ------------------------------------------

		// Sum the signal components into a composite signal p.d.f.


		// A d d  s i g n a l   a n d   b a c k g r o u n d
		// ------------------------------------------------

		// Sum the composite signal and background 
		RooAddPdf  *model=new RooAddPdf("model","",RooArgList(*bkg,*cb,*gaus),RooArgList(nbkg,nsig,nsig2)) ;


		// S a m p l e ,   f i t   a n d   p l o t   m o d e l
		// ---------------------------------------------------

		// Generate a data sample of 1000 events in x from model
		//TFile *datafile = new TFile("/scratchfs/bes/houyr/root_signalmc/kkpi_ana_20000sgmc.root");
		//TTree *datatree = (TTree*)datafile->Get("tree");
		//RooDataSet *data = new RooDataSet("data","data",datatree,*dE_min);
		// Fit model to data
		model->fitTo(*data,Extended(kTRUE)) ;

		/*double sigma = 0;
			double sigmae = 0;
			double f = sig1frac->getVal(),s1=sigma1->getVal(),s2=sigma2->getVal(),m1=mean1->getVal(),m2=mean2->getVal();
		//double fe = sig1frac->getErr(),s1e=sigma1->getErr(),s2e=sigma2->getErr(),m1e=mean1->getErr(),m2e=mean2->getErr();
		sigma = sqrt(f*s1*s1+(1-f)*s2*s2+f*(1-f)*(m1-m2)*(m1-m2));*/
		// Plot data and PDF overlaid
		RooPlot* xframe = dE_min->frame(-0.1,0.1,100) ;
		data->plotOn(xframe) ;
		model->plotOn(xframe,RooFit::LineColor(kRed)) ;

		// Overlay the background component of model with a dashed line
		model->plotOn(xframe,Components(*bkg),LineColor(kBlue),LineStyle(kDashed)) ;

		// Overlay the background+sig2 components of model with a dotted line
		//model->plotOn(xframe,Components(RooArgSet(*bkg,*sig2)),LineStyle(kDotted)) ;

		model->plotOn(xframe,Components(RooArgSet(*cb,*gaus)),LineStyle(kDashed),LineColor(kRed));

		// Print structure of composite p.d.f.
		model->Print("t") ;

		xframe->SetXTitle("#DeltaE(GeV)");
xframe->SetYTitle("Events/(2 MeV)");

		RooCurve *curve = (RooCurve*)xframe->getObject(1);
		RooHist *histo = (RooHist*)xframe->getHist("h_data");
		//std::cout<<"sigmatotal: "<<sigma<<std::endl;
		TPaveText *pt = new TPaveText(0.20,0.54,0.53,0.94,"BRNDC");
		pt->SetBorderSize(1);
		pt->SetFillColor(10);
		pt->SetTextAlign(12);
		pt->SetTextSize(0.03);
		TString Par0  = "D^{0}#rightarrow#phi#pi^{+}(Signal MC)" ;
		TString Par1V = Form("%5.1f", nbkg.getVal() );
		TString Par1E = Form("%5.1f", nbkg.getError() );
		TString Par1  = "N_{bkg} = " + Par1V + " #pm " + Par1E;
		TString Par2V = Form("%5.1f", nsig.getVal()+nsig2.getVal() );
		TString Par2E = Form("%5.1f", sqrt(nsig.getError()*nsig.getError()+nsig2.getError()*nsig2.getError()));
		TString Par2  = "N_{sig} = " + Par2V + " #pm " + Par2E;

		TString Par3V = Form("%7.2f", (mean1->getVal())*1000 );
		//TString Par3V = Form("%7.2f", (2*MBC-mean.getVal())*1000.00 );  
		//TString Par3E = Form("%3.2f", mean.getError()*1000.00 );
		TString Par3E = Form("%3.2f", mean1->getError()*1000 );
		TString Par3  = "mean_{1} = " + Par3V + " #pm " + Par3E + " MeV" ;
		TString Par4V = Form("%4.2f", sigma1->getVal()*1000.00 );
		TString Par4E = Form("%4.1f", sigma1->getError()*1000.00 );
		TString Par4  = "sigma_{1} = " + Par4V + " #pm " + Par4E + " MeV" ;
		TString Par5V = Form("%7.3f", alpha->getVal() );
		TString Par5E = Form("%3.3f", alpha->getError() );
		TString Par5  = "#alpha = " + Par5V + " #pm " + Par5E  ;
		TString Par6V = Form("%4.2f", n->getVal() );
		TString Par6E = Form("%4.2f", n->getError() );
		TString Par6  = "n = " + Par6V + " #pm " + Par6E ;
		TString Par8V = Form("%7.2f", (mean2->getVal())*1000 );
		TString Par8E = Form("%3.2f", mean2->getError()*1000 );
		TString Par8  = "mean_{2} = " + Par8V + " #pm " + Par8E + " MeV" ;
		TString Par9V = Form("%4.2f", sigma2->getVal()*1000.00 );
		TString Par9E = Form("%4.1f", sigma2->getError()*1000.00 );
		TString Par9  = "sigma_{2} = " + Par9V + " #pm " + Par9E + " MeV" ;

		TString Par7 = Form("#chi^{2}/ndf = %.0f/%.0d", curve->chiSquare(*histo,9)*(histo->GetN()-9),histo->GetN()-9);
		//TString Par7 = Form("#chi^{2}/ndf = %.3f", curve->chiSquare(*histo,9));
		TText *text;
		text = pt->AddText(Par0);
		text = pt->AddText(Par1);
		text = pt->AddText(Par2);
		text = pt->AddText(Par3);
		text = pt->AddText(Par4);
		text = pt->AddText(Par5);
		text = pt->AddText(Par6);
		text=pt->AddText(Par8);
		text=pt->AddText(Par9);
		text = pt->AddText(Par7);
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
		//Canvas->SaveAs("");
}


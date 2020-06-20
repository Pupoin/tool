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

void chisquare()
{
		// Declare observable x
		RooRealVar *dE_min=new RooRealVar("dE_min","dE_min",-0.1,0.1) ;
		TFile *datafile = new TFile("/afs/ihep.ac.cn/users/l/lincx/scratchfs/job_ana/root/all_deltaE.root");
		TTree *datatree = (TTree*)datafile->Get("TDphipi");
		RooDataSet *data = new RooDataSet("data","data",datatree,*dE_min);
		// Create two Gaussian PDFs g1(x,mean1,sigma) anf g2(x,mean2,sigma) and their parameters
		RooRealVar *mean1=new RooRealVar("mean1","mean of gauss1",0,-0.01,0.01) ;
		RooRealVar *sigma1=new RooRealVar("sigma1","width of gaussians",0.03,0.00,0.06) ;
		RooRealVar *alpha=new RooRealVar("alpha","alpha",1.0, 0, 10);
		RooRealVar *n = new RooRealVar("n","n",10, 0,150);
		RooCBShape *cb=new RooCBShape("cb","cb", *dE_min, *mean1, *sigma1, *alpha, *n);
		RooPolynomial *bkg=new RooPolynomial("bkg","background component",*dE_min);
		RooRealVar nsig("nsig","nsig",10000,0,100000);
		RooRealVar nbkg("nbkg","nbkg",10000,0,50000);
    RooRealVar nsig2("ngaus","ngaus",10000,0,100000);
		
                RooRealVar *mean2=new RooRealVar("mean2","",0,-0.001,0.005);
                RooRealVar *sigma2=new RooRealVar("sigma2","",0.003,0.0,0.03);
                RooGaussian *res=new RooGaussian("res","Signal component 2",*dE_min,*mean2,*sigma2) ;
		RooAddPdf  *sig=new RooAddPdf("sig","",RooArgList(*cb,*res),RooArgList(nsig,nsig2)) ;
                //rxs=new RooFFTConvPdf("rxs","signal x resolution",*dE_min,*sig,*res);

		// Sum the composite signal and background 
		RooAddPdf  *model=new RooAddPdf("model","",RooArgList(*bkg,*res,*sig),RooArgList(nbkg,nsig2,nsig)) ;
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

		model->plotOn(xframe,Components(RooArgSet(*sig,*res)),LineStyle(kDashed),LineColor(kRed));

		// Print structure of composite p.d.f.
		model->Print("t") ;

		xframe->SetXTitle("#DeltaE (GeV)");
                xframe->SetYTitle("Event/(2 MeV)");

		RooCurve *curve = (RooCurve*)xframe->getObject(1);
		RooHist *histo = (RooHist*)xframe->getHist("h_data");
		

   Int_t i,np = histo.GetN() ;
   Double_t x,y,eyl,eyh,exl,exh ;
   
    // Find starting and ending bin of histogram based on range of RooCurve
     Double_t xstart,xstop ;
   
  #if ROOT_VERSION_CODE >= ROOT_VERSION(4,0,1)
     GetPoint(0,xstart,y) ;
     GetPoint(GetN()-1,xstop,y) ;
   #else
    const_cast<RooCurve*>(this)->GetPoint(0,xstart,y) ;
     const_cast<RooCurve*>(this)->GetPoint(GetN()-1,xstop,y) ;
  #endif
   
    Int_t nbin(0) ;
  
     Double_t chisq(0) ;
     for (i=0 ; i<np ; i++) {   
   
       // Retrieve histogram contents
       ((RooHist&)hist).GetPoint(i,x,y) ;
   
       // Check if point is in range of curve
        if (x<xstart || x>xstop) continue ;
   
       eyl = hist.GetEYlow()[i] ;
       eyh = hist.GetEYhigh()[i] ;
       exl = hist.GetEXlow()[i] ;
       exh = hist.GetEXhigh()[i] ;
   
       // Integrate function over this bin
       Double_t avg = average(x-exl,x+exh) ;
   
       // Add pull^2 to chisq
      if (y!=0) {      
         Double_t pull = (y>avg) ? ((y-avg)/eyl) : ((y-avg)/eyh) ;
         chisq += pull*pull ;
         nbin++ ;
      }
     }
   
     // Return chisq/nDOF 
     return chisq / (nbin-nFitParam) ;
   }
   
}


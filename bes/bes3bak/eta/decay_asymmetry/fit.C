/// \file
 /// \ingroup tutorial_roofit
 /// \notebook -js
 ///  'BASIC FUNCTIONALITY' RooFit tutorial macro #102
 ///
 ///  Importing data from ROOT TTrees and THx histograms
 ///
 /// \macro_image
 /// \macro_output
 /// \macro_code
 /// \author 07/2008 - Wouter Verkerke 
 
 
 #include "RooRealVar.h"
 #include "RooDataSet.h"
 #include "RooDataHist.h"
 #include "RooGaussian.h"
 #include "TCanvas.h"
 #include "RooPlot.h"
 #include "TTree.h"
 #include "TH1D.h"
 #include "TRandom.h"
 using namespace RooFit ;
 
 TH1* makeTH1() ;
 TTree* makeTTree() ;
 
 
 void fit()
 {
    // ---------------------------------------------------
    // I m p o r t i n g   R O O T   h i s t o g r a m s 
    // ===================================================
 
    // I m p o r t   T H 1   i n t o   a   R o o D a t a H i s t
    // ---------------------------------------------------------
 
    // Create a ROOT TH1 histogram
    TH1* hh = makeTH1() ;
 
    // Declare observable x
    // RooRealVar x("x","x",-1,1) ;
    RooRealVar x("Costheta_sigma", "cos#theta_{#Sigma^{+}}", -1, 1);

    // Create a binned dataset that imports contents of TH1 and associates its contents to observable 'x'
    RooDataHist dh("dh","dh",x,Import(*hh)) ;
 
 
    // P l o t   a n d   f i t   a   R o o D a t a H i s t
    // ---------------------------------------------------
 
    // Make plot of binned dataset showing Poisson error bars (RooFit default)
    RooPlot* frame = x.frame(Title("Imported TH1 with Poisson error bars")) ;
    dh.plotOn(frame) ; 
 
    // Fit a Gaussian p.d.f to the data
    // RooRealVar mean("mean","mean",0,-10,10) ;
    // RooRealVar sigma("sigma","sigma",3,0.1,10) ;
    // RooGaussian gauss("gauss","gauss",x,mean,sigma) ;
        RooRealVar p0("p0","p0",0.5, -2, 2) ;
    RooRealVar p1("p1","p1",-20, -1000000, 10000) ;
    // // RooRealVar p2("p2","p2",3.0) ;
    // RooFormulaVar funcpol("f","polynomial",x,RooArgList(p0,p1)) ;
    // RooFormulaVar funcpol("f","exp(foo)*sqrt(bar)", RooArgList(foo,bar)) ;
    RooPolynomial poly("poly", "cubic polynomial", x, RooArgList(p0) );

    poly.fitTo(dh) ;
    poly.plotOn(frame) ;
 
    // P l o t   a n d   f i t   a   R o o D a t a H i s t   w i t h   i n t e r n a l   e r r o r s
    // ---------------------------------------------------------------------------------------------
 
    // If histogram has custom error (i.e. its contents is does not originate from a Poisson process
    // but e.g. is a sum of weighted events) you can data with symmetric 'sum-of-weights' error instead
    // (same error bars as shown by ROOT)
    RooPlot* frame2 = x.frame(Title("Imported TH1 with internal errors")) ;
    dh.plotOn(frame2,DataError(RooAbsData::SumW2)) ; 
    poly.plotOn(frame2) ;
 /*
    // Please note that error bars shown (Poisson or SumW2) are for visualization only, the are NOT used
    // in a maximum likelihood fit
    //
    // A (binned) ML fit will ALWAYS assume the Poisson error interpretation of data (the mathematical definition 
    // of likelihood does not take any external definition of errors). Data with non-unit weights can only be correctly
    // fitted with a chi^2 fit (see rf602_chi2fit.C) 
 
 
    // -----------------------------------------
    // I m p o r t i n g   R O O T  T T r e e s
    // =========================================
 
 
    // I m p o r t   T T r e e   i n t o   a   R o o D a t a S e t
    // -----------------------------------------------------------
 
    TTree* tree = makeTTree() ;
 
    // Define 2nd observable y
    RooRealVar y("y","y",-10,10) ;
 
    // Construct unbinned dataset importing tree branches x and y matching between branches and RooRealVars 
    // is done by name of the branch/RRV 
    // 
    // Note that ONLY entries for which x,y have values within their allowed ranges as defined in 
    // RooRealVar x and y are imported. Since the y values in the import tree are in the range [-15,15]
    // and RRV y defines a range [-10,10] this means that the RooDataSet below will have less entries than the TTree 'tree'
 
    RooDataSet ds("ds","ds",RooArgSet(x,y),Import(*tree)) ;
 
 */
    // P l o t   d a t a s e t   w i t h   m u l t i p l e   b i n n i n g   c h o i c e s
    // ------------------------------------------------------------------------------------
 
    // Print number of events in dataset
    // ds.Print() ;
 
    // // Print unbinned dataset with default frame binning (100 bins)
    // RooPlot* frame3 = y.frame(Title("Unbinned data shown in default frame binning")) ;
    // ds.plotOn(frame3) ;
 
    // // Print unbinned dataset with custom binning choice (20 bins)
    // RooPlot* frame4 = y.frame(Title("Unbinned data shown with custom binning")) ;
    // ds.plotOn(frame4,Binning(20)) ;
 
    // Draw all frames on a canvas
    TCanvas* c = new TCanvas("rf102_dataimport","rf102_dataimport",800,800) ;
    c->Divide(2,2) ;
    c->cd(1) ; gPad->SetLeftMargin(0.15) ; frame->GetYaxis()->SetTitleOffset(1.4) ; frame->Draw() ;
    // c->cd(2) ; gPad->SetLeftMargin(0.15) ; frame2->GetYaxis()->SetTitleOffset(1.4) ; frame2->Draw() ;
    // c->cd(3) ; gPad->SetLeftMargin(0.15) ; frame3->GetYaxis()->SetTitleOffset(1.4) ; frame3->Draw() ;
    // c->cd(4) ; gPad->SetLeftMargin(0.15) ; frame4->GetYaxis()->SetTitleOffset(1.4) ; frame4->Draw() ;
    c->SaveAs("tmp.png");
 }
 
 
 
 
 TH1* makeTH1() 
 {
    // Create ROOT TH1 filled with a Gaussian distribution
 
    // TH1D* hh = new TH1D("hh","hh",25,-10,10) ;
    // for (int i=0 ; i<100 ; i++) {
    //    hh->Fill(gRandom->Gaus(0,3)) ;
    // }
    // return hh ;
    TChain *chain_data = new TChain("tree");
    chain_data->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/decay_asymmetry/total_Costheta_sigma.root");
    chain_data->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2_eta3pi/decay_asymmetry/total_Costheta_sigma.root");
    TH1F *histo = new TH1F("histo","histo", 5, -1, 1);
    chain_data->Project("histo", "Costheta_sigma", "M_BC_r3c>2.276 && M_BC_r3c<2.3");
    
    // sideband 
    TChain *chain_sd1 = new TChain("tree");
    TChain *chain_sd2 = new TChain("tree");
    chain_sd1->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/decay_asymmetry/total_Costheta_sigma.root");
    chain_sd2->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2_eta3pi/decay_asymmetry/total_Costheta_sigma.root");
    TH1F *histo_sideband1 = new TH1F("histo_sideband1","histo_sideband1", 5, -1, 1);
    TH1F *histo_sideband2 = new TH1F("histo_sideband2","histo_sideband2", 5, -1, 1);
    chain_sd1->Project("histo_sideband1", "Costheta_sigma", "(M_BC_r3c>2.25 && M_BC_r3c<2.27) || (M_BC_r3c>2.31 && M_BC_r3c<2.33)");
    chain_sd2->Project("histo_sideband2", "Costheta_sigma", "(M_BC_r3c>2.25 && M_BC_r3c<2.27) || (M_BC_r3c>2.31 && M_BC_r3c<2.33)");

    // histo_sideband1->Scale(0.73213);
    // histo_sideband2->Scale(0.62175);

    histo->Add(histo_sideband1,-0.73213);
    histo->Add(histo_sideband2,-0.62175);
    return histo;
 }
 
 
 TTree* makeTTree() 
 {
   // Create ROOT TTree filled with a Gaussian distribution in x and a uniform distribution in y
 
   TTree* tree = new TTree("tree","tree") ;
   Double_t* px = new Double_t ;
   Double_t* py = new Double_t ;
   tree->Branch("x",px,"x/D") ;
   tree->Branch("y",py,"y/D") ;
   for (int i=0 ; i<100 ; i++) {
     *px = gRandom->Gaus(0,3) ;
     *py = gRandom->Uniform()*30 - 15 ;
     tree->Fill() ;
   }
   return tree ;
 }
 
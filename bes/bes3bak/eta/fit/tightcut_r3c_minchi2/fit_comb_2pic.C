#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooSimultaneous.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"
#include "TCut.h"
#include "TSystem.h"
#include "TString.h"
#include "TLegend.h"
#include "TChain.h"
#include "RooFit.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooArgSet.h"
#include "RooFitResult.h"
#include "RooChebychev.h"
#include "RooPolynomial.h"
#include "RooPlot.h"
#include "RooGaussModel.h"
#include "RooFFTConvPdf.h"
#include "RooBifurGauss.h"
#include "RooBukinPdf.h"
#include "RooNumConvPdf.h"
#include "RooKeysPdf.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "iostream"
#include "string"
#include "TAxis.h"
#include "RooBreitWigner.h"
#include "RooGaussian.h"
#include "RooArgusBG.h"
#include "RooArgList.h"
#include "RooAbsPdf.h"
#include "TH1.h"

using namespace std;
using namespace RooFit;



Double_t xmin = 2.25;
Double_t xmax = 2.34919;
Double_t xbins = 25;
Double_t mbcmin = 2.25;
Double_t mbcmax = 2.34919;
TCut cut_np = "(np !=0 && npbar != 0)";
// TCut cut = "(refm>=0.115&&refm<=0.15) && (refmORsigm1m>=0.115&&refmORsigm1m<=0.15) && (sigmam>=1.174 && sigmam<=1.2) && (dipim<0.48 || dipim>0.52)";
TCut cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919))";
// TCut cut_deltaE_ref = "((deltaE_min>-0.033) && (deltaE_min<0.022))";
// TCut cut_deltaE_sig = "((deltaE_min>-0.021) && (deltaE_min<0.015))";
// TCut cut_chi2 = "(chi2_min_r3c< 29)";
TCut cut_ref = (cut_mbc && "(chi2_min_r3c<17) && (dipim<0.44 || dipim>0.52)" && cut_np);
TCut cut_sig = (cut_mbc && "(chi2_min_r3c<17)" && cut_np);
// RooRealVar *M_BC_r3c = new RooRealVar("M_BC_r3c", "M_BC_r3c", mbcmin, mbcmax);


Double_t xmin_4600 = 2.25, xmax_4600 = 2.299765;
Double_t xmin_4612 = 2.25, xmax_4612 = 2.30579;
Double_t xmin_4620 = 2.25, xmax_4620 = 2.31387;
Double_t xmin_4640 = 2.25, xmax_4640 = 2.320255;
Double_t xmin_4660 = 2.25, xmax_4660 = 2.33046;
Double_t xmin_4680 = 2.25, xmax_4680 = 2.34079;
Double_t xmin_4700 = 2.25, xmax_4700 = 2.34919;

RooRealVar *var_4600 = new RooRealVar("M_BC_r3c","M_{BC}", xmin_4600, xmax_4600); 
RooRealVar *var_4612 = new RooRealVar("M_BC_r3c","M_{BC}", xmin_4612, xmax_4612); 
RooRealVar *var_4620 = new RooRealVar("M_BC_r3c","M_{BC}", xmin_4620, xmax_4620); 
RooRealVar *var_4640 = new RooRealVar("M_BC_r3c","M_{BC}", xmin_4640, xmax_4640); 
RooRealVar *var_4660 = new RooRealVar("M_BC_r3c","M_{BC}", xmin_4660, xmax_4660); 
RooRealVar *var_4680 = new RooRealVar("M_BC_r3c","M_{BC}", xmin_4680, xmax_4680); 
RooRealVar *var_4700 = new RooRealVar("M_BC_r3c","M_{BC}", xmin_4700, xmax_4700); 


// 27 3.7
// 25 3.65
// 20 3.8
// 15 3.9
// 10 3.6
Double_t FCN_bkg = -24374.1;
RooRealVar Bratio("Bratio", "Br of sig/ref", 0.3, 0., 0.7);	
// RooRealVar Bratio("Bratio", "Br of sig/ref", 0);	

int fit_comb_2pic()
{

    TH1::SetDefaultSumw2(1);
    TString a("Events/");
    char b[30];
    sprintf(b, "(%5.1f", (xmax - xmin) / xbins * 1000);
    TString c(" MeV/c^{2})");
    TString ytitle = a + b + c;

    //
    // sig 
    TChain *tr_data0_sig = new TChain("tree");    tr_data0_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/4600data_removedouble.root");
    TChain *tr_data1_sig = new TChain("tree");    tr_data1_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/4612data_removedouble.root");
    TChain *tr_data2_sig = new TChain("tree");    tr_data2_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/4620data_removedouble.root");
    TChain *tr_data3_sig = new TChain("tree");	  tr_data3_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/4640data_removedouble.root");
    TChain *tr_data4_sig = new TChain("tree");	  tr_data4_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/4660data_removedouble.root");
    TChain *tr_data5_sig = new TChain("tree");	  tr_data5_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/4680data_removedouble.root");
    TChain *tr_data6_sig = new TChain("tree");    tr_data6_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/4700data_removedouble.root");

    // ref
    TChain *tr_data0 = new TChain("tree");    tr_data0->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/data/cutmassroot/tightcut_r3c_minchi2/4600data_adddipim.root");
    TChain *tr_data1 = new TChain("tree");    tr_data1->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/data/cutmassroot/tightcut_r3c_minchi2/4612data_adddipim.root");
    TChain *tr_data2 = new TChain("tree");    tr_data2->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/data/cutmassroot/tightcut_r3c_minchi2/4620data_adddipim.root");
    TChain *tr_data3 = new TChain("tree");	  tr_data3->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/data/cutmassroot/tightcut_r3c_minchi2/4640data_adddipim.root");
    TChain *tr_data4 = new TChain("tree");	  tr_data4->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/data/cutmassroot/tightcut_r3c_minchi2/4660data_adddipim.root");
    TChain *tr_data5 = new TChain("tree");	  tr_data5->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/data/cutmassroot/tightcut_r3c_minchi2/4680data_adddipim.root");
    TChain *tr_data6 = new TChain("tree");    tr_data6->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/data/cutmassroot/tightcut_r3c_minchi2/4700data_adddipim.root");

    // ____________________ MC
    TTree *tr_fit0_sig = tr_data0_sig->CopyTree(cut_sig);    RooDataSet *data0_sig = new RooDataSet("data0_sig"," M_BC_r3c", tr_fit0_sig, RooArgSet(*var_4600));
    TTree *tr_fit1_sig = tr_data1_sig->CopyTree(cut_sig);    RooDataSet *data1_sig = new RooDataSet("data1_sig", "M_BC_r3c", tr_fit1_sig, RooArgSet(*var_4612));
    TTree *tr_fit2_sig = tr_data2_sig->CopyTree(cut_sig);    RooDataSet *data2_sig = new RooDataSet("data2_sig", "M_BC_r3c", tr_fit2_sig, RooArgSet(*var_4620));
    TTree *tr_fit3_sig = tr_data3_sig->CopyTree(cut_sig);    RooDataSet *data3_sig = new RooDataSet("data3_sig", "M_BC_r3c", tr_fit3_sig, RooArgSet(*var_4640));
    TTree *tr_fit4_sig = tr_data4_sig->CopyTree(cut_sig);    RooDataSet *data4_sig = new RooDataSet("data4_sig", "M_BC_r3c", tr_fit4_sig, RooArgSet(*var_4660));
    TTree *tr_fit5_sig = tr_data5_sig->CopyTree(cut_sig);    RooDataSet *data5_sig = new RooDataSet("data5_sig", "M_BC_r3c", tr_fit5_sig, RooArgSet(*var_4680));
    TTree *tr_fit6_sig = tr_data6_sig->CopyTree(cut_sig);    RooDataSet *data6_sig = new RooDataSet("data6_sig", "M_BC_r3c", tr_fit6_sig, RooArgSet(*var_4700));

    TTree *tr_fit0 = tr_data0->CopyTree(cut_ref);    RooDataSet *data0 = new RooDataSet("data0", "M_BC_r3c", tr_fit0, RooArgSet(*var_4600));
    TTree *tr_fit1 = tr_data1->CopyTree(cut_ref);    RooDataSet *data1 = new RooDataSet("data1", "M_BC_r3c", tr_fit1, RooArgSet(*var_4612));
    TTree *tr_fit2 = tr_data2->CopyTree(cut_ref);    RooDataSet *data2 = new RooDataSet("data2", "M_BC_r3c", tr_fit2, RooArgSet(*var_4620));
    TTree *tr_fit3 = tr_data3->CopyTree(cut_ref);    RooDataSet *data3 = new RooDataSet("data3", "M_BC_r3c", tr_fit3, RooArgSet(*var_4640));
    TTree *tr_fit4 = tr_data4->CopyTree(cut_ref);    RooDataSet *data4 = new RooDataSet("data4", "M_BC_r3c", tr_fit4, RooArgSet(*var_4660));
    TTree *tr_fit5 = tr_data5->CopyTree(cut_ref);    RooDataSet *data5 = new RooDataSet("data5", "M_BC_r3c", tr_fit5, RooArgSet(*var_4680));
    TTree *tr_fit6 = tr_data6->CopyTree(cut_ref);    RooDataSet *data6 = new RooDataSet("data6", "M_BC_r3c", tr_fit6, RooArgSet(*var_4700));

    // orignal
    RooRealVar mean_all("mean_all", "mean_all",  -9.9217e-05, -0.001, 0.001);
    RooRealVar sigma_all("sigma_all", "sigma_all",  3.1748e-05, 0, 0.001);
    
    // RooRealVar mean_all("mean_all", "mean_all",  -1.3832e-04 -  1.26e-04);
    // RooRealVar sigma_all("sigma_all", "sigma_all",  4.6448e-05 +  7.03e-05);

    RooGaussModel guass_4600("guass_4600", "guass_4600", *var_4600, mean_all, sigma_all);
    RooGaussModel guass_4612("guass_4612", "guass_4612", *var_4612, mean_all, sigma_all);
    RooGaussModel guass_4620("guass_4620", "guass_4620", *var_4620, mean_all, sigma_all);
    RooGaussModel guass_4640("guass_4640", "guass_4640", *var_4640, mean_all, sigma_all);
    RooGaussModel guass_4660("guass_4660", "guass_4660", *var_4660, mean_all, sigma_all);
    RooGaussModel guass_4680("guass_4680", "guass_4680", *var_4680, mean_all, sigma_all);
    RooGaussModel guass_4700("guass_4700", "guass_4700", *var_4700, mean_all, sigma_all);

    // sig-- shape
    TFile *pdf0_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/eta/pdf/tightcut_r3c_minchi2/4600_sig_shapepdf.root"); RooWorkspace *wspace0_sig = (RooWorkspace *)pdf0_sig->Get("wspace"); RooAbsPdf *shapepdf0_sig = wspace0_sig->pdf("modelPdf"); shapepdf0_sig->SetName("shapepdf0_sig");
    TFile *pdf1_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/eta/pdf/tightcut_r3c_minchi2/4612_sig_shapepdf.root"); RooWorkspace *wspace1_sig = (RooWorkspace *)pdf1_sig->Get("wspace"); RooAbsPdf *shapepdf1_sig = wspace1_sig->pdf("modelPdf"); shapepdf1_sig->SetName("shapepdf1_sig");
    TFile *pdf2_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/eta/pdf/tightcut_r3c_minchi2/4620_sig_shapepdf.root"); RooWorkspace *wspace2_sig = (RooWorkspace *)pdf2_sig->Get("wspace"); RooAbsPdf *shapepdf2_sig = wspace2_sig->pdf("modelPdf"); shapepdf2_sig->SetName("shapepdf2_sig");
    TFile *pdf3_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/eta/pdf/tightcut_r3c_minchi2/4640_sig_shapepdf.root"); RooWorkspace *wspace3_sig = (RooWorkspace *)pdf3_sig->Get("wspace"); RooAbsPdf *shapepdf3_sig = wspace3_sig->pdf("modelPdf"); shapepdf3_sig->SetName("shapepdf3_sig");
    TFile *pdf4_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/eta/pdf/tightcut_r3c_minchi2/4660_sig_shapepdf.root"); RooWorkspace *wspace4_sig = (RooWorkspace *)pdf4_sig->Get("wspace"); RooAbsPdf *shapepdf4_sig = wspace4_sig->pdf("modelPdf"); shapepdf4_sig->SetName("shapepdf4_sig");
    TFile *pdf5_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/eta/pdf/tightcut_r3c_minchi2/4680_sig_shapepdf.root"); RooWorkspace *wspace5_sig = (RooWorkspace *)pdf5_sig->Get("wspace"); RooAbsPdf *shapepdf5_sig = wspace5_sig->pdf("modelPdf"); shapepdf5_sig->SetName("shapepdf5_sig");
    TFile *pdf6_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/eta/pdf/tightcut_r3c_minchi2/4700_sig_shapepdf.root"); RooWorkspace *wspace6_sig = (RooWorkspace *)pdf6_sig->Get("wspace"); RooAbsPdf *shapepdf6_sig = wspace6_sig->pdf("modelPdf"); shapepdf6_sig->SetName("shapepdf6_sig");

    // ref-- shape
    TFile *pdf0 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/pdf/tightcut_r3c_minchi2/4612_ref_shapepdf.root"); RooWorkspace *wspace0 = (RooWorkspace *)pdf0->Get("wspace"); RooAbsPdf *shapepdf0 = wspace0->pdf("modelPdf"); shapepdf0->SetName("shapepdf0");
    TFile *pdf1 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/pdf/tightcut_r3c_minchi2/4612_ref_shapepdf.root"); RooWorkspace *wspace1 = (RooWorkspace *)pdf1->Get("wspace"); RooAbsPdf *shapepdf1 = wspace1->pdf("modelPdf"); shapepdf1->SetName("shapepdf1");
    TFile *pdf2 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/pdf/tightcut_r3c_minchi2/4620_ref_shapepdf.root"); RooWorkspace *wspace2 = (RooWorkspace *)pdf2->Get("wspace"); RooAbsPdf *shapepdf2 = wspace2->pdf("modelPdf"); shapepdf2->SetName("shapepdf2");
    TFile *pdf3 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/pdf/tightcut_r3c_minchi2/4640_ref_shapepdf.root"); RooWorkspace *wspace3 = (RooWorkspace *)pdf3->Get("wspace"); RooAbsPdf *shapepdf3 = wspace3->pdf("modelPdf"); shapepdf3->SetName("shapepdf3");
    TFile *pdf4 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/pdf/tightcut_r3c_minchi2/4660_ref_shapepdf.root"); RooWorkspace *wspace4 = (RooWorkspace *)pdf4->Get("wspace"); RooAbsPdf *shapepdf4 = wspace4->pdf("modelPdf"); shapepdf4->SetName("shapepdf4");
    TFile *pdf5 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/pdf/tightcut_r3c_minchi2/4680_ref_shapepdf.root"); RooWorkspace *wspace5 = (RooWorkspace *)pdf5->Get("wspace"); RooAbsPdf *shapepdf5 = wspace5->pdf("modelPdf"); shapepdf5->SetName("shapepdf5");
    TFile *pdf6 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/pdf/tightcut_r3c_minchi2/4700_ref_shapepdf.root"); RooWorkspace *wspace6 = (RooWorkspace *)pdf6->Get("wspace"); RooAbsPdf *shapepdf6 = wspace6->pdf("modelPdf"); shapepdf6->SetName("shapepdf6");

    // sig-- shape x guass
    RooAbsPdf *sigpdf0_sig = new RooFFTConvPdf("sigpdf0_sig", "shapepdf0_sig (X) gauss", *var_4600, *shapepdf0_sig, guass_4600);
    RooAbsPdf *sigpdf1_sig = new RooFFTConvPdf("sigpdf1_sig", "shapepdf1_sig (X) gauss", *var_4612, *shapepdf1_sig, guass_4612);
    RooAbsPdf *sigpdf2_sig = new RooFFTConvPdf("sigpdf2_sig", "shapepdf2_sig (X) gauss", *var_4620, *shapepdf2_sig, guass_4620);
    RooAbsPdf *sigpdf3_sig = new RooFFTConvPdf("sigpdf3_sig", "shapepdf3_sig (X) gauss", *var_4640, *shapepdf3_sig, guass_4640);
    RooAbsPdf *sigpdf4_sig = new RooFFTConvPdf("sigpdf4_sig", "shapepdf4_sig (X) gauss", *var_4660, *shapepdf4_sig, guass_4660);
    RooAbsPdf *sigpdf5_sig = new RooFFTConvPdf("sigpdf5_sig", "shapepdf5_sig (X) gauss", *var_4680, *shapepdf5_sig, guass_4680);
    RooAbsPdf *sigpdf6_sig = new RooFFTConvPdf("sigpdf6_sig", "shapepdf6_sig (X) gauss", *var_4700, *shapepdf6_sig, guass_4700);


    // ref-- shape x guass
    RooAbsPdf *sigpdf0 = new RooFFTConvPdf("sigpdf0", "shapepdf0 (X) gauss", *var_4600, *shapepdf0, guass_4600);
    RooAbsPdf *sigpdf1 = new RooFFTConvPdf("sigpdf1", "shapepdf1 (X) gauss", *var_4612, *shapepdf1, guass_4612);
    RooAbsPdf *sigpdf2 = new RooFFTConvPdf("sigpdf2", "shapepdf2 (X) gauss", *var_4620, *shapepdf2, guass_4620);
    RooAbsPdf *sigpdf3 = new RooFFTConvPdf("sigpdf3", "shapepdf3 (X) gauss", *var_4640, *shapepdf3, guass_4640);
    RooAbsPdf *sigpdf4 = new RooFFTConvPdf("sigpdf4", "shapepdf4 (X) gauss", *var_4660, *shapepdf4, guass_4660);
    RooAbsPdf *sigpdf5 = new RooFFTConvPdf("sigpdf5", "shapepdf5 (X) gauss", *var_4680, *shapepdf5, guass_4680);
    RooAbsPdf *sigpdf6 = new RooFFTConvPdf("sigpdf6", "shapepdf6 (X) gauss", *var_4700, *shapepdf6, guass_4700);

    // ____________________ sig argus background
    RooRealVar m0_sig("m0_sig", "m0_sig", 2.299765);   RooRealVar c0_sig("c0_sig", "c0_sig", -2.1266e+01, -50, 50);    RooArgusBG argus0_sig("argus0_sig", "argus0 sig", *var_4600, m0_sig, c0_sig);
    RooRealVar m1_sig("m1_sig", "m1_sig", 2.30579);    RooRealVar c1_sig("c1_sig", "c1_sig", -6.0660e+00, -50, 50);    RooArgusBG argus1_sig("argus1_sig", "argus1 sig", *var_4612, m1_sig, c1_sig);
    RooRealVar m2_sig("m2_sig", "m2_sig", 2.31387);    RooRealVar c2_sig("c2_sig", "c2_sig", -4.9716e+00, -50, 50);    RooArgusBG argus2_sig("argus2_sig", "argus2 sig", *var_4620, m2_sig, c2_sig);
    RooRealVar m3_sig("m3_sig", "m3_sig", 2.320255);   RooRealVar c3_sig("c3_sig", "c3_sig", -2.4289e+00, -50, 50);    RooArgusBG argus3_sig("argus3_sig", "argus3 sig", *var_4640, m3_sig, c3_sig);
    RooRealVar m4_sig("m4_sig", "m4_sig", 2.33046);    RooRealVar c4_sig("c4_sig", "c4_sig", -2.2689e+01, -50, 50);    RooArgusBG argus4_sig("argus4_sig", "argus4 sig", *var_4660, m4_sig, c4_sig);
    RooRealVar m5_sig("m5_sig", "m5_sig", 2.34079);    RooRealVar c5_sig("c5_sig", "c5_sig", -9.3432e+00, -50, 50);    RooArgusBG argus5_sig("argus5_sig", "argus5 sig", *var_4680, m5_sig, c5_sig);
    RooRealVar m6_sig("m6_sig", "m6_sig", 2.34919);    RooRealVar c6_sig("c6_sig", "c6_sig", -7.9593e+00, -50, 50);    RooArgusBG argus6_sig("argus6_sig", "argus6 sig", *var_4700, m6_sig, c6_sig);

    // ____________________ ref argus background
    RooRealVar m0("m0", "m0", 2.299765);   RooRealVar c0("c0", "c0", 1.5143e+00,  -50, 50);    RooArgusBG argus0("argus0", "argus0", *var_4600, m0, c0);
    RooRealVar m1("m1", "m1", 2.30579);    RooRealVar c1("c1", "c1", 1.4943e+01,  -50, 50);    RooArgusBG argus1("argus1", "argus1", *var_4612, m1, c1);
    RooRealVar m2("m2", "m2", 2.31387);    RooRealVar c2("c2", "c2", 2.9315e+00,  -50, 50);    RooArgusBG argus2("argus2", "argus2", *var_4620, m2, c2);
    RooRealVar m3("m3", "m3", 2.320255);   RooRealVar c3("c3", "c3", -3.1054e+00, -50, 50);    RooArgusBG argus3("argus3", "argus3", *var_4640, m3, c3);
    RooRealVar m4("m4", "m4", 2.33046);    RooRealVar c4("c4", "c4", -4.8423e+00, -50, 50);    RooArgusBG argus4("argus4", "argus4", *var_4660, m4, c4);
    RooRealVar m5("m5", "m5", 2.34079);    RooRealVar c5("c5", "c5", -4.3007e+00, -50, 50);    RooArgusBG argus5("argus5", "argus5", *var_4680, m5, c5);
    RooRealVar m6("m6", "m6", 2.34919);    RooRealVar c6("c6", "c6", -5.4013e+00, -50, 50);    RooArgusBG argus6("argus6", "argus6", *var_4700, m6, c6);

    // ____________________ ref signal/bkg num
    RooRealVar nsig_mode0("nsig_mode0", "signal of mode0", 0.05 * tr_fit0->GetEntries(), 0, 1.2 * tr_fit0->GetEntries());    RooRealVar nbkg0("nbkg0", "bkg number of mode0", 0.05 * tr_fit0->GetEntries(), 0, 1.2 * tr_fit0->GetEntries());
    RooRealVar nsig_mode1("nsig_mode1", "signal of mode1", 0.05 * tr_fit1->GetEntries(), 0, 1.2 * tr_fit1->GetEntries());    RooRealVar nbkg1("nbkg1", "bkg number of mode1", 0.05 * tr_fit1->GetEntries(), 0, 1.2 * tr_fit1->GetEntries());	
    RooRealVar nsig_mode2("nsig_mode2", "signal of mode2", 0.05 * tr_fit2->GetEntries(), 0, 1.2 * tr_fit2->GetEntries());    RooRealVar nbkg2("nbkg2", "bkg number of mode2", 0.05 * tr_fit2->GetEntries(), 0, 1.2 * tr_fit2->GetEntries());
    RooRealVar nsig_mode3("nsig_mode3", "signal of mode3", 0.05 * tr_fit3->GetEntries(), 0, 1.2 * tr_fit3->GetEntries());    RooRealVar nbkg3("nbkg3", "bkg number of mode3", 0.05 * tr_fit3->GetEntries(), 0, 1.2 * tr_fit3->GetEntries());
    RooRealVar nsig_mode4("nsig_mode4", "signal of mode4", 0.05 * tr_fit4->GetEntries(), 0, 1.2 * tr_fit4->GetEntries());    RooRealVar nbkg4("nbkg4", "bkg number of mode4", 0.05 * tr_fit4->GetEntries(), 0, 1.2 * tr_fit4->GetEntries());
    RooRealVar nsig_mode5("nsig_mode5", "signal of mode5", 0.05 * tr_fit5->GetEntries(), 0, 1.2 * tr_fit5->GetEntries());    RooRealVar nbkg5("nbkg5", "bkg number of mode5", 0.05 * tr_fit5->GetEntries(), 0, 1.2 * tr_fit5->GetEntries());
    RooRealVar nsig_mode6("nsig_mode6", "signal of mode6", 0.05 * tr_fit6->GetEntries(), 0, 1.2 * tr_fit6->GetEntries());    RooRealVar nbkg6("nbkg6", "bkg number of mode6", 0.05 * tr_fit6->GetEntries(), 0, 1.2 * tr_fit6->GetEntries());
    
    // ____________________ sig signal/bkg num
    double Br_sig_inter = 0.200845266; 
    double Br_ref_inter = 0.503631863;

    RooFormulaVar nsig_mode0_sig("nsig_mode0_sig", "signal of mode0 sig", "Bratio * nsig_mode0* 0.200845266  *0.0861/  0.503631863  /0.0991", RooArgSet(Bratio, nsig_mode0 ));	RooRealVar nbkg0_sig("nbkg0_sig", "bkg number of mode0 sig", 0.05 * tr_fit0_sig->GetEntries(), 0, 1.2 * tr_fit0_sig->GetEntries());
    RooFormulaVar nsig_mode1_sig("nsig_mode1_sig", "signal of mode1 sig", "Bratio * nsig_mode1* 0.200845266  *0.0845/  0.503631863  /0.0979", RooArgSet(Bratio, nsig_mode1 ));	RooRealVar nbkg1_sig("nbkg1_sig", "bkg number of mode1 sig", 0.05 * tr_fit1_sig->GetEntries(), 0, 1.2 * tr_fit1_sig->GetEntries());
    RooFormulaVar nsig_mode2_sig("nsig_mode2_sig", "signal of mode2 sig", "Bratio * nsig_mode2* 0.200845266  *0.0830/  0.503631863  /0.0964", RooArgSet(Bratio, nsig_mode2 ));	RooRealVar nbkg2_sig("nbkg2_sig", "bkg number of mode2 sig", 0.05 * tr_fit2_sig->GetEntries(), 0, 1.2 * tr_fit2_sig->GetEntries());
    RooFormulaVar nsig_mode3_sig("nsig_mode3_sig", "signal of mode3 sig", "Bratio * nsig_mode3* 0.200845266  *0.0818/  0.503631863  /0.0956", RooArgSet(Bratio, nsig_mode3 ));	RooRealVar nbkg3_sig("nbkg3_sig", "bkg number of mode3 sig", 0.05 * tr_fit3_sig->GetEntries(), 0, 1.2 * tr_fit3_sig->GetEntries());
    RooFormulaVar nsig_mode4_sig("nsig_mode4_sig", "signal of mode4 sig", "Bratio * nsig_mode4* 0.200845266  *0.0799/  0.503631863  /0.0951", RooArgSet(Bratio, nsig_mode4 ));	RooRealVar nbkg4_sig("nbkg4_sig", "bkg number of mode4 sig", 0.05 * tr_fit4_sig->GetEntries(), 0, 1.2 * tr_fit4_sig->GetEntries());
    RooFormulaVar nsig_mode5_sig("nsig_mode5_sig", "signal of mode5 sig", "Bratio * nsig_mode5* 0.200845266  *0.0787/  0.503631863  /0.0922", RooArgSet(Bratio, nsig_mode5 ));	RooRealVar nbkg5_sig("nbkg5_sig", "bkg number of mode5 sig", 0.05 * tr_fit5_sig->GetEntries(), 0, 1.2 * tr_fit5_sig->GetEntries());
    RooFormulaVar nsig_mode6_sig("nsig_mode6_sig", "signal of mode6 sig", "Bratio * nsig_mode6* 0.200845266  *0.0771/  0.503631863  /0.0920", RooArgSet(Bratio, nsig_mode6 ));	RooRealVar nbkg6_sig("nbkg6_sig", "bkg number of mode6 sig", 0.05 * tr_fit6_sig->GetEntries(), 0, 1.2 * tr_fit6_sig->GetEntries());


    //
    // ____________________
    var_4600->setRange("fitrange", xmin_4600, xmax_4600);
    var_4612->setRange("fitrange", xmin_4612, xmax_4612);
    var_4620->setRange("fitrange", xmin_4620, xmax_4620);
    var_4640->setRange("fitrange", xmin_4640, xmax_4640);
    var_4660->setRange("fitrange", xmin_4660, xmax_4660);
    var_4680->setRange("fitrange", xmin_4680, xmax_4680);
    var_4700->setRange("fitrange", xmin_4700, xmax_4700);
    // sig
    RooAddPdf *model0_sig = new RooAddPdf("model0_sig", "model0_sig", RooArgList(*sigpdf0_sig, argus0_sig), RooArgList(nsig_mode0_sig, nbkg0_sig));
    RooAddPdf *model1_sig = new RooAddPdf("model1_sig", "model1_sig", RooArgList(*sigpdf1_sig, argus1_sig), RooArgList(nsig_mode1_sig, nbkg1_sig));
    RooAddPdf *model2_sig = new RooAddPdf("model2_sig", "model2_sig", RooArgList(*sigpdf2_sig, argus2_sig), RooArgList(nsig_mode2_sig, nbkg2_sig));
    RooAddPdf *model3_sig = new RooAddPdf("model3_sig", "model3_sig", RooArgList(*sigpdf3_sig, argus3_sig), RooArgList(nsig_mode3_sig, nbkg3_sig));
    RooAddPdf *model4_sig = new RooAddPdf("model4_sig", "model4_sig", RooArgList(*sigpdf4_sig, argus4_sig), RooArgList(nsig_mode4_sig, nbkg4_sig));
    RooAddPdf *model5_sig = new RooAddPdf("model5_sig", "model5_sig", RooArgList(*sigpdf5_sig, argus5_sig), RooArgList(nsig_mode5_sig, nbkg5_sig));
    RooAddPdf *model6_sig = new RooAddPdf("model6_sig", "model6_sig", RooArgList(*sigpdf6_sig, argus6_sig), RooArgList(nsig_mode6_sig, nbkg6_sig));

    // ref
    RooAddPdf *model0 = new RooAddPdf("model0", "model0", RooArgList(*sigpdf0, argus0), RooArgList(nsig_mode0, nbkg0));
    RooAddPdf *model1 = new RooAddPdf("model1", "model1", RooArgList(*sigpdf1, argus1), RooArgList(nsig_mode1, nbkg1));
    RooAddPdf *model2 = new RooAddPdf("model2", "model2", RooArgList(*sigpdf2, argus2), RooArgList(nsig_mode2, nbkg2));
    RooAddPdf *model3 = new RooAddPdf("model3", "model3", RooArgList(*sigpdf3, argus3), RooArgList(nsig_mode3, nbkg3));
    RooAddPdf *model4 = new RooAddPdf("model4", "model4", RooArgList(*sigpdf4, argus4), RooArgList(nsig_mode4, nbkg4));
    RooAddPdf *model5 = new RooAddPdf("model5", "model5", RooArgList(*sigpdf5, argus5), RooArgList(nsig_mode5, nbkg5));
    RooAddPdf *model6 = new RooAddPdf("model6", "model6", RooArgList(*sigpdf6, argus6), RooArgList(nsig_mode6, nbkg6));

    //constraints
    RooAbsReal* nl_4600  =  model0_sig->createNLL(*data0_sig);
    RooAbsReal* nl_4612  =  model1_sig->createNLL(*data1_sig);
    RooAbsReal* nl_4620  =  model2_sig->createNLL(*data2_sig);
    RooAbsReal* nl_4640  =  model3_sig->createNLL(*data3_sig);
    RooAbsReal* nl_4660  =  model4_sig->createNLL(*data4_sig);
    RooAbsReal* nl_4680  =  model5_sig->createNLL(*data5_sig);
    RooAbsReal* nl_4700  =  model6_sig->createNLL(*data6_sig);


    RooAbsReal* ref_nl_4600  =  model0->createNLL(*data0);
    RooAbsReal* ref_nl_4612  =  model1->createNLL(*data1);
    RooAbsReal* ref_nl_4620  =  model2->createNLL(*data2);
    RooAbsReal* ref_nl_4640  =  model3->createNLL(*data3);
    RooAbsReal* ref_nl_4660  =  model4->createNLL(*data4);
    RooAbsReal* ref_nl_4680  =  model5->createNLL(*data5);
    RooAbsReal* ref_nl_4700  =  model6->createNLL(*data6);

    RooArgSet allList;
    allList.add(*nl_4600);
    allList.add(*nl_4612);
    allList.add(*nl_4620);
    allList.add(*nl_4640);
    allList.add(*nl_4660);
    allList.add(*nl_4680);
    allList.add(*nl_4700);

    allList.add(*ref_nl_4600);
    allList.add(*ref_nl_4612);
    allList.add(*ref_nl_4620);
    allList.add(*ref_nl_4640);
    allList.add(*ref_nl_4660);
    allList.add(*ref_nl_4680);
    allList.add(*ref_nl_4700);
    
        // RooPlot *frame_mode0 = M_BC_r3c->frame(2.25, 2.35, 20);
        // frame_mode0->SetXTitle("M_BC_r3c #pi0 4600");
        // model0->plotOn(frame_mode0, Components("*sigpdf0"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        // frame_mode0->Draw();
        // return 0;

    RooAddition nll("nll", "nll", allList);
    RooMinuit mm(nll);
    mm.migrad();
    mm.hesse();

    RooFitResult *result = mm.save();
    result->Print("v");

    cout << __LINE__ << ", 4600 sig nsig_mode0_sig: "<< nsig_mode0_sig.getVal() << endl;
    cout << __LINE__ << ", 4612 sig nsig_mode1_sig: "<< nsig_mode1_sig.getVal() << endl;

    // ================================v========   D R A W  ====================================================================
    if(1)
    {
        TCanvas *can = new TCanvas("can", "simu fit", 400*2 * 1.8, 300*7 * 1.8); //setPad();
        can->Divide(2, 7);
        can->SetFillColor(0);
        // sig 4600
        RooPlot *frame_mode0_sig = var_4600->frame(xmin, 2.3, 20);
        frame_mode0_sig->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode0_sig->SetTitle("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta,     #sqrt{s}=4.600 GeV,     567 pb^{-1}");
        frame_mode0_sig->SetYTitle(ytitle);
        frame_mode0_sig->GetYaxis()->SetTitleOffset(1.2);
        frame_mode0_sig->GetYaxis()->SetTitleSize(0.04);
        frame_mode0_sig->GetXaxis()->SetTitleSize(0.04);
        data0_sig->plotOn(frame_mode0_sig, LineWidth(2));
        model0_sig->plotOn(frame_mode0_sig, LineColor(kRed), LineWidth(3));
        model0_sig->plotOn(frame_mode0_sig, Components("sigpdf0_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        model0_sig->plotOn(frame_mode0_sig, Components("argus0_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        can->cd(1);  
        frame_mode0_sig->Draw();
        gPad->Update();
        TPaveText* title = (TPaveText*)gPad->FindObject("title");
        // title->InsertText("");
        title->SetTextAlign(10);
        title->SetX1NDC(0.09);
        title->SetTextSize(0.04);
        title->SetY1NDC(0.82);
        title->SetX2NDC(0.47);
        title->SetY2NDC(0.980);
        gPad->Modified();
        gPad->Update();
        
        // ref 4600
        RooPlot *frame_mode0 = var_4600->frame( xmin, 2.3, 20);
        frame_mode0->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode0->SetYTitle(ytitle);
        frame_mode0->SetTitle("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #pi^{0},    #sqrt{s}=4.600 GeV,     567 pb^{-1}");
        frame_mode0->GetYaxis()->SetTitleOffset(1.2);
        frame_mode0->GetYaxis()->SetTitleSize(0.04);
        frame_mode0->GetXaxis()->SetTitleSize(0.04);
        data0->plotOn(frame_mode0, LineWidth(2));
        model0->plotOn(frame_mode0, LineColor(kRed), LineWidth(3));
        model0->plotOn(frame_mode0, Components("sigpdf0"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        model0->plotOn(frame_mode0, Components("argus0"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        can->cd(2);  
        frame_mode0->Draw();
        gPad->Update();
        title = (TPaveText*)gPad->FindObject("title");
        //title->InsertText\("#Lambda_\{c\}\^\{\+\} #rightarrow #Sigma\^\{\+\} #pi_\{0\}"\);
        title->SetTextAlign(10);
        title->SetX1NDC(0.09);
        title->SetTextSize(0.04);
        title->SetY1NDC(0.82);
        title->SetX2NDC(0.47);
        title->SetY2NDC(0.980);
        gPad->Modified();
        gPad->Update();

        // sig 4612
        RooPlot *frame_mode1_sig = var_4612->frame(xmin, 2.30579, 20);
        frame_mode1_sig->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode1_sig->SetYTitle(ytitle);
        frame_mode1_sig->SetTitle("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta,     #sqrt{s}=4.612 GeV,     102 pb^{-1}");
        frame_mode1_sig->GetYaxis()->SetTitleOffset(1.2);
        frame_mode1_sig->GetYaxis()->SetTitleSize(0.04);
        frame_mode1_sig->GetXaxis()->SetTitleSize(0.04);
        data1_sig->plotOn(frame_mode1_sig, LineWidth(2));
        model1_sig->plotOn(frame_mode1_sig, LineColor(kRed), LineWidth(3));
        model1_sig->plotOn(frame_mode1_sig, Components("sigpdf1_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        model1_sig->plotOn(frame_mode1_sig, Components("argus1_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        can->cd(3);  
        frame_mode1_sig->Draw();
        gPad->Update();
        title = (TPaveText*)gPad->FindObject("title");
        //title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta");
        title->SetTextAlign(10);
        title->SetX1NDC(0.09);
        title->SetTextSize(0.04);
        title->SetY1NDC(0.82);
        title->SetX2NDC(0.47);
        title->SetY2NDC(0.980);
        gPad->Modified();
        gPad->Update();
        // ref 4612
        RooPlot *frame_mode1 = var_4612->frame( xmin, 2.30579, 20);
        frame_mode1->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode1->SetYTitle(ytitle);
        frame_mode1->SetTitle("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #pi^{0},     #sqrt{s}=4.612 GeV,     102 pb^{-1}");
        frame_mode1->GetYaxis()->SetTitleOffset(1.2);
        frame_mode1->GetYaxis()->SetTitleSize(0.04);
        frame_mode1->GetXaxis()->SetTitleSize(0.04);
        data1->plotOn(frame_mode1, LineWidth(1));
        model1->plotOn(frame_mode1, LineColor(kRed), LineWidth(3));
        model1->plotOn(frame_mode1, Components("sigpdf1"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        model1->plotOn(frame_mode1, Components("argus1"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        can->cd(4);  
        frame_mode1->Draw();
        gPad->Update();
        title = (TPaveText*)gPad->FindObject("title");
        //title->InsertText\("#Lambda_\{c\}\^\{\+\} #rightarrow #Sigma\^\{\+\} #pi_\{0\}"\);
        title->SetTextAlign(10);
        title->SetX1NDC(0.09);
        title->SetTextSize(0.04);
        title->SetY1NDC(0.82);
        title->SetX2NDC(0.47);
        title->SetY2NDC(0.980);
        gPad->Modified();
        gPad->Update();

        // sig 4620
        RooPlot *frame_mode2_sig = var_4620->frame(xmin, 2.31387, 20);
        frame_mode2_sig->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode2_sig->SetYTitle(ytitle);
        frame_mode2_sig->SetTitle("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta,     #sqrt{s}=4.628 GeV,     517 pb^{-1}");
        frame_mode2_sig->GetYaxis()->SetTitleOffset(1.2);
        frame_mode2_sig->GetYaxis()->SetTitleSize(0.04);
        frame_mode2_sig->GetXaxis()->SetTitleSize(0.04);
        data2_sig->plotOn(frame_mode2_sig, LineWidth(2));
        model2_sig->plotOn(frame_mode2_sig, LineColor(kRed), LineWidth(3));
        model2_sig->plotOn(frame_mode2_sig, Components("sigpdf2_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        model2_sig->plotOn(frame_mode2_sig, Components("argus2_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        can->cd(5);  
        frame_mode2_sig->Draw();
        gPad->Update();
        title = (TPaveText*)gPad->FindObject("title");
        //title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta");
        title->SetTextAlign(10);
        title->SetX1NDC(0.09);
        title->SetTextSize(0.04);
        title->SetY1NDC(0.82);
        title->SetX2NDC(0.47);
        title->SetY2NDC(0.980);
        gPad->Modified();
        gPad->Update();
        // ref 4620
        RooPlot *frame_mode2 = var_4620->frame( xmin, 2.31387, 20);
        frame_mode2->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode2->SetYTitle(ytitle);
        frame_mode2->SetTitle("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #pi^{0},     #sqrt{s}=4.628 GeV     517 pb^{-1}");
        frame_mode2->GetYaxis()->SetTitleOffset(1.2);
        frame_mode2->GetYaxis()->SetTitleSize(0.04);
        frame_mode2->GetXaxis()->SetTitleSize(0.04);
        data2->plotOn(frame_mode2, LineWidth(2));
        model2->plotOn(frame_mode2, LineColor(kRed), LineWidth(3));
        model2->plotOn(frame_mode2, Components("sigpdf2"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        model2->plotOn(frame_mode2, Components("argus2"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        can->cd(6);  
        frame_mode2->Draw();
        gPad->Update();
        title = (TPaveText*)gPad->FindObject("title");
        //title->InsertText\("#Lambda_\{c\}\^\{\+\} #rightarrow #Sigma\^\{\+\} #pi_\{0\}"\);
        title->SetTextAlign(10);
        title->SetX1NDC(0.09);
        title->SetTextSize(0.04);
        title->SetY1NDC(0.82);
        title->SetX2NDC(0.47);
        title->SetY2NDC(0.980);
        gPad->Modified();
        gPad->Update();
        
        // sig 4640
        RooPlot *frame_mode3_sig = var_4640->frame(xmin, 2.3202550, 25);
        frame_mode3_sig->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode3_sig->SetYTitle(ytitle);
        frame_mode3_sig->SetTitle("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta,     #sqrt{s}=4.641 GeV,     537 pb^{-1}");
        frame_mode3_sig->GetYaxis()->SetTitleOffset(1.2);
        frame_mode3_sig->GetYaxis()->SetTitleSize(0.04);
        frame_mode3_sig->GetXaxis()->SetTitleSize(0.04);
        data3_sig->plotOn(frame_mode3_sig, LineWidth(2));
        model3_sig->plotOn(frame_mode3_sig, LineColor(kRed), LineWidth(3));
        model3_sig->plotOn(frame_mode3_sig, Components("sigpdf3_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        model3_sig->plotOn(frame_mode3_sig, Components("argus3_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        can->cd(7);  
        frame_mode3_sig->Draw();
        gPad->Update();
        title = (TPaveText*)gPad->FindObject("title");
        //title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta");
        title->SetTextAlign(10);
        title->SetX1NDC(0.09);
        title->SetTextSize(0.04);
        title->SetY1NDC(0.82);
        title->SetX2NDC(0.47);
        title->SetY2NDC(0.980);
        gPad->Modified();
        gPad->Update();
        // ref 4640
        RooPlot *frame_mode3 = var_4640->frame( xmin, 2.3202550, 25);
        frame_mode3->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode3->SetYTitle(ytitle);
        frame_mode3->SetTitle("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #pi^{0},     #sqrt{s}=4.641 GeV,     537 pb^{-1}");
        frame_mode3->GetYaxis()->SetTitleOffset(1.2);
        frame_mode3->GetYaxis()->SetTitleSize(0.04);
        frame_mode3->GetXaxis()->SetTitleSize(0.04);
        data3->plotOn(frame_mode3, LineWidth(2));
        model3->plotOn(frame_mode3, LineColor(kRed), LineWidth(3));
        model3->plotOn(frame_mode3, Components("sigpdf3"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        model3->plotOn(frame_mode3, Components("argus3"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        can->cd(8);  
        frame_mode3->Draw();
        gPad->Update();
        title = (TPaveText*)gPad->FindObject("title");
        //title->InsertText\("#Lambda_\{c\}\^\{\+\} #rightarrow #Sigma\^\{\+\} #pi_\{0\}"\);
        title->SetTextAlign(10);
        title->SetX1NDC(0.09);
        title->SetTextSize(0.04);
        title->SetY1NDC(0.82);
        title->SetX2NDC(0.47);
        title->SetY2NDC(0.980);
        gPad->Modified();	
        gPad->Update();
        // can->SaveAs("svg_fit_comb.svg");

        //   ------             ----               ----
        // TCanvas *can2 = new TCanvas("can2", "simu fit2", 800, 900); //setPad();
        // can2->Divide(2, 3);
        // can2->SetFillColor(0);
        // sig 4660
        RooPlot *frame_mode4_sig = var_4660->frame(xmin, 2.3304600, 25);
        frame_mode4_sig->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode4_sig->SetYTitle(ytitle);
        frame_mode4_sig->SetTitle("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta,    #sqrt{s}=4.661 GeV,     523 pb^{-1}");
        frame_mode4_sig->GetYaxis()->SetTitleOffset(1.2);
        frame_mode4_sig->GetYaxis()->SetTitleSize(0.04);
        frame_mode4_sig->GetXaxis()->SetTitleSize(0.04);
        data4_sig->plotOn(frame_mode4_sig, LineWidth(2));
        model4_sig->plotOn(frame_mode4_sig, LineColor(kRed), LineWidth(3));
        model4_sig->plotOn(frame_mode4_sig, Components("sigpdf4_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        model4_sig->plotOn(frame_mode4_sig, Components("argus4_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        can->cd(9);  
        frame_mode4_sig->Draw();
        gPad->Update();
        title = (TPaveText*)gPad->FindObject("title");
        //title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta");
        title->SetTextAlign(10);
        title->SetX1NDC(0.09);
        title->SetTextSize(0.04);
        title->SetY1NDC(0.82);
        title->SetX2NDC(0.47);
        title->SetY2NDC(0.980);
        gPad->Modified();
        gPad->Update();	
        // ref 4660
        RooPlot *frame_mode4 = var_4660->frame( xmin, 2.3304600, 25);
        frame_mode4->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode4->SetYTitle(ytitle);
        frame_mode4->SetTitle("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #pi^{0},     #sqrt{s}=4.661 GeV,     523 pb^{-1}");
        frame_mode4->GetYaxis()->SetTitleOffset(1.2);
        frame_mode4->GetYaxis()->SetTitleSize(0.04);
        frame_mode4->GetXaxis()->SetTitleSize(0.04);
        data4->plotOn(frame_mode4, LineWidth(2));
        model4->plotOn(frame_mode4, LineColor(kRed), LineWidth(3));
        model4->plotOn(frame_mode4, Components("sigpdf4"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        model4->plotOn(frame_mode4, Components("argus4"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        can->cd(10);  
        frame_mode4->Draw();
        gPad->Update();
        title = (TPaveText*)gPad->FindObject("title");
        //title->InsertText\("#Lambda_\{c\}\^\{\+\} #rightarrow #Sigma\^\{\+\} #pi_\{0\}"\);
        title->SetTextAlign(10);
        title->SetX1NDC(0.09);
        title->SetTextSize(0.04);
        title->SetY1NDC(0.82);
        title->SetX2NDC(0.47);
        title->SetY2NDC(0.980);
        gPad->Modified();	
        gPad->Update();
        
        // sig 4680
        RooPlot *frame_mode5_sig = var_4680->frame( xmin, 2.3407900, 30);
        frame_mode5_sig->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode5_sig->SetYTitle(ytitle);
        frame_mode5_sig->SetTitle("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta,     #sqrt{s}=4.682 GeV,     1657 pb^{-1}");
        frame_mode5_sig->GetYaxis()->SetTitleOffset(1.2);
        frame_mode5_sig->GetYaxis()->SetTitleSize(0.04);
        frame_mode5_sig->GetXaxis()->SetTitleSize(0.04);
        data5_sig->plotOn(frame_mode5_sig, LineWidth(2));
        model5_sig->plotOn(frame_mode5_sig, LineColor(kRed), LineWidth(3));
        model5_sig->plotOn(frame_mode5_sig, Components("sigpdf5_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        model5_sig->plotOn(frame_mode5_sig, Components("argus5_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        can->cd(11);  
        frame_mode5_sig->Draw();
        gPad->Update();
        title = (TPaveText*)gPad->FindObject("title");
        //title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta");
        title->SetTextAlign(10);
        title->SetX1NDC(0.09);
        title->SetTextSize(0.04);
        title->SetY1NDC(0.82);
        title->SetX2NDC(0.47);
        title->SetY2NDC(0.980);
        gPad->Modified();	
        gPad->Update();
        // ref 4680
        RooPlot *frame_mode5 = var_4680->frame( xmin, 2.3407900, 30);
        frame_mode5->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode5->SetYTitle(ytitle);
        frame_mode5->SetTitle("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #pi^{0},     #sqrt{s}=4.682 GeV,     1657 pb^{-1}");
        frame_mode5->GetYaxis()->SetTitleOffset(1.2);
        frame_mode5->GetYaxis()->SetTitleSize(0.04);
        frame_mode5->GetXaxis()->SetTitleSize(0.04);
        data5->plotOn(frame_mode5, LineWidth(2));
        model5->plotOn(frame_mode5, LineColor(kRed), LineWidth(3));
        model5->plotOn(frame_mode5, Components("sigpdf5"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        model5->plotOn(frame_mode5, Components("argus5"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        can->cd(12);  
        frame_mode5->Draw();
        gPad->Update();
        title = (TPaveText*)gPad->FindObject("title");
        //title->InsertText\("#Lambda_\{c\}\^\{\+\} #rightarrow #Sigma\^\{\+\} #pi_\{0\}"\);
        title->SetTextAlign(10);
        title->SetX1NDC(0.09);
        title->SetTextSize(0.04);
        title->SetY1NDC(0.82);
        title->SetX2NDC(0.47);
        title->SetY2NDC(0.980);
        gPad->Modified();	
        gPad->Update();
        
        
        // sig 4700
        RooPlot *frame_mode6_sig = var_4700->frame( xmin, 2.34919, 30);
        frame_mode6_sig->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode6_sig->SetYTitle(ytitle);
        frame_mode6_sig->SetTitle("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta,     #sqrt{s}=4.698 GeV,     532 pb^{-1}");
        frame_mode6_sig->GetYaxis()->SetTitleOffset(1.2);
        frame_mode6_sig->GetYaxis()->SetTitleSize(0.04);
        frame_mode6_sig->GetXaxis()->SetTitleSize(0.04);
        data6_sig->plotOn(frame_mode6_sig, LineWidth(2));
        // model6_sig->plotOn(frame_mode6_sig, LineColor(kRed), LineWidth(3));
        // model6_sig->plotOn(frame_mode6_sig, Components("sigpdf6_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        // model6_sig->plotOn(frame_mode6_sig, Components("argus6_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        can->cd(13);  
        frame_mode6_sig->Draw();
        gPad->Update();
        title = (TPaveText*)gPad->FindObject("title");
        //title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta");
        title->SetTextAlign(10);
        title->SetX1NDC(0.09);
        title->SetTextSize(0.04);
        title->SetY1NDC(0.82);
        title->SetX2NDC(0.47);
        title->SetY2NDC(0.980);
        gPad->Modified();
        gPad->Update();
        // ref 4700
        RooPlot *frame_mode6 = var_4700->frame( xmin, 2.34919, 30);
        frame_mode6->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode6->SetYTitle(ytitle);
        frame_mode6->SetTitle("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta,     #sqrt{s}=4.698 GeV,     532 pb^{-1}");
        frame_mode6->GetYaxis()->SetTitleOffset(1.2);
        frame_mode6->GetYaxis()->SetTitleSize(0.04);
        frame_mode6->GetXaxis()->SetTitleSize(0.04);
        data6->plotOn(frame_mode6, LineWidth(2));
        model6->plotOn(frame_mode6, LineColor(kRed), LineWidth(3));
        model6->plotOn(frame_mode6, Components("sigpdf6"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        model6->plotOn(frame_mode6, Components("argus6"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        can->cd(14);  
        frame_mode6->Draw();
        gPad->Update();
        title = (TPaveText*)gPad->FindObject("title");
        //title->InsertText\("#Lambda_\{c\}\^\{\+\} #rightarrow #Sigma\^\{\+\} #pi_\{0\}"\);
        title->SetTextAlign(10);
        title->SetX1NDC(0.09);
        title->SetTextSize(0.04);
        title->SetY1NDC(0.82);
        title->SetX2NDC(0.47);
        title->SetY2NDC(0.980);
        gPad->Modified();
        gPad->Update();
        // can->SaveAs("svg_fit_comb.pdf");
        can->SaveAs("b.png");
    }

    // ================================================================================
    // ********************************************************************************
    
    if(1)
    {
        cout << "_________________________________________________________________" << endl;
        TCanvas *can3 = new TCanvas("can3", "simu fit3", 800, 600); 
        can3->SetFillColor(0);
        can3->cd();

            
        // RooCategory combine("combine", "combine");
        // combine.defineType("mode0");
        // combine.defineType("mode1");
        // combine.defineType("mode2");
        // combine.defineType("mode3");
        // combine.defineType("mode4");
        // combine.defineType("mode5");
        // combine.defineType("mode6");

        // RooDataSet *combData = new RooDataSet("combData", "combined data", 
            // RooArgSet(*var_4600, *var_4612, *var_4620, *var_4640, *var_4660, *var_4680, *var_4700), Index(combine), 
            // Import("mode0", *data0_sig), Import("mode1", *data1_sig), Import("mode2", *data2_sig), Import("mode3", *data3_sig), 
            // Import("mode4", *data4_sig), Import("mode5", *data5_sig), Import("mode6", *data6_sig));
        
        RooRealVar *M_BC_r3c = new RooRealVar("M_BC_r3c", "M_BC_r3c", mbcmin, mbcmax);
        RooDataSet *combData = new RooDataSet("combData", "combined data",  RooArgSet(*M_BC_r3c));
        combData->append(*data0_sig);
        combData->append(*data1_sig);
        combData->append(*data2_sig);
        combData->append(*data3_sig);
        combData->append(*data4_sig);
        combData->append(*data5_sig);
        combData->append(*data6_sig);
        // sig
        RooAddPdf *pdfSig = new RooAddPdf("pdfSig", "pdfSig", 
            RooArgList(*model0_sig,   *model1_sig,  *model2_sig, *model3_sig, *model4_sig, *model5_sig, *model6_sig ));
            
        // RooAddPdf *sig_pdfSig = new RooAddPdf("sig_pdfSig", "sig_pdfSig", 
        //     RooArgList(*model0_sig,   *model1_sig,  *model2_sig, *model3_sig, *model4_sig, *model5_sig, *model6_sig ), 
        //     RooArgList(nsig_mode0_sig, nsig_mode1_sig, nsig_mode2_sig,  nsig_mode3_sig, nsig_mode4_sig, nsig_mode5_sig, nsig_mode6_sig));
        
        // RooAddPdf *sig_pdfBkg = new RooAddPdf("sig_pdfBkg", "sig_pdfBkg",
        //     RooArgList(*model0_sig, *model1_sig, *model2_sig, *model3_sig, *model4_sig, *model5_sig, *model6_sig),
        //     RooArgList(nbkg0_sig, nbkg1_sig, nbkg2_sig, nbkg3_sig, nbkg4_sig, nbkg5_sig, nbkg6_sig ));

        RooPlot *frame_mode_sig = M_BC_r3c->frame( mbcmin, mbcmax, 40);
        frame_mode_sig->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode_sig->SetYTitle(ytitle);
        frame_mode_sig->SetTitle("all data");
        frame_mode_sig->GetYaxis()->SetTitleOffset(1.2);
        frame_mode_sig->GetYaxis()->SetTitleSize(0.04);
        frame_mode_sig->GetXaxis()->SetTitleSize(0.04);
        combData->plotOn(frame_mode_sig,  LineWidth(2));
        // pdfSig->plotOn(frame_mode_sig, LineColor(kRed),  LineWidth(3));
        pdfSig->plotOn(frame_mode_sig,  Components("argus*_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        pdfSig->plotOn(frame_mode_sig, Components("sigpdf6_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        pdfSig->plotOn(frame_mode_sig, Components("sigpdf5_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        pdfSig->plotOn(frame_mode_sig, Components("sigpdf*_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));

        // model0_sig->plotOn(frame_mode_sig, Components("*sigpdf0_sig"), Name("sigHist_0") LineColor(kGreen), LineWidth(3), LineStyle(kDashed), Invisible());
        // model1_sig->plotOn(frame_mode_sig, Components("*sigpdf1_sig"), Name("sigHist_1") LineColor(kGreen), LineWidth(3), LineStyle(kDashed), Invisible());
        // model2_sig->plotOn(frame_mode_sig, Components("*sigpdf2_sig"), Name("sigHist_2") LineColor(kGreen), LineWidth(3), LineStyle(kDashed), Invisible());
        // model3_sig->plotOn(frame_mode_sig, Components("*sigpdf3_sig"), Name("sigHist_3") LineColor(kGreen), LineWidth(3), LineStyle(kDashed), Invisible());
        // model4_sig->plotOn(frame_mode_sig, Components("*sigpdf4_sig"), Name("sigHist_4") LineColor(kGreen), LineWidth(3), LineStyle(kDashed), Invisible());
        // model5_sig->plotOn(frame_mode_sig, Components("*sigpdf5_sig"), Name("sigHist_5") LineColor(kGreen), LineWidth(3), LineStyle(kDashed), Invisible());
        // model6_sig->plotOn(frame_mode_sig, Components("*sigpdf6_sig"), Name("sigHist_6") LineColor(kGreen), LineWidth(3), LineStyle(kDashed), Invisible());

        // sigpdf0_sig->plotOn(frame_mode_sig, Components("sigpdf*_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));


        frame_mode_sig->Draw();
        can3->SaveAs("a.png");
    }



    
    //
    //
    // cout << endl;
    cout << "Br: " << Bratio.getVal() << " +/- " << Bratio.getError() << endl;
    // cout << "result->minNll(): " <<result->minNll() << endl;

    cout << __LINE__ << ", 4600 ref nbkg0: "<< nbkg0.getVal() << endl;
    cout << __LINE__ << ", 4612 ref nbkg1: "<< nbkg1.getVal() << endl;
    cout << __LINE__ << ", 4620 ref nbkg2: "<< nbkg2.getVal() << endl;
    cout << __LINE__ << ", 4640 ref nbkg3: "<< nbkg3.getVal() << endl;
    cout << __LINE__ << ", 4660 ref nbkg4: "<< nbkg4.getVal() << endl;
    cout << __LINE__ << ", 4680 ref nbkg5: "<< nbkg5.getVal() << endl;
    cout << __LINE__ << ", 4700 ref nbkg6: "<< nbkg6.getVal() << endl;

    cout << __LINE__ << ", 4600 sig nbkg0: "<< nbkg0_sig.getVal() << endl;
    cout << __LINE__ << ", 4612 sig nbkg1: "<< nbkg1_sig.getVal() << endl;
    cout << __LINE__ << ", 4620 sig nbkg2: "<< nbkg2_sig.getVal() << endl;
    cout << __LINE__ << ", 4640 sig nbkg3: "<< nbkg3_sig.getVal() << endl;
    cout << __LINE__ << ", 4660 sig nbkg4: "<< nbkg4_sig.getVal() << endl;
    cout << __LINE__ << ", 4680 sig nbkg5: "<< nbkg5_sig.getVal() << endl;
    cout << __LINE__ << ", 4700 sig nbkg6: "<< nbkg6_sig.getVal() << endl;

    cout << __LINE__ << ", 4600 ref nsig_mode0: "<< nsig_mode0.getVal() << endl;
    cout << __LINE__ << ", 4612 ref nsig_mode1: "<< nsig_mode1.getVal() << endl;
    cout << __LINE__ << ", 4620 ref nsig_mode2: "<< nsig_mode2.getVal() << endl;
    cout << __LINE__ << ", 4640 ref nsig_mode3: "<< nsig_mode3.getVal() << endl;
    cout << __LINE__ << ", 4660 ref nsig_mode4: "<< nsig_mode4.getVal() << endl;
    cout << __LINE__ << ", 4680 ref nsig_mode5: "<< nsig_mode5.getVal() << endl;
    cout << __LINE__ << ", 4670 ref nsig_mode6: "<< nsig_mode6.getVal() << endl;

    cout << __LINE__ << ", 4600 sig nsig_mode0_sig: "<< nsig_mode0_sig.getVal() << endl;
    cout << __LINE__ << ", 4612 sig nsig_mode1_sig: "<< nsig_mode1_sig.getVal() << endl;
    cout << __LINE__ << ", 4620 sig nsig_mode2_sig: "<< nsig_mode2_sig.getVal() << endl;
    cout << __LINE__ << ", 4640 sig nsig_mode3_sig: "<< nsig_mode3_sig.getVal() << endl;
    cout << __LINE__ << ", 4660 sig nsig_mode4_sig: "<< nsig_mode4_sig.getVal() << endl;
    cout << __LINE__ << ", 4680 sig nsig_mode5_sig: "<< nsig_mode5_sig.getVal() << endl;
    cout << __LINE__ << ", 4700 sig nsig_mode6_sig: "<< nsig_mode6_sig.getVal() << endl;

    // //
    // // //
    // Double_t DeltaLL = 2 * fabs(result->minNll() - FCN_bkg);
    // Double_t prob = TMath::Prob(DeltaLL, 1);
    // Double_t nSigma = sqrt(2) * TMath::ErfcInverse(prob);
    // cout << "result->minNll() " << result->minNll() << " " << "|FCN_single - FCN_bkg| = " << DeltaLL << endl;
    // cout << " Sigma: " << nSigma << endl;
    return 0;
}
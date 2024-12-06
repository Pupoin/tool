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
TCut cut_ref = (cut_mbc && "(chi2_min_r3c< 30)" && cut_np);
TCut cut_sig = (cut_mbc && "(chi2_min_r3c< 30)" && cut_np);
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
Double_t FCN_bkg = -13763.9;
RooRealVar Bratio("Bratio", "Br of sig/ref", 0.335808, 0.135808, 0.535808);	
// RooRealVar Bratio("Bratio", "Br of sig/ref", 0);	

int fit_toymc_comb()
{

    TH1::SetDefaultSumw2(1);
    TString a("Events/");
    char b[30];
    sprintf(b, "(%5.1f", (xmax - xmin) / xbins * 1000);
    TString c(" MeV/c^{2})");
    TString ytitle = a + b + c;

    //
    // sig 
    // TChain *tr_data0_sig = new TChain("tree");    tr_data0_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/4600data_removedouble.root");
    // TChain *tr_data1_sig = new TChain("tree");    tr_data1_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/4612data_removedouble.root");
    // TChain *tr_data2_sig = new TChain("tree");    tr_data2_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/4620data_removedouble.root");
    // TChain *tr_data3_sig = new TChain("tree");	  tr_data3_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/4640data_removedouble.root");
    // TChain *tr_data4_sig = new TChain("tree");	  tr_data4_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/4660data_removedouble.root");
    // TChain *tr_data5_sig = new TChain("tree");	  tr_data5_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/4680data_removedouble.root");
    // TChain *tr_data6_sig = new TChain("tree");    tr_data6_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/data/cutmassroot/tightcut_r3c_minchi2/4700data_removedouble.root");

    // // ref
    // TChain *tr_data0 = new TChain("tree");    tr_data0->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/data/cutmassroot/tightcut_r3c_minchi2/4600data_adddipim.root");
    // TChain *tr_data1 = new TChain("tree");    tr_data1->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/data/cutmassroot/tightcut_r3c_minchi2/4612data_adddipim.root");
    // TChain *tr_data2 = new TChain("tree");    tr_data2->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/data/cutmassroot/tightcut_r3c_minchi2/4620data_adddipim.root");
    // TChain *tr_data3 = new TChain("tree");	  tr_data3->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/data/cutmassroot/tightcut_r3c_minchi2/4640data_adddipim.root");
    // TChain *tr_data4 = new TChain("tree");	  tr_data4->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/data/cutmassroot/tightcut_r3c_minchi2/4660data_adddipim.root");
    // TChain *tr_data5 = new TChain("tree");	  tr_data5->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/data/cutmassroot/tightcut_r3c_minchi2/4680data_adddipim.root");
    // TChain *tr_data6 = new TChain("tree");    tr_data6->Add("/publicfs/ucas/user/yuanchy8/7.0.6/pi0/data/cutmassroot/tightcut_r3c_minchi2/4700data_adddipim.root");

    // ____________________ data
    // TTree *tr_fit0_sig = tr_data0_sig->CopyTree(cut_sig);    RooDataSet *data0_sig = new RooDataSet("data0_sig"," M_BC_r3c", tr_fit0_sig, RooArgSet(*var_4600));
    // TTree *tr_fit1_sig = tr_data1_sig->CopyTree(cut_sig);    RooDataSet *data1_sig = new RooDataSet("data1_sig", "M_BC_r3c", tr_fit1_sig, RooArgSet(*var_4612));
    // TTree *tr_fit2_sig = tr_data2_sig->CopyTree(cut_sig);    RooDataSet *data2_sig = new RooDataSet("data2_sig", "M_BC_r3c", tr_fit2_sig, RooArgSet(*var_4620));
    // TTree *tr_fit3_sig = tr_data3_sig->CopyTree(cut_sig);    RooDataSet *data3_sig = new RooDataSet("data3_sig", "M_BC_r3c", tr_fit3_sig, RooArgSet(*var_4640));
    // TTree *tr_fit4_sig = tr_data4_sig->CopyTree(cut_sig);    RooDataSet *data4_sig = new RooDataSet("data4_sig", "M_BC_r3c", tr_fit4_sig, RooArgSet(*var_4660));
    // TTree *tr_fit5_sig = tr_data5_sig->CopyTree(cut_sig);    RooDataSet *data5_sig = new RooDataSet("data5_sig", "M_BC_r3c", tr_fit5_sig, RooArgSet(*var_4680));
    // TTree *tr_fit6_sig = tr_data6_sig->CopyTree(cut_sig);    RooDataSet *data6_sig = new RooDataSet("data6_sig", "M_BC_r3c", tr_fit6_sig, RooArgSet(*var_4700));

    // TTree *tr_fit0 = tr_data0->CopyTree(cut_ref);    RooDataSet *data0 = new RooDataSet("data0", "M_BC_r3c", tr_fit0, RooArgSet(*var_4600));
    // TTree *tr_fit1 = tr_data1->CopyTree(cut_ref);    RooDataSet *data1 = new RooDataSet("data1", "M_BC_r3c", tr_fit1, RooArgSet(*var_4612));
    // TTree *tr_fit2 = tr_data2->CopyTree(cut_ref);    RooDataSet *data2 = new RooDataSet("data2", "M_BC_r3c", tr_fit2, RooArgSet(*var_4620));
    // TTree *tr_fit3 = tr_data3->CopyTree(cut_ref);    RooDataSet *data3 = new RooDataSet("data3", "M_BC_r3c", tr_fit3, RooArgSet(*var_4640));
    // TTree *tr_fit4 = tr_data4->CopyTree(cut_ref);    RooDataSet *data4 = new RooDataSet("data4", "M_BC_r3c", tr_fit4, RooArgSet(*var_4660));
    // TTree *tr_fit5 = tr_data5->CopyTree(cut_ref);    RooDataSet *data5 = new RooDataSet("data5", "M_BC_r3c", tr_fit5, RooArgSet(*var_4680));
    // TTree *tr_fit6 = tr_data6->CopyTree(cut_ref);    RooDataSet *data6 = new RooDataSet("data6", "M_BC_r3c", tr_fit6, RooArgSet(*var_4700));

    // orignal
    RooRealVar mean_all_toy("mean_all", "mean_all",  -1.0337e-04);
    RooRealVar sigma_all_toy("sigma_all", "sigma_all",  7.3984e-06);
    
    // RooRealVar mean_all("mean_all", "mean_all",  -1.3832e-04 -  1.26e-04);
    // RooRealVar sigma_all("sigma_all", "sigma_all",  4.6448e-05 +  7.03e-05);

    RooGaussModel guass_4600_toy("guass_4600", "guass_4600", *var_4600, mean_all_toy, sigma_all_toy);
    RooGaussModel guass_4612_toy("guass_4612", "guass_4612", *var_4612, mean_all_toy, sigma_all_toy);
    RooGaussModel guass_4620_toy("guass_4620", "guass_4620", *var_4620, mean_all_toy, sigma_all_toy);
    RooGaussModel guass_4640_toy("guass_4640", "guass_4640", *var_4640, mean_all_toy, sigma_all_toy);
    RooGaussModel guass_4660_toy("guass_4660", "guass_4660", *var_4660, mean_all_toy, sigma_all_toy);
    RooGaussModel guass_4680_toy("guass_4680", "guass_4680", *var_4680, mean_all_toy, sigma_all_toy);
    RooGaussModel guass_4700_toy("guass_4700", "guass_4700", *var_4700, mean_all_toy, sigma_all_toy);

    // sig-- shape
    TFile *pdf0_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/4600_sig_shapepdf.root"); RooWorkspace *wspace0_sig = (RooWorkspace *)pdf0_sig->Get("wspace"); RooAbsPdf *shapepdf0_sig = wspace0_sig->pdf("modelPdf");  shapepdf0_sig->SetName("shapepdf0_sig");
    TFile *pdf1_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/4612_sig_shapepdf.root"); RooWorkspace *wspace1_sig = (RooWorkspace *)pdf1_sig->Get("wspace"); RooAbsPdf *shapepdf1_sig = wspace1_sig->pdf("modelPdf");  shapepdf1_sig->SetName("shapepdf1_sig");
    TFile *pdf2_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/4620_sig_shapepdf.root"); RooWorkspace *wspace2_sig = (RooWorkspace *)pdf2_sig->Get("wspace"); RooAbsPdf *shapepdf2_sig = wspace2_sig->pdf("modelPdf");  shapepdf2_sig->SetName("shapepdf2_sig");
    TFile *pdf3_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/4640_sig_shapepdf.root"); RooWorkspace *wspace3_sig = (RooWorkspace *)pdf3_sig->Get("wspace"); RooAbsPdf *shapepdf3_sig = wspace3_sig->pdf("modelPdf");  shapepdf3_sig->SetName("shapepdf3_sig");
    TFile *pdf4_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/4660_sig_shapepdf.root"); RooWorkspace *wspace4_sig = (RooWorkspace *)pdf4_sig->Get("wspace"); RooAbsPdf *shapepdf4_sig = wspace4_sig->pdf("modelPdf");  shapepdf4_sig->SetName("shapepdf4_sig");
    TFile *pdf5_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/4680_sig_shapepdf.root"); RooWorkspace *wspace5_sig = (RooWorkspace *)pdf5_sig->Get("wspace"); RooAbsPdf *shapepdf5_sig = wspace5_sig->pdf("modelPdf");  shapepdf5_sig->SetName("shapepdf5_sig");
    TFile *pdf6_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/4700_sig_shapepdf.root"); RooWorkspace *wspace6_sig = (RooWorkspace *)pdf6_sig->Get("wspace"); RooAbsPdf *shapepdf6_sig = wspace6_sig->pdf("modelPdf");  shapepdf6_sig->SetName("shapepdf6_sig");

    // ref-- shape
    TFile *pdf0 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/4612_ref_shapepdf.root"); RooWorkspace *wspace0 = (RooWorkspace *)pdf0->Get("wspace"); RooAbsPdf *shapepdf0 = wspace0->pdf("modelPdf");  shapepdf0->SetName("shapepdf0");
    TFile *pdf1 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/4612_ref_shapepdf.root"); RooWorkspace *wspace1 = (RooWorkspace *)pdf1->Get("wspace"); RooAbsPdf *shapepdf1 = wspace1->pdf("modelPdf");  shapepdf1->SetName("shapepdf1");
    TFile *pdf2 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/4620_ref_shapepdf.root"); RooWorkspace *wspace2 = (RooWorkspace *)pdf2->Get("wspace"); RooAbsPdf *shapepdf2 = wspace2->pdf("modelPdf");  shapepdf2->SetName("shapepdf2");
    TFile *pdf3 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/4640_ref_shapepdf.root"); RooWorkspace *wspace3 = (RooWorkspace *)pdf3->Get("wspace"); RooAbsPdf *shapepdf3 = wspace3->pdf("modelPdf");  shapepdf3->SetName("shapepdf3");
    TFile *pdf4 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/4660_ref_shapepdf.root"); RooWorkspace *wspace4 = (RooWorkspace *)pdf4->Get("wspace"); RooAbsPdf *shapepdf4 = wspace4->pdf("modelPdf");  shapepdf4->SetName("shapepdf4");
    TFile *pdf5 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/4680_ref_shapepdf.root"); RooWorkspace *wspace5 = (RooWorkspace *)pdf5->Get("wspace"); RooAbsPdf *shapepdf5 = wspace5->pdf("modelPdf");  shapepdf5->SetName("shapepdf5");
    TFile *pdf6 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/4700_ref_shapepdf.root"); RooWorkspace *wspace6 = (RooWorkspace *)pdf6->Get("wspace"); RooAbsPdf *shapepdf6 = wspace6->pdf("modelPdf");  shapepdf6->SetName("shapepdf6");

    // sig-- shape x guass
    RooAbsPdf *sigpdf0_sig_toy = new RooFFTConvPdf("sigpdf0_sig_toy", "shapepdf0_sig (X) gauss", *var_4600, *shapepdf0_sig, guass_4600_toy);
    RooAbsPdf *sigpdf1_sig_toy = new RooFFTConvPdf("sigpdf1_sig_toy", "shapepdf1_sig (X) gauss", *var_4612, *shapepdf1_sig, guass_4612_toy);
    RooAbsPdf *sigpdf2_sig_toy = new RooFFTConvPdf("sigpdf2_sig_toy", "shapepdf2_sig (X) gauss", *var_4620, *shapepdf2_sig, guass_4620_toy);
    RooAbsPdf *sigpdf3_sig_toy = new RooFFTConvPdf("sigpdf3_sig_toy", "shapepdf3_sig (X) gauss", *var_4640, *shapepdf3_sig, guass_4640_toy);
    RooAbsPdf *sigpdf4_sig_toy = new RooFFTConvPdf("sigpdf4_sig_toy", "shapepdf4_sig (X) gauss", *var_4660, *shapepdf4_sig, guass_4660_toy);
    RooAbsPdf *sigpdf5_sig_toy = new RooFFTConvPdf("sigpdf5_sig_toy", "shapepdf5_sig (X) gauss", *var_4680, *shapepdf5_sig, guass_4680_toy);
    RooAbsPdf *sigpdf6_sig_toy = new RooFFTConvPdf("sigpdf6_sig_toy", "shapepdf6_sig (X) gauss", *var_4700, *shapepdf6_sig, guass_4700_toy);


    // ref-- shape x guass
    RooAbsPdf *sigpdf0_toy = new RooFFTConvPdf("sigpdf0_toy", "shapepdf0 (X) gauss", *var_4600, *shapepdf0, guass_4600_toy);
    RooAbsPdf *sigpdf1_toy = new RooFFTConvPdf("sigpdf1_toy", "shapepdf1 (X) gauss", *var_4612, *shapepdf1, guass_4612_toy);
    RooAbsPdf *sigpdf2_toy = new RooFFTConvPdf("sigpdf2_toy", "shapepdf2 (X) gauss", *var_4620, *shapepdf2, guass_4620_toy);
    RooAbsPdf *sigpdf3_toy = new RooFFTConvPdf("sigpdf3_toy", "shapepdf3 (X) gauss", *var_4640, *shapepdf3, guass_4640_toy);
    RooAbsPdf *sigpdf4_toy = new RooFFTConvPdf("sigpdf4_toy", "shapepdf4 (X) gauss", *var_4660, *shapepdf4, guass_4660_toy);
    RooAbsPdf *sigpdf5_toy = new RooFFTConvPdf("sigpdf5_toy", "shapepdf5 (X) gauss", *var_4680, *shapepdf5, guass_4680_toy);
    RooAbsPdf *sigpdf6_toy = new RooFFTConvPdf("sigpdf6_toy", "shapepdf6 (X) gauss", *var_4700, *shapepdf6, guass_4700_toy);

    // ____________________ sig argus background
    RooRealVar m0_sig_toy("m0_sig", "m0_sig", 2.299765);   RooRealVar c0_sig_toy("c0_sig", "c0_sig",  -4.8444e+01 );    RooArgusBG argus0_sig_toy("argus0_sig", "argus0 sig", *var_4600, m0_sig_toy, c0_sig_toy);
    RooRealVar m1_sig_toy("m1_sig", "m1_sig", 2.30579);    RooRealVar c1_sig_toy("c1_sig", "c1_sig",  -2.7955e+01 );    RooArgusBG argus1_sig_toy("argus1_sig", "argus1 sig", *var_4612, m1_sig_toy, c1_sig_toy);
    RooRealVar m2_sig_toy("m2_sig", "m2_sig", 2.31387);    RooRealVar c2_sig_toy("c2_sig", "c2_sig",  -3.3582e+01 );    RooArgusBG argus2_sig_toy("argus2_sig", "argus2 sig", *var_4620, m2_sig_toy, c2_sig_toy);
    RooRealVar m3_sig_toy("m3_sig", "m3_sig", 2.320255);   RooRealVar c3_sig_toy("c3_sig", "c3_sig",   7.2811e+00 );    RooArgusBG argus3_sig_toy("argus3_sig", "argus3 sig", *var_4640, m3_sig_toy, c3_sig_toy);
    RooRealVar m4_sig_toy("m4_sig", "m4_sig", 2.33046);    RooRealVar c4_sig_toy("c4_sig", "c4_sig",   9.9953e+00 );    RooArgusBG argus4_sig_toy("argus4_sig", "argus4 sig", *var_4660, m4_sig_toy, c4_sig_toy);
    RooRealVar m5_sig_toy("m5_sig", "m5_sig", 2.34079);    RooRealVar c5_sig_toy("c5_sig", "c5_sig",   4.1393e+00 );    RooArgusBG argus5_sig_toy("argus5_sig", "argus5 sig", *var_4680, m5_sig_toy, c5_sig_toy);
    RooRealVar m6_sig_toy("m6_sig", "m6_sig", 2.34919);    RooRealVar c6_sig_toy("c6_sig", "c6_sig",  -1.4445e+01 );    RooArgusBG argus6_sig_toy("argus6_sig", "argus6 sig", *var_4700, m6_sig_toy, c6_sig_toy);

    // ____________________ ref argus background
    RooRealVar m0_toy("m0", "m0", 2.299765);   RooRealVar c0_toy("c0", "c0", -7.9392e+00);    RooArgusBG argus0_toy("argus0", "argus0", *var_4600, m0_toy, c0_toy);
    RooRealVar m1_toy("m1", "m1", 2.30579);    RooRealVar c1_toy("c1", "c1", -2.0546e+01);    RooArgusBG argus1_toy("argus1", "argus1", *var_4612, m1_toy, c1_toy);
    RooRealVar m2_toy("m2", "m2", 2.31387);    RooRealVar c2_toy("c2", "c2", -3.2705e+00);    RooArgusBG argus2_toy("argus2", "argus2", *var_4620, m2_toy, c2_toy);
    RooRealVar m3_toy("m3", "m3", 2.320255);   RooRealVar c3_toy("c3", "c3", -5.0874e+00);    RooArgusBG argus3_toy("argus3", "argus3", *var_4640, m3_toy, c3_toy);
    RooRealVar m4_toy("m4", "m4", 2.33046);    RooRealVar c4_toy("c4", "c4", -9.7769e+00);    RooArgusBG argus4_toy("argus4", "argus4", *var_4660, m4_toy, c4_toy);
    RooRealVar m5_toy("m5", "m5", 2.34079);    RooRealVar c5_toy("c5", "c5", -3.9885e+00);    RooArgusBG argus5_toy("argus5", "argus5", *var_4680, m5_toy, c5_toy);
    RooRealVar m6_toy("m6", "m6", 2.34919);    RooRealVar c6_toy("c6", "c6", -1.5633e+00);    RooArgusBG argus6_toy("argus6", "argus6", *var_4700, m6_toy, c6_toy);

    // ____________________ ref signal/bkg num
    RooRealVar nsig_mode0_toy("nsig_mode0_toy", "signal of mode0", 4.3216e+01);    RooRealVar nbkg0_toy("nbkg0_toy", "bkg number of mode0", 1.5954e+02);
    RooRealVar nsig_mode1_toy("nsig_mode1_toy", "signal of mode1", 3.4852e+00);    RooRealVar nbkg1_toy("nbkg1_toy", "bkg number of mode1", 3.1258e+01); 
    RooRealVar nsig_mode2_toy("nsig_mode2_toy", "signal of mode2", 3.5279e+01);    RooRealVar nbkg2_toy("nbkg2_toy", "bkg number of mode2", 1.4577e+02);
    RooRealVar nsig_mode3_toy("nsig_mode3_toy", "signal of mode3", 5.0929e+01);    RooRealVar nbkg3_toy("nbkg3_toy", "bkg number of mode3", 1.8282e+02);
    RooRealVar nsig_mode4_toy("nsig_mode4_toy", "signal of mode4", 4.4570e+01);    RooRealVar nbkg4_toy("nbkg4_toy", "bkg number of mode4", 1.5450e+02);
    RooRealVar nsig_mode5_toy("nsig_mode5_toy", "signal of mode5", 1.3127e+02);    RooRealVar nbkg5_toy("nbkg5_toy", "bkg number of mode5", 5.5308e+02);
    RooRealVar nsig_mode6_toy("nsig_mode6_toy", "signal of mode6", 4.4910e+01);    RooRealVar nbkg6_toy("nbkg6_toy", "bkg number of mode6", 1.8562e+02);
    
    // ____________________ sig signal/bkg num
    // double Br_sig_inter = 0.200845266; 
    // double Br_ref_inter = 0.503631863;
    RooRealVar Bratio_toy("Bratio_toy", "Br of sig/ref", 0.335808);	

    RooFormulaVar nsig_mode0_sig_toy("nsig_mode0_sig_toy", "signal of mode0 sig", "Bratio_toy * nsig_mode0_toy* 0.085359238  *0.0314/  0.449239622  /0.0322", RooArgSet(Bratio_toy, nsig_mode0_toy ));
    RooFormulaVar nsig_mode1_sig_toy("nsig_mode1_sig_toy", "signal of mode1 sig", "Bratio_toy * nsig_mode1_toy* 0.085359238  *0.0284/  0.449239622  /0.0299", RooArgSet(Bratio_toy, nsig_mode1_toy ));
    RooFormulaVar nsig_mode2_sig_toy("nsig_mode2_sig_toy", "signal of mode2 sig", "Bratio_toy * nsig_mode2_toy* 0.085359238  *0.0283/  0.449239622  /0.0299", RooArgSet(Bratio_toy, nsig_mode2_toy ));
    RooFormulaVar nsig_mode3_sig_toy("nsig_mode3_sig_toy", "signal of mode3 sig", "Bratio_toy * nsig_mode3_toy* 0.085359238  *0.0283/  0.449239622  /0.0297", RooArgSet(Bratio_toy, nsig_mode3_toy ));
    RooFormulaVar nsig_mode4_sig_toy("nsig_mode4_sig_toy", "signal of mode4 sig", "Bratio_toy * nsig_mode4_toy* 0.085359238  *0.0280/  0.449239622  /0.0290", RooArgSet(Bratio_toy, nsig_mode4_toy ));
    RooFormulaVar nsig_mode5_sig_toy("nsig_mode5_sig_toy", "signal of mode5 sig", "Bratio_toy * nsig_mode5_toy* 0.085359238  *0.0280/  0.449239622  /0.0289", RooArgSet(Bratio_toy, nsig_mode5_toy ));
    RooFormulaVar nsig_mode6_sig_toy("nsig_mode6_sig_toy", "signal of mode6 sig", "Bratio_toy * nsig_mode6_toy* 0.085359238  *0.0279/  0.449239622  /0.0289", RooArgSet(Bratio_toy, nsig_mode6_toy ));


   /*RooRealVar nsig_mode0_sig_toy("nsig_mode0_sig_toy", "signal of mode0 sig", 12.24512); */   RooRealVar nbkg0_sig_toy("nbkg0_sig", "bkg number of mode0 sig", 9.5562e+00); 
   /*RooRealVar nsig_mode1_sig_toy("nsig_mode1_sig_toy", "signal of mode1 sig", 0.211224); */   RooRealVar nbkg1_sig_toy("nbkg1_sig", "bkg number of mode1 sig", 0.0000e+00); 
   /*RooRealVar nsig_mode2_sig_toy("nsig_mode2_sig_toy", "signal of mode2 sig", 18.03438); */   RooRealVar nbkg2_sig_toy("nbkg2_sig", "bkg number of mode2 sig", 1.5904e+01); 
   /*RooRealVar nsig_mode3_sig_toy("nsig_mode3_sig_toy", "signal of mode3 sig", 14.28544); */   RooRealVar nbkg3_sig_toy("nbkg3_sig", "bkg number of mode3 sig", 1.1189e+01); 
   /*RooRealVar nsig_mode4_sig_toy("nsig_mode4_sig_toy", "signal of mode4 sig", 10.94881); */   RooRealVar nbkg4_sig_toy("nbkg4_sig", "bkg number of mode4 sig", 8.2031e+00); 
   /*RooRealVar nsig_mode5_sig_toy("nsig_mode5_sig_toy", "signal of mode5 sig", 50.71465); */   RooRealVar nbkg5_sig_toy("nbkg5_sig", "bkg number of mode5 sig", 4.2600e+01); 
   /*RooRealVar nsig_mode6_sig_toy("nsig_mode6_sig_toy", "signal of mode6 sig", 13.49601); */   RooRealVar nbkg6_sig_toy("nbkg6_sig", "bkg number of mode6 sig", 1.0730e+01); 



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
    RooAddPdf *model0_sig_toy = new RooAddPdf("model0_sig_toy", "model0_sig_toy", RooArgList(*sigpdf0_sig_toy, argus0_sig_toy), RooArgList(nsig_mode0_sig_toy, nbkg0_sig_toy));
    RooAddPdf *model1_sig_toy = new RooAddPdf("model1_sig_toy", "model1_sig_toy", RooArgList(*sigpdf1_sig_toy, argus1_sig_toy), RooArgList(nsig_mode1_sig_toy, nbkg1_sig_toy));
    RooAddPdf *model2_sig_toy = new RooAddPdf("model2_sig_toy", "model2_sig_toy", RooArgList(*sigpdf2_sig_toy, argus2_sig_toy), RooArgList(nsig_mode2_sig_toy, nbkg2_sig_toy));
    RooAddPdf *model3_sig_toy = new RooAddPdf("model3_sig_toy", "model3_sig_toy", RooArgList(*sigpdf3_sig_toy, argus3_sig_toy), RooArgList(nsig_mode3_sig_toy, nbkg3_sig_toy));
    RooAddPdf *model4_sig_toy = new RooAddPdf("model4_sig_toy", "model4_sig_toy", RooArgList(*sigpdf4_sig_toy, argus4_sig_toy), RooArgList(nsig_mode4_sig_toy, nbkg4_sig_toy));
    RooAddPdf *model5_sig_toy = new RooAddPdf("model5_sig_toy", "model5_sig_toy", RooArgList(*sigpdf5_sig_toy, argus5_sig_toy), RooArgList(nsig_mode5_sig_toy, nbkg5_sig_toy));
    RooAddPdf *model6_sig_toy = new RooAddPdf("model6_sig_toy", "model6_sig_toy", RooArgList(*sigpdf6_sig_toy, argus6_sig_toy), RooArgList(nsig_mode6_sig_toy, nbkg6_sig_toy));

    // ref
    RooAddPdf *model0_toy = new RooAddPdf("model0", "model0", RooArgList(*sigpdf0_toy, argus0_toy), RooArgList(nsig_mode0_toy, nbkg0_toy));
    RooAddPdf *model1_toy = new RooAddPdf("model1", "model1", RooArgList(*sigpdf1_toy, argus1_toy), RooArgList(nsig_mode1_toy, nbkg1_toy));
    RooAddPdf *model2_toy = new RooAddPdf("model2", "model2", RooArgList(*sigpdf2_toy, argus2_toy), RooArgList(nsig_mode2_toy, nbkg2_toy));
    RooAddPdf *model3_toy = new RooAddPdf("model3", "model3", RooArgList(*sigpdf3_toy, argus3_toy), RooArgList(nsig_mode3_toy, nbkg3_toy));
    RooAddPdf *model4_toy = new RooAddPdf("model4", "model4", RooArgList(*sigpdf4_toy, argus4_toy), RooArgList(nsig_mode4_toy, nbkg4_toy));
    RooAddPdf *model5_toy = new RooAddPdf("model5", "model5", RooArgList(*sigpdf5_toy, argus5_toy), RooArgList(nsig_mode5_toy, nbkg5_toy));
    RooAddPdf *model6_toy = new RooAddPdf("model6", "model6", RooArgList(*sigpdf6_toy, argus6_toy), RooArgList(nsig_mode6_toy, nbkg6_toy));


    // generate toy mc 
    double times = 1.;
    double seed=121;
    RooRandom::randomGenerator()->SetSeed(seed);
    
    RooDataSet *data0_sig = model0_sig_toy->generate(*var_4600, times * 12.24512); //  new RooDataSet("data0_sig"," M_BC_r3c", tr_fit0_sig, RooArgSet(*var_4600));
    RooDataSet *data1_sig = model1_sig_toy->generate(*var_4612, times * 0.211224); //  new RooDataSet("data1_sig", "M_BC_r3c", tr_fit1_sig, RooArgSet(*var_4612));
    RooDataSet *data2_sig = model2_sig_toy->generate(*var_4620, times * 18.03438); //  new RooDataSet("data2_sig", "M_BC_r3c", tr_fit2_sig, RooArgSet(*var_4620));
    RooDataSet *data3_sig = model3_sig_toy->generate(*var_4640, times * 14.28544); //  new RooDataSet("data3_sig", "M_BC_r3c", tr_fit3_sig, RooArgSet(*var_4640));
    RooDataSet *data4_sig = model4_sig_toy->generate(*var_4660, times * 10.94881); //  new RooDataSet("data4_sig", "M_BC_r3c", tr_fit4_sig, RooArgSet(*var_4660));
    RooDataSet *data5_sig = model5_sig_toy->generate(*var_4680, times * 50.71465); //  new RooDataSet("data5_sig", "M_BC_r3c", tr_fit5_sig, RooArgSet(*var_4680));
    RooDataSet *data6_sig = model6_sig_toy->generate(*var_4700, times * 13.49601); //  new RooDataSet("data6_sig", "M_BC_r3c", tr_fit6_sig, RooArgSet(*var_4700));

    RooDataSet *data0 = model0_toy->generate(*var_4600, times * 202.7569); // RooDataSet("data0", "M_BC_r3c", tr_fit0, RooArgSet(*var_4600));
    RooDataSet *data1 = model1_toy->generate(*var_4612, times * 34.74283); // RooDataSet("data1", "M_BC_r3c", tr_fit1, RooArgSet(*var_4612));
    RooDataSet *data2 = model2_toy->generate(*var_4620, times * 181.0453); // RooDataSet("data2", "M_BC_r3c", tr_fit2, RooArgSet(*var_4620));
    RooDataSet *data3 = model3_toy->generate(*var_4640, times * 233.7544); // RooDataSet("data3", "M_BC_r3c", tr_fit3, RooArgSet(*var_4640));
    RooDataSet *data4 = model4_toy->generate(*var_4660, times * 199.0725); // RooDataSet("data4", "M_BC_r3c", tr_fit4, RooArgSet(*var_4660));
    RooDataSet *data5 = model5_toy->generate(*var_4680, times * 684.351 ); // RooDataSet("data5", "M_BC_r3c", tr_fit5, RooArgSet(*var_4680));
    RooDataSet *data6 = model6_toy->generate(*var_4700, times * 230.5333); // RooDataSet("data6", "M_BC_r3c", tr_fit6, RooArgSet(*var_4700));


    // ----------------------------- model for fit--------------------------------------------------------------------------------------------------------------------
    // ----------------------------- model for fit--------------------------------------------------------------------------------------------------------------------
    // ----------------------------- model for fit--------------------------------------------------------------------------------------------------------------------
    // ----------------------------- model for fit--------------------------------------------------------------------------------------------------------------------
    // ----------------------------- model for fit--------------------------------------------------------------------------------------------------------------------


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
    RooRealVar nsig_mode0("nsig_mode0", "signal of mode0", 0.05 * data0->sumEntries(), 0, 1.2 * data0->sumEntries());    RooRealVar nbkg0("nbkg0", "bkg number of mode0", 0.05 * data0->sumEntries(), 0, 1.2 * data0->sumEntries());
    RooRealVar nsig_mode1("nsig_mode1", "signal of mode1", 0.05 * data1->sumEntries(), 0, 1.2 * data1->sumEntries());    RooRealVar nbkg1("nbkg1", "bkg number of mode1", 0.05 * data1->sumEntries(), 0, 1.2 * data1->sumEntries());	
    RooRealVar nsig_mode2("nsig_mode2", "signal of mode2", 0.05 * data2->sumEntries(), 0, 1.2 * data2->sumEntries());    RooRealVar nbkg2("nbkg2", "bkg number of mode2", 0.05 * data2->sumEntries(), 0, 1.2 * data2->sumEntries());
    RooRealVar nsig_mode3("nsig_mode3", "signal of mode3", 0.05 * data3->sumEntries(), 0, 1.2 * data3->sumEntries());    RooRealVar nbkg3("nbkg3", "bkg number of mode3", 0.05 * data3->sumEntries(), 0, 1.2 * data3->sumEntries());
    RooRealVar nsig_mode4("nsig_mode4", "signal of mode4", 0.05 * data4->sumEntries(), 0, 1.2 * data4->sumEntries());    RooRealVar nbkg4("nbkg4", "bkg number of mode4", 0.05 * data4->sumEntries(), 0, 1.2 * data4->sumEntries());
    RooRealVar nsig_mode5("nsig_mode5", "signal of mode5", 0.05 * data5->sumEntries(), 0, 1.2 * data5->sumEntries());    RooRealVar nbkg5("nbkg5", "bkg number of mode5", 0.05 * data5->sumEntries(), 0, 1.2 * data5->sumEntries());
    RooRealVar nsig_mode6("nsig_mode6", "signal of mode6", 0.05 * data6->sumEntries(), 0, 1.2 * data6->sumEntries());    RooRealVar nbkg6("nbkg6", "bkg number of mode6", 0.05 * data6->sumEntries(), 0, 1.2 * data6->sumEntries());
    
    // ____________________ sig signal/bkg num
    double Br_sig_inter = 0.085359238;
    double Br_ref_inter = 0.449239622;
    RooFormulaVar nsig_mode0_sig("nsig_mode0_sig", "signal of mode0 sig", "Bratio * nsig_mode0* 0.085359238  *0.0314/  0.449239622  /0.0322", RooArgSet(Bratio, nsig_mode0 ));	RooRealVar nbkg0_sig("nbkg0_sig", "bkg number of mode0 sig", 0.05 * data0_sig->sumEntries(), 0, 1.2 * data0_sig->sumEntries());
    RooFormulaVar nsig_mode1_sig("nsig_mode1_sig", "signal of mode1 sig", "Bratio * nsig_mode1* 0.085359238  *0.0284/  0.449239622  /0.0299", RooArgSet(Bratio, nsig_mode1 ));	RooRealVar nbkg1_sig("nbkg1_sig", "bkg number of mode1 sig", 0.05 * data1_sig->sumEntries(), 0, 1.2 * data1_sig->sumEntries());
    RooFormulaVar nsig_mode2_sig("nsig_mode2_sig", "signal of mode2 sig", "Bratio * nsig_mode2* 0.085359238  *0.0283/  0.449239622  /0.0299", RooArgSet(Bratio, nsig_mode2 ));	RooRealVar nbkg2_sig("nbkg2_sig", "bkg number of mode2 sig", 0.05 * data2_sig->sumEntries(), 0, 1.2 * data2_sig->sumEntries());
    RooFormulaVar nsig_mode3_sig("nsig_mode3_sig", "signal of mode3 sig", "Bratio * nsig_mode3* 0.085359238  *0.0283/  0.449239622  /0.0297", RooArgSet(Bratio, nsig_mode3 ));	RooRealVar nbkg3_sig("nbkg3_sig", "bkg number of mode3 sig", 0.05 * data3_sig->sumEntries(), 0, 1.2 * data3_sig->sumEntries());
    RooFormulaVar nsig_mode4_sig("nsig_mode4_sig", "signal of mode4 sig", "Bratio * nsig_mode4* 0.085359238  *0.0280/  0.449239622  /0.0290", RooArgSet(Bratio, nsig_mode4 ));	RooRealVar nbkg4_sig("nbkg4_sig", "bkg number of mode4 sig", 0.05 * data4_sig->sumEntries(), 0, 1.2 * data4_sig->sumEntries());
    RooFormulaVar nsig_mode5_sig("nsig_mode5_sig", "signal of mode5 sig", "Bratio * nsig_mode5* 0.085359238  *0.0280/  0.449239622  /0.0289", RooArgSet(Bratio, nsig_mode5 ));	RooRealVar nbkg5_sig("nbkg5_sig", "bkg number of mode5 sig", 0.05 * data5_sig->sumEntries(), 0, 1.2 * data5_sig->sumEntries());
    RooFormulaVar nsig_mode6_sig("nsig_mode6_sig", "signal of mode6 sig", "Bratio * nsig_mode6* 0.085359238  *0.0279/  0.449239622  /0.0289", RooArgSet(Bratio, nsig_mode6 ));	RooRealVar nbkg6_sig("nbkg6_sig", "bkg number of mode6 sig", 0.05 * data6_sig->sumEntries(), 0, 1.2 * data6_sig->sumEntries());


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


    
    //-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------









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

    // ================================v========   D R A W  ====================================================================
    // ********************************************************************************
    if(1)
    {
        TCanvas *can = new TCanvas("can", "simu fit", 400*2 * 1.8, 300*7 * 1.8); //setPad();
        can->Divide(2, 7);
        can->SetFillColor(0);

        RooRealVar *myvar[] = {var_4600, var_4612, var_4620, var_4640, var_4660, var_4680, var_4700};
        double endpoint[]={2.299765, 2.30579, 2.31387, 2.320255, 2.33046,  2.34079, 2.34919 };
        int integral_lum[]={567, 104, 522, 552, 530,  1669, 536 };


        RooDataSet *data_sig[] = {data0_sig, data1_sig, data2_sig, data3_sig, data4_sig, data5_sig, data6_sig};
        RooAbsPdf *mode_sig[] = {model0_sig, model1_sig, model2_sig, model3_sig, model4_sig, model5_sig, model6_sig}; 


        RooDataSet *data_ref[] = {data0, data1, data2, data3, data4, data5, data6};
        RooAbsPdf *mode_ref[] = {model0, model1, model2, model3, model4, model5, model6}; 

        for(int i = 0; i<7; i++)
        {
            // sig 4600
            // TCanvas *can1 = new TCanvas("can", "simu fit", 400 * 1.8, 300 * 1.8); //setPad();
            // can1->SetFillColor(0);

            RooPlot *frame_mode0_sig = myvar[i]->frame(xmin, endpoint[i], xbins);

            frame_mode0_sig->SetXTitle("M_{BC} (GeV/c^{2})");
            frame_mode0_sig->SetTitle(TString::Format("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta',     #sqrt{s}=%.3f GeV,     %d pb^{-1}", endpoint[i]*2, integral_lum[i]));
            frame_mode0_sig->SetYTitle(TString::Format("Events/(%.2fMeV/c^{2})", (endpoint[i] - mbcmin) / xbins * 1000));
            frame_mode0_sig->GetYaxis()->SetTitleOffset(1.2);
            frame_mode0_sig->GetYaxis()->SetTitleSize(0.04);
            frame_mode0_sig->GetXaxis()->SetTitleSize(0.04);
            data_sig[i]->plotOn(frame_mode0_sig, LineWidth(2));
            mode_sig[i]->plotOn(frame_mode0_sig, LineColor(kRed), LineWidth(3));
            mode_sig[i]->plotOn(frame_mode0_sig, Components(TString::Format("sigpdf%1d_sig", i)), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
            mode_sig[i]->plotOn(frame_mode0_sig, Components(TString::Format("argus%1d_sig", i)), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
            can->cd(i*2+1);  
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
            // can1->SaveAs(("toymcetaprimesig_" + to_string(int(endpoint[i]*2000)) + ".png" ).c_str());
            // can1->SaveAs(("etaprimesig_" + to_string(int(endpoint[i]*2000)) + ".pdf" ).c_str());
            
            
            // ref 4600
            // TCanvas *can2 = new TCanvas("can", "simu fit", 400 * 1.8, 300 * 1.8); //setPad();
            // can2->SetFillColor(0);

            RooPlot *frame_mode0 = myvar[i]->frame( xmin, endpoint[i], xbins);
            frame_mode0->SetXTitle("M_{BC} (GeV/c^{2})");
            frame_mode0->SetYTitle(TString::Format("Events/(%.2fMeV/c^{2})", (endpoint[i] - mbcmin) / xbins * 1000));
            frame_mode0->SetTitle(TString::Format("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #omega,     #sqrt{s}=%.3f GeV,     %d pb^{-1}", endpoint[i]*2, integral_lum[i] ));
            frame_mode0->GetYaxis()->SetTitleOffset(1.2);
            frame_mode0->GetYaxis()->SetTitleSize(0.04);
            frame_mode0->GetXaxis()->SetTitleSize(0.04);
            data_ref[i]->plotOn(frame_mode0, LineWidth(2));
            mode_ref[i]->plotOn(frame_mode0, LineColor(kRed), LineWidth(3));
            mode_ref[i]->plotOn(frame_mode0, Components(TString::Format("sigpdf%1d", i)), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
            mode_ref[i]->plotOn(frame_mode0, Components(TString::Format("argus%1d", i)), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
            can->cd(i*2+2);  
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
            // can2->SaveAs(("toymcomegaref_" + to_string(int(endpoint[i]*2000)) + ".png" ).c_str());
            // can2->SaveAs(("omegaref_" + to_string(int(endpoint[i]*2000)) + ".pdf" ).c_str());
                
        }

        // can->SaveAs("svg_fit_comb.pdf");
        can->SaveAs("io.png");
    }

    // ================================================================================
    // ********************************************************************************
    
    if(0)
    {
        cout << "_________________________________________________________________" << endl;
        TCanvas *can3 = new TCanvas("can3", "simu fit3", 700, 600); 
        can3->SetFillColor(0);
        can3->SetMargin(0.15, 0.03, 0.15, 0.1);
        can3->cd();
        
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
        RooAddPdf *pdfSig = new RooAddPdf("pdfSig", "pdfSig", RooArgList(*model0_sig,   *model1_sig,  *model2_sig, *model3_sig, *model4_sig, *model5_sig, *model6_sig ));
            
        RooPlot *frame_mode_sig = M_BC_r3c->frame( mbcmin, mbcmax, 40);
        frame_mode_sig->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode_sig->SetYTitle(ytitle);
        frame_mode_sig->GetYaxis()->SetTitleOffset(1.2);
        frame_mode_sig->GetYaxis()->SetTitleSize(0.04);
        frame_mode_sig->GetXaxis()->SetTitleSize(0.04);
        combData->plotOn(frame_mode_sig,  LineWidth(2));
        pdfSig->plotOn(frame_mode_sig, LineColor(kRed),  LineWidth(3));
        pdfSig->plotOn(frame_mode_sig,  Components("argus*_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        pdfSig->plotOn(frame_mode_sig, Components("sigpdf*_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
        
        frame_mode_sig->SetTitle(" ");
        frame_mode_sig->SetLabelSize(0.045, "xy");
        frame_mode_sig->SetTitleSize(0.06, "xy");
        frame_mode_sig->GetXaxis()->SetNdivisions(210);
        frame_mode_sig->Draw();

        TPaveText *pt = new TPaveText(0.96-0.25, 1-0.16-0.1, 0.96, 1-0.16, "blNDC");      
        pt->SetBorderSize(0);
        pt->SetFillColor(0);
        // pt->SetLineColor(5);
        // pt->SetTextColor(5);
        pt->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta'");
        // pt->SetTextAlign(12);
        // pt->SetTextSize(12);
        pt->Draw();

        can3->SaveAs("toymcsvg_fit_comb_sig.png");
        // can3->SaveAs("svg_fit_comb_sig.pdf");



        /////////////////////  draw ref  ////////////////////////////////////////// 
        TCanvas *can4 = new TCanvas("can4", "simu fit3", 700, 600); 
        can4->SetFillColor(0);
        can4->SetMargin(0.15, 0.03, 0.15, 0.1);
        can4->cd();
        
        RooDataSet *combData_ref = new RooDataSet("combData_ref", "combined data",  RooArgSet(*M_BC_r3c));
        combData_ref->append(*data0);
        combData_ref->append(*data1);
        combData_ref->append(*data2);
        combData_ref->append(*data3);
        combData_ref->append(*data4);
        combData_ref->append(*data5);
        combData_ref->append(*data6);

        // ref
        RooAddPdf *pdfRef = new RooAddPdf("pdfRef", "pdfRef", RooArgList(*model0, *model1, *model2, *model3, *model4, *model5, *model6 ));
            
        RooPlot *frame_mode_ref = M_BC_r3c->frame( mbcmin, mbcmax, 40);
        frame_mode_ref->SetXTitle("M_{BC} (GeV/c^{2})");
        frame_mode_ref->SetYTitle(ytitle);
        frame_mode_ref->SetTitle(" ");
        frame_mode_ref->GetYaxis()->SetTitleOffset(1.2);
        frame_mode_ref->GetYaxis()->SetTitleSize(0.04);
        frame_mode_ref->GetXaxis()->SetTitleSize(0.04);
        combData_ref->plotOn(frame_mode_ref,  LineWidth(2));
        pdfRef->plotOn(frame_mode_ref, LineColor(kRed),  LineWidth(3));
        pdfRef->plotOn(frame_mode_ref,  Components("argus*"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        pdfRef->plotOn(frame_mode_ref, Components("sigpdf*"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));

        frame_mode_ref->SetLabelSize(0.045, "xy");
        frame_mode_ref->SetTitleSize(0.06, "xy");
        frame_mode_ref->GetXaxis()->SetNdivisions(210);
        frame_mode_ref->SetTitle(" ");
        frame_mode_ref->Draw();

        TPaveText *pt2 = new TPaveText(0.96-0.25, 1-0.16-0.1, 0.96, 1-0.16, "blNDC");      
        pt2->SetBorderSize(0);
        pt2->SetFillColor(0);
        // pt2->SetLineColor(5);
        // pt2->SetTextColor(5);
        pt2->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #omega");
        // pt2->SetTextAlign(12);
        // pt->SetTextSize(12);
        pt2->Draw();

        can4->SaveAs("toymcsvg_fit_comb_ref.png");
        // can4->SaveAs("svg_fit_comb_ref.pdf");
    }



    
    //
    //
    // cout << endl;
    cout << "Br: " << Bratio.getVal() << " +/- " << Bratio.getError() << endl;
    // cout << "result->minNll(): " <<result->minNll() << endl;

    cout << __LINE__ << ", 4600 ref nbkg0: "<< nbkg0.getVal() << " +/- " << nbkg0.getError() << endl;
    cout << __LINE__ << ", 4612 ref nbkg1: "<< nbkg1.getVal() << " +/- " << nbkg1.getError() << endl;
    cout << __LINE__ << ", 4620 ref nbkg2: "<< nbkg2.getVal() << " +/- " << nbkg2.getError() << endl;
    cout << __LINE__ << ", 4640 ref nbkg3: "<< nbkg3.getVal() << " +/- " << nbkg3.getError() << endl;
    cout << __LINE__ << ", 4660 ref nbkg4: "<< nbkg4.getVal() << " +/- " << nbkg4.getError() << endl;
    cout << __LINE__ << ", 4680 ref nbkg5: "<< nbkg5.getVal() << " +/- " << nbkg5.getError() << endl;
    cout << __LINE__ << ", 4700 ref nbkg6: "<< nbkg6.getVal() << " +/- " << nbkg6.getError() << endl;

    cout << __LINE__ << ", 4600 sig nbkg0: "<< nbkg0_sig.getVal() << " +/- " << nbkg0_sig.getError() <<  endl;
    cout << __LINE__ << ", 4612 sig nbkg1: "<< nbkg1_sig.getVal() << " +/- " << nbkg1_sig.getError() <<  endl;
    cout << __LINE__ << ", 4620 sig nbkg2: "<< nbkg2_sig.getVal() << " +/- " << nbkg2_sig.getError() <<  endl;
    cout << __LINE__ << ", 4640 sig nbkg3: "<< nbkg3_sig.getVal() << " +/- " << nbkg3_sig.getError() <<  endl;
    cout << __LINE__ << ", 4660 sig nbkg4: "<< nbkg4_sig.getVal() << " +/- " << nbkg4_sig.getError() <<  endl;
    cout << __LINE__ << ", 4680 sig nbkg5: "<< nbkg5_sig.getVal() << " +/- " << nbkg5_sig.getError() <<  endl;
    cout << __LINE__ << ", 4700 sig nbkg6: "<< nbkg6_sig.getVal() << " +/- " << nbkg6_sig.getError() <<  endl;

    cout << __LINE__ << ", 4600 ref nsig_mode0: "<< nsig_mode0.getVal() <<  " +/- " << nsig_mode0.getError() << endl;
    cout << __LINE__ << ", 4612 ref nsig_mode1: "<< nsig_mode1.getVal() <<  " +/- " << nsig_mode1.getError() << endl;
    cout << __LINE__ << ", 4620 ref nsig_mode2: "<< nsig_mode2.getVal() <<  " +/- " << nsig_mode2.getError() << endl;
    cout << __LINE__ << ", 4640 ref nsig_mode3: "<< nsig_mode3.getVal() <<  " +/- " << nsig_mode3.getError() << endl;
    cout << __LINE__ << ", 4660 ref nsig_mode4: "<< nsig_mode4.getVal() <<  " +/- " << nsig_mode4.getError() << endl;
    cout << __LINE__ << ", 4680 ref nsig_mode5: "<< nsig_mode5.getVal() <<  " +/- " << nsig_mode5.getError() << endl;
    cout << __LINE__ << ", 4670 ref nsig_mode6: "<< nsig_mode6.getVal() <<  " +/- " << nsig_mode6.getError() << endl;

    cout << __LINE__ << ", 4600 sig nsig_mode0_sig: "<< nsig_mode0_sig.getVal() <<  " +/- " << nsig_mode0_sig.getPropagatedError(*result, RooArgSet(Bratio, nsig_mode0 )) << endl;
    cout << __LINE__ << ", 4612 sig nsig_mode1_sig: "<< nsig_mode1_sig.getVal() <<  " +/- " << nsig_mode1_sig.getPropagatedError(*result, RooArgSet(Bratio, nsig_mode1 )) << endl;
    cout << __LINE__ << ", 4620 sig nsig_mode2_sig: "<< nsig_mode2_sig.getVal() <<  " +/- " << nsig_mode2_sig.getPropagatedError(*result, RooArgSet(Bratio, nsig_mode2 )) << endl;
    cout << __LINE__ << ", 4640 sig nsig_mode3_sig: "<< nsig_mode3_sig.getVal() <<  " +/- " << nsig_mode3_sig.getPropagatedError(*result, RooArgSet(Bratio, nsig_mode3 )) << endl;
    cout << __LINE__ << ", 4660 sig nsig_mode4_sig: "<< nsig_mode4_sig.getVal() <<  " +/- " << nsig_mode4_sig.getPropagatedError(*result, RooArgSet(Bratio, nsig_mode4 )) << endl;
    cout << __LINE__ << ", 4680 sig nsig_mode5_sig: "<< nsig_mode5_sig.getVal() <<  " +/- " << nsig_mode5_sig.getPropagatedError(*result, RooArgSet(Bratio, nsig_mode5 )) << endl;
    cout << __LINE__ << ", 4700 sig nsig_mode6_sig: "<< nsig_mode6_sig.getVal() <<  " +/- " << nsig_mode6_sig.getPropagatedError(*result, RooArgSet(Bratio, nsig_mode6 )) << endl;

    cout << __LINE__ << "mean_all: "<< nsig_mode6_sig.getVal() <<  " +/- " << nsig_mode6_sig.getPropagatedError(*result, RooArgSet(Bratio, nsig_mode6 )) << endl;
    cout << __LINE__ << ": "<< nsig_mode6_sig.getVal() <<  " +/- " << nsig_mode6_sig.getPropagatedError(*result, RooArgSet(Bratio, nsig_mode6 )) << endl;
    
    cout << "mean: " << mean_all.getVal() << " " <<  mean_all.getError() << endl;
    cout << "sigma: " << sigma_all.getVal() << " " <<  sigma_all.getError() << endl;


    cout << "______________________ " << endl;
    cout << "signal mode, sig = " << nsig_mode0_sig.getVal()+nsig_mode1_sig.getVal()+nsig_mode2_sig.getVal()+nsig_mode3_sig.getVal()+nsig_mode4_sig.getVal()+nsig_mode5_sig.getVal()+nsig_mode6_sig.getVal() << endl;
    cout << "signal mode, bkg = " << nbkg0_sig.getVal()+nbkg1_sig.getVal()+nbkg2_sig.getVal()+nbkg3_sig.getVal()+nbkg4_sig.getVal()+nbkg5_sig.getVal()+nbkg6_sig.getVal() << endl;
    

    // //
    // // //
    Double_t DeltaLL = 2 * fabs(result->minNll() - FCN_bkg);
    Double_t prob = TMath::Prob(DeltaLL, 1);
    Double_t nSigma = sqrt(2) * TMath::ErfcInverse(prob);
    cout << "result->minNll() " << result->minNll() << " " << "|FCN_single - FCN_bkg| = " << DeltaLL << endl;
    cout << " Sigma: " << nSigma << endl;
    return 0;
}
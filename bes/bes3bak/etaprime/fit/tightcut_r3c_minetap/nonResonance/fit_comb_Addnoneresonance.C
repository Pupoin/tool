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
Double_t xbins = 40;
Double_t mbcmin = 2.25;
Double_t mbcmax = 2.34919;
TCut cut_np = "(np !=0 && npbar != 0)";
// TCut cut = "(refm>=0.115&&refm<=0.15) && (refmORsigm1m>=0.115&&refmORsigm1m<=0.15) && (sigmam>=1.174 && sigmam<=1.2) && (dipim<0.48 || dipim>0.52)";
TCut cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919))";
// TCut cut_deltaE_ref = "((deltaE_min>-0.033) && (deltaE_min<0.022))";
// TCut cut_deltaE_sig = "((deltaE_min>-0.021) && (deltaE_min<0.015))";
// TCut cut_chi2 = "(chi2_min_r3c< 29)";
TCut cut_ref = (cut_mbc && "(chi2_min_r3c< 30)" && cut_np && "(etaprimemr3c>0.76&&etaprimemr3c<0.8)");
TCut cut_sig = (cut_mbc && "(chi2_min_r3c< 30)" && cut_np && "(etaprimemr3c>0.946&&etaprimemr3c<0.968)");

// sideband
TCut cut_refsb = (cut_mbc && "(chi2_min_r3c< 30)" && cut_np && "((etaprimemr3c>0.68&&etaprimemr3c<0.72)||(etaprimemr3c>0.84&&etaprimemr3c<0.89))");
// TCut cut_sig = (cut_mbc && "(chi2_min_r3c< 30)" && cut_np && "((etaprimemr3c>0.91&&etaprimemr3c<0.93)||(etaprimemr3c>1&&etaprimemr3c<1.02))");
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
RooRealVar Bratio("Bratio", "Br of sig/ref", 0.37574, 0., 1);	
// RooRealVar Bratio("Bratio", "Br of sig/ref", 0);	

int fit_comb_Addnoneresonance()
{

    TH1::SetDefaultSumw2(1);
    TString a("Events / ");
    char b[30];
    sprintf(b, "(%1.1f", (xmax - xmin) / xbins * 1000);
    TString c("MeV/#font[12]{c^{2}})");
    TString ytitle = a + b + c;

    //
    // sig decay channel
    TChain *tr_data0_sig = new TChain("tree");    tr_data0_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/tightcut_r3c_minetap/4600data_selB2.root");
    TChain *tr_data1_sig = new TChain("tree");    tr_data1_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/tightcut_r3c_minetap/4612data_selB2.root");
    TChain *tr_data2_sig = new TChain("tree");    tr_data2_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/tightcut_r3c_minetap/4620data_selB2.root");
    TChain *tr_data3_sig = new TChain("tree");	  tr_data3_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/tightcut_r3c_minetap/4640data_selB2.root");
    TChain *tr_data4_sig = new TChain("tree");	  tr_data4_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/tightcut_r3c_minetap/4660data_selB2.root");
    TChain *tr_data5_sig = new TChain("tree");	  tr_data5_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/tightcut_r3c_minetap/4680data_selB2.root");
    TChain *tr_data6_sig = new TChain("tree");    tr_data6_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/tightcut_r3c_minetap/4700data_selB2.root");

    // ref decay channel
    TChain *tr_data0 = new TChain("tree");    tr_data0->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/tightcut_r3c_minomega/4600data_selB2.root");
    TChain *tr_data1 = new TChain("tree");    tr_data1->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/tightcut_r3c_minomega/4612data_selB2.root");
    TChain *tr_data2 = new TChain("tree");    tr_data2->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/tightcut_r3c_minomega/4620data_selB2.root");
    TChain *tr_data3 = new TChain("tree");	  tr_data3->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/tightcut_r3c_minomega/4640data_selB2.root");
    TChain *tr_data4 = new TChain("tree");	  tr_data4->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/tightcut_r3c_minomega/4660data_selB2.root");
    TChain *tr_data5 = new TChain("tree");	  tr_data5->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/tightcut_r3c_minomega/4680data_selB2.root");
    TChain *tr_data6 = new TChain("tree");    tr_data6->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/tightcut_r3c_minomega/4700data_selB2.root");

    // ____________________ 

    // sig decay channel
    TTree *tr_fit0_sig = tr_data0_sig->CopyTree(cut_sig);    RooDataSet *data0_sig = new RooDataSet("data0_sig"," M_BC_r3c", tr_fit0_sig, RooArgSet(*var_4600));
    TTree *tr_fit1_sig = tr_data1_sig->CopyTree(cut_sig);    RooDataSet *data1_sig = new RooDataSet("data1_sig", "M_BC_r3c", tr_fit1_sig, RooArgSet(*var_4612));
    TTree *tr_fit2_sig = tr_data2_sig->CopyTree(cut_sig);    RooDataSet *data2_sig = new RooDataSet("data2_sig", "M_BC_r3c", tr_fit2_sig, RooArgSet(*var_4620));
    TTree *tr_fit3_sig = tr_data3_sig->CopyTree(cut_sig);    RooDataSet *data3_sig = new RooDataSet("data3_sig", "M_BC_r3c", tr_fit3_sig, RooArgSet(*var_4640));
    TTree *tr_fit4_sig = tr_data4_sig->CopyTree(cut_sig);    RooDataSet *data4_sig = new RooDataSet("data4_sig", "M_BC_r3c", tr_fit4_sig, RooArgSet(*var_4660));
    TTree *tr_fit5_sig = tr_data5_sig->CopyTree(cut_sig);    RooDataSet *data5_sig = new RooDataSet("data5_sig", "M_BC_r3c", tr_fit5_sig, RooArgSet(*var_4680));
    TTree *tr_fit6_sig = tr_data6_sig->CopyTree(cut_sig);    RooDataSet *data6_sig = new RooDataSet("data6_sig", "M_BC_r3c", tr_fit6_sig, RooArgSet(*var_4700));
    // ref decay channel
    TTree *tr_fit0 = tr_data0->CopyTree(cut_ref);    RooDataSet *data0 = new RooDataSet("data0", "M_BC_r3c", tr_fit0, RooArgSet(*var_4600));
    TTree *tr_fit1 = tr_data1->CopyTree(cut_ref);    RooDataSet *data1 = new RooDataSet("data1", "M_BC_r3c", tr_fit1, RooArgSet(*var_4612));
    TTree *tr_fit2 = tr_data2->CopyTree(cut_ref);    RooDataSet *data2 = new RooDataSet("data2", "M_BC_r3c", tr_fit2, RooArgSet(*var_4620));
    TTree *tr_fit3 = tr_data3->CopyTree(cut_ref);    RooDataSet *data3 = new RooDataSet("data3", "M_BC_r3c", tr_fit3, RooArgSet(*var_4640));
    TTree *tr_fit4 = tr_data4->CopyTree(cut_ref);    RooDataSet *data4 = new RooDataSet("data4", "M_BC_r3c", tr_fit4, RooArgSet(*var_4660));
    TTree *tr_fit5 = tr_data5->CopyTree(cut_ref);    RooDataSet *data5 = new RooDataSet("data5", "M_BC_r3c", tr_fit5, RooArgSet(*var_4680));
    TTree *tr_fit6 = tr_data6->CopyTree(cut_ref);    RooDataSet *data6 = new RooDataSet("data6", "M_BC_r3c", tr_fit6, RooArgSet(*var_4700));
    //ref decay channel sideband
    TTree *tr_fit0sb = tr_data0->CopyTree(cut_refsb);    RooDataSet *data0sb = new RooDataSet("data0sb"," M_BC_r3c", tr_fit0sb, RooArgSet(*var_4600));
    TTree *tr_fit1sb = tr_data1->CopyTree(cut_refsb);    RooDataSet *data1sb = new RooDataSet("data1sb", "M_BC_r3c", tr_fit1sb, RooArgSet(*var_4612));
    TTree *tr_fit2sb = tr_data2->CopyTree(cut_refsb);    RooDataSet *data2sb = new RooDataSet("data2sb", "M_BC_r3c", tr_fit2sb, RooArgSet(*var_4620));
    TTree *tr_fit3sb = tr_data3->CopyTree(cut_refsb);    RooDataSet *data3sb = new RooDataSet("data3sb", "M_BC_r3c", tr_fit3sb, RooArgSet(*var_4640));
    TTree *tr_fit4sb = tr_data4->CopyTree(cut_refsb);    RooDataSet *data4sb = new RooDataSet("data4sb", "M_BC_r3c", tr_fit4sb, RooArgSet(*var_4660));
    TTree *tr_fit5sb = tr_data5->CopyTree(cut_refsb);    RooDataSet *data5sb = new RooDataSet("data5sb", "M_BC_r3c", tr_fit5sb, RooArgSet(*var_4680));
    TTree *tr_fit6sb = tr_data6->CopyTree(cut_refsb);    RooDataSet *data6sb = new RooDataSet("data6sb", "M_BC_r3c", tr_fit6sb, RooArgSet(*var_4700));

    RooRealVar mean_all("mean_all", "mean_all", -1.0572e-04, -0.001, 0.001);
    RooRealVar sigma_all("sigma_all", "sigma_all",  3.5676e-06, 0, 0.001);
    
    // RooRealVar mean_all("mean_all", "mean_all",  -9.3493e-05 -  1.91e-04);
    // RooRealVar sigma_all("sigma_all", "sigma_all",  5.0716e-04 -  3.75e-04);

    RooGaussModel guass_4600("guass_4600", "guass_4600", *var_4600, mean_all, sigma_all);
    RooGaussModel guass_4612("guass_4612", "guass_4612", *var_4612, mean_all, sigma_all);
    RooGaussModel guass_4620("guass_4620", "guass_4620", *var_4620, mean_all, sigma_all);
    RooGaussModel guass_4640("guass_4640", "guass_4640", *var_4640, mean_all, sigma_all);
    RooGaussModel guass_4660("guass_4660", "guass_4660", *var_4660, mean_all, sigma_all);
    RooGaussModel guass_4680("guass_4680", "guass_4680", *var_4680, mean_all, sigma_all);
    RooGaussModel guass_4700("guass_4700", "guass_4700", *var_4700, mean_all, sigma_all);


    // sid
    // sig decay channel -- shape
    TFile *pdf0_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/4600_sig_shapepdf.root"); RooWorkspace *wspace0_sig = (RooWorkspace *)pdf0_sig->Get("wspace"); RooAbsPdf *shapepdf0_sig = wspace0_sig->pdf("modelPdf");  shapepdf0_sig->SetName("shapepdf0_sig");
    TFile *pdf1_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/4612_sig_shapepdf.root"); RooWorkspace *wspace1_sig = (RooWorkspace *)pdf1_sig->Get("wspace"); RooAbsPdf *shapepdf1_sig = wspace1_sig->pdf("modelPdf");  shapepdf1_sig->SetName("shapepdf1_sig");
    TFile *pdf2_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/4620_sig_shapepdf.root"); RooWorkspace *wspace2_sig = (RooWorkspace *)pdf2_sig->Get("wspace"); RooAbsPdf *shapepdf2_sig = wspace2_sig->pdf("modelPdf");  shapepdf2_sig->SetName("shapepdf2_sig");
    TFile *pdf3_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/4640_sig_shapepdf.root"); RooWorkspace *wspace3_sig = (RooWorkspace *)pdf3_sig->Get("wspace"); RooAbsPdf *shapepdf3_sig = wspace3_sig->pdf("modelPdf");  shapepdf3_sig->SetName("shapepdf3_sig");
    TFile *pdf4_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/4660_sig_shapepdf.root"); RooWorkspace *wspace4_sig = (RooWorkspace *)pdf4_sig->Get("wspace"); RooAbsPdf *shapepdf4_sig = wspace4_sig->pdf("modelPdf");  shapepdf4_sig->SetName("shapepdf4_sig");
    TFile *pdf5_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/4680_sig_shapepdf.root"); RooWorkspace *wspace5_sig = (RooWorkspace *)pdf5_sig->Get("wspace"); RooAbsPdf *shapepdf5_sig = wspace5_sig->pdf("modelPdf");  shapepdf5_sig->SetName("shapepdf5_sig");
    TFile *pdf6_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/tightcut_r3c_minetap/4700_sig_shapepdf.root"); RooWorkspace *wspace6_sig = (RooWorkspace *)pdf6_sig->Get("wspace"); RooAbsPdf *shapepdf6_sig = wspace6_sig->pdf("modelPdf");  shapepdf6_sig->SetName("shapepdf6_sig");

    // ref decay channel-- shape
    TFile *pdf0 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/4600_ref_shapepdf.root"); RooWorkspace *wspace0 = (RooWorkspace *)pdf0->Get("wspace"); RooAbsPdf *shapepdf0 = wspace0->pdf("modelPdf");  shapepdf0->SetName("shapepdf0");
    TFile *pdf1 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/4612_ref_shapepdf.root"); RooWorkspace *wspace1 = (RooWorkspace *)pdf1->Get("wspace"); RooAbsPdf *shapepdf1 = wspace1->pdf("modelPdf");  shapepdf1->SetName("shapepdf1");
    TFile *pdf2 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/4620_ref_shapepdf.root"); RooWorkspace *wspace2 = (RooWorkspace *)pdf2->Get("wspace"); RooAbsPdf *shapepdf2 = wspace2->pdf("modelPdf");  shapepdf2->SetName("shapepdf2");
    TFile *pdf3 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/4640_ref_shapepdf.root"); RooWorkspace *wspace3 = (RooWorkspace *)pdf3->Get("wspace"); RooAbsPdf *shapepdf3 = wspace3->pdf("modelPdf");  shapepdf3->SetName("shapepdf3");
    TFile *pdf4 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/4660_ref_shapepdf.root"); RooWorkspace *wspace4 = (RooWorkspace *)pdf4->Get("wspace"); RooAbsPdf *shapepdf4 = wspace4->pdf("modelPdf");  shapepdf4->SetName("shapepdf4");
    TFile *pdf5 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/4680_ref_shapepdf.root"); RooWorkspace *wspace5 = (RooWorkspace *)pdf5->Get("wspace"); RooAbsPdf *shapepdf5 = wspace5->pdf("modelPdf");  shapepdf5->SetName("shapepdf5");
    TFile *pdf6 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/4700_ref_shapepdf.root"); RooWorkspace *wspace6 = (RooWorkspace *)pdf6->Get("wspace"); RooAbsPdf *shapepdf6 = wspace6->pdf("modelPdf");  shapepdf6->SetName("shapepdf6");

    // ref decay channel- sideband - shape
    TFile *pdf0sb = new TFile("/scratchfs/bes/yuanchy8/omega/shape_3pi/cutmassroot/tightcut_r3c_minomega/pdf/4600_ref_shapepdf.root"); RooWorkspace *wspace0sb = (RooWorkspace *)pdf0sb->Get("wspace"); RooAbsPdf *shapepdf0sb = wspace0sb->pdf("modelPdf");  shapepdf0sb->SetName("shapepdf0sb");
    TFile *pdf1sb = new TFile("/scratchfs/bes/yuanchy8/omega/shape_3pi/cutmassroot/tightcut_r3c_minomega/pdf/4612_ref_shapepdf.root"); RooWorkspace *wspace1sb = (RooWorkspace *)pdf1sb->Get("wspace"); RooAbsPdf *shapepdf1sb = wspace1sb->pdf("modelPdf");  shapepdf1sb->SetName("shapepdf1sb");
    TFile *pdf2sb = new TFile("/scratchfs/bes/yuanchy8/omega/shape_3pi/cutmassroot/tightcut_r3c_minomega/pdf/4620_ref_shapepdf.root"); RooWorkspace *wspace2sb = (RooWorkspace *)pdf2sb->Get("wspace"); RooAbsPdf *shapepdf2sb = wspace2sb->pdf("modelPdf");  shapepdf2sb->SetName("shapepdf2sb");
    TFile *pdf3sb = new TFile("/scratchfs/bes/yuanchy8/omega/shape_3pi/cutmassroot/tightcut_r3c_minomega/pdf/4640_ref_shapepdf.root"); RooWorkspace *wspace3sb = (RooWorkspace *)pdf3sb->Get("wspace"); RooAbsPdf *shapepdf3sb = wspace3sb->pdf("modelPdf");  shapepdf3sb->SetName("shapepdf3sb");
    TFile *pdf4sb = new TFile("/scratchfs/bes/yuanchy8/omega/shape_3pi/cutmassroot/tightcut_r3c_minomega/pdf/4660_ref_shapepdf.root"); RooWorkspace *wspace4sb = (RooWorkspace *)pdf4sb->Get("wspace"); RooAbsPdf *shapepdf4sb = wspace4sb->pdf("modelPdf");  shapepdf4sb->SetName("shapepdf4sb");
    TFile *pdf5sb = new TFile("/scratchfs/bes/yuanchy8/omega/shape_3pi/cutmassroot/tightcut_r3c_minomega/pdf/4680_ref_shapepdf.root"); RooWorkspace *wspace5sb = (RooWorkspace *)pdf5sb->Get("wspace"); RooAbsPdf *shapepdf5sb = wspace5sb->pdf("modelPdf");  shapepdf5sb->SetName("shapepdf5sb");
    TFile *pdf6sb = new TFile("/scratchfs/bes/yuanchy8/omega/shape_3pi/cutmassroot/tightcut_r3c_minomega/pdf/4700_ref_shapepdf.root"); RooWorkspace *wspace6sb = (RooWorkspace *)pdf6sb->Get("wspace"); RooAbsPdf *shapepdf6sb = wspace6sb->pdf("modelPdf");  shapepdf6sb->SetName("shapepdf6sb");


    // sig decay channel-- shape x guass
    RooAbsPdf *sigpdf0_sig = new RooFFTConvPdf("sigpdf0_sig", "shapepdf0_sig (X) gauss", *var_4600, *shapepdf0_sig, guass_4600);
    RooAbsPdf *sigpdf1_sig = new RooFFTConvPdf("sigpdf1_sig", "shapepdf1_sig (X) gauss", *var_4612, *shapepdf1_sig, guass_4612);
    RooAbsPdf *sigpdf2_sig = new RooFFTConvPdf("sigpdf2_sig", "shapepdf2_sig (X) gauss", *var_4620, *shapepdf2_sig, guass_4620);
    RooAbsPdf *sigpdf3_sig = new RooFFTConvPdf("sigpdf3_sig", "shapepdf3_sig (X) gauss", *var_4640, *shapepdf3_sig, guass_4640);
    RooAbsPdf *sigpdf4_sig = new RooFFTConvPdf("sigpdf4_sig", "shapepdf4_sig (X) gauss", *var_4660, *shapepdf4_sig, guass_4660);
    RooAbsPdf *sigpdf5_sig = new RooFFTConvPdf("sigpdf5_sig", "shapepdf5_sig (X) gauss", *var_4680, *shapepdf5_sig, guass_4680);
    RooAbsPdf *sigpdf6_sig = new RooFFTConvPdf("sigpdf6_sig", "shapepdf6_sig (X) gauss", *var_4700, *shapepdf6_sig, guass_4700);


    // ref decay channel -- shape x guass
    RooAbsPdf *sigpdf0 = new RooFFTConvPdf("sigpdf0", "shapepdf0 (X) gauss", *var_4600, *shapepdf0, guass_4600);
    RooAbsPdf *sigpdf1 = new RooFFTConvPdf("sigpdf1", "shapepdf1 (X) gauss", *var_4612, *shapepdf1, guass_4612);
    RooAbsPdf *sigpdf2 = new RooFFTConvPdf("sigpdf2", "shapepdf2 (X) gauss", *var_4620, *shapepdf2, guass_4620);
    RooAbsPdf *sigpdf3 = new RooFFTConvPdf("sigpdf3", "shapepdf3 (X) gauss", *var_4640, *shapepdf3, guass_4640);
    RooAbsPdf *sigpdf4 = new RooFFTConvPdf("sigpdf4", "shapepdf4 (X) gauss", *var_4660, *shapepdf4, guass_4660);
    RooAbsPdf *sigpdf5 = new RooFFTConvPdf("sigpdf5", "shapepdf5 (X) gauss", *var_4680, *shapepdf5, guass_4680);
    RooAbsPdf *sigpdf6 = new RooFFTConvPdf("sigpdf6", "shapepdf6 (X) gauss", *var_4700, *shapepdf6, guass_4700);

    // ref decay channel- sideband - shape x guass
    RooAbsPdf *SBsigpdf0 = new RooFFTConvPdf("SBsigpdf0", "shapepdf0sb (X) gauss", *var_4600, *shapepdf0sb, guass_4600);
    RooAbsPdf *SBsigpdf1 = new RooFFTConvPdf("SBsigpdf1", "shapepdf1sb (X) gauss", *var_4612, *shapepdf1sb, guass_4612);
    RooAbsPdf *SBsigpdf2 = new RooFFTConvPdf("SBsigpdf2", "shapepdf2sb (X) gauss", *var_4620, *shapepdf2sb, guass_4620);
    RooAbsPdf *SBsigpdf3 = new RooFFTConvPdf("SBsigpdf3", "shapepdf3sb (X) gauss", *var_4640, *shapepdf3sb, guass_4640);
    RooAbsPdf *SBsigpdf4 = new RooFFTConvPdf("SBsigpdf4", "shapepdf4sb (X) gauss", *var_4660, *shapepdf4sb, guass_4660);
    RooAbsPdf *SBsigpdf5 = new RooFFTConvPdf("SBsigpdf5", "shapepdf5sb (X) gauss", *var_4680, *shapepdf5sb, guass_4680);
    RooAbsPdf *SBsigpdf6 = new RooFFTConvPdf("SBsigpdf6", "shapepdf6sb (X) gauss", *var_4700, *shapepdf6sb, guass_4700);


    // ____________________ sig decay channel, argus background 
    RooRealVar m0_sig("m0_sig", "m0_sig", 2.299765);   RooRealVar c0_sig("c0_sig", "c0_sig", -2.1266e+01, -70, 20);    RooArgusBG argus0_sig("argus0_sig", "argus0 sig", *var_4600, m0_sig, c0_sig);
    RooRealVar m1_sig("m1_sig", "m1_sig", 2.30579);    RooRealVar c1_sig("c1_sig", "c1_sig", -6.0660e+00, -70, 20);    RooArgusBG argus1_sig("argus1_sig", "argus1 sig", *var_4612, m1_sig, c1_sig);
    RooRealVar m2_sig("m2_sig", "m2_sig", 2.31387);    RooRealVar c2_sig("c2_sig", "c2_sig", -4.9716e+00, -70, 20);    RooArgusBG argus2_sig("argus2_sig", "argus2 sig", *var_4620, m2_sig, c2_sig);
    RooRealVar m3_sig("m3_sig", "m3_sig", 2.320255);   RooRealVar c3_sig("c3_sig", "c3_sig", -2.4289e+00, -70, 20);    RooArgusBG argus3_sig("argus3_sig", "argus3 sig", *var_4640, m3_sig, c3_sig);
    RooRealVar m4_sig("m4_sig", "m4_sig", 2.33046);    RooRealVar c4_sig("c4_sig", "c4_sig", -2.2689e+01, -70, 20);    RooArgusBG argus4_sig("argus4_sig", "argus4 sig", *var_4660, m4_sig, c4_sig);
    RooRealVar m5_sig("m5_sig", "m5_sig", 2.34079);    RooRealVar c5_sig("c5_sig", "c5_sig", -9.3432e+00, -70, 20);    RooArgusBG argus5_sig("argus5_sig", "argus5 sig", *var_4680, m5_sig, c5_sig);
    RooRealVar m6_sig("m6_sig", "m6_sig", 2.34919);    RooRealVar c6_sig("c6_sig", "c6_sig", -7.9593e+00, -70, 20);    RooArgusBG argus6_sig("argus6_sig", "argus6 sig", *var_4700, m6_sig, c6_sig);

    // ____________________ ref decay channel, argus background
    RooRealVar m0("m0", "m0", 2.299765);   RooRealVar c0("c0", "c0", -7.5954e+0,  -70, 20);    RooArgusBG argus0("argus0", "argus0", *var_4600, m0, c0);
    RooRealVar m1("m1", "m1", 2.30579);    RooRealVar c1("c1", "c1", 1.4943e+01,  -70, 20);    RooArgusBG argus1("argus1", "argus1", *var_4612, m1, c1);
    RooRealVar m2("m2", "m2", 2.31387);    RooRealVar c2("c2", "c2", 2.9315e+00,  -70, 20);    RooArgusBG argus2("argus2", "argus2", *var_4620, m2, c2);
    RooRealVar m3("m3", "m3", 2.320255);   RooRealVar c3("c3", "c3", -3.1054e+00, -70, 20);    RooArgusBG argus3("argus3", "argus3", *var_4640, m3, c3);
    RooRealVar m4("m4", "m4", 2.33046);    RooRealVar c4("c4", "c4", -4.8423e+00, -70, 20);    RooArgusBG argus4("argus4", "argus4", *var_4660, m4, c4);
    RooRealVar m5("m5", "m5", 2.34079);    RooRealVar c5("c5", "c5", -4.3007e+00, -70, 20);    RooArgusBG argus5("argus5", "argus5", *var_4680, m5, c5);
    RooRealVar m6("m6", "m6", 2.34919);    RooRealVar c6("c6", "c6", -5.4013e+00, -70, 20);    RooArgusBG argus6("argus6", "argus6", *var_4700, m6, c6);

    // ____________________ ref decay channel, signal  num
    RooRealVar nsig_mode0("nsig_mode0", "signal of mode0", 0.05 * tr_fit0->GetEntries(), 0, 1.2 * tr_fit0->GetEntries());    
    RooRealVar nsig_mode1("nsig_mode1", "signal of mode1", 0.05 * tr_fit1->GetEntries(), 0, 1.2 * tr_fit1->GetEntries());    
    RooRealVar nsig_mode2("nsig_mode2", "signal of mode2", 0.05 * tr_fit2->GetEntries(), 0, 1.2 * tr_fit2->GetEntries());    
    RooRealVar nsig_mode3("nsig_mode3", "signal of mode3", 0.05 * tr_fit3->GetEntries(), 0, 1.2 * tr_fit3->GetEntries());    
    RooRealVar nsig_mode4("nsig_mode4", "signal of mode4", 0.05 * tr_fit4->GetEntries(), 0, 1.2 * tr_fit4->GetEntries());    
    RooRealVar nsig_mode5("nsig_mode5", "signal of mode5", 0.05 * tr_fit5->GetEntries(), 0, 1.2 * tr_fit5->GetEntries());    
    RooRealVar nsig_mode6("nsig_mode6", "signal of mode6", 0.05 * tr_fit6->GetEntries(), 0, 1.2 * tr_fit6->GetEntries());    
    // ref  sideband  
    RooRealVar nref_sb0("nref_sb0", "signal of mode0sb", 0, 0, 30);    
    RooRealVar nref_sb1("nref_sb1", "signal of mode1sb", 0, 0, 30);    
    RooRealVar nref_sb2("nref_sb2", "signal of mode2sb", 0, 0, 30);    
    RooRealVar nref_sb3("nref_sb3", "signal of mode3sb", 0, 0, 30);    
    RooRealVar nref_sb4("nref_sb4", "signal of mode4sb", 0, 0, 30);    
    RooRealVar nref_sb5("nref_sb5", "signal of mode5sb", 0, 0, 30);    
    RooRealVar nref_sb6("nref_sb6", "signal of mode6sb", 0, 0, 30);    

    // ref sideband  in sigal region
    RooFormulaVar nref0("nref0", "signal of mode0sb", "0.582975 * nref_sb0", RooArgList(nref_sb0));    
    RooFormulaVar nref1("nref1", "signal of mode1sb", "0.582975 * nref_sb1", RooArgList(nref_sb1));    
    RooFormulaVar nref2("nref2", "signal of mode2sb", "0.582975 * nref_sb2", RooArgList(nref_sb2));    
    RooFormulaVar nref3("nref3", "signal of mode3sb", "0.582975 * nref_sb3", RooArgList(nref_sb3));    
    RooFormulaVar nref4("nref4", "signal of mode4sb", "0.582975 * nref_sb4", RooArgList(nref_sb4));    
    RooFormulaVar nref5("nref5", "signal of mode5sb", "0.582975 * nref_sb5", RooArgList(nref_sb5));    
    RooFormulaVar nref6("nref6", "signal of mode6sb", "0.582975 * nref_sb6", RooArgList(nref_sb6));

    // ref bkg num
    RooRealVar nbkg0("nbkg0", "bkg number of mode0", 0.05 * tr_fit0->GetEntries(), 0, 1.2 * tr_fit0->GetEntries());
    RooRealVar nbkg1("nbkg1", "bkg number of mode1", 0.05 * tr_fit1->GetEntries(), 0, 1.2 * tr_fit1->GetEntries());	
    RooRealVar nbkg2("nbkg2", "bkg number of mode2", 0.05 * tr_fit2->GetEntries(), 0, 1.2 * tr_fit2->GetEntries());
    RooRealVar nbkg3("nbkg3", "bkg number of mode3", 0.05 * tr_fit3->GetEntries(), 0, 1.2 * tr_fit3->GetEntries());
    RooRealVar nbkg4("nbkg4", "bkg number of mode4", 0.05 * tr_fit4->GetEntries(), 0, 1.2 * tr_fit4->GetEntries());
    RooRealVar nbkg5("nbkg5", "bkg number of mode5", 0.05 * tr_fit5->GetEntries(), 0, 1.2 * tr_fit5->GetEntries());
    RooRealVar nbkg6("nbkg6", "bkg number of mode6", 0.05 * tr_fit6->GetEntries(), 0, 1.2 * tr_fit6->GetEntries());

    // ref bkg num in sideband
    RooRealVar nSBbkg0("nSBbkg0", "bkg number of mode0 SB", 0.05 * tr_fit0sb->GetEntries(), 0, 1.2 * tr_fit0sb->GetEntries());
    RooRealVar nSBbkg1("nSBbkg1", "bkg number of mode1 SB", 0.05 * tr_fit1sb->GetEntries(), 0, 1.2 * tr_fit1sb->GetEntries());	
    RooRealVar nSBbkg2("nSBbkg2", "bkg number of mode2 SB", 0.05 * tr_fit2sb->GetEntries(), 0, 1.2 * tr_fit2sb->GetEntries());
    RooRealVar nSBbkg3("nSBbkg3", "bkg number of mode3 SB", 0.05 * tr_fit3sb->GetEntries(), 0, 1.2 * tr_fit3sb->GetEntries());
    RooRealVar nSBbkg4("nSBbkg4", "bkg number of mode4 SB", 0.05 * tr_fit4sb->GetEntries(), 0, 1.2 * tr_fit4sb->GetEntries());
    RooRealVar nSBbkg5("nSBbkg5", "bkg number of mode5 SB", 0.05 * tr_fit5sb->GetEntries(), 0, 1.2 * tr_fit5sb->GetEntries());
    RooRealVar nSBbkg6("nSBbkg6", "bkg number of mode6 SB", 0.05 * tr_fit6sb->GetEntries(), 0, 1.2 * tr_fit6sb->GetEntries());

    // ____________________ sig signal/bkg num
    double Br_sig_inter = 0.085359238;
    double Br_ref_inter = 0.449239622;

    RooFormulaVar nsig_mode0_sig("nsig_mode0_sig", "signal of mode0 sig", "Bratio * nsig_mode0* 0.085359238  *0.0314/  0.449239622  /0.0322", RooArgSet(Bratio, nsig_mode0 ));	RooRealVar nbkg0_sig("nbkg0_sig", "bkg number of mode0 sig", 0.05 * tr_fit0_sig->GetEntries(), 0, 1.2 * tr_fit0_sig->GetEntries());
    RooFormulaVar nsig_mode1_sig("nsig_mode1_sig", "signal of mode1 sig", "Bratio * nsig_mode1* 0.085359238  *0.0284/  0.449239622  /0.0299", RooArgSet(Bratio, nsig_mode1 ));	RooRealVar nbkg1_sig("nbkg1_sig", "bkg number of mode1 sig", 0.05 * tr_fit1_sig->GetEntries(), 0, 1.2 * tr_fit1_sig->GetEntries());
    RooFormulaVar nsig_mode2_sig("nsig_mode2_sig", "signal of mode2 sig", "Bratio * nsig_mode2* 0.085359238  *0.0283/  0.449239622  /0.0299", RooArgSet(Bratio, nsig_mode2 ));	RooRealVar nbkg2_sig("nbkg2_sig", "bkg number of mode2 sig", 0.05 * tr_fit2_sig->GetEntries(), 0, 1.2 * tr_fit2_sig->GetEntries());
    RooFormulaVar nsig_mode3_sig("nsig_mode3_sig", "signal of mode3 sig", "Bratio * nsig_mode3* 0.085359238  *0.0283/  0.449239622  /0.0297", RooArgSet(Bratio, nsig_mode3 ));	RooRealVar nbkg3_sig("nbkg3_sig", "bkg number of mode3 sig", 0.05 * tr_fit3_sig->GetEntries(), 0, 1.2 * tr_fit3_sig->GetEntries());
    RooFormulaVar nsig_mode4_sig("nsig_mode4_sig", "signal of mode4 sig", "Bratio * nsig_mode4* 0.085359238  *0.0280/  0.449239622  /0.0290", RooArgSet(Bratio, nsig_mode4 ));	RooRealVar nbkg4_sig("nbkg4_sig", "bkg number of mode4 sig", 0.05 * tr_fit4_sig->GetEntries(), 0, 1.2 * tr_fit4_sig->GetEntries());
    RooFormulaVar nsig_mode5_sig("nsig_mode5_sig", "signal of mode5 sig", "Bratio * nsig_mode5* 0.085359238  *0.0280/  0.449239622  /0.0289", RooArgSet(Bratio, nsig_mode5 ));	RooRealVar nbkg5_sig("nbkg5_sig", "bkg number of mode5 sig", 0.05 * tr_fit5_sig->GetEntries(), 0, 1.2 * tr_fit5_sig->GetEntries());
    RooFormulaVar nsig_mode6_sig("nsig_mode6_sig", "signal of mode6 sig", "Bratio * nsig_mode6* 0.085359238  *0.0279/  0.449239622  /0.0289", RooArgSet(Bratio, nsig_mode6 ));	RooRealVar nbkg6_sig("nbkg6_sig", "bkg number of mode6 sig", 0.05 * tr_fit6_sig->GetEntries(), 0, 1.2 * tr_fit6_sig->GetEntries());


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
    RooAddPdf *model0 = new RooAddPdf("model0", "model0", RooArgList(*sigpdf0, *SBsigpdf0, argus0), RooArgList(nsig_mode0, nref0, nbkg0));
    RooAddPdf *model1 = new RooAddPdf("model1", "model1", RooArgList(*sigpdf1, *SBsigpdf1, argus1), RooArgList(nsig_mode1, nref1, nbkg1));
    RooAddPdf *model2 = new RooAddPdf("model2", "model2", RooArgList(*sigpdf2, *SBsigpdf2, argus2), RooArgList(nsig_mode2, nref2, nbkg2));
    RooAddPdf *model3 = new RooAddPdf("model3", "model3", RooArgList(*sigpdf3, *SBsigpdf3, argus3), RooArgList(nsig_mode3, nref3, nbkg3));
    RooAddPdf *model4 = new RooAddPdf("model4", "model4", RooArgList(*sigpdf4, *SBsigpdf4, argus4), RooArgList(nsig_mode4, nref4, nbkg4));
    RooAddPdf *model5 = new RooAddPdf("model5", "model5", RooArgList(*sigpdf5, *SBsigpdf5, argus5), RooArgList(nsig_mode5, nref5, nbkg5));
    RooAddPdf *model6 = new RooAddPdf("model6", "model6", RooArgList(*sigpdf6, *SBsigpdf6, argus6), RooArgList(nsig_mode6, nref6, nbkg6));

    // pdf in sideband reigon in ref channel 
    RooAddPdf *model0_3pisb = new RooAddPdf("model03pisb", "model03pisb", RooArgList(*SBsigpdf0, argus0), RooArgList(nref_sb0, nSBbkg0));
    RooAddPdf *model1_3pisb = new RooAddPdf("model13pisb", "model13pisb", RooArgList(*SBsigpdf1, argus1), RooArgList(nref_sb1, nSBbkg1));
    RooAddPdf *model2_3pisb = new RooAddPdf("model23pisb", "model23pisb", RooArgList(*SBsigpdf2, argus2), RooArgList(nref_sb2, nSBbkg2));
    RooAddPdf *model3_3pisb = new RooAddPdf("model33pisb", "model33pisb", RooArgList(*SBsigpdf3, argus3), RooArgList(nref_sb3, nSBbkg3));
    RooAddPdf *model4_3pisb = new RooAddPdf("model43pisb", "model43pisb", RooArgList(*SBsigpdf4, argus4), RooArgList(nref_sb4, nSBbkg4));
    RooAddPdf *model5_3pisb = new RooAddPdf("model53pisb", "model53pisb", RooArgList(*SBsigpdf5, argus5), RooArgList(nref_sb5, nSBbkg5));
    RooAddPdf *model6_3pisb = new RooAddPdf("model63pisb", "model63pisb", RooArgList(*SBsigpdf6, argus6), RooArgList(nref_sb6, nSBbkg6));


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

    RooAbsReal* ref_nl_4600sb  =  model0_3pisb->createNLL(*data0sb);
    RooAbsReal* ref_nl_4612sb  =  model1_3pisb->createNLL(*data1sb);
    RooAbsReal* ref_nl_4620sb  =  model2_3pisb->createNLL(*data2sb);
    RooAbsReal* ref_nl_4640sb  =  model3_3pisb->createNLL(*data3sb);
    RooAbsReal* ref_nl_4660sb  =  model4_3pisb->createNLL(*data4sb);
    RooAbsReal* ref_nl_4680sb  =  model5_3pisb->createNLL(*data5sb);
    RooAbsReal* ref_nl_4700sb  =  model6_3pisb->createNLL(*data6sb);

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

    allList.add(*ref_nl_4600sb);
    allList.add(*ref_nl_4612sb);
    allList.add(*ref_nl_4620sb);
    allList.add(*ref_nl_4640sb);
    allList.add(*ref_nl_4660sb);
    allList.add(*ref_nl_4680sb);
    allList.add(*ref_nl_4700sb);
    
        // RooPlot *frame_mode0 = M_BC_r3c->frame(2.25, 2.35, 20);
        // frame_mode0->SetXTitle("M_BC_r3c #pi0 4600");
        // model0->plotOn(frame_mode0, Components("*sigpdf0"), LineColor(kGreen+1), LineWidth(3), LineStyle(kDashed));
        // frame_mode0->Draw();
        // return 0;

    RooAddition nll("nll", "nll", allList);
    RooMinuit mm(nll);
    mm.migrad();
    mm.hesse();

// std::shared_ptr<RooAbsL> likelihood = buildLikelihood(pdf, data);

//     RooMinimizer mm(likelihood);
//     mm.setStrategy(2);
//     mm.migrad();
//     mm.hesse();

    // ================================v========   D R A W  ====================================================================
    // ********************************************************************************
    if(1)
    {
        // TCanvas *can = new TCanvas("can", "simu fit", 400*2 * 1.8, 300*7 * 1.8); //setPad();
        // can->Divide(2, 7);
        // can->SetFillColor(0);

        RooRealVar *myvar[] = {var_4600, var_4612, var_4620, var_4640, var_4660, var_4680, var_4700};
        double endpoint[]={2.299765, 2.30579, 2.31387, 2.320255, 2.33046,  2.34079, 2.34919 };
        int integral_lum[]={567, 104, 522, 552, 530,  1669, 536 };


        RooDataSet *data_sig[] = {data0_sig, data1_sig, data2_sig, data3_sig, data4_sig, data5_sig, data6_sig};
        RooAbsPdf *mode_sig[] = {model0_sig, model1_sig, model2_sig, model3_sig, model4_sig, model5_sig, model6_sig}; 


        RooDataSet *data_ref[] = {data0, data1, data2, data3, data4, data5, data6};
        RooAbsPdf *mode_ref[] = {model0, model1, model2, model3, model4, model5, model6}; 

        RooDataSet *data_sb[] = {data0sb, data1sb, data2sb, data3sb, data4sb, data5sb, data6sb};
        RooAbsPdf *mode_3pi_sb[] = {model0_3pisb, model1_3pisb, model2_3pisb, model3_3pisb, model4_3pisb, model5_3pisb, model6_3pisb}; 


        for(int i = 0; i<7; i++)
        {
            // sig 4600
            TCanvas *can1 = new TCanvas("can", "simu fit", 400 * 1.8, 300 * 1.8); //setPad();
            can1->SetFillColor(0);

            RooPlot *frame_mode0_sig = myvar[i]->frame(xmin, endpoint[i], xbins);

            frame_mode0_sig->SetXTitle("M_{BC} (GeV/#font[12]{c^{2}})");
            frame_mode0_sig->SetTitle(TString::Format("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta',     #sqrt{s}=%.3f GeV,     %d pb^{-1}", endpoint[i]*2, integral_lum[i]));
            frame_mode0_sig->SetYTitle(TString::Format("Events/(%.2fMeV/#font[12]{c^{2}})", (endpoint[i] - mbcmin) / xbins * 1000));
            frame_mode0_sig->GetYaxis()->SetTitleOffset(1.2);
            frame_mode0_sig->GetYaxis()->SetTitleSize(0.04);
            frame_mode0_sig->GetXaxis()->SetTitleSize(0.04);
            data_sig[i]->plotOn(frame_mode0_sig, LineWidth(2));
            mode_sig[i]->plotOn(frame_mode0_sig, LineColor(kRed), LineWidth(3));
            mode_sig[i]->plotOn(frame_mode0_sig, Components(TString::Format("sigpdf%1d_sig", i)), LineColor(kGreen+1), LineWidth(3), LineStyle(kDashed));
            mode_sig[i]->plotOn(frame_mode0_sig, Components(TString::Format("argus%1d_sig", i)), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
            // can->cd(i*2+1);  
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
            can1->SaveAs(("syserr_etaprimesig_" + to_string(int(endpoint[i]*2000)) + ".png" ).c_str());
            can1->SaveAs(("syserr_etaprimesig_" + to_string(int(endpoint[i]*2000)) + ".pdf" ).c_str());


            
            
            // ref 4600
            TCanvas *can2 = new TCanvas("can", "simu fit", 400 * 1.8, 300 * 1.8); //setPad();
            can2->SetFillColor(0);

            RooPlot *frame_mode0 = myvar[i]->frame( xmin, endpoint[i], xbins);
            frame_mode0->SetXTitle("M_{BC} (GeV/#font[12]{c^{2}})");
            frame_mode0->SetYTitle(TString::Format("Events/(%.2fMeV/#font[12]{c^{2}})", (endpoint[i] - mbcmin) / xbins * 1000));
            frame_mode0->SetTitle(TString::Format("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #omega,     #sqrt{s}=%.3f GeV,     %d pb^{-1}", endpoint[i]*2, integral_lum[i] ));
            frame_mode0->GetYaxis()->SetTitleOffset(1.2);
            frame_mode0->GetYaxis()->SetTitleSize(0.04);
            frame_mode0->GetXaxis()->SetTitleSize(0.04);
            data_ref[i]->plotOn(frame_mode0, LineWidth(2));
            mode_ref[i]->plotOn(frame_mode0, LineColor(kRed), LineWidth(3));
            mode_ref[i]->plotOn(frame_mode0, Components(TString::Format("sigpdf%1d", i)), LineColor(kGreen+1), LineWidth(3), LineStyle(kDashed));
            mode_ref[i]->plotOn(frame_mode0, Components(TString::Format("argus%1d", i)), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
            mode_ref[i]->plotOn(frame_mode0, Name("pdf_bkgsb"), Components("SBsigpdf?"), LineColor(kMagenta+1), LineWidth(3), LineStyle(kDashed));
            // can->cd(i*2+2);  
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

            can2->SaveAs(("syserr_omegaref_" + to_string(int(endpoint[i]*2000)) + ".png" ).c_str());
            can2->SaveAs(("syserr_omegaref_" + to_string(int(endpoint[i]*2000)) + ".pdf" ).c_str());

                
            /////////////////////  draw ref  sideband ////////////////////////////////////////// 
            TCanvas *can55 = new TCanvas("can55", "simu fit3", 400 * 1.8, 300 * 1.8); 
            can55->SetFillColor(0);
            // can55->SetMargin(0.15, 0.03, 0.15, 0.1);
            // can55->cd();
            
            // ref              
            RooPlot *frame_mode_refsb0 = myvar[i]->frame( xmin, endpoint[i], xbins);
            frame_mode_refsb0->SetXTitle("M_{BC} (GeV/#font[12]{c^{2}})");
            frame_mode_refsb0->SetYTitle(TString::Format("Events/(%.2fMeV/#font[12]{c^{2}})", (endpoint[i] - mbcmin) / xbins * 1000));
            frame_mode_refsb0->SetTitle(TString::Format("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #omega,     #sqrt{s}=%.3f GeV,     %d pb^{-1}", endpoint[i]*2, integral_lum[i] ));
            frame_mode_refsb0->GetYaxis()->SetTitleOffset(1.2);
            frame_mode_refsb0->GetYaxis()->SetTitleSize(0.04);
            frame_mode_refsb0->GetXaxis()->SetTitleSize(0.04);
            data_sb[i]->plotOn(frame_mode_refsb0, Name("data"), LineWidth(2));
            mode_3pi_sb[i]->plotOn(frame_mode_refsb0, Name("sum"), LineColor(kRed),  LineWidth(3));
            mode_3pi_sb[i]->plotOn(frame_mode_refsb0, Name("pdf_argus"), Components("argus*"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
            mode_3pi_sb[i]->plotOn(frame_mode_refsb0, Name("pdf_bkgsb"), Components("SBsigpdf?"), LineColor(kMagenta+1), LineWidth(3), LineStyle(kDashed));


            frame_mode_refsb0->Draw();
            gPad->Update();
            title = (TPaveText*)gPad->FindObject("title");
            // title->InsertText("");
            title->SetTextAlign(10);
            title->SetX1NDC(0.09);
            title->SetTextSize(0.04);
            title->SetY1NDC(0.82);
            title->SetX2NDC(0.47);
            title->SetY2NDC(0.980);
            gPad->Modified();
            gPad->Update();

            can55->SaveAs(("syserr_omegaref_sb_" + to_string(int(endpoint[i]*2000)) + ".png" ).c_str());
            can55->SaveAs(("syserr_omegaref_sb_" + to_string(int(endpoint[i]*2000)) + ".pdf" ).c_str());

                
        }

        // can->SaveAs("svg_fit_comb.pdf");
        // can->SaveAs("svg_fit_comb.png");
    }
    

    // ================================================================================
    // ********************************************************************************
    
    if(1)
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
            
        RooPlot *frame_mode_sig = M_BC_r3c->frame( mbcmin, mbcmax, xbins);
        frame_mode_sig->SetXTitle("M_{BC} (GeV/#font[12]{c^{2}})");
        frame_mode_sig->SetYTitle(ytitle);
        frame_mode_sig->GetYaxis()->SetTitleOffset(1.2);
        frame_mode_sig->GetYaxis()->SetTitleSize(0.04);
        frame_mode_sig->GetXaxis()->SetTitleSize(0.04);
        combData->plotOn(frame_mode_sig, Name("data"), LineWidth(2));
        pdfSig->plotOn(frame_mode_sig, Name("sum"), LineColor(kRed),  LineWidth(3));
        pdfSig->plotOn(frame_mode_sig, Name("pdf_argus"), Components("argus*_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        pdfSig->plotOn(frame_mode_sig, Name("pdf_sig"), Components("sigpdf*_sig"), LineColor(kGreen+1), LineWidth(3), LineStyle(9));
        
        frame_mode_sig->SetTitle(" ");
        frame_mode_sig->SetLabelSize(0.045, "xy");
        frame_mode_sig->SetTitleSize(0.06, "xy");
        frame_mode_sig->GetXaxis()->SetNdivisions(205);
        frame_mode_sig->Draw();

        TPaveText *pt = new TPaveText(0.96-0.5, 1-0.16-0.06, 0.96, 1-0.16, "blNDC");      
        pt->SetBorderSize(0);
        pt->SetFillColor(0);
        // pt->SetLineColor(5);
        // pt->SetTextColor(5);
        pt->InsertText("#Lambda_{c}^{+}#rightarrow#Sigma^{+}#eta'");
        // pt->SetTextAlign(12);
        // pt->SetTextSize(12);
        pt->Draw();
        
        TLegend *legend3 = new TLegend(0.62, 0.44, 0.91, 0.78);
        // legend3->SetHeader("#sqrt{s}=4628 GeV");
        legend3->AddEntry(frame_mode_sig->findObject("data"), "data", "el");
        legend3->AddEntry(frame_mode_sig->findObject("sum"), "sum", "l");
        legend3->AddEntry(frame_mode_sig->findObject("pdf_argus"), "ARGUS BG", "l");
        // legend3->AddEntry(frame_mode_sig->findObject("pdf_bkgsb"), "non-resonance BKG", "l");
        legend3->AddEntry(frame_mode_sig->findObject("pdf_sig"), "signal", "l");
        // legend3->AddEntry("hist_data", "data", "f");
        // legend3->AddEntry("hist_inclusive_sig", "signal", "f");
        // legend3->AddEntry("hist_inclusive_bkg", "#Lambda_{c}#bar{#Lambda_{c}} bkg", "f");
        legend3->SetBorderSize(0);
        legend3->SetFillColor(0);
        legend3->Draw();

        can3->SaveAs("c_sig.png");
        can3->SaveAs("simu_sig.pdf");

        gStyle->SetLegendTextSize(0.04);


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
            
        RooPlot *frame_mode_ref = M_BC_r3c->frame( mbcmin, mbcmax, xbins);
        frame_mode_ref->SetXTitle("M_{BC} (GeV/#font[12]{c^{2}})");
        frame_mode_ref->SetYTitle(ytitle);
        frame_mode_ref->SetTitle(" ");
        frame_mode_ref->GetYaxis()->SetTitleOffset(1.2);
        frame_mode_ref->GetYaxis()->SetTitleSize(0.04);
        frame_mode_ref->GetXaxis()->SetTitleSize(0.04);
        combData_ref->plotOn(frame_mode_ref, Name("data"), LineWidth(2));
        pdfRef->plotOn(frame_mode_ref, Name("sum"), LineColor(kRed),  LineWidth(3));
        pdfRef->plotOn(frame_mode_ref, Name("pdf_argus"), Components("argus*"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        pdfRef->plotOn(frame_mode_ref, Name("pdf_sig"), Components("sigpdf?"), LineColor(kGreen+1), LineWidth(3), LineStyle(9));
        pdfRef->plotOn(frame_mode_ref, Name("pdf_bkgsb"), Components("SBsigpdf?"), LineColor(kMagenta+1), LineWidth(3), LineStyle(kDashed));

        frame_mode_ref->SetLabelSize(0.045, "xy");
        frame_mode_ref->SetTitleSize(0.06, "xy");
        frame_mode_ref->GetXaxis()->SetNdivisions(205);
        frame_mode_ref->SetTitle(" ");
        frame_mode_ref->Draw();

        TPaveText *pt2 = new TPaveText(0.96-0.5, 1-0.16-0.06, 0.96, 1-0.16, "blNDC");      
        pt2->SetBorderSize(0);
        pt2->SetFillColor(0);
        // pt2->SetLineColor(5);
        // pt2->SetTextColor(5);
        pt2->InsertText("#Lambda_{c}^{+}#rightarrow#Sigma^{+}#omega");
        // pt2->SetTextAlign(12);
        // pt->SetTextSize(12);
        pt2->Draw();

        TLegend *legend = new TLegend(0.62, 0.44, 0.91, 0.78);
        // legend->SetHeader("#sqrt{s}=4628 GeV");
        legend->AddEntry(frame_mode_ref->findObject("data"), "data", "el");
        legend->AddEntry(frame_mode_ref->findObject("sum"), "sum", "l");
        legend->AddEntry(frame_mode_ref->findObject("pdf_argus"), "ARGUS BG", "l");
        legend->AddEntry(frame_mode_ref->findObject("pdf_bkgsb"), "non-resonant BG", "l");
        legend->AddEntry(frame_mode_ref->findObject("pdf_sig"), "signal", "l");
        // legend->AddEntry("hist_data", "data", "f");
        // legend->AddEntry("hist_inclusive_sig", "signal", "f");
        // legend->AddEntry("hist_inclusive_bkg", "#Lambda_{c}#bar{#Lambda_{c}} bkg", "f");
        legend->SetBorderSize(0);
        legend->SetFillColor(0);
        legend->Draw();

        can4->SaveAs("c_ref.png");
        can4->SaveAs("simu_ref.pdf");





        /////////////////////  draw ref  sideband ////////////////////////////////////////// 
        TCanvas *can5 = new TCanvas("can5", "simu fit3", 700, 600); 
        can5->SetFillColor(0);
        can5->SetMargin(0.15, 0.03, 0.15, 0.1);
        can5->cd();
        
        RooDataSet *combData_refsb = new RooDataSet("combData_refsb", "combined data",  RooArgSet(*M_BC_r3c));
        combData_refsb->append(*data0sb);
        combData_refsb->append(*data1sb);
        combData_refsb->append(*data2sb);
        combData_refsb->append(*data3sb);
        combData_refsb->append(*data4sb);
        combData_refsb->append(*data5sb);
        combData_refsb->append(*data6sb);

        // ref
        RooAddPdf *pdfRefsb = new RooAddPdf("pdfRefsb", "pdfRefsb", RooArgList(*model0_3pisb, *model1_3pisb, *model2_3pisb, *model3_3pisb, *model4_3pisb, *model5_3pisb, *model6_3pisb ));
            
        RooPlot *frame_mode_refsb = M_BC_r3c->frame( mbcmin, mbcmax, 25);
        frame_mode_refsb->SetXTitle("M_{BC} (GeV/#font[12]{c^{2}})");
        frame_mode_refsb->SetYTitle(ytitle);
        frame_mode_refsb->SetTitle(" ");
        frame_mode_refsb->GetYaxis()->SetTitleOffset(1.2);
        frame_mode_refsb->GetYaxis()->SetTitleSize(0.04);
        frame_mode_refsb->GetXaxis()->SetTitleSize(0.04);
        combData_refsb->plotOn(frame_mode_refsb, Name("data"), LineWidth(2));
        pdfRefsb->plotOn(frame_mode_refsb, Name("sum"), LineColor(kRed),  LineWidth(3));
        pdfRefsb->plotOn(frame_mode_refsb, Name("pdf_argus"), Components("argus*"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
        pdfRefsb->plotOn(frame_mode_refsb, Name("pdf_bkgsb"), Components("SBsigpdf?"), LineColor(kMagenta+1), LineWidth(3), LineStyle(kDashed));

        frame_mode_refsb->SetLabelSize(0.045, "xy");
        frame_mode_refsb->SetTitleSize(0.06, "xy");
        frame_mode_refsb->GetXaxis()->SetNdivisions(205);
        frame_mode_refsb->SetTitle(" ");
        frame_mode_refsb->Draw();

        TPaveText *pt2sb = new TPaveText(0.96-0.4, 1-0.16-0.06, 0.86, 1-0.16, "blNDC");      
        pt2sb->SetBorderSize(0);
        pt2sb->SetFillColor(0);
        // pt2sb->SetLineColor(5);
        // pt2sb->SetTextColor(5);
        pt2sb->InsertText("#Lambda_{c}^{+}#rightarrow#Sigma^{+}#omega");
        // pt2sb->SetTextAlign(12);
        // pt->SetTextSize(12);
        pt2sb->Draw();


        TLegend *legend2 = new TLegend(0.64, 0.44, 0.91, 0.78);
        // legend2->SetHeader("#sqrt{s}=4628 GeV");
        legend2->AddEntry(frame_mode_refsb->findObject("data"), "data", "el");
        legend2->AddEntry(frame_mode_refsb->findObject("sum"), "sum", "l");
        legend2->AddEntry(frame_mode_refsb->findObject("pdf_argus"), "ARGUS BG", "l");
        legend2->AddEntry(frame_mode_refsb->findObject("pdf_bkgsb"), "non-resonant BG", "l");
        // legend2->AddEntry(frame_mode_refsb->findObject("pdf_sig"), "signal", "l");
        // legend2->AddEntry("hist_data", "data", "f");
        // legend2->AddEntry("hist_inclusive_sig", "signal", "f");
        // legend2->AddEntry("hist_inclusive_bkg", "#Lambda_{c}#bar{#Lambda_{c}} bkg", "f");
        legend2->SetBorderSize(0);
        legend2->SetFillColor(0);
        legend2->Draw();

        can5->SaveAs("c_sb.png");
        can5->SaveAs("simu_refsb.pdf");

    }

    RooFitResult *result = mm.save();
    result->Print("v");


    
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


    cout << "______________________ " << endl;
    cout << "signal mode, sig = " << nsig_mode0_sig.getVal()+nsig_mode1_sig.getVal()+nsig_mode2_sig.getVal()+nsig_mode3_sig.getVal()+nsig_mode4_sig.getVal()+nsig_mode5_sig.getVal()+nsig_mode6_sig.getVal() << endl;
    cout << "signal mode, bkg = " << nbkg0_sig.getVal()+nbkg1_sig.getVal()+nbkg2_sig.getVal()+nbkg3_sig.getVal()+nbkg4_sig.getVal()+nbkg5_sig.getVal()+nbkg6_sig.getVal() << endl;
    
    cout << "ref mode, sig = " << nsig_mode0.getVal()+nsig_mode1.getVal()+nsig_mode2.getVal()+nsig_mode3.getVal()+nsig_mode4.getVal()+nsig_mode5.getVal()+nsig_mode6.getVal() << endl;
    cout << "ref mode, bkg = " << nbkg0.getVal()+nbkg1.getVal()+nbkg2.getVal()+nbkg3.getVal()+nbkg4.getVal()+nbkg5.getVal()+nbkg6.getVal() << endl;


    // //
    // // //
    Double_t DeltaLL = 2 * fabs(result->minNll() - FCN_bkg);
    Double_t prob = TMath::Prob(DeltaLL, 1);
    Double_t nSigma = sqrt(2) * TMath::ErfcInverse(prob);
    cout << "result->minNll() " << result->minNll() << " " << "|FCN_single - FCN_bkg| = " << DeltaLL << endl;
    cout << " Sigma: " << nSigma << endl;
    return 0;
}
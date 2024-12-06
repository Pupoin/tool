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
// TCut cut_np = "(np !=0 && npbar != 0)";
// TCut cut_mass = "(refm>=0.115&&refm<=0.15) && (refmORsigm1m>=0.115&&refmORsigm1m<=0.15) && (sigmam>=1.174 && sigmam<=1.2) && (dipim<0.48 || dipim>0.52)";
TCut cut_mbc = "((M_BC>=2.25) && (M_BC<=2.34919))";
TCut cut_deltaE_ref = "((deltaE_min>-0.033) && (deltaE_min<0.022))";
TCut cut_deltaE_sig = "((deltaE_min>-0.021) && (deltaE_min<0.015))";
TCut cut_ref = (cut_mbc && cut_deltaE_ref);
TCut cut_sig = (cut_mbc && cut_deltaE_sig);
RooRealVar *M_BC = new RooRealVar("M_BC", "M_BC", mbcmin, mbcmax);


int fit_comb()
{

	TH1::SetDefaultSumw2(1);
	TString a("Events/");
	char b[30];
	sprintf(b, "(%5.1f", (xmax - xmin) / xbins * 1000);
	TString c(" MeV/c^{2})");
	TString ytitle = a + b + c;

	//
	// sig 
	TChain *tr_data0_sig = new TChain("tree");    tr_data0_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/zhou2me/4600data_mass.root");
	TChain *tr_data1_sig = new TChain("tree");    tr_data1_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/zhou2me/4612data_mass.root");
	TChain *tr_data2_sig = new TChain("tree");    tr_data2_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/zhou2me/4620data_mass.root");
	TChain *tr_data3_sig = new TChain("tree");	  tr_data3_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/zhou2me/4640data_mass.root");
	TChain *tr_data4_sig = new TChain("tree");	  tr_data4_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/zhou2me/4660data_mass.root");
	TChain *tr_data5_sig = new TChain("tree");	  tr_data5_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/zhou2me/4680data_mass.root");
	TChain *tr_data6_sig = new TChain("tree");    tr_data6_sig->Add("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/data/cutmassroot/zhou2me/4700data_mass.root");

	// ref
	TChain *tr_data0 = new TChain("tree");    tr_data0->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/zhou2me/4600data_mass.root");
	TChain *tr_data1 = new TChain("tree");    tr_data1->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/zhou2me/4612data_mass.root");
	TChain *tr_data2 = new TChain("tree");    tr_data2->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/zhou2me/4620data_mass.root");
	TChain *tr_data3 = new TChain("tree");	  tr_data3->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/zhou2me/4640data_mass.root");
	TChain *tr_data4 = new TChain("tree");	  tr_data4->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/zhou2me/4660data_mass.root");
	TChain *tr_data5 = new TChain("tree");	  tr_data5->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/zhou2me/4680data_mass.root");
	TChain *tr_data6 = new TChain("tree");    tr_data6->Add("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/zhou2me/4700data_mass.root");

	// ____________________ MC
	TTree *tr_fit0_sig = tr_data0_sig->CopyTree(cut_sig);    RooDataSet *data0_sig = new RooDataSet("data0_sig"," M_BC", tr_fit0_sig, RooArgSet(*M_BC));
	TTree *tr_fit1_sig = tr_data1_sig->CopyTree(cut_sig);    RooDataSet *data1_sig = new RooDataSet("data1_sig", "M_BC", tr_fit1_sig, RooArgSet(*M_BC));
	TTree *tr_fit2_sig = tr_data2_sig->CopyTree(cut_sig);    RooDataSet *data2_sig = new RooDataSet("data2_sig", "M_BC", tr_fit2_sig, RooArgSet(*M_BC));
	TTree *tr_fit3_sig = tr_data3_sig->CopyTree(cut_sig);    RooDataSet *data3_sig = new RooDataSet("data3_sig", "M_BC", tr_fit3_sig, RooArgSet(*M_BC));
	TTree *tr_fit4_sig = tr_data4_sig->CopyTree(cut_sig);    RooDataSet *data4_sig = new RooDataSet("data4_sig", "M_BC", tr_fit4_sig, RooArgSet(*M_BC));
	TTree *tr_fit5_sig = tr_data5_sig->CopyTree(cut_sig);    RooDataSet *data5_sig = new RooDataSet("data5_sig", "M_BC", tr_fit5_sig, RooArgSet(*M_BC));
	TTree *tr_fit6_sig = tr_data6_sig->CopyTree(cut_sig);    RooDataSet *data6_sig = new RooDataSet("data6_sig", "M_BC", tr_fit6_sig, RooArgSet(*M_BC));

	TTree *tr_fit0 = tr_data0->CopyTree(cut_ref);    RooDataSet *data0 = new RooDataSet("data0","M_BC", tr_fit0, RooArgSet(*M_BC));
	TTree *tr_fit1 = tr_data1->CopyTree(cut_ref);    RooDataSet *data1 = new RooDataSet("data1","M_BC", tr_fit1, RooArgSet(*M_BC));
	TTree *tr_fit2 = tr_data2->CopyTree(cut_ref);    RooDataSet *data2 = new RooDataSet("data2", "M_BC", tr_fit2, RooArgSet(*M_BC));
	TTree *tr_fit3 = tr_data3->CopyTree(cut_ref);    RooDataSet *data3 = new RooDataSet("data3", "M_BC", tr_fit3, RooArgSet(*M_BC));
	TTree *tr_fit4 = tr_data4->CopyTree(cut_ref);    RooDataSet *data4 = new RooDataSet("data4", "M_BC", tr_fit4, RooArgSet(*M_BC));
	TTree *tr_fit5 = tr_data5->CopyTree(cut_ref);    RooDataSet *data5 = new RooDataSet("data5", "M_BC", tr_fit5, RooArgSet(*M_BC));
	TTree *tr_fit6 = tr_data6->CopyTree(cut_ref);    RooDataSet *data6 = new RooDataSet("data6", "M_BC", tr_fit6, RooArgSet(*M_BC));

	/*		// sig
			// RooRealVar mean_mode0_sig("mean_mode0_sig", "mean_mode0_sig",  4.0819e-05, -0.003, 0.003);
			// RooRealVar sigma_mode0_sig("sigma_mode0_sig", "sigma_mode0_sig",  1.1335e-05, 0, 0.003);

			// RooRealVar mean_mode1_sig("mean_mode1_sig", "mean_mode1_sig",  2.9999e-03, -0.003, 0.003);
			// RooRealVar sigma_mode1_sig("sigma_mode1_sig", "sigma_mode1_sig",  1.9998e-03, 0, 0.002);

			// RooRealVar mean_mode2_sig("mean_mode2_sig", "mean_mode2_sig",  -1.4412e-03, -0.003, 0.003);
			// RooRealVar sigma_mode2_sig("sigma_mode2_sig", "sigma_mode2_sig",  2.1885e-04, 0, 0.002);

			// RooRealVar mean_mode3_sig("mean_mode3_sig", "mean_mode3_sig",  1.0274e-03, -0.003, 0.003);
			// RooRealVar sigma_mode3_sig("sigma_mode3_sig", "sigma_mode3_sig",  1.2193e-03, 0, 0.002);

			// RooRealVar mean_mode4_sig("mean_mode4_sig", "mean_mode4_sig" ,  8.7235e-04, -0.003, 0.003);
			// RooRealVar sigma_mode4_sig("sigma_mode4_sig", "sigma_mode4_sig",  8.8929e-07,0, 0.001);

			// RooRealVar mean_mode5_sig("mean_mode5_sig", "mean_mode5_sig",  1.5600e-03, -0.003, 0.003);
			// RooRealVar sigma_mode5_sig("sigma_mode5_sig", "sigma_mode5_sig",  1.2833e-03,  0, 0.003);

			// RooRealVar mean_mode6_sig("mean_mode6_sig", "mean_mode6_sig",   3.8853e-04, -0.003, 0.003);
			// RooRealVar sigma_mode6_sig("sigma_mode6_sig", "sigma_mode6_sig", 4.1229e-05, 0, 0.0001);

			// RooGaussModel gauss_mode0_sig("gauss_mode0_sig", "gauss_mode0_sig", *M_BC, mean_mode0_sig, sigma_mode0_sig);
			// RooGaussModel gauss_mode1_sig("gauss_mode1_sig", "gauss_mode1_sig", *M_BC, mean_mode1_sig, sigma_mode1_sig);
			// RooGaussModel gauss_mode2_sig("gauss_mode2_sig", "gauss_mode2_sig", *M_BC, mean_mode2_sig, sigma_mode2_sig);
			// RooGaussModel gauss_mode3_sig("gauss_mode3_sig", "gauss_mode3_sig", *M_BC, mean_mode3_sig, sigma_mode3_sig);
			// RooGaussModel gauss_mode4_sig("gauss_mode4_sig", "gauss_mode4_sig", *M_BC, mean_mode4_sig, sigma_mode4_sig);
			// RooGaussModel gauss_mode5_sig("gauss_mode5_sig", "gauss_mode5_sig", *M_BC, mean_mode5_sig, sigma_mode5_sig);	
			// RooGaussModel gauss_mode6_sig("gauss_mode6_sig", "gauss_mode6_sig", *M_BC, mean_mode6_sig, sigma_mode6_sig);


			// ref
			// RooRealVar mean_mode0("mean_mode0", "mean_mode0",  3.7533e-15);// , 0.0, 0.002);
			// RooRealVar sigma_mode0("sigma_mode0", "sigma_mode0", 5.6453e-04);//,  0, 0.003);

			// RooRealVar mean_mode1("mean_mode1", "mean_mode1", 1.8116e-08);// , -0.00, 0.001);
			// RooRealVar sigma_mode1("sigma_mode1", "sigma_mode1", 5.6888e-05,  0, 0.002);

			// RooRealVar mean_mode2("mean_mode2", "mean_mode2",  -4.3533e-04);//, -0.003, 0.003);
			// RooRealVar sigma_mode2("sigma_mode2", "sigma_mode2", 4.2171e-04,  0, 0.003);

			// RooRealVar mean_mode3("mean_mode3", "mean_mode3",  -1.1315e-04);//, -0.003, 0.003);
			// RooRealVar sigma_mode3("sigma_mode3", "sigma_mode3", 3.7087e-05,  0, 0.003);

			// RooRealVar mean_mode4("mean_mode4", "mean_mode4",  2.0936e-04);//, -0.003, 0.003);
			// RooRealVar sigma_mode4("sigma_mode4", "sigma_mode4", 2.8575e-03,  0, 0.003);

			// RooRealVar mean_mode5("mean_mode5", "mean_mode5", -2.0118e-04);//, -0.003, 0.003);
			// RooRealVar sigma_mode5("sigma_mode5", "sigma_mode5", 1.0652e-03,  0, 0.003);

			// RooRealVar mean_mode6("mean_mode6", "mean_mode6",  2.2919e-11);//,-0.00, 0.003);
			// RooRealVar sigma_mode6("sigma_mode6", "sigma_mode6", 0.7683e-03,  0, 0.003);

			// RooGaussModel gauss_mode0("gauss_mode0", "gauss_mode0", *M_BC, mean_mode0, sigma_mode0);
			// RooGaussModel gauss_mode1("gauss_mode1", "gauss_mode1", *M_BC, mean_mode1, sigma_mode1);
			// RooGaussModel gauss_mode2("gauss_mode2", "gauss_mode2", *M_BC, mean_mode2, sigma_mode2);
			// RooGaussModel gauss_mode3("gauss_mode3", "gauss_mode3", *M_BC, mean_mode3, sigma_mode3);
			// RooGaussModel gauss_mode4("gauss_mode4", "gauss_mode4", *M_BC, mean_mode4, sigma_mode4);
			// RooGaussModel gauss_mode5("gauss_mode5", "gauss_mode5", *M_BC, mean_mode5, sigma_mode5);
			// RooGaussModel gauss_mode6("gauss_mode6", "gauss_mode6", *M_BC, mean_mode6, sigma_mode6);
	*/
	RooRealVar mean_sig("mean_sig", "mean_sig",  4.0819e-05, -0.003, 0.003);
	RooRealVar sigma_sig("sigma_sig", "sigma_sig",  1.1335e-05, 0, 0.003);
	RooGaussModel gauss_sig("gauss_sig", "gauss_sig", *M_BC, mean_sig, sigma_sig);
	
	RooRealVar mean_ref("mean_ref", "mean_ref",  4.0819e-05, -0.003, 0.003);
	RooRealVar refma_ref("refma_ref", "refma_ref",  1.1335e-05, 0, 0.003);
	RooGaussModel gauss_ref("gauss_ref", "gauss_ref", *M_BC, mean_ref, refma_ref);

	// sig-- shape
	TFile *pdf0_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/zhou2me/4600_sig_shapepdf.root"); RooWorkspace *wspace0_sig = (RooWorkspace *)pdf0_sig->Get("wspace"); RooAbsPdf *shapepdf0_sig = wspace0_sig->pdf("modelPdf");
	TFile *pdf1_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/zhou2me/4612_sig_shapepdf.root"); RooWorkspace *wspace1_sig = (RooWorkspace *)pdf1_sig->Get("wspace"); RooAbsPdf *shapepdf1_sig = wspace1_sig->pdf("modelPdf");
	TFile *pdf2_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/zhou2me/4620_sig_shapepdf.root"); RooWorkspace *wspace2_sig = (RooWorkspace *)pdf2_sig->Get("wspace"); RooAbsPdf *shapepdf2_sig = wspace2_sig->pdf("modelPdf");
	TFile *pdf3_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/zhou2me/4640_sig_shapepdf.root"); RooWorkspace *wspace3_sig = (RooWorkspace *)pdf3_sig->Get("wspace"); RooAbsPdf *shapepdf3_sig = wspace3_sig->pdf("modelPdf");
	TFile *pdf4_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/zhou2me/4660_sig_shapepdf.root"); RooWorkspace *wspace4_sig = (RooWorkspace *)pdf4_sig->Get("wspace"); RooAbsPdf *shapepdf4_sig = wspace4_sig->pdf("modelPdf");
	TFile *pdf5_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/zhou2me/4680_sig_shapepdf.root"); RooWorkspace *wspace5_sig = (RooWorkspace *)pdf5_sig->Get("wspace"); RooAbsPdf *shapepdf5_sig = wspace5_sig->pdf("modelPdf");
	TFile *pdf6_sig = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/pdf/zhou2me/4700_sig_shapepdf.root"); RooWorkspace *wspace6_sig = (RooWorkspace *)pdf6_sig->Get("wspace"); RooAbsPdf *shapepdf6_sig = wspace6_sig->pdf("modelPdf");

	// ref-- shape
	TFile *pdf0 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/zhou2me/4612_ref_shapepdf.root"); RooWorkspace *wspace0 = (RooWorkspace *)pdf0->Get("wspace"); RooAbsPdf *shapepdf0 = wspace0->pdf("modelPdf");
	TFile *pdf1 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/zhou2me/4612_ref_shapepdf.root"); RooWorkspace *wspace1 = (RooWorkspace *)pdf1->Get("wspace"); RooAbsPdf *shapepdf1 = wspace1->pdf("modelPdf");
	TFile *pdf2 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/zhou2me/4620_ref_shapepdf.root"); RooWorkspace *wspace2 = (RooWorkspace *)pdf2->Get("wspace"); RooAbsPdf *shapepdf2 = wspace2->pdf("modelPdf");
	TFile *pdf3 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/zhou2me/4640_ref_shapepdf.root"); RooWorkspace *wspace3 = (RooWorkspace *)pdf3->Get("wspace"); RooAbsPdf *shapepdf3 = wspace3->pdf("modelPdf");
	TFile *pdf4 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/zhou2me/4660_ref_shapepdf.root"); RooWorkspace *wspace4 = (RooWorkspace *)pdf4->Get("wspace"); RooAbsPdf *shapepdf4 = wspace4->pdf("modelPdf");
	TFile *pdf5 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/zhou2me/4680_ref_shapepdf.root"); RooWorkspace *wspace5 = (RooWorkspace *)pdf5->Get("wspace"); RooAbsPdf *shapepdf5 = wspace5->pdf("modelPdf");
	TFile *pdf6 = new TFile("/publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/zhou2me/4700_ref_shapepdf.root"); RooWorkspace *wspace6 = (RooWorkspace *)pdf6->Get("wspace"); RooAbsPdf *shapepdf6 = wspace6->pdf("modelPdf");

	// sig-- shape x guass
	RooAbsPdf *sigpdf0_sig = new RooFFTConvPdf("sigpdf0_sig", "modelPdf (X) gauss", *M_BC, *shapepdf0_sig, gauss_sig);
	RooAbsPdf *sigpdf1_sig = new RooFFTConvPdf("sigpdf1_sig", "modelPdf (X) gauss", *M_BC, *shapepdf1_sig, gauss_sig);
	RooAbsPdf *sigpdf2_sig = new RooFFTConvPdf("sigpdf2_sig", "modelPdf (X) gauss", *M_BC, *shapepdf2_sig, gauss_sig);
	RooAbsPdf *sigpdf3_sig = new RooFFTConvPdf("sigpdf3_sig", "modelPdf (X) gauss", *M_BC, *shapepdf3_sig, gauss_sig);
	RooAbsPdf *sigpdf4_sig = new RooFFTConvPdf("sigpdf4_sig", "modelPdf (X) gauss", *M_BC, *shapepdf4_sig, gauss_sig);
	RooAbsPdf *sigpdf5_sig = new RooFFTConvPdf("sigpdf5_sig", "modelPdf (X) gauss", *M_BC, *shapepdf5_sig, gauss_sig);
	RooAbsPdf *sigpdf6_sig = new RooFFTConvPdf("sigpdf6_sig", "modelPdf (X) gauss", *M_BC, *shapepdf6_sig, gauss_sig);


	// ref-- shape x guass
	RooAbsPdf *sigpdf0 = new RooFFTConvPdf("sigpdf0", "modelPdf (X) gauss", *M_BC, *shapepdf0, gauss_ref);
	RooAbsPdf *sigpdf1 = new RooFFTConvPdf("sigpdf1", "modelPdf (X) gauss", *M_BC, *shapepdf1, gauss_ref);
	RooAbsPdf *sigpdf2 = new RooFFTConvPdf("sigpdf2", "modelPdf (X) gauss", *M_BC, *shapepdf2, gauss_ref);
	RooAbsPdf *sigpdf3 = new RooFFTConvPdf("sigpdf3", "modelPdf (X) gauss", *M_BC, *shapepdf3, gauss_ref);
	RooAbsPdf *sigpdf4 = new RooFFTConvPdf("sigpdf4", "modelPdf (X) gauss", *M_BC, *shapepdf4, gauss_ref);
	RooAbsPdf *sigpdf5 = new RooFFTConvPdf("sigpdf5", "modelPdf (X) gauss", *M_BC, *shapepdf5, gauss_ref);
	RooAbsPdf *sigpdf6 = new RooFFTConvPdf("sigpdf6", "modelPdf (X) gauss", *M_BC, *shapepdf6, gauss_ref);

	// ____________________ sig argus background
	RooRealVar m0_sig("m0_sig", "m0_sig", 2.299765);   RooRealVar c0_sig("c0_sig", "c0_sig", -2.1266e+01, -50, 50);    RooArgusBG argus0_sig("argus0_sig", "argus0 sig", *M_BC, m0_sig, c0_sig);
	RooRealVar m1_sig("m1_sig", "m1_sig", 2.30579);    RooRealVar c1_sig("c1_sig", "c1_sig", -6.0660e+00, -50, 50);    RooArgusBG argus1_sig("argus1_sig", "argus1 sig", *M_BC, m1_sig, c1_sig);
	RooRealVar m2_sig("m2_sig", "m2_sig", 2.31387);    RooRealVar c2_sig("c2_sig", "c2_sig", -4.9716e+00, -50, 50);    RooArgusBG argus2_sig("argus2_sig", "argus2 sig", *M_BC, m2_sig, c2_sig);
	RooRealVar m3_sig("m3_sig", "m3_sig", 2.320255);   RooRealVar c3_sig("c3_sig", "c3_sig", -2.4289e+00, -50, 50);    RooArgusBG argus3_sig("argus3_sig", "argus3 sig", *M_BC, m3_sig, c3_sig);
	RooRealVar m4_sig("m4_sig", "m4_sig", 2.33046);    RooRealVar c4_sig("c4_sig", "c4_sig", -2.2689e+01, -50, 50);    RooArgusBG argus4_sig("argus4_sig", "argus4 sig", *M_BC, m4_sig, c4_sig);
	RooRealVar m5_sig("m5_sig", "m5_sig", 2.34079);    RooRealVar c5_sig("c5_sig", "c5_sig", -9.3432e+00, -50, 50);    RooArgusBG argus5_sig("argus5_sig", "argus5 sig", *M_BC, m5_sig, c5_sig);
	RooRealVar m6_sig("m6_sig", "m6_sig", 2.34919);    RooRealVar c6_sig("c6_sig", "c6_sig", -7.9593e+00, -50, 50);    RooArgusBG argus6_sig("argus6_sig", "argus6 sig", *M_BC, m6_sig, c6_sig);

	// ____________________ ref argus background
	RooRealVar m0("m0", "m0", 2.299765);   RooRealVar c0("c0", "c0", 1.5143e+00,  -50, 50);    RooArgusBG argus0("argus0", "argus0", *M_BC, m0, c0);
	RooRealVar m1("m1", "m1", 2.30579);    RooRealVar c1("c1", "c1", 1.4943e+01,  -50, 50);    RooArgusBG argus1("argus1", "argus1", *M_BC, m1, c1);
	RooRealVar m2("m2", "m2", 2.31387);    RooRealVar c2("c2", "c2", 2.9315e+00,  -50, 50);    RooArgusBG argus2("argus2", "argus2", *M_BC, m2, c2);
	RooRealVar m3("m3", "m3", 2.320255);   RooRealVar c3("c3", "c3", -3.1054e+00, -50, 50);    RooArgusBG argus3("argus3", "argus3", *M_BC, m3, c3);
	RooRealVar m4("m4", "m4", 2.33046);    RooRealVar c4("c4", "c4", -4.8423e+00, -50, 50);    RooArgusBG argus4("argus4", "argus4", *M_BC, m4, c4);
	RooRealVar m5("m5", "m5", 2.34079);    RooRealVar c5("c5", "c5", -4.3007e+00, -50, 50);    RooArgusBG argus5("argus5", "argus5", *M_BC, m5, c5);
	RooRealVar m6("m6", "m6", 2.34919);    RooRealVar c6("c6", "c6", -5.4013e+00, -50, 50);    RooArgusBG argus6("argus6", "argus6", *M_BC, m6, c6);

	// ____________________ ref signal/bkg num
	RooRealVar nsig_mode0("nsig_mode0", "signal of mode0", /*0, 00, 100 */0.05 * tr_fit0->GetEntries(), 0, 1.2 * tr_fit0->GetEntries());    RooRealVar nbkg0("nbkg0", "bkg number of mode0", /*00, 0, 150 */0.05 * tr_fit0->GetEntries(), 0, 1.2 * tr_fit0->GetEntries());
	RooRealVar nsig_mode1("nsig_mode1", "signal of mode1", /*02, 0, 40  */0.05 * tr_fit1->GetEntries(), 0, 1.2 * tr_fit1->GetEntries());    RooRealVar nbkg1("nbkg1", "bkg number of mode1", /*8, 0, 50   */0.05 * tr_fit1->GetEntries(), 0, 1.2 * tr_fit1->GetEntries());	
	RooRealVar nsig_mode2("nsig_mode2", "signal of mode2", /*04, 0, 100 */0.05 * tr_fit2->GetEntries(), 0, 1.2 * tr_fit2->GetEntries());    RooRealVar nbkg2("nbkg2", "bkg number of mode2", /*5, 0, 150  */0.05 * tr_fit2->GetEntries(), 0, 1.2 * tr_fit2->GetEntries());
	RooRealVar nsig_mode3("nsig_mode3", "signal of mode3", /*8, 0, 100  */0.05 * tr_fit3->GetEntries(), 0, 1.2 * tr_fit3->GetEntries());    RooRealVar nbkg3("nbkg3", "bkg number of mode3", /*0, 0, 180  */0.05 * tr_fit3->GetEntries(), 0, 1.2 * tr_fit3->GetEntries());
	RooRealVar nsig_mode4("nsig_mode4", "signal of mode4", /*19, 0, 100 */0.05 * tr_fit4->GetEntries(), 0, 1.2 * tr_fit4->GetEntries());    RooRealVar nbkg4("nbkg4", "bkg number of mode4", /*19, 10, 160*/0.05 * tr_fit4->GetEntries(), 0, 1.2 * tr_fit4->GetEntries());
	RooRealVar nsig_mode5("nsig_mode5", "signal of mode5", /*6, 0, 300  */0.05 * tr_fit4->GetEntries(), 0, 1.2 * tr_fit4->GetEntries());    RooRealVar nbkg5("nbkg5", "bkg number of mode5", /*51, 00, 600*/0.05 * tr_fit5->GetEntries(), 0, 1.2 * tr_fit5->GetEntries());
	RooRealVar nsig_mode6("nsig_mode6", "signal of mode6", /*01, 0, 100 */0.05 * tr_fit6->GetEntries(), 0, 1.2 * tr_fit6->GetEntries());    RooRealVar nbkg6("nbkg6", "bkg number of mode6", /*17, 10, 185*/0.05 * tr_fit6->GetEntries(), 0, 1.2 * tr_fit6->GetEntries());
	
	// ____________________ sig signal/bkg num
	double Br_sig_inter = 0.085560; 
	double Br_ref_inter = 0.44924;

	RooRealVar Bratio("Bratio", "Br of sig/ref", 0.2, 0.1, 1);	
	// RooRealVar Bratio("Bratio", "Br of sig/ref", 0);	
	RooFormulaVar nsig_mode0_sig("nsig_mode0_sig", "signal of mode0 sig", "Bratio * nsig_mode0* 0.085560  *0.0564/  0.44924  /0.0591", RooArgSet(Bratio, nsig_mode0 ));	RooRealVar nbkg0_sig("nbkg0_sig", "bkg number of mode0 sig", /*23, 10, 50  */ 0.05 * tr_fit0_sig->GetEntries(), 0, 1.2 * tr_fit0_sig->GetEntries());
	RooFormulaVar nsig_mode1_sig("nsig_mode1_sig", "signal of mode1 sig", "Bratio * nsig_mode1* 0.085560  *0.0517/  0.44924  /0.0565", RooArgSet(Bratio, nsig_mode1 ));	RooRealVar nbkg1_sig("nbkg1_sig", "bkg number of mode1 sig", /*23, 10, 50  */ 0.05 * tr_fit1_sig->GetEntries(), 0, 1.1 * tr_fit1_sig->GetEntries());
	RooFormulaVar nsig_mode2_sig("nsig_mode2_sig", "signal of mode2 sig", "Bratio * nsig_mode2* 0.085560  *0.0525/  0.44924  /0.0546", RooArgSet(Bratio, nsig_mode2 ));	RooRealVar nbkg2_sig("nbkg2_sig", "bkg number of mode2 sig", /*23, 10, 50  */ 0.05 * tr_fit2_sig->GetEntries(), 0, 1.2 * tr_fit2_sig->GetEntries());
	RooFormulaVar nsig_mode3_sig("nsig_mode3_sig", "signal of mode3 sig", "Bratio * nsig_mode3* 0.085560  *0.0529/  0.44924  /0.0559", RooArgSet(Bratio, nsig_mode3 ));	RooRealVar nbkg3_sig("nbkg3_sig", "bkg number of mode3 sig", /*19, 10, 50  */ 0.05 * tr_fit3_sig->GetEntries(), 0, 1.2 * tr_fit3_sig->GetEntries());
	RooFormulaVar nsig_mode4_sig("nsig_mode4_sig", "signal of mode4 sig", "Bratio * nsig_mode4* 0.085560  *0.0516/  0.44924  /0.0550", RooArgSet(Bratio, nsig_mode4 ));	RooRealVar nbkg4_sig("nbkg4_sig", "bkg number of mode4 sig", /*28, 10, 50  */ 0.05 * tr_fit4_sig->GetEntries(), 0, 1.2 * tr_fit4_sig->GetEntries());
	RooFormulaVar nsig_mode5_sig("nsig_mode5_sig", "signal of mode5 sig", "Bratio * nsig_mode5* 0.085560  *0.0514/  0.44924  /0.0548", RooArgSet(Bratio, nsig_mode5 ));	RooRealVar nbkg5_sig("nbkg5_sig", "bkg number of mode5 sig", /*102, 10, 150*/ 0.05 * tr_fit5_sig->GetEntries(), 0, 1.2 * tr_fit5_sig->GetEntries());
	RooFormulaVar nsig_mode6_sig("nsig_mode6_sig", "signal of mode6 sig", "Bratio * nsig_mode6* 0.085560  *0.0513/  0.44924  /0.0533", RooArgSet(Bratio, nsig_mode6 ));	RooRealVar nbkg6_sig("nbkg6_sig", "bkg number of mode6 sig", /*30, 10, 50  */ 0.05 * tr_fit6_sig->GetEntries(), 0, 1.2 * tr_fit6_sig->GetEntries());



	//
	// ____________________
	M_BC->setRange("fitrange", 2.25, 2.34919);
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
	
		// RooPlot *frame_mode0 = M_BC->frame(2.25, 2.35, 20);
		// frame_mode0->SetXTitle("M_BC #pi0 4600");
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
	TCanvas *can = new TCanvas("can", "simu fit", 400*2 * 1.8, 300*7 * 1.8); //setPad();
	can->Divide(2, 7);
	can->SetFillColor(0);
	// sig 4600
	RooPlot *frame_mode0_sig = M_BC->frame(xmin, 2.3, 20);
	frame_mode0_sig->SetXTitle("M_BC (GeV)");
	frame_mode0_sig->SetTitle("#sqrt{s}=4.6 GeV, 567 pb^{-1}");
	frame_mode0_sig->SetYTitle(ytitle);
	frame_mode0_sig->GetYaxis()->SetTitleOffset(1.2);
	frame_mode0_sig->GetYaxis()->SetTitleSize(0.04);
	frame_mode0_sig->GetXaxis()->SetTitleSize(0.04);
	data0_sig->plotOn(frame_mode0_sig, LineWidth(2));
	model0_sig->plotOn(frame_mode0_sig, LineColor(kRed), LineWidth(3));
	model0_sig->plotOn(frame_mode0_sig, Components("*sigpdf0_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
	model0_sig->plotOn(frame_mode0_sig, Components("argus0_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
	can->cd(1);  
	frame_mode0_sig->Draw();
	gPad->Update();
	TPaveText* title = (TPaveText*)gPad->FindObject("title");
	title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta'");
	title->SetTextAlign(12);
	title->SetX1NDC(0.12);
	title->SetY1NDC(0.72);
	title->SetX2NDC(0.5);
	title->SetY2NDC(0.86);
	gPad->Modified();
	gPad->Update();
	// ref 4600
	RooPlot *frame_mode0 = M_BC->frame( xmin, 2.3, 20);
	frame_mode0->SetXTitle("M_BC (GeV)");
	frame_mode0->SetYTitle(ytitle);
	frame_mode0->SetTitle("#sqrt{s}=4.6 GeV, 567 pb^{-1}");
	frame_mode0->GetYaxis()->SetTitleOffset(1.2);
	frame_mode0->GetYaxis()->SetTitleSize(0.04);
	frame_mode0->GetXaxis()->SetTitleSize(0.04);
	data0->plotOn(frame_mode0, LineWidth(2));
	model0->plotOn(frame_mode0, LineColor(kRed), LineWidth(3));
	model0->plotOn(frame_mode0, Components("*sigpdf0"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
	model0->plotOn(frame_mode0, Components("argus0"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
	can->cd(2);  
	frame_mode0->Draw();
	gPad->Update();
    title = (TPaveText*)gPad->FindObject("title");
	title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #omega");
	title->SetTextAlign(12);
	title->SetX1NDC(0.12);
	title->SetY1NDC(0.72);
	title->SetX2NDC(0.5);
	title->SetY2NDC(0.86);
	gPad->Modified();
	gPad->Update();

	// sig 4612
	RooPlot *frame_mode1_sig = M_BC->frame(xmin, 2.30579, 20);
	frame_mode1_sig->SetXTitle("M_BC (GeV)");
	frame_mode1_sig->SetYTitle(ytitle);
	frame_mode1_sig->SetTitle("#sqrt{s}=4.612 GeV, 102 pb^{-1}");
	frame_mode1_sig->GetYaxis()->SetTitleOffset(1.2);
	frame_mode1_sig->GetYaxis()->SetTitleSize(0.04);
	frame_mode1_sig->GetXaxis()->SetTitleSize(0.04);
	data1_sig->plotOn(frame_mode1_sig, LineWidth(2));
	model1_sig->plotOn(frame_mode1_sig, LineColor(kRed), LineWidth(3));
	model1_sig->plotOn(frame_mode1_sig, Components("*sigpdf1_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
	model1_sig->plotOn(frame_mode1_sig, Components("argus1_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
	can->cd(3);  
	frame_mode1_sig->Draw();
	gPad->Update();
	title = (TPaveText*)gPad->FindObject("title");
	title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta'");
	title->SetTextAlign(12);
	title->SetX1NDC(0.12);
	title->SetY1NDC(0.72);
	title->SetX2NDC(0.5);
	title->SetY2NDC(0.86);
	gPad->Modified();
	gPad->Update();
	// ref 4612
	RooPlot *frame_mode1 = M_BC->frame( xmin, 2.30579, 20);
	frame_mode1->SetXTitle("M_BC (GeV)");
	frame_mode1->SetYTitle(ytitle);
	frame_mode1->SetTitle("#sqrt{s}=4.612 GeV, 102 pb^{-1}");
	frame_mode1->GetYaxis()->SetTitleOffset(1.2);
	frame_mode1->GetYaxis()->SetTitleSize(0.04);
	frame_mode1->GetXaxis()->SetTitleSize(0.04);
	data1->plotOn(frame_mode1, LineWidth(1));
	model1->plotOn(frame_mode1, LineColor(kRed), LineWidth(3));
	model1->plotOn(frame_mode1, Components("*sigpdf1"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
	model1->plotOn(frame_mode1, Components("argus1"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
	can->cd(4);  
	frame_mode1->Draw();
	gPad->Update();
	title = (TPaveText*)gPad->FindObject("title");
	title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #omega");
	title->SetTextAlign(12);
	title->SetX1NDC(0.12);
	title->SetY1NDC(0.72);
	title->SetX2NDC(0.5);
	title->SetY2NDC(0.86);
	gPad->Modified();
	gPad->Update();

	// sig 4620
	RooPlot *frame_mode2_sig = M_BC->frame(xmin, 2.31387, 20);
	frame_mode2_sig->SetXTitle("M_BC (GeV)");
	frame_mode2_sig->SetYTitle(ytitle);
	frame_mode2_sig->SetTitle("#sqrt{s}=4.627 GeV, 517 pb^{-1}");
	frame_mode2_sig->GetYaxis()->SetTitleOffset(1.2);
	frame_mode2_sig->GetYaxis()->SetTitleSize(0.04);
	frame_mode2_sig->GetXaxis()->SetTitleSize(0.04);
	data2_sig->plotOn(frame_mode2_sig, LineWidth(2));
	model2_sig->plotOn(frame_mode2_sig, LineColor(kRed), LineWidth(3));
	model2_sig->plotOn(frame_mode2_sig, Components("*sigpdf2_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
	model2_sig->plotOn(frame_mode2_sig, Components("argus2_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
	can->cd(5);  
	frame_mode2_sig->Draw();
	gPad->Update();
	title = (TPaveText*)gPad->FindObject("title");
	title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta'");
	title->SetTextAlign(12);
	title->SetX1NDC(0.12);
	title->SetY1NDC(0.72);
	title->SetX2NDC(0.5);
	title->SetY2NDC(0.86);
	gPad->Modified();
	gPad->Update();
	// ref 4620
	RooPlot *frame_mode2 = M_BC->frame( xmin, 2.31387, 20);
	frame_mode2->SetXTitle("M_BC (GeV)");
	frame_mode2->SetYTitle(ytitle);
	frame_mode2->SetTitle("#sqrt{s}=4.627 GeV, 517 pb^{-1}");
	frame_mode2->GetYaxis()->SetTitleOffset(1.2);
	frame_mode2->GetYaxis()->SetTitleSize(0.04);
	frame_mode2->GetXaxis()->SetTitleSize(0.04);
	data2->plotOn(frame_mode2, LineWidth(2));
	model2->plotOn(frame_mode2, LineColor(kRed), LineWidth(3));
	model2->plotOn(frame_mode2, Components("*sigpdf2"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
	model2->plotOn(frame_mode2, Components("argus2"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
	can->cd(6);  
	frame_mode2->Draw();
	gPad->Update();
	title = (TPaveText*)gPad->FindObject("title");
	title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #omega");
	title->SetTextAlign(12);
	title->SetX1NDC(0.12);
	title->SetY1NDC(0.72);
	title->SetX2NDC(0.5);
	title->SetY2NDC(0.86);
	gPad->Modified();
	gPad->Update();
	
	// sig 4640
	RooPlot *frame_mode3_sig = M_BC->frame(xmin, 2.3202550, 25);
	frame_mode3_sig->SetXTitle("M_BC (GeV)");
	frame_mode3_sig->SetYTitle(ytitle);
	frame_mode3_sig->SetTitle("#sqrt{s}=4.64 GeV, 537 pb^{-1}");
	frame_mode3_sig->GetYaxis()->SetTitleOffset(1.2);
	frame_mode3_sig->GetYaxis()->SetTitleSize(0.04);
	frame_mode3_sig->GetXaxis()->SetTitleSize(0.04);
	data3_sig->plotOn(frame_mode3_sig, LineWidth(2));
	model3_sig->plotOn(frame_mode3_sig, LineColor(kRed), LineWidth(3));
	model3_sig->plotOn(frame_mode3_sig, Components("*sigpdf3_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
	model3_sig->plotOn(frame_mode3_sig, Components("argus3_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
	can->cd(7);  
	frame_mode3_sig->Draw();
	gPad->Update();
	title = (TPaveText*)gPad->FindObject("title");
	title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta'");
	title->SetTextAlign(12);
	title->SetX1NDC(0.12);
	title->SetY1NDC(0.72);
	title->SetX2NDC(0.5);
	title->SetY2NDC(0.86);
	gPad->Modified();
	gPad->Update();
	// ref 4640
	RooPlot *frame_mode3 = M_BC->frame( xmin, 2.3202550, 25);
	frame_mode3->SetXTitle("M_BC (GeV)");
	frame_mode3->SetYTitle(ytitle);
	frame_mode3->SetTitle("#sqrt{s}=4.64 GeV, 537 pb^{-1}");
	frame_mode3->GetYaxis()->SetTitleOffset(1.2);
	frame_mode3->GetYaxis()->SetTitleSize(0.04);
	frame_mode3->GetXaxis()->SetTitleSize(0.04);
	data3->plotOn(frame_mode3, LineWidth(2));
	model3->plotOn(frame_mode3, LineColor(kRed), LineWidth(3));
	model3->plotOn(frame_mode3, Components("*sigpdf3"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
	model3->plotOn(frame_mode3, Components("argus3"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
	can->cd(8);  
	frame_mode3->Draw();
	gPad->Update();
	title = (TPaveText*)gPad->FindObject("title");
	title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #omega");
	title->SetTextAlign(12);
	title->SetX1NDC(0.12);
	title->SetY1NDC(0.72);
	title->SetX2NDC(0.5);
	title->SetY2NDC(0.86);
	gPad->Modified();	
	gPad->Update();
	// can->SaveAs("svg_fit_comb.svg");

	//   ------             ----               ----
	// TCanvas *can2 = new TCanvas("can2", "simu fit2", 800, 900); //setPad();
	// can2->Divide(2, 3);
	// can2->SetFillColor(0);
	// sig 4660
	RooPlot *frame_mode4_sig = M_BC->frame(xmin, 2.3304600, 25);
	frame_mode4_sig->SetXTitle("M_BC (GeV)");
	frame_mode4_sig->SetYTitle(ytitle);
	frame_mode4_sig->SetTitle("#sqrt{s}=4.66 GeV, 523 pb^{-1}");
	frame_mode4_sig->GetYaxis()->SetTitleOffset(1.2);
	frame_mode4_sig->GetYaxis()->SetTitleSize(0.04);
	frame_mode4_sig->GetXaxis()->SetTitleSize(0.04);
	data4_sig->plotOn(frame_mode4_sig, LineWidth(2));
	model4_sig->plotOn(frame_mode4_sig, LineColor(kRed), LineWidth(3));
	model4_sig->plotOn(frame_mode4_sig, Components("*sigpdf4_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
	model4_sig->plotOn(frame_mode4_sig, Components("argus4_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
	can->cd(9);  
	frame_mode4_sig->Draw();
	gPad->Update();
	title = (TPaveText*)gPad->FindObject("title");
	title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta'");
	title->SetTextAlign(12);
	title->SetX1NDC(0.12);
	title->SetY1NDC(0.72);
	title->SetX2NDC(0.5);
	title->SetY2NDC(0.86);
	gPad->Modified();
	gPad->Update();	
	// ref 4660
	RooPlot *frame_mode4 = M_BC->frame( xmin, 2.3304600, 25);
	frame_mode4->SetXTitle("M_BC (GeV)");
	frame_mode4->SetYTitle(ytitle);
	frame_mode4->SetTitle("#sqrt{s}=4.66 GeV, 523 pb^{-1}");
	frame_mode4->GetYaxis()->SetTitleOffset(1.2);
	frame_mode4->GetYaxis()->SetTitleSize(0.04);
	frame_mode4->GetXaxis()->SetTitleSize(0.04);
	data4->plotOn(frame_mode4, LineWidth(2));
	model4->plotOn(frame_mode4, LineColor(kRed), LineWidth(3));
	model4->plotOn(frame_mode4, Components("*sigpdf4"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
	model4->plotOn(frame_mode4, Components("argus4"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
	can->cd(10);  
	frame_mode4->Draw();
	gPad->Update();
	title = (TPaveText*)gPad->FindObject("title");
	title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #omega");
	title->SetTextAlign(12);
	title->SetX1NDC(0.12);
	title->SetY1NDC(0.72);
	title->SetX2NDC(0.5);
	title->SetY2NDC(0.86);
	gPad->Modified();	
	gPad->Update();
	
	// sig 4680
	RooPlot *frame_mode5_sig = M_BC->frame( xmin, 2.3407900, 30);
	frame_mode5_sig->SetXTitle("M_BC (GeV)");
	frame_mode5_sig->SetYTitle(ytitle);
	frame_mode5_sig->SetTitle("#sqrt{s}=4.68 GeV, 1657 pb^{-1}");
	frame_mode5_sig->GetYaxis()->SetTitleOffset(1.2);
	frame_mode5_sig->GetYaxis()->SetTitleSize(0.04);
	frame_mode5_sig->GetXaxis()->SetTitleSize(0.04);
	data5_sig->plotOn(frame_mode5_sig, LineWidth(2));
	model5_sig->plotOn(frame_mode5_sig, LineColor(kRed), LineWidth(3));
	model5_sig->plotOn(frame_mode5_sig, Components("*sigpdf5_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
	model5_sig->plotOn(frame_mode5_sig, Components("argus5_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
	can->cd(11);  
	frame_mode5_sig->Draw();
	gPad->Update();
	title = (TPaveText*)gPad->FindObject("title");
	title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta'");
	title->SetTextAlign(12);
	title->SetX1NDC(0.12);
	title->SetY1NDC(0.72);
	title->SetX2NDC(0.5);
	title->SetY2NDC(0.86);
	gPad->Modified();	
	gPad->Update();
	// ref 4680
	RooPlot *frame_mode5 = M_BC->frame( xmin, 2.3407900, 30);
	frame_mode5->SetXTitle("M_BC (GeV)");
	frame_mode5->SetYTitle(ytitle);
	frame_mode5->SetTitle("#sqrt{s}=4.68 GeV, 1657 pb^{-1}");
	frame_mode5->GetYaxis()->SetTitleOffset(1.2);
	frame_mode5->GetYaxis()->SetTitleSize(0.04);
	frame_mode5->GetXaxis()->SetTitleSize(0.04);
	data5->plotOn(frame_mode5, LineWidth(2));
	model5->plotOn(frame_mode5, LineColor(kRed), LineWidth(3));
	model5->plotOn(frame_mode5, Components("*sigpdf5"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
	model5->plotOn(frame_mode5, Components("argus5"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
	can->cd(12);  
	frame_mode5->Draw();
	gPad->Update();
	title = (TPaveText*)gPad->FindObject("title");
	title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #omega");
	title->SetTextAlign(12);
	title->SetX1NDC(0.12);
	title->SetY1NDC(0.72);
	title->SetX2NDC(0.5);
	title->SetY2NDC(0.86);
	gPad->Modified();	
	gPad->Update();
	
	
	// sig 4700
	RooPlot *frame_mode6_sig = M_BC->frame( xmin, 2.34919, 30);
	frame_mode6_sig->SetXTitle("M_BC (GeV)");
	frame_mode6_sig->SetYTitle(ytitle);
	frame_mode6_sig->SetTitle("#sqrt{s}=4.70 GeV, 532 pb^{-1}");
	frame_mode6_sig->GetYaxis()->SetTitleOffset(1.2);
	frame_mode6_sig->GetYaxis()->SetTitleSize(0.04);
	frame_mode6_sig->GetXaxis()->SetTitleSize(0.04);
	data6_sig->plotOn(frame_mode6_sig, LineWidth(2));
	model6_sig->plotOn(frame_mode6_sig, LineColor(kRed), LineWidth(3));
	model6_sig->plotOn(frame_mode6_sig, Components("*sigpdf6_sig"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
	model6_sig->plotOn(frame_mode6_sig, Components("argus6_sig"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
	can->cd(13);  
	frame_mode6_sig->Draw();
	gPad->Update();
	title = (TPaveText*)gPad->FindObject("title");
	title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta'");
	title->SetTextAlign(12);
	title->SetX1NDC(0.12);
	title->SetY1NDC(0.72);
	title->SetX2NDC(0.5);
	title->SetY2NDC(0.86);
	gPad->Modified();
	gPad->Update();
	// ref 4700
	RooPlot *frame_mode6 = M_BC->frame( xmin, 2.34919, 30);
	frame_mode6->SetXTitle("M_BC (GeV)");
	frame_mode6->SetYTitle(ytitle);
	frame_mode6->SetTitle("#sqrt{s}=4.70 GeV, 532 pb^{-1}");
	frame_mode6->GetYaxis()->SetTitleOffset(1.2);
	frame_mode6->GetYaxis()->SetTitleSize(0.04);
	frame_mode6->GetXaxis()->SetTitleSize(0.04);
	data6->plotOn(frame_mode6, LineWidth(2));
	model6->plotOn(frame_mode6, LineColor(kRed), LineWidth(3));
	model6->plotOn(frame_mode6, Components("*sigpdf6"), LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
	model6->plotOn(frame_mode6, Components("argus6"), LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
	can->cd(14);  
	frame_mode6->Draw();
	gPad->Update();
	title = (TPaveText*)gPad->FindObject("title");
	title->InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #omega");
	title->SetTextAlign(12);
	title->SetX1NDC(0.12);
	title->SetY1NDC(0.72);
	title->SetX2NDC(0.5);
	title->SetY2NDC(0.86);
	gPad->Modified();
	gPad->Update();
	// can->SaveAs("svg_fit_comb.pdf");
	can->SaveAs("svg_fit_comb.png");

	TCanvas *can3 = new TCanvas("can3", "simu fit3", 800, 600); 
	can3->SetFillColor(0);
	can3->cd();

	
	// RooAddPdf *sigpdf = new RooAddPdf("sigpdf", "sigpdf", RooArgList(*sigpdf_sig,*sigpdf_bkg));
	
	RooCategory combine("combine", "combine");
	combine.defineType("mode0");
	combine.defineType("mode1");
	combine.defineType("mode2");
	combine.defineType("mode3");
	combine.defineType("mode4");
	combine.defineType("mode5");
	combine.defineType("mode6");

	RooDataSet *combData = new RooDataSet("combData", "combined data", *M_BC, Index(combine), 
			Import("mode0", *data0_sig), Import("mode1", *data1_sig), Import("mode2", *data2_sig), Import("mode3", *data3_sig), 
			Import("mode4", *data4_sig), Import("mode5", *data5_sig), Import("mode6", *data6_sig));

	// ref
	// RooAddPdf *model0 = new RooAddPdf("model0", "model0", RooArgList(*sigpdf0, argus0), RooArgList(nsig_mode0, nbkg0));

	RooRealVar frac("frac", "fraction of component in signal", 1);


	RooAddPdf *sigpdf_sig = new RooAddPdf("sigpdf_sig", "sigpdf_sig", RooArgList(*sigpdf0_sig, *sigpdf1_sig, *sigpdf2_sig, *sigpdf3_sig, *sigpdf4_sig, *sigpdf5_sig, *sigpdf6_sig ), 
																      RooArgList(frac, frac, frac, frac, frac, frac, frac), kTRUE);
	// RooAddPdf *sigpdf_bkg = new RooAddPdf("sigpdf_bkg", "sigpdf_bkg", RooArgList(argus0_sig, argus1_sig, argus2_sig, argus3_sig, argus4_sig, argus5_sig, argus6_sig ), 
	// 															      RooArgList(nbkg0_sig, nbkg1_sig, nbkg2_sig, nbkg3_sig, nbkg4_sig, nbkg5_sig, nbkg6_sig), kTRUE);


	RooPlot *frame_mode_ref = M_BC->frame( xmin, 2.34919, 30);
	frame_mode_ref->SetXTitle("M_BC (GeV)");
	frame_mode_ref->SetYTitle(ytitle);
	// frame_mode_ref->SetTitle("#sqrt{s}=4.70 GeV, 532 pb^{-1}");
	frame_mode_ref->GetYaxis()->SetTitleOffset(1.2);
	frame_mode_ref->GetYaxis()->SetTitleSize(0.04);
	frame_mode_ref->GetXaxis()->SetTitleSize(0.04);
	combData->plotOn(frame_mode_ref, LineWidth(2));
	// simPdf->plotOn(frame_mode_ref, LineColor(kRed), LineWidth(3));
	sigpdf_sig->plotOn(frame_mode_ref, LineColor(kGreen), LineWidth(3), LineStyle(kDashed));
	// sigpdf_bkg->plotOn(frame_mode_ref, LineColor(kBlue), LineWidth(3), LineStyle(kDashed));
	frame_mode_ref->Draw();
	can3->SaveAs("a.png");




	
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

	// RooAbsReal *isig2 = sigpdf2->createIntegral(*M_BC, NormSet(*M_BC), Range(2.276, 2.293));
	// RooAbsReal *ibkg = argus->createIntegral(*M_BC, NormSet(*M_BC), Range(2.276, 2.293));
	// cout << "nsig_4620: " << br_Sigmaref.getVal() * N_4620 << " +/- " << br_Sigmaref.getError() * N_4620 << endl;
	// cout << "nbkg_4620: " << nbkg2.getVal() << " +/- " << nbkg2.getError() << endl;

	// RooAbsReal *isig3 = sigpdf3->createIntegral(*M_BC, NormSet(*M_BC), Range(2.276, 2.293));
	// // RooAbsReal *ibkg = argus->createIntegral(*M_BC, NormSet(*M_BC), Range(2.276, 2.293));
	// cout << "nsig_4640: " << br_Sigmaref.getVal() * N_4640 << " +/- " << br_Sigmaref.getError() * N_4640 << endl;
	// // cout << "nbkg_4640: " << nbkg3.getVal() << " +/- " << nbkg3.getError() << endl;

	// RooAbsReal *isig4 = sigpdf4->createIntegral(*M_BC, NormSet(*M_BC), Range(2.276, 2.293));
	// // RooAbsReal *ibkg = argus->createIntegral(*M_BC, NormSet(*M_BC), Range(2.276, 2.293));
	// cout << "nsig_4660: " << br_Sigmaref.getVal() * N_4660 << " +/- " << br_Sigmaref.getError() * N_4660 << endl;
	// // cout << "nbkg_4660: " << nbkg4.getVal() << " +/- " << nbkg4.getError() << endl;

	// RooAbsReal *isig5 = sigpdf5->createIntegral(*M_BC, NormSet(*M_BC), Range(2.276, 2.293));
	// // RooAbsReal *ibkg = argus->createIntegral(*M_BC, NormSet(*M_BC), Range(2.276, 2.293));
	// cout << "nsig_4680: " << br_Sigmaref.getVal() * N_4680 << " +/- " << br_Sigmaref.getError() * N_4680 << endl;
	// // cout << "nbkg_4680: " << nbkg5.getVal() << " +/- " << nbkg5.getError() << endl;
	
	// RooAbsReal *isig6 = sigpdf6->createIntegral(*M_BC, NormSet(*M_BC), Range(2.276, 2.293));
	// // RooAbsReal *ibkg = argus->createIntegral(*M_BC, NormSet(*M_BC), Range(2.276, 2.293));
	// cout << "nsig_4700: " << br_Sigmaref.getVal() * N_4700 << " +/- " << br_Sigmaref.getError() * N_4700 << endl;
	// // cout << "nbkg_4700: " << nbkg6.getVal() << " +/- " << nbkg6.getError() << endl;

	// //
	// // //
	Double_t FCN_bkg = -39687.9; 
	Double_t DeltaLL = 2 * fabs(result->minNll() - FCN_bkg);
	Double_t prob = TMath::Prob(DeltaLL, 1);
	Double_t nSigma = sqrt(2) * TMath::ErfcInverse(prob);
	cout << "|FCN_single - FCN_bkg| = " << DeltaLL << endl;
	cout << " Sigma: " << nSigma << endl;
	return 0;
}
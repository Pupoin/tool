#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooCBShape.h"
#include "RooConstVar.h"
#include "RooChebychev.h"
#include "RooArgusBG.h"
#include "RooAddition.h"
#include "RooMinuit.h"
#include "RooFitResult.h"
#include "TLegend.h"
#include "RooAddPdf.h"
#include "RooWorkspace.h"
#include "RooKeysPdf.h"
#include "RooPlot.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1F.h"
#include "THStack.h"
#include "TMath.h"


using namespace std;
using namespace RooFit;

int energyPoint[7] = {4600, 4612, 4626, 4640, 4660, 4680, 4700};
const int N = 7;

void mantou(){
	//file name
	TString kpnamesig[N];
	TString kpnamesb[N];
	TString kpnameall[N];
	TString kpnamesball[N];
	TString rootfnamesig[N];
	TString rootfnamesb[N];
	for(int i = 0; i < N; i++){
		rootfnamesig[i].Form("/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/tightcut_r3c_minomega/%idata_selB2.root", energyPoint[i]);
		rootfnamesb[i].Form( "/publicfs/ucas/user/yuanchy8/7.0.6/omega/data/cutmassroot/tightcut_r3c_minomega/%idata_selB2.root", energyPoint[i]);
		//rootfnamesig[i].Form("/publicfs/ucas/user/zhulinx/7.0.6/ana/LambdaC/STag/data/syserrpomega/omega/sigmapipiLoose/cutAllAnaFitLatR%i.root", energyPoint[i]);
		//rootfnamesb[i].Form("/publicfs/ucas/user/zhulinx/7.0.6/ana/LambdaC/STag/data/syserrpomega/omega/sigmapipiLoose/cutAllAnaFitSbLatR%i.root", energyPoint[i]);
		//kpnamesig[i].Form("/publicfs/ucas/user/zhulinx/7.0.6/ana/LambdaC/STag/sigmc/%i/pomega_inc/root/plan/test/vetonew/wSigLatMode%i.root", energyPoint[i], energyPoint[i]);
		///publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/4612_ref_shapepdf.root
		kpnamesig[i].Form("publicfs/ucas/user/yuanchy8/7.0.6/omega/pdf/tightcut_r3c_minomega/%i_ref_shapepdf.root", energyPoint[i]);
		//kpnamesb[i].Form("/publicfs/ucas/user/zhulinx/7.0.6/ana/LambdaC/STag/sigmc/%i/pomega_inc/root/plan/test/vetonew/wSbLatMode%i.root", energyPoint[i], energyPoint[i]);
		//kpnamesb[i].Form("/publicfs/ucas/user/zhulinx/7.0.6/ana/LambdaC/STag/sigmc/pomega_peak/%i/p3pi/root/plan/test/vetonew/wSbLat%i.root", energyPoint[i], energyPoint[i]);
		kpnamesb[i].Form("/scratchfs/bes/yuanchy8/omega/shape_3pi/cutmassroot/tightcut_r3c_minomega/pdf/%i_ref_shapepdf.root", energyPoint[i]);
		
		
		kpnameall[i].Form("/scratchfs/bes/zhulinx/7.0.6/ana/LambdaC/STag/data/syserrpomega/smear_mc/omega/AllLatPi0%i.root", energyPoint[i]);
		kpnamesball[i].Form("/scratchfs/bes/zhulinx/7.0.6/ana/LambdaC/STag/data/syserrpomega/smear_mc/omega/SbAllLatPi0%i.root", energyPoint[i]);
	}
	
	//Title Name
	Double_t xmin = 2.25;
	Double_t xmax[N];
	xmax[0] = 2.299765; xmax[1] = 2.30579; xmax[2] = 2.31387; xmax[3] = 2.320255; xmax[4] = 2.33046; xmax[5] = 2.34079; xmax[6] = 2.34919;
	Int_t xbins = 20;
	char xb[N][20];
	TString xtitle[N];
	TString xa("Events/"); 
	TString xd(" MeV/c^{2})");
	for(int i = 0; i < N; i++){
        sprintf(xb[i], "(%5.1f", (xmax[i]-xmin)/xbins*1000);
        xtitle[i] = xa+xb[i]+xd;
    }   
    
    Double_t FCN_bkg = -327503;            // FCN from background fit to calculate the significance.
	
	//Define mbc
	RooRealVar *mbc[N];
    for(int i = 0; i < N; i++){
        mbc[i] = new RooRealVar("M_BC_r3c", "M_BC_r3c", xmin, xmax[i]);
    }
	
	//Generate Dataset
	TChain *chain[N]; TChain *chainSb[N];
	TTree *myTree[N]; TTree *myTreeSb[N];
	//TString cutsig = "mBC>2.25&&mBC<2.35&&etamass>0.75&&etamass<0.81&&deltae>-0.03&&deltae<0.02&&(pipimass>0.52||pipimass<0.48)&&r<0.9";
	//TString cutsb = "mBC>2.25&&mBC<2.35&&((etamass>0.65&&etamass<0.72)||(etamass>0.84&&etamass<0.87))&&deltae>-0.03&&deltae<0.02&&(pipimass>0.52||pipimass<0.48)&&r<0.9";
	TString cutsig = "(np !=0 && npbar != 0) && (chi2_min_r3c< 30) && (etaprimemr3c>0.76&&etaprimemr3c<0.8)";
	TString cutsb = "(np !=0 && npbar != 0) && (chi2_min_r3c< 30) &&((etaprimemr3c>0.68&&etaprimemr3c<0.72)||(etaprimemr3c>0.84&&etaprimemr3c<0.89))";
	TFile *f[N], *fSb[N], *fAll[N], *fSbAll[N];
	for(int i = 0; i < N; i++){
		chain[i] = new TChain("tree");
		chain[i] -> Add(rootfnamesig[i]);
		myTree[i] = chain[i] -> CopyTree(cutsig, "", 1000000000, 0);
	}
	for(int i = 0; i < N; i++){
		chainSb[i] = new TChain("tree");
		chainSb[i] -> Add(rootfnamesb[i]);
		myTreeSb[i] = chainSb[i] -> CopyTree(cutsb, "", 1000000000, 0);
	}
	for(int j = 0; j < N; j++){
		f[j] = TFile::Open(kpnamesig[j]);
		fSb[j] = TFile::Open(kpnamesb[j]);
		fAll[j] = TFile::Open(kpnameall[j]);
		fSbAll[j] = TFile::Open(kpnamesball[j]);
	}
	RooDataSet *dataSet[N], *dataSetSb[N];
	for(int i = 0; i < N; i++){
		dataSet[i] = new RooDataSet(TString::Format("dataSet_%i", i), TString::Format("dataSet_%i", i), RooArgSet(*mbc[i]), Import(*myTree[i]));
		dataSetSb[i] = new RooDataSet(TString::Format("dataSetSb_%i", i), TString::Format("dataSetSb_%i", i), RooArgSet(*mbc[i]), Import(*myTreeSb[i]));
	}
	
	//Load Pdf
	RooAbsPdf *simuPdf[N], *simuPdfSb[N], *simuPdfAll[N], *simuPdfSbAll[N];
	RooWorkspace *w[N], *wSb[N], *wAll[N];
	for(int i = 0; i < N; i++){
		//w[i] = (RooWorkspace*)f[i] -> Get("w");
		//simuPdf[i] = w[i] -> pdf(TString::Format("simuPdf_%i", energyPoint[i]));
		simuPdf[i] = (RooAbsPdf*)f[i] -> Get("modelPdf"); simuPdf[i]->SetName(TString::Format("simuPdf_%i", energyPoint[i]));
		//wSb[i] = (RooWorkspace*)fSb[i] -> Get("w");
		//simuPdfSb[i] = wSb[i] -> pdf(TString::Format("simuPdfSb_%i", energyPoint[i]));
		simuPdfSb[i] = (RooAbsPdf*)fSb[i]->Get("modelPdf"); simuPdfSb[i]->SetName(TString::Format("simuPdfSb_%i", energyPoint[i]));
		//wAll[i] = (RooWorkspace*)fAll[i] -> Get("w");
		//simuPdfAll[i] = wAll[i] -> pdf(TString::Format("simuPdfAll_%i", energyPoint[i]));
		simuPdfAll[i] = (RooAbsPdf*)fAll[i]->Get(TString::Format("simuPdfAll_%i_11", energyPoint[i]));
		simuPdfSbAll[i] = (RooAbsPdf*)fSbAll[i]->Get(TString::Format("simuPdfSbAll_%i_11", energyPoint[i]));
	}
	
	//Background Pdf
	RooRealVar *m0[N], *_c[N];
	RooArgusBG *bkg[N];
	double _c_ini[N] = {-10, -10, -10, -10, -10, -10, -10};
	for(int i = 0; i < N; i++){
		m0[i] = new RooRealVar(TString::Format("m0_%i", i), TString::Format("m0_%i", i), xmax[i]);
		_c[i] = new RooRealVar(TString::Format("_c%i", i), TString::Format("_c%i", i), -10, -70., 20.);
		bkg[i] = new RooArgusBG(TString::Format("bkg_%i", i), TString::Format("bkg_%i", i), *mbc[i], *m0[i], *_c[i]);
	}
	
	RooRealVar *B = new RooRealVar("B", "B", 1.24e-3, 0., 1.);
	RooFormulaVar *nsig[N], *nsigSb[N];
	RooRealVar *nbkg[N], *nsb[N], *nbkgSb[N];

	float factor[N] = {31785.6, 4921.37, 25154.3, 26409.9, 24843.2, 73830.5, 22282.8}; //Pi0 Match 349 r<0.9
	//float factor[N] = {30158.6, 4669.66, 23857.1, 25080.7, 23613.6, 70005.3, 21130.7}; //Pi0 Match 349 r<0.85
	//float factor[N] = {32896.9, 5089.28, 26044.8, 27337.6, 25667.2, 76336.3, 23080.5}; //Pi0 Match 349 r<0.95
	//float factor[N] = {31855.6, 4932.2, 25209.7, 26468.1, 24898.0, 73933.1, 22331.8}; //Proton Trk
	//float factor[N] = {31806.2, 4924.6, 25170.7, 26427.1, 24859.4, 73878.5, 22297.3}; //Proton PID
	//float factor[N] = {31983.8, 4951.6, 25308.0, 26572.0, 24995.2, 74281.2, 22418.4}; //Pion trk
	//float factor[N] = {31848.2, 4931.2, 25205.5, 26464.3, 24895.5, 73989.8, 22331.3}; //Pion pid
	//float factor[N] = {31830.3, 4944.1, 25256.1, 26473.4, 24877.9, 73756.2, 22259.1}; //angular 1
	//float factor[N] = {31696.1, 4875.9, 24950.8, 26283.0, 24773.9, 73979.2, 22330.1}; //angular 2
	//float factor[N] = {31455.7, 4872.49, 24888.7, 26159.4, 24600.4, 73194.4, 22103.4}; //veto
	//float factor[N] = {31681.7, 4899.62, 25066.1, 26287, 24751.6, 73604.7, 22210.7}; //deltaE
	
	//float factor[N] = {31568.3342, 4919.4381, 25067.3689, 26513.2432, 24779.0947, 73922.2391, 22196.0780}; //alpha=1.0 beta=1.0 gamma=0.01
	//float factor[7] = {31606.8750, 4898.8347, 25096.9867, 26487.5853, 24575.4903, 73017.8056, 22486.4123}; //alpha=1.0, beta=1.0, gamma=100
	/*
	float readFactor[5][N];
	ifstream inFile("/publicfs/ucas/user/zhulinx/7.0.6/ana/LambdaC/STag/sigmc/syserrpomega/omega/trackpid/factor.csv", ios::in);
	if(!inFile){
		cout << "Open file failure!!!" << endl;
		exit(1);
	}
	
	string line; string part;
	int count = 0;
	while(getline(inFile, line)){
		istringstream sin(line);
		
		for(int k = 0; k < 5; k++){
			getline(sin, part, ',');
			readFactor[k][count] = atof(part.c_str());
		}
		
		count++;
	}
	inFile.close();
	
	cout << "factor proton track: " << endl;
	for(int k = 0; k < N; k++){
		cout << readFactor[0][k] << " ";
	}
	cout << endl;*/
	/*
	//exit(0);
	
	/*float factor[N];
	for(int k = 0; k < N; k++){
		factor[k] = readFactor[4][k];
	}*/
	
	//int factor[N] = {31054, 4814, 24588, 25848, 24289, 72306, 21838}; //proton track
	//int factor[N] = {31192, 4834, 24692, 25952, 24384, 72589, 21919}; //proton pid
	//int factor[N] = {30517, 4731, 24170, 25414, 23887, 71120, 21484}; //pi0 reconstruction
	//int factor[N] = {31074, 4818, 24614, 25880, 24325, 72432, 21878}; //pion track
	//int factor[N] = {31120, 4824, 24646, 25913, 24353, 72504, 21899}; //pion pid
	//float factor[N] = {31366.3, 4879.4, 24914.5, 26156.4, 24552.5, 72966.5, 22027.9}; //angle factor 1
	//float factor[N] = {31242.4, 4809.4, 24597.1, 25938.3, 24436.8, 73019.0, 22077.6}; //angle factor 2
	//float factor[N] = {31381.7, 4866.57, 24867.9, 26136.4, 24566.6, 73125.9, 22094.1}; //Vr Loose
	//float factor[N] = {31207.9, 4834.49, 24696.2, 25953.1, 24391.0, 72571.9, 21917.7}; //Vr Tight
	//float factor[N] = {31418.7, 4871.7, 24882.4, 26171.4, 24585.1, 73214.7, 22115.6}; //lambdapipi0 Loose
	//float factor[N] = {31233.6, 4842.5, 24729.0, 26014.4, 24441.8, 72762.0, 21980.8}; //lambdapipi0 Tight
	//float factor[N] = {32021.0, 4970.0, 25367.3, 26653.5, 25064.4, 74596.0, 22537.2}; //pkspi0 Loose
	//float factor[N] = {30635.4, 4748.1, 24269.6, 25496.3, 23973.0, 71372.1, 21529.6}; //pkspi0 Tight
	//float factor[N] = {31489.4, 4884.6, 24927.8, 26215.7, 24641.6, 73363.4, 22171.3}; //sigmapipi Loose
	//float factor[N] = {31151.9, 4829.1, 24665.0, 25946.4, 24377.9, 72553.5, 21924.0}; //sigmapipi Tight
	//float factor[N] = {31249.0, 4839.3, 24742.5, 25982.4, 24428.1, 72801.6, 21997.8}; //delta E window

	Double_t nbkg_ini[N], nbkg_min[N], nbkg_max[N];
	nbkg_ini[0] = 1000.;  nbkg_ini[1] = 1000.;  nbkg_ini[2] = 1000.;  nbkg_ini[3] = 1000.;  nbkg_ini[4] = 1000.;
	nbkg_ini[5] = 3000.; nbkg_ini[6] = 1000.;
	nbkg_min[0] = 0.;    nbkg_min[1] = 0.;    nbkg_min[2] = 0.;    nbkg_min[3] = 0.;    nbkg_min[4] = 0.;
	nbkg_min[5] = 0.;    nbkg_min[6] = 0.;
	nbkg_max[0] = 2000.; nbkg_max[1] = 2000.; nbkg_max[2] = 2000.; nbkg_max[3] = 2000.; nbkg_max[4] = 2000.;
	nbkg_max[5] = 5000.; nbkg_max[6] = 2000.;
	
	for(int i = 0; i < N; i++){
		nbkg[i] = new RooRealVar(TString::Format("nbkg_%i", i), TString::Format("nbkg_%i", i), nbkg_ini[i], nbkg_min[i], nbkg_max[i]);
	}

	Double_t nsb_ini[N], nsb_min[N], nsb_max[N];
	nsb_ini[0] = 5.;  nsb_ini[1] = 50.;  nsb_ini[2] = 50.;  nsb_ini[3] = 10.;  nsb_ini[4] = 5.;
	nsb_ini[5] = 5.;  nsb_ini[6] = 10.;
	nsb_min[0] = 0.;   nsb_min[1] = 0.;   nsb_min[2] = 0.;   nsb_min[3] = 0.;   nsb_min[4] = 0.;
	nsb_min[5] = 0.;   nsb_min[6] = 0.;
	nsb_max[0] = 100.; nsb_max[1] = 100.; nsb_max[2] = 100.; nsb_max[3] = 100.; nsb_max[4] = 100.;
	nsb_max[5] = 500.; nsb_max[6] = 100.;
	
	for(int i = 0; i < N; i++){
		nsb[i] = new RooRealVar(TString::Format("nsb_%i", i), TString::Format("nsb_%i", i), nsb_ini[i], nsb_min[i], nsb_max[i]);
	}
	//nsb[6]->setVal(10.);

	Double_t nbkgSb_ini[N], nbkgSb_min[N], nbkgSb_max[N];
	nbkgSb_ini[0] = 3000.;  nbkgSb_ini[1] = 3000.;  nbkgSb_ini[2] = 3000.;  nbkgSb_ini[3] = 3000.;  nbkgSb_ini[4] = 3000.;
	nbkgSb_ini[5] = 10000.; nbkgSb_ini[6] = 3000.;
	nbkgSb_min[0] = 0.;    nbkgSb_min[1] = 0.;    nbkgSb_min[2] = 0.;    nbkgSb_min[3] = 0.;    nbkgSb_min[4] = 0.;
	nbkgSb_min[5] = 0.;    nbkgSb_min[6] = 0.;
	nbkgSb_max[0] = 5000.; nbkgSb_max[1] = 5000.; nbkgSb_max[2] = 5000.; nbkgSb_max[3] = 5000.; nbkgSb_max[4] = 5000.;
	nbkgSb_max[5] = 15000.; nbkgSb_max[6] = 5000.;

	for(int i = 0; i < N; i++){
		nbkgSb[i] = new RooRealVar(TString::Format("nbkgSb_%i", i), TString::Format("nbkgSb_%i", i), nbkgSb_ini[i], nbkgSb_min[i], nbkgSb_max[i]);
	}
	
	for(int i = 0; i < N; i++){
		nsig[i] = new RooFormulaVar(TString::Format("nsig_%i", i), TString::Format("%f*B", factor[i]), RooArgList(*B));
		nsigSb[i] = new RooFormulaVar(TString::Format("nsigSb_%i", i), TString::Format("0.582975*nsb_%i", i), RooArgList(*nsb[i])); //fitting 0.582975
		//0.485
	}
	
	//Model, combine signal and background
	RooAddPdf *pdf[N], *pdfSb[N];
	for(int i = 0; i < N; i++){
		cout << "mantou !!!" << endl;
		pdf[i] = new RooAddPdf(TString::Format("pdf_%i", i), TString::Format("pdf_%i", i), RooArgList(*simuPdf[i], *simuPdfSb[i], *bkg[i]), RooArgList(*nsig[i], *nsigSb[i], *nbkg[i]));
		//pdf[i] = new RooAddPdf(TString::Format("pdf_%i", i), TString::Format("pdf_%i", i), RooArgList(*simuPdfSb[i], *bkg[i]), RooArgList(*nsigSb[i], *nbkg[i]));
		cout << "mantou !!!" << endl;
		pdfSb[i] = new RooAddPdf(TString::Format("pdfSb_%i", i), TString::Format("pdfSb_%i", i), RooArgList(*simuPdfSb[i], *bkg[i]), RooArgList(*nsb[i], *nbkgSb[i]));
	}
	
	for(int i = 0; i < N; i++){
		f[i]->Close();
		fSb[i]->Close();
		fAll[i]->Close();
		fSbAll[i]->Close();
	}
	
	//Simultaneous Fit
	RooAbsReal *nl[N], *nlSb[N]; RooArgSet allList;
	for(int i = 0; i < N; i++){
		nl[i] = pdf[i]->createNLL(*dataSet[i]);
		nlSb[i] = pdfSb[i]->createNLL(*dataSetSb[i]);
	}
	for(int i = 0; i < N; i++){
		allList.add(*nl[i]);
	}
	for(int i = 0; i < N; i++){
		allList.add(*nlSb[i]);
	}
		
	RooAddition nll("nll","nll", allList);
    RooMinuit mm(nll);
    mm.migrad();
    mm.hesse();
	
	RooFitResult* m_fitres = mm.save() ;
    m_fitres->Print("v");
	
	
	//combine data
	//signal region
	
	TChain* chain_all; TTree* tree_all;
	chain_all = new TChain("tree");
    chain_all->Add("/publicfs/ucas/user/zhulinx/7.0.6/ana/LambdaC/STag/data/merge/optimize/vetonew/allCutOmegaDataFitLat.root");
    tree_all = chain_all->CopyTree(cutsig, "", 1000000000000000, 0);
	RooDataSet *allData=new RooDataSet("allData", "mBC(GeV)", RooArgSet(*mbc[6]), Import(*tree_all));

    //double Nsig_all = B->getVal()*(31785.6+4921.37+25154.3+26409.9+24843.2+73830.5+22282.8);
	double Nsig_all = 0.; double Nsigsb_all = 0.;
	for(int i = 0; i < N; i++){
		Nsig_all = nsig[i]->getVal()+Nsig_all;
		Nsigsb_all = nsigSb[i]->getVal()+Nsigsb_all;
	}

	double Nbkg_all = 0.;  Nsigsb_all = 0.;
	for(int i = 0; i < N; i++){
		Nbkg_all = nbkg[i]->getVal()+Nbkg_all;
		Nsigsb_all = nsigSb[i]->getVal()+Nsigsb_all;
	}
    
    RooArgList sig_All_List, nsig_All_List;
    RooArgList bkg_All_List, nbkg_All_List;
	RooArgList sigSb_All_List, nsigSb_All_List;
    
	for(int i = 0; i < N; i++){
		sig_All_List.add(*simuPdfAll[i]);
		bkg_All_List.add(*bkg[i]);
		sigSb_All_List.add(*simuPdfSbAll[i]);
		nsig_All_List.add(*nsig[i]);
		nbkg_All_List.add(*nbkg[i]);
		nsigSb_All_List.add(*nsigSb[i]);
	}
	
    RooRealVar* nsig_All = new RooRealVar("nsig_All", "Combine Nsig", Nsig_all);
    RooRealVar* nbkg_All = new RooRealVar("nbkg_All", "Combine Nbkg", Nbkg_all);
	RooRealVar* nsigSb_All = new RooRealVar("nsigSb_All", "nsigSb_All", Nsigsb_all);
    
    RooAddPdf* sig_All = new RooAddPdf("sig_All", "Combine sigpdf", sig_All_List, nsig_All_List);
    RooAddPdf* bkg_All = new RooAddPdf("bkg_All", "Combine bkgpdf", bkg_All_List, nbkg_All_List);
	RooAddPdf* sigSb_All = new RooAddPdf("sigSb_All", "Combine bkgsbpdf", sigSb_All_List, nsigSb_All_List);
	
	RooAddPdf* pdf_All = new RooAddPdf("pdf_All", "Combine pdf", RooArgList(*sig_All, *bkg_All, *sigSb_All), RooArgList(*nsig_All, *nbkg_All, *nsigSb_All));
	
	delete tree_all; delete chain_all;
	
	//sideband region
	
	TChain* chain_sb; TTree* tree_sb;
	chain_sb = new TChain("tree");
    chain_sb->Add("/publicfs/ucas/user/zhulinx/7.0.6/ana/LambdaC/STag/data/merge/optimize/vetonew/allCutOmegaDataFitSbLat.root");
    tree_sb = chain_sb->CopyTree(cutsb,"",1000000000,0);
	RooDataSet *sbData=new RooDataSet("sbData","mBC(GeV)", RooArgSet(*mbc[6]), Import(*tree_sb));
	
	double Nbkg_sb = 0.; double Nsb = 0.;
	for(int i = 0; i < N; i++){
		Nbkg_sb = nbkgSb[i]->getVal()+Nbkg_sb;
		Nsb = nsb[i]->getVal()+Nsb;
	}
    RooArgList sb_List, nsb_List;
	RooArgList bkgSb_List, nbkgSb_List;
    
	for(int i = 0; i < N; i++){
		sb_List.add(*simuPdfSbAll[i]);
		bkgSb_List.add(*bkg[i]);
		nsb_List.add(*nsb[i]);
		nbkgSb_List.add(*nbkgSb[i]);
	}
	
    RooRealVar* nsb_all = new RooRealVar("nsb_all", "Combine Nsb", Nsb);
	RooRealVar* nbkgSb_all = new RooRealVar("nbkgsb_all", "nbkgsb", Nbkg_sb);
    
    RooAddPdf* sb = new RooAddPdf("sb", "Combine sb", sb_List, nsb_List);
	RooAddPdf* bkgSb = new RooAddPdf("bkgSb", "Combine bkgsb", bkgSb_List, nbkgSb_List);
	
	RooAddPdf* pdf_Sb = new RooAddPdf("pdf_Sb", "Combine pdf", RooArgList(*sb, *bkgSb), RooArgList(*nsb_all, *nbkgSb_all));
	
	delete tree_sb; delete chain_sb;
	
	//Draw All
	RooPlot* frameAll = new RooPlot("All","All",*mbc[6],xmin,xmax[6],xbins);
	frameAll->SetTitle("");
	allData->plotOn(frameAll) ;
	pdf_All->plotOn(frameAll,Name("pdf_All"),LineColor(kGreen)) ;
	pdf_All->plotOn(frameAll,Name("bkg_All"),Components(*bkg_All),LineColor(kBlue),LineStyle(kDashed)) ;
	pdf_All->plotOn(frameAll,Name("sig_All"),Components(*sig_All),LineColor(kRed),LineWidth(5),LineStyle(kDashed)) ;
	pdf_All->plotOn(frameAll,Name("sigSb_All"),Components(*sigSb_All),LineColor(kViolet),LineStyle(kDashed)) ;
	frameAll->GetXaxis()->SetTitle("M_{BC} (GeV/c^{2})");
    frameAll->GetXaxis()->SetTitleOffset(0.80);
    frameAll->GetXaxis()->SetTitleSize(0.06);
	frameAll->GetXaxis()->SetTitleFont(132);
	frameAll->GetXaxis()->SetLabelFont(132);
    frameAll->GetYaxis()->SetTitle(xtitle[6]);
    frameAll->GetYaxis()->SetTitleOffset(0.80);
    frameAll->GetYaxis()->SetTitleSize(0.06);
	frameAll->GetYaxis()->SetTitleFont(132);
	frameAll->GetYaxis()->SetLabelFont(132);
	
	RooPlot* frameSbAll = new RooPlot("Sb","Sb",*mbc[6],xmin,xmax[6],xbins);
	frameSbAll->SetTitle("");
	sbData->plotOn(frameSbAll) ;
	pdf_Sb->plotOn(frameSbAll,Name("pdf_Sb"),LineColor(kGreen)) ;
	pdf_Sb->plotOn(frameSbAll,Name("bkgSb"),Components(*bkgSb),LineColor(kBlue),LineStyle(kDashed)) ;
	pdf_Sb->plotOn(frameSbAll,Name("sb"),Components(*sb),LineColor(kViolet),LineStyle(kDashed)) ;
	frameSbAll -> GetXaxis()->SetTitle("M_{BC} (GeV/c^{2})");
    frameSbAll -> GetYaxis()->SetTitle(xtitle[6]);
    frameSbAll->GetXaxis()->SetTitleOffset(0.80);
    frameSbAll->GetXaxis()->SetTitleSize(0.06);
	frameSbAll->GetXaxis()->SetTitleFont(132);
	frameSbAll->GetXaxis()->SetLabelFont(132);
    frameSbAll->GetYaxis()->SetTitle(xtitle[6]);
    frameSbAll->GetYaxis()->SetTitleOffset(0.80);
    frameSbAll->GetYaxis()->SetTitleSize(0.06);
	frameSbAll->GetYaxis()->SetTitleFont(132);
	frameSbAll->GetYaxis()->SetLabelFont(132);
	
	TLegend *lAll;
    lAll = new TLegend(0.18, 0.35, 0.38, 0.55, NULL, "brNDC");
    lAll->AddEntry(frameAll->findObject("pdf_All"), "sum", "l");
    lAll->AddEntry(frameAll->findObject("sig_All"), "sig", "l");
    lAll->AddEntry(frameAll->findObject("sigSb_All"), "from omega non-signal", "l");
    lAll->AddEntry(frameAll->findObject("bkg_All"), "bkg", "l");
    lAll->SetFillColor(0);
    lAll->SetFillStyle(0);
    lAll->SetTextSize(0.05);
    lAll->SetTextFont(132);
    lAll->SetLineColor(0);

    TLegend *lSbAll;
    lSbAll = new TLegend(0.18, 0.35, 0.38, 0.55, NULL, "brNDC");
    lSbAll->AddEntry(frameSbAll->findObject("pdf_Sb"), "peak bkg+bkg", "l");
    lSbAll->AddEntry(frameSbAll->findObject("sb"), "peak bkg", "l");
    lSbAll->AddEntry(frameSbAll->findObject("bkgSb"), "bkg", "l");
    lSbAll->SetFillColor(0);
    lSbAll->SetFillStyle(0);
    lSbAll->SetTextSize(0.05);
    lSbAll->SetTextFont(132);
    lSbAll->SetLineColor(0);
	
	TCanvas* cAll = new TCanvas("cAll","cAll",800,600) ;
	TPad* padAll = dynamic_cast<TPad*>(cAll->cd());
	padAll -> SetLeftMargin(0.15);
	frameAll -> Draw(); lAll -> Draw(); 
	cAll -> SetBottomMargin(0.15); cAll -> SetLeftMargin(0.15);
	cAll -> Draw();
	cAll -> SaveAs("cAll.png");




	TCanvas* cSB = new TCanvas("cSB","cSB",800,600) ;
	TPad* padSB = dynamic_cast<TPad*>(cSB->cd());
	padSB -> SetLeftMargin(0.15);
	frameSbAll -> Draw(); lSbAll -> Draw(); 
	cSB -> SetBottomMargin(0.15); cSB -> SetLeftMargin(0.15);
	cSB -> Draw();
	cSB->SaveAs("cSB.png");
	
	// c.SaveAs("matu.png");
	//Double_t FCN_bkg = -165555;
	// Double_t FCN_bkg = -165557;
    // Double_t DeltaLL = 2 * fabs( m_fitres->minNll() - FCN_bkg );
    // Double_t prob = TMath::Prob( DeltaLL, 1 );
    // Double_t nSigma = sqrt(2) * TMath::ErfcInverse( prob );
    // cout<< " 2ln(L) = " << DeltaLL << endl;
    // cout<< " Sigma: " << nSigma << endl;
}

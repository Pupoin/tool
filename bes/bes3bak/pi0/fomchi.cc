#include "iostream"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include "TText.h"
#include <vector>
#include <string>
#include "TFile.h"
#include "TTree.h"
using namespace RooFit;
using namespace std;

void calcu(TChain *chain, TString chi2cut);

int NN = 30;
double nsig = 0, nbkg = 0, fom = 0, fom2 = 0;
int fomchi()
{
    TChain *chain = new TChain("tree");

    chain->Add("./LL/cutmassroot/4600LL_cut_mass_dipi.root"); //40
    chain->Add("./LL/cutmassroot/4600LL_cut_mass_dipi.root");
    chain->Add("./LL/cutmassroot/4612LL_cut_mass_dipi.root");  //40
    chain->Add("./LL/cutmassroot/4612LL_cut_mass_dipi.root");
    chain->Add("./LL/cutmassroot/4620LL_cut_mass_dipi.root");
    chain->Add("./LL/cutmassroot/4640LL_cut_mass_dipi.root");
    chain->Add("./LL/cutmassroot/4660LL_cut_mass_dipi.root");
    chain->Add("./LL/cutmassroot/4680LL_cut_mass_dipi.root");
    chain->Add("./LL/cutmassroot/4700LL_cut_mass_dipi.root");

    chain->Add("./hadron/cutmassroot/4600hadron_cut_mass_dipi.root"); // 40
    chain->Add("./hadron/cutmassroot/4600hadron_cut_mass_dipi.root");
    chain->Add("./hadron/cutmassroot/4612hadron_cut_mass_dipi.root");  //40
    chain->Add("./hadron/cutmassroot/4612hadron_cut_mass_dipi.root");
    chain->Add("./hadron/cutmassroot/4620hadron_cut_mass_dipi.root");
    chain->Add("./hadron/cutmassroot/4640hadron_cut_mass_dipi.root");
    chain->Add("./hadron/cutmassroot/4660hadron_cut_mass_dipi.root");
    chain->Add("./hadron/cutmassroot/4680hadron_cut_mass_dipi.root"); 
    chain->Add("./hadron/cutmassroot/4680hadron_cut_mass_dipi.root"); // 40times
    chain->Add("./hadron/cutmassroot/4700hadron_cut_mass_dipi.root");

    TString chi2("");

    TFile *file = new TFile("fom.root", "RECREATE");
    TTree *t = new TTree("tree", "");
    double m_nsig, m_nbkg, m_fom, m_chi2, m_fom2;
    t->Branch("chi2", &m_chi2);
    t->Branch("nsig", &m_nsig);
    t->Branch("nbkg", &m_nbkg);
    t->Branch("s_sb", &m_fom);  // s/sqrt(s+b)
    t->Branch("s_b", &m_fom2); // s/sqrt(b)
    

    for (int i = 1; i < NN; i++)
    {
        char b[20];
        sprintf(b, "(chi2_min_r1c<%5.1f)", i);
        chi2 = b;

        calcu(chain, chi2);
        m_chi2 = i;
        m_nsig = nsig;
        m_nbkg = nbkg;
        m_fom = fom;
        m_fom2 = fom2;
        t->Fill();

        // cout << "line_" << __LINE__ << " " << chi2 << endl;
        cout << i << " "<<  nsig << " " << nbkg << " " << fom << " " << fom2 << endl;
    }
    t->Write();
    file->Close();
    return 0;
}

void calcu(TChain *chain, TString chi2cut)
{

    TCut cut_np = "(np !=0 && npbar != 0)";
    //TCut cut_mass = "(etam>=0.5&&etam<=0.56 ) && (pi0m>=0.115&&pi0m<=0.15)";
    // TCut cut_mass = "(pi0m>=0.115&&pi0m<=0.15) && (pi0mORetam1m>=0.115&&pi0mORetam1m<=0.15) && (sigmam>=1.174 && sigmam<=1.2) && (dipim<0.48 || dipim>0.52)";
    //TCut cut_deltaE = "((deltaE_min>-0.03) && (deltaE_min<0.02))";
    TCut cut_chi2 = chi2cut;
    TCut cut_mbc = "((M_BC>=2.276) && (M_BC<=2.293))";
    TCut cut_sum1 = (cut_chi2 && cut_mbc && cut_np && "(dipim<0.48 || dipim>0.52)");

    TCut cut_sig = "(signal==1 || signal==-1)";
    TCut cut_bkg = "(signal!=1 && signal!=-1)";

    nsig = chain->GetEntries(cut_sum1 && cut_sig);
    nbkg = chain->GetEntries(cut_sum1 && cut_bkg);
    fom = nsig / sqrt(nsig + nbkg);
    fom2 = nsig / sqrt(nbkg);
}

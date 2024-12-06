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

void calcu_deltaE(TChain *chain, TString deltaEcut);

int NN = 30;
double nsig = 0, nbkg = 0, fom_s_sb = 0, fom_s_b = 0;

int fomchi()
{
    TChain *chain = new TChain("tree");
    chain->Add("LL_mass.root"); 
    chain->Add("../../../hadron/cutmassroot/zhou/hadron_mass_cutLc.root"); 

    TString deltaE("");

    TFile *file = new TFile("fom.root", "RECREATE");
    TTree *t = new TTree("tree", "");

    double m_nsig, m_nbkg, m_fom_s_sb, m_fom_s_b;
    double m_deltaE_up, m_deltaE_down;

    t->Branch("deltaE_up", &m_deltaE_up);
    t->Branch("deltaE_down", &m_deltaE_down);
    t->Branch("nsig", &m_nsig);
    t->Branch("nbkg", &m_nbkg);
    t->Branch("s_sb", &m_fom_s_sb);  // s/sqrt(s+b)
    t->Branch("s_b", &m_fom_s_b); // s/sqrt(b)
    

    for (double down=-0.01; down >= -0.1; down-=0.01)
    {        
        for (double up=0.01; up <= 0.1; up+=0.01)
        {
            char b[50];
            sprintf(b, "(%5.5f<deltaE_min_1c && deltaE_min_1c <%5.5f)", down, up);
            deltaE = b;

            calcu_deltaE(chain, deltaE);
            
            m_deltaE_up = up;
            m_deltaE_down = down;

            m_nsig = nsig;
            m_nbkg = nbkg;
            m_fom_s_sb = fom_s_sb;
            m_fom_s_b = fom_s_b;

            t->Fill();
        }        
    }
    t->Write();
    file->Close();
    return 0;
}

void calcu_deltaE(TChain *chain, TString deltaEcut)
{

    // TCut cut_np = "(np !=0 && npbar != 0)";
    //TCut cut_mass = "(etam>=0.5&&etam<=0.56 ) && (pi0m>=0.115&&pi0m<=0.15)";
    //TCut cut_mass = "(pi0m>=0.115&&pi0m<=0.15) && (pi0mORetam1m>=0.115&&pi0mORetam1m<=0.15) && (sigmam>=1.174 && sigmam<=1.2)";
    //TCut cut_deltaE = "((deltaE_min>-0.03) && (deltaE_min<0.02))";
    TCut cut_mbc = "((M_BC_1c>=2.276) && (M_BC_1c<=2.293))";
    TCut cut_sum1 = (deltaEcut && cut_mbc);

    TCut cut_sig = "(signal==1 || signal==-1)";
    TCut cut_bkg = !cut_sig;

    nsig = chain->GetEntries(cut_sum1 && cut_sig);
    nbkg = chain->GetEntries(cut_sum1 && cut_bkg);
    fom_s_sb = nsig / sqrt(nsig + nbkg);
    fom_s_b = nsig / sqrt(nbkg);
    cout << " " << deltaEcut << " ,sig "<<  nsig << " ,nbkg " << nbkg << " ,s/sqrt(s+b) " << fom_s_sb << " ,s/sqrt(b) " << fom_s_b << endl;
}

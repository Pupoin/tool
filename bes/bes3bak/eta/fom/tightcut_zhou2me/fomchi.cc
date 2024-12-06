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
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_zhou2me/4600LL.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_zhou2me/4612LL.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_zhou2me/4600LL.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_zhou2me/4612LL.root"); 
    // 4600, 4612, x double
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_zhou2me/4620LL.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_zhou2me/4640LL.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_zhou2me/4660LL.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_zhou2me/4680LL.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_zhou2me/4700LL.root"); 

    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_zhou2me/4600hadron.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_zhou2me/4612hadron.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_zhou2me/4600hadron.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_zhou2me/4612hadron.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_zhou2me/4680hadron.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_zhou2me/4680hadron.root"); 
    // 4600, 4612, 4680, x double
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_zhou2me/4620hadron.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_zhou2me/4640hadron.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_zhou2me/4660hadron.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_zhou2me/4700hadron.root"); 


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
    

    for (double down=-0.001; down >= -0.1; down-=0.001)
    {        
        for (double up=0.001; up <= 0.1; up+=0.001)
        {
            char b[50];
            sprintf(b, "(%2.5f<deltaE_min_c && deltaE_min_c<%2.5f)", down, up);
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
    //TCut cut_deltaE = "((deltaE_min_c>-0.03) && (deltaE_min_c<0.02))";
    TCut cut_mbc = "(M_BC_c>=2.276 && M_BC_c<=2.3)";
    TCut cut_sum1 = (deltaEcut && cut_mbc);

    TCut cut_sig = "(signal==1 || signal==-1)";
    TCut cut_bkg = !cut_sig;

    nsig = chain->GetEntries(cut_sum1 && cut_sig);
    nbkg = chain->GetEntries(cut_sum1 && cut_bkg);
    fom_s_sb = nsig / sqrt(nsig + nbkg);
    fom_s_b = nsig / sqrt(nbkg);
    cout << " " << deltaEcut << " ,sig "<<  nsig << " ,nbkg " << nbkg << " ,s/sqrt(s+b) " << fom_s_sb << " ,s/sqrt(b) " << fom_s_b << endl;
}

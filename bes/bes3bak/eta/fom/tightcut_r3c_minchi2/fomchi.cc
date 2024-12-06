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

    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_r3c_minchi2/4600LL_selB.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_r3c_minchi2/4612LL_selB.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_r3c_minchi2/4620LL_selB.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_r3c_minchi2/4640LL_selB.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_r3c_minchi2/4660LL_selB.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_r3c_minchi2/4680LL_selB.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/LL/cutmassroot/tightcut_r3c_minchi2/4700LL_selB.root"); 

    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_r3c_minchi2/4600hadron_selB.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_r3c_minchi2/4612hadron_selB.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_r3c_minchi2/4620hadron_selB.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_r3c_minchi2/4640hadron_selB.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_r3c_minchi2/4660hadron_selB.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_r3c_minchi2/4680hadron_selB.root"); 
    chain->Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/hadron/cutmassroot/tightcut_r3c_minchi2/4700hadron_selB.root"); 

    TString deltaE("");

    TFile *file = new TFile("fom_1lum.root", "RECREATE");
    TTree *t = new TTree("tree", "");

    double m_nsig, m_nbkg, m_fom_s_sb, m_fom_s_b;
    double m_deltaE_up, m_deltaE_down;

    t->Branch("deltaE_up", &m_deltaE_up);
    t->Branch("deltaE_down", &m_deltaE_down);
    t->Branch("nsig", &m_nsig);
    t->Branch("nbkg", &m_nbkg);
    t->Branch("s_sb", &m_fom_s_sb);  // s/sqrt(s+b)
    t->Branch("s_b", &m_fom_s_b); // s/sqrt(b)
    

    for (double down=1; down <= 50; down ++)
    {        
        // for (double up=0.001; up <= 0.1; up+=0.001)
        {
            char b[50];
            // sprintf(b, "(%2.5f<deltaE_min && deltaE_min<%2.5f)", down, up);
            sprintf(b, "(chi2_min_r3c<%2.1f)", down);
            deltaE = b;

            calcu_deltaE(chain, deltaE);
            
            // m_deltaE_up = up;
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

    TCut cut_np = "(np !=0 && npbar != 0)";
    //TCut cut_mass = "(etam>=0.5&&etam<=0.56 ) && (pi0m>=0.115&&pi0m<=0.15)";
    //TCut cut_mass = "(pi0m>=0.115&&pi0m<=0.15) && (pi0mORetam1m>=0.115&&pi0mORetam1m<=0.15) && (sigmam>=1.174 && sigmam<=1.2)";
    //TCut cut_deltaE = "((deltaE_min>-0.03) && (deltaE_min<0.02))";
    // TCut cut_mbc = "(M_BC_r3c>=2.276 && M_BC_r3c<=2.293)";
    TCut cut_mbc = "(M_BC_r3c>=2.276 && M_BC_r3c<=2.3)";
    TCut cut_sum1 = (deltaEcut && cut_mbc && cut_np);

    TCut cut_sig = "(signal==1 || signal==-1)";
    TCut cut_bkg = !cut_sig;

    nsig = int(chain->GetEntries(cut_sum1 && cut_sig) * 0.17/40);
    nbkg = int(chain->GetEntries(cut_sum1 && cut_bkg) * 0.3/40 );
    fom_s_sb = nsig / sqrt(nsig + nbkg);
    fom_s_b = nsig / sqrt(nbkg);
    cout << " " << deltaEcut << " ,sig "<<  nsig << " ,nbkg " << nbkg << " ,s/sqrt(s+b) " << fom_s_sb << " ,s/sqrt(b) " << fom_s_b << endl;
}

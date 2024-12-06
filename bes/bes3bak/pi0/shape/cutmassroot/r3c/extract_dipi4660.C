#include <TBranch.h>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <TTree.h>
#include <iostream>
typedef std::vector<int> Vint;
typedef std::vector<double> Vdouble;
//typedef std::vector<TLorentzVector> Vp4;
// const double mass[5] = {0.000511, 0.105658, 0.139570,0.493677, 0.938272};

using namespace std;

void extract_dipi4660() 
{

  Double_t deltaE_min, M_BC, pi0m, pi0mORetam1m, sigmamR1c, chi2_min_r1c, g1[4], g2[4], g3[4], g4[4];
  Int_t event, signal, indexmc, pdgid[200], np, npbar;

  TChain *chain = new TChain("tree");
  chain->Add("../4660shape.root");
  TCut cut_mass = "(pi0mORetam1m>=0.115&&pi0mORetam1m<=0.15 ) && (pi0m>=0.115&&pi0m<=0.15) && (sigmamR1c>=1.174&&sigmamR1c<=1.2)";
  TTree *t = chain->CopyTree(cut_mass, "");

  t->SetBranchAddress("event", &event);
  t->SetBranchAddress("deltaE_min", &deltaE_min);
  t->SetBranchAddress("M_BC", &M_BC);
  t->SetBranchAddress("indexmc", &indexmc);
  // t->SetBranchAddress("pdgid", &pdgid);
  t->SetBranchAddress("np", &np);
  t->SetBranchAddress("npbar", &npbar);
  t->SetBranchAddress("gam1", &g1);
  t->SetBranchAddress("gam2", &g2);
  t->SetBranchAddress("gam3", &g3);
  t->SetBranchAddress("gam4", &g4);
  t->SetBranchAddress("pi0mORetam1m", &pi0mORetam1m);
  t->SetBranchAddress("pi0m", &pi0m);
  t->SetBranchAddress("sigmamR1c", &sigmamR1c);
  t->SetBranchAddress("signal", &signal);
  t->SetBranchAddress("chi2_min_r1c", &chi2_min_r1c);

  // new file
  TFile *f_new = new TFile("4660shape_cut_mass_dipi.root", "recreate");
  TTree *tree = new TTree("tree", "");

  Int_t m_event, m_indexmc, m_pdgid[200], m_Lc, m_np, m_npbar, m_signal;
  Double_t m_deltaE_min, m_M_BC, m_pi0mORetam1m, m_pi0m, m_dipim, m_sigmamR1c, m_chi2_min_r1c;

  tree->Branch("event", &m_event);
  tree->Branch("deltaE_min", &m_deltaE_min);
  tree->Branch("M_BC", &m_M_BC);
  tree->Branch("indexmc", &m_indexmc, "m_indexmc/I");
  //tree->Branch("pdgid", m_pdgid, "m_pdgid/I");
  //tree->Branch("Lc", &m_Lc, "m_Lc/I");
  tree->Branch("np", &m_np);
  tree->Branch("npbar", &m_npbar);

  tree->Branch("pi0mORetam1m", &m_pi0mORetam1m);
  tree->Branch("pi0m", &m_pi0m);
  tree->Branch("sigmamR1c", &m_sigmamR1c);
  tree->Branch("dipim", &m_dipim);
  tree->Branch("signal", &m_signal);
  tree->Branch("chi2_min_r1c", &m_chi2_min_r1c);

  TLorentzVector tmp;
  int n = t->GetEntries();
  cout << "n:" << n << endl;
  for (int i = 0; i < n; i++) {
    if ( i%20000==0 && i != 0)
      cout << i << endl;
	
    t->GetEvent(i);
    tmp[0] = g1[0]+g2[0]+g3[0]+g4[0];
    tmp[1] = g1[1]+g2[1]+g3[1]+g4[1];
    tmp[2] = g1[2]+g2[2]+g3[2]+g4[2];
    tmp[3] = g1[3]+g2[3]+g3[3]+g4[3];
	
    m_dipim = tmp.M();

    m_event = event;
    m_deltaE_min = deltaE_min;
    m_M_BC = M_BC;
    m_indexmc = indexmc;
    m_np = np;
    m_npbar = npbar;
    m_pi0mORetam1m = pi0mORetam1m;
    m_pi0m = pi0m;
    m_sigmamR1c = sigmamR1c;
    m_signal = signal;
    m_chi2_min_r1c = chi2_min_r1c;
    
    tree->Fill();
    //break;
  }
  tree->Write();
}

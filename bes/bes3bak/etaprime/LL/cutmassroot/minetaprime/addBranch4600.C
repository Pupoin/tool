#include <TBranch.h>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <TTree.h>
// #include "HepLorentzVector.h"
#include <iostream>
typedef std::vector<int> Vint;
typedef std::vector<double> Vdouble;
//typedef std::vector<TLorentzVector> Vp4;
// const double mass[5] = {0.000511 + 0.105658 + 0.139570 +0.493677 + 0.938272};

using namespace std;

void addBranch4600() {

  TFile *f = new TFile("4600LL_mass.root" , "update");
  TTree *t = (TTree *)f->Get("tree");


  Int_t event;
  Double_t deltaE_min , M_BC;
  int indexmc , indexmc_p , indexmc_m , ndaughterAm , ndaughterAp;
  int pdgid_p[200] , pdgid_m[200] , Am_id[200] , Ap_id[200] ;
  double  mode1 ,mode2 ,mode3;
  Int_t np , npbar;

  t->SetBranchAddress("event" , &event);
  t->SetBranchAddress("Am_id" , &Am_id);
  t->SetBranchAddress("Ap_id" , &Ap_id);
  t->SetBranchAddress("ndaughterAm" , &ndaughterAm);
  t->SetBranchAddress("ndaughterAp" , &ndaughterAp);


  Int_t new_signal = 999;

  auto newBranch = t->Branch("new_signal" , &new_signal , "new_signal/I");

  for (int i = 0; i < t->GetEntries(); i++)
  {
    t->GetEvent(i);
    new_signal = 999;
    if (ndaughterAp == 11 && Ap_id[0] == 3222 && Ap_id[1] == 331 && Ap_id[2] == 2212 && Ap_id[3] == 111 && Ap_id[4] == 211 && Ap_id[5] == -211 && Ap_id[6] == 221 && Ap_id[7] == 22 && Ap_id[8] == 22 && Ap_id[9] == 22 && Ap_id[10] == 22)
    {
        new_signal = 1;
    }
    if (ndaughterAm == 11 && Am_id[0] == -3222 && Am_id[1] == 331 && Am_id[2] == -2212 && Am_id[3] == 111 && Am_id[4] == 211 && Am_id[5] == -211 && Am_id[6] == 221 && Am_id[7] == 22 && Am_id[8] == 22 && Am_id[9] == 22 && Am_id[10] == 22)
	{
        new_signal = -1;
    }
    newBranch->Fill();
    // break;
  }

 
  t->Write(); 
  f->Write();
  f->Close();
}

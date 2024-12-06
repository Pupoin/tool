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

void cutLc() {

  // read file
  TChain *chain = new TChain("tree");
  chain->Add("hadron_mass.root");

  TCut cut_mode = ("mode1==0 && mode2==0 && mode3==96"); 
  TFile *f_new = new TFile("hadron_mass_cutLc.root", "recreate");
  TTree *tree_new = chain->CopyTree(!cut_mode, "");
  tree_new->Write();

}

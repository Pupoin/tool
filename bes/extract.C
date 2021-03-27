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

void extract() {

  // read file
  TChain *chain = new TChain("tree");
  chain->Add("LL.root");

  TCut cut_mass = "(etam>=0.5&&etam<=0.56 ) && (pi0m>=0.115&&pi0m<=0.15) && (sigmam>=1.174&&sigmam<=1.2)";
  
  TFile *f_new = new TFile("LL_selected.root", "recreate");
  TTree *tree_new = chain->CopyTree(cut_mass, "");
  tree_new->Write();

}

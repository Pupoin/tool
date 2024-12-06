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

void extract4680() {

  // read file
  TChain *chain = new TChain("tree");
  chain->Add("./4680shape.root");

  TCut cut_mass = "(etam>=0.5&&etam<=0.56 ) && (pi0m>=0.115&&pi0m<=0.15) && (sigmam>=1.174&&sigmam<=1.2 && etaprimem>0.946 && etaprimem<0.968)";
  
  TFile *f_new = new TFile("4680shape_mass.root", "recreate");
  TTree *tree_new = chain->CopyTree(cut_mass, "");
  tree_new->Write();

}

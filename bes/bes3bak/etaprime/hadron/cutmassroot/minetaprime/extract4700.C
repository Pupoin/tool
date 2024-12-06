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

void extract4700() {

  // read file
  TChain *chain = new TChain("tree");
  chain->Add("./4700hadron.root");

  TCut cut_mass = "(etam>=0.5&&etam<=0.56 ) && (pi0m>=0.115&&pi0m<=0.15) && (sigmam1c>=1.174&&sigmam1c<=1.2 && etaprimem1c>0.946 && etaprimem1c<0.968)";
  TCut cut_mode = ("mode1==0 && mode2==0 && mode3==96");
  //TCut cut_mass = "(etam>=0.5&&etam<=0.56 ) && (pi0m>=0.115&&pi0m<=0.15) && (sigmam1c>=1.174&&sigmam1c<=1.2) && deltaE_min_1c>-0.026 && deltaE_min_1c<0.029";
  
  TFile *f_new = new TFile("4700hadron_mass.root", "recreate");
  TTree *tree_new = chain->CopyTree(cut_mass && !cut_mode, "");
  tree_new->Write();

}

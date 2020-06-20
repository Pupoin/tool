#include <TFile.h>
#include <TBranch.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TChain.h>
#include <iostream>
#include "Rtypes.h"
typedef std::vector<int> Vint;
typedef std::vector<double> Vdouble;
typedef std::vector<TLorentzVector> Vp4;
// const double mass[5] = {0.000511, 0.105658, 0.139570,0.493677, 0.938272};

using namespace std;

// void chisq_SigmapEta()
int mass() {

  Int_t run, event;
  Int_t isig;
  Int_t charge[2000];
  Double_t chi2_3C[2000], chi2_4C[2000], angle[2000], deltaE_min[2000],
      M_BC[2000];
  // pi02
  Double_t p4_of_Gamma1_Eta_before_4C[2000][4],
      p4_of_Gamma2_Eta_before_4C[2000][4], p4_of_Gamma1_Eta_after_4C[2000][4],
      p4_of_Gamma2_Eta_after_4C[2000][4];
  // sigma+
  Double_t p4_of_gamma1_pi0_Sigma_after_4C[2000][4],
      p4_of_gamma2_pi0_Sigma_after_4C[2000][4],
      p4_of_proton_Sigma_after_4C[2000][4],
      p4_of_gamma1_pi0_Sigma_before_4C[2000][4],
      p4_of_gamma2_pi0_Sigma_before_4C[2000][4],
      p4_of_proton_Sigma_before_4C[2000][4],
      p4_of_gamma1_pi0_Sigma_after_3C[2000][4],
      p4_of_gamma2_pi0_Sigma_after_3C[2000][4];

  // truth info

  // File
  char txt_oldfile[] = "all.root";
  char txt_oldtree[] = "SigmapEta";
  char txt_newfile[] = "DD_selected.root";
  char txt_newtree[] = "STag";
  char *filename = txt_oldfile;
  char *treename = txt_oldtree;
  char *newfilename = txt_newfile;
  char *newtreename = txt_newtree;

  // cut
  double ang = 10.; // 15.	needed to be confirmed
  double pi0MinMass = 0.115; // 0.115
  double pi0MaxMass = 0.150; // 0.150
  double etaMinMass = 0.50; // 0.505
  double etaMaxMass = 0.560; // 0.575
  double sigmaMinMass = 1.174; // 1.176
  double sigmaMaxMass = 1.20; // 1.20
  double deltaEMin = -0.04; //-0.04
  double deltaEMax = 0.04; // 0.02
  double mbcMin = 2.25; // 2.25
  double mbcMax = 2.3; // 2.3

  // read file
  TFile *f = new TFile(filename, "");
  TTree *t = (TTree *)f->Get(treename);

  t->SetBranchAddress("run", &run);
  t->SetBranchAddress("event", &event);

  t->SetBranchAddress("isig", &isig);
  t->SetBranchAddress("charge", &charge);
  t->SetBranchAddress("chi2_3C", &chi2_3C);
  t->SetBranchAddress("chi2_4C", &chi2_4C); // for choose best candidate
  t->SetBranchAddress("angle", &angle);
  t->SetBranchAddress("deltaE_min", &deltaE_min);
  t->SetBranchAddress("M_BC", &M_BC);

  // pi02
  t->SetBranchAddress("p4_of_Gamma1_Eta_before_4C",
                      &p4_of_Gamma1_Eta_before_4C); // cut eta mass
  t->SetBranchAddress("p4_of_Gamma2_Eta_before_4C",
                      &p4_of_Gamma2_Eta_before_4C); // cut eta mass
  t->SetBranchAddress("p4_of_Gamma1_Eta_after_4C",
                      &p4_of_Gamma1_Eta_after_4C); // for mbc
  t->SetBranchAddress("p4_of_Gamma2_Eta_after_4C",
                      &p4_of_Gamma2_Eta_after_4C); // for mbc

  // sigma+
  t->SetBranchAddress("p4_of_gamma1_pi0_Sigma_after_4C",
                      &p4_of_gamma1_pi0_Sigma_after_4C); // for mbc
  t->SetBranchAddress("p4_of_gamma2_pi0_Sigma_after_4C",
                      &p4_of_gamma2_pi0_Sigma_after_4C); // for mbc
  t->SetBranchAddress("p4_of_proton_Sigma_after_4C",
                      &p4_of_proton_Sigma_after_4C); // for mbc

  t->SetBranchAddress("p4_of_gamma1_pi0_Sigma_before_4C",
                      &p4_of_gamma1_pi0_Sigma_before_4C); // cut pi0 mass
  t->SetBranchAddress("p4_of_gamma2_pi0_Sigma_before_4C",
                      &p4_of_gamma2_pi0_Sigma_before_4C); // cut pi0 mass
  t->SetBranchAddress("p4_of_proton_Sigma_before_4C",
                      &p4_of_proton_Sigma_before_4C); // cut sigma mass
  t->SetBranchAddress("p4_of_gamma1_pi0_Sigma_after_3C",
                      &p4_of_gamma1_pi0_Sigma_after_3C); // cut sigma mass
  t->SetBranchAddress("p4_of_gamma2_pi0_Sigma_after_3C",
                      &p4_of_gamma2_pi0_Sigma_after_3C); // cut sigma mass

  // prepare new file
  TFile *f_new = new TFile(newfilename, "recreate");
  TTree *tree = new TTree(newtreename, "");

  Double_t m_deltaE_min, m_bc;
  Double_t m_Eta_mass, m_Pi0_Sigma_mass, m_Sigma_mass;

  tree->Branch("mass_Eta", &m_Eta_mass, "m_Eta_mass/D");
  tree->Branch("mass_Pi0_Sigma", &m_Pi0_Sigma_mass, "m_Pi0_Sigma_mass/D");
  tree->Branch("mass_Sigma", &m_Sigma_mass, "m_Sigma_mass/D");
  tree->Branch("deltaE_min", &m_deltaE_min, "m_deltaE_min/D");
  tree->Branch("M_BC", &m_bc, "m_bc/D");

  int nevent = t->GetEntries();
  for (int ievent = 0; ievent < nevent; ievent++) {
    t->GetEvent(ievent);

    if (isig == 0)
      continue;

    Vint vec_charge;
    vec_charge.clear();

    Vdouble vec_chi2_3C, vec_chi2_4C, vec_angle, vec_deltaE_min, vec_M_BC;
    vec_chi2_3C.clear();
    vec_chi2_4C.clear();
    vec_angle.clear();
    vec_deltaE_min.clear();
    vec_M_BC.clear();

    // eta
    Vp4 vec_p4_of_Gamma1_Eta_before_4C, vec_p4_of_Gamma2_Eta_before_4C,
        vec_p4_of_Gamma1_Eta_after_4C, vec_p4_of_Gamma2_Eta_after_4C;
    vec_p4_of_Gamma1_Eta_before_4C.clear();
    vec_p4_of_Gamma2_Eta_before_4C.clear();
    vec_p4_of_Gamma1_Eta_after_4C.clear();
    vec_p4_of_Gamma2_Eta_after_4C.clear();

    // sigma+
    Vp4 vec_p4_of_gamma1_pi0_Sigma_after_4C,
        vec_p4_of_gamma2_pi0_Sigma_after_4C, vec_p4_of_pi0_Sigma_after_4C,
        vec_p4_of_proton_Sigma_after_4C, vec_p4_of_gamma1_pi0_Sigma_before_4C,
        vec_p4_of_gamma2_pi0_Sigma_before_4C, vec_p4_of_proton_Sigma_before_4C,
        vec_p4_of_gamma1_pi0_Sigma_after_3C,
        vec_p4_of_gamma2_pi0_Sigma_after_3C;
    vec_p4_of_gamma1_pi0_Sigma_after_4C.clear();
    vec_p4_of_gamma2_pi0_Sigma_after_4C.clear();
    vec_p4_of_proton_Sigma_after_4C.clear();
    vec_p4_of_gamma1_pi0_Sigma_before_4C.clear();
    vec_p4_of_gamma2_pi0_Sigma_before_4C.clear();
    vec_p4_of_proton_Sigma_before_4C.clear();
    vec_p4_of_gamma1_pi0_Sigma_after_3C.clear();
    vec_p4_of_gamma2_pi0_Sigma_after_3C.clear();

    // mass
    Vdouble vec_mass_Pi0, vec_mass_Eta, vec_mass_Pi0_Sigma,
        vec_mass_Sigma /*,vec_mass_2Pi012,vec_mass_2Pi013,vec_mass_2Pi023*/;
    vec_mass_Pi0.clear();
    vec_mass_Eta.clear();
    vec_mass_Pi0_Sigma.clear();
    vec_mass_Sigma
        .clear(); /*vec_mass_2Pi012.clear();vec_mass_2Pi013.clear();vec_mass_2Pi023.clear();*/

    for (int i = 0; i < isig; i++) {
      // get p4
      TLorentzVector pi0_p4, eta_p4, pi0_sigma_p4, sigma_p4;
      TLorentzVector pi0_p4_4c, eta_p4_4c, pi0_sigma_p4_4c;
      for (int p = 0; p < 4; p++) {
        eta_p4[p] =
            p4_of_Gamma1_Eta_before_4C[i][p] + p4_of_Gamma2_Eta_before_4C[i][p];
        pi0_sigma_p4[p] = p4_of_gamma1_pi0_Sigma_before_4C[i][p] +
                          p4_of_gamma2_pi0_Sigma_before_4C[i][p];

        eta_p4_4c[p] =
            p4_of_Gamma1_Eta_after_4C[i][p] + p4_of_Gamma2_Eta_after_4C[i][p];
        pi0_sigma_p4_4c[p] = p4_of_gamma1_pi0_Sigma_after_4C[i][p] +
                             p4_of_gamma2_pi0_Sigma_after_4C[i][p];
        sigma_p4[p] = p4_of_gamma1_pi0_Sigma_after_3C[i][p] +
                      p4_of_gamma2_pi0_Sigma_after_3C[i][p] +
                      p4_of_proton_Sigma_before_4C[i][p];
      }
      // cut pi0 with mass region

      double mass_eta = eta_p4.M(), mass_pi0_sigma = pi0_sigma_p4.M(),
             mass_sigma = sigma_p4.M();

      if (mass_eta > etaMaxMass || mass_eta < etaMinMass)
        continue;
      if (mass_pi0_sigma > pi0MaxMass || mass_pi0_sigma < pi0MinMass)
        continue;
      if (mass_sigma > sigmaMaxMass || mass_sigma < sigmaMinMass)
        continue;

      // cut angle between gamma and antiproton
      if (angle[i] <= ang)
        continue;

      // mbc and deltaE cut
      if (M_BC[i] < mbcMin || M_BC[i] > mbcMax)
        continue;
      if (deltaE_min[i] < deltaEMin || deltaE_min[i] > deltaEMax)
        continue;

      // choose best pi0 for sigma
      // save
      vec_charge.push_back(charge[i]);
      vec_chi2_3C.push_back(chi2_3C[i]);
      vec_chi2_4C.push_back(chi2_4C[i]);
      vec_angle.push_back(angle[i]);
      vec_deltaE_min.push_back(deltaE_min[i]);
      vec_M_BC.push_back(M_BC[i]);

      // pi02
      vec_p4_of_Gamma1_Eta_before_4C.push_back(p4_of_Gamma1_Eta_before_4C[i]);
      vec_p4_of_Gamma2_Eta_before_4C.push_back(p4_of_Gamma2_Eta_before_4C[i]);
      vec_p4_of_Gamma1_Eta_after_4C.push_back(p4_of_Gamma1_Eta_after_4C[i]);
      vec_p4_of_Gamma2_Eta_after_4C.push_back(p4_of_Gamma2_Eta_after_4C[i]);

      // sigma+
      vec_p4_of_gamma1_pi0_Sigma_after_4C.push_back(
          p4_of_gamma1_pi0_Sigma_after_4C[i]);
      vec_p4_of_gamma2_pi0_Sigma_after_4C.push_back(
          p4_of_gamma2_pi0_Sigma_after_4C[i]);
      vec_p4_of_proton_Sigma_after_4C.push_back(p4_of_proton_Sigma_after_4C[i]);
      vec_p4_of_gamma1_pi0_Sigma_before_4C.push_back(
          p4_of_gamma1_pi0_Sigma_before_4C[i]);
      vec_p4_of_gamma2_pi0_Sigma_before_4C.push_back(
          p4_of_gamma2_pi0_Sigma_before_4C[i]);
      vec_p4_of_proton_Sigma_before_4C.push_back(
          p4_of_proton_Sigma_before_4C[i]);
      vec_p4_of_gamma1_pi0_Sigma_after_3C.push_back(
          p4_of_gamma1_pi0_Sigma_after_3C[i]);
      vec_p4_of_gamma2_pi0_Sigma_after_3C.push_back(
          p4_of_gamma2_pi0_Sigma_after_3C[i]);

      // mass
      vec_mass_Eta.push_back(mass_eta);
      vec_mass_Pi0_Sigma.push_back(mass_pi0_sigma);
      vec_mass_Sigma.push_back(mass_sigma);
    }
    if (vec_chi2_4C.size() != 0) {
      // m_run = run;
      // m_event = event;

      double chisq_min_tmp = 9999.;

      for (unsigned int j = 0; j < vec_chi2_4C.size(); j++) {
        if (fabs(vec_chi2_4C[j]) < fabs(chisq_min_tmp)) {
          chisq_min_tmp = fabs(vec_chi2_4C[j]);

          m_deltaE_min = vec_deltaE_min[j];
          m_bc = vec_M_BC[j];

          // mass
          // m_Pi0_mass = vec_mass_Pi0[j];
          m_Eta_mass = vec_mass_Eta[j];
          m_Pi0_Sigma_mass = vec_mass_Pi0_Sigma[j];
          m_Sigma_mass = vec_mass_Sigma[j];
        }
      }
      tree->Fill();
    }
  }

  tree->Write();
  f_new->Close();
  f->Close();
  //	TChain *chain1 = new TChain ("DTag");
  //	chain1->Add("Tag*.root");
  //	TFile * file = new TFile("data_tagAll.root","recreate");
  //	TTree *tree1 = chain1->CopyTree("");
  //	tree1->Write();
  //	file->Close();

  return 0;
}

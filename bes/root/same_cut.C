#include <string>
#include <vector>
#include <iostream>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
using namespace std;
typedef std::vector<int> Vint;
typedef std::vector<double> Vdouble;
//typedef std::vector<HepLorentzVector> Vp4;
typedef std::vector<string> Vstring;
const double mass[5] = {0.000511, 0.105658, 0.139570,0.493677, 0.938272};
void same_cut(){
    
    //define the variables
    Double_t deltaE[1000]; Int_t deltaE_index; Double_t mbc[1000];
    Double_t km_p4[1000][4]; Double_t kp_p4[1000][4];
    Int_t indexmc; Int_t motheridx[100]; Int_t pdgid[100]; Int_t flag1;
    Double_t pi_p4[1000][4]; Double_t sigD_p4[1000][4]; Int_t pi_charge[1000];
    Int_t nMC;Int_t mother[500];Int_t pid[500]; 
    Double_t truemom[500],truept[500],truephi[500],truetheta[500];    

    //the input file
    TFile* f;
    TTree* t;
    //the output file
    TFile* f_new;
    TTree* tree;
    
    
    f=new TFile("all.root","");
    t=(TTree*)f->Get("TDphipi");
    //load the tuples
    TBranch *branch1  = t->GetBranch("deltaE");
    TBranch *branch2  = t->GetBranch("deltaE_index");
    TBranch *branch3  = t->GetBranch("mbc");
    TBranch *branch4  = t->GetBranch("km_p4");
    TBranch *branch5  = t->GetBranch("kp_p4");
    TBranch *branch6  = t->GetBranch("indexmc");
    TBranch *branch7  = t->GetBranch("motheridx");
    TBranch *branch8  = t->GetBranch("pdgid");
    TBranch *branch9  = t->GetBranch("flag1");
    TBranch *branch10 = t->GetBranch("pi_p4");
    TBranch *branch11 = t->GetBranch("sigD_p4");
    TBranch *branch12 = t->GetBranch("pi_charge");
    TBranch *branch13 = t->GetBranch("nMC");
    TBranch *branch14 = t->GetBranch("pid");
    TBranch *branch15 = t->GetBranch("mother");
    TBranch *branch16 = t->GetBranch("truemom");
    TBranch *branch17 = t->GetBranch("truept");
    TBranch *branch18 = t->GetBranch("truephi");
    TBranch *branch19 = t->GetBranch("truetheta");
    
    
    branch1->SetAddress(&deltaE);
    branch2->SetAddress(&deltaE_index);
    branch3->SetAddress(&mbc);
    branch4->SetAddress(&km_p4);
    branch5->SetAddress(&kp_p4);
    branch6->SetAddress(&indexmc);
    branch7->SetAddress(&motheridx);
    branch8->SetAddress(&pdgid);
    branch9->SetAddress(&flag1);
    branch10->SetAddress(&pi_p4);
    branch11->SetAddress(&sigD_p4);
    branch12->SetAddress(&pi_charge);
    branch13->SetAddress(&nMC);
    branch14->SetAddress(&pid);
    branch15->SetAddress(&mother);
    branch16->SetAddress(&truemom);
    branch17->SetAddress(&truept);
    branch18->SetAddress(&truephi);
    branch19->SetAddress(&truetheta);
    
    int nevent=t->GetEntries();
    
    Double_t dE_min;Double_t mbc_1;Double_t M_phi;Double_t E_phi;Double_t P_phi;
    Double_t km_p4_x;Double_t km_p4_y;Double_t km_p4_z;Double_t km_p4_t;
    Double_t kp_p4_x;Double_t kp_p4_y;Double_t kp_p4_z;Double_t kp_p4_t;
    Int_t indexmc_1; Int_t motheridx_1[100]; Int_t pdgid_1[100];Int_t flag1_1;
    Int_t AA;Int_t BB;Int_t CC;
    Double_t pi_p4_x;Double_t pi_p4_y;Double_t pi_p4_z;Double_t pi_p4_t;
    Double_t sigD_p4_x;Double_t sigD_p4_y;Double_t sigD_p4_z;Double_t sigD_p4_t;
    Int_t pi_charge_1;
    Int_t nMC_1, pid_1[500],mother_1[500];
    Double_t truemom_1[500],truept_1[500],truephi_1[500],truetheta_1[500];
    Int_t index_deltaE;

    //recreate the new file
    f_new=new TFile("same_deltaE.root","recreate");
    tree=new TTree("TDphipi","");
    //tree=t->CloneTree(0);
    tree->Branch("dE_min",&dE_min,"dE_min/D");
    tree->Branch("mbc_1",&mbc_1,"mbc_1/D");
    tree->Branch("E_phi",&E_phi,"E_phi/D");
    tree->Branch("P_phi",&P_phi,"P_phi/D");
    tree->Branch("M_phi",&M_phi,"M_phi/D");
    tree->Branch("indexmc_1",&indexmc_1,"indexmc_1/I");
    tree->Branch("motheridx_1",&motheridx_1,"motheridx_1[indexmc_1]/I");
    tree->Branch("pdgid_1",&pdgid_1,"pdgid_1[indexmc_1]/I");
    tree->Branch("flag1_1",&flag1_1,"flag1_1/I");
    tree->Branch("AA",&AA,"AA/I");
    tree->Branch("BB",&BB,"BB/I");
    tree->Branch("CC",&CC,"CC/I");
    tree->Branch("index_deltaE",&index_deltaE,"index_deltaE/I");
    tree->Branch("nMC_1",&nMC_1,"nMC_1/I");
    tree->Branch("mother_1",&mother_1,"mother_1[nMC_1]/I");
    tree->Branch("pid_1",&pid_1,"pid_1[nMC_1]/I");
    tree->Branch("truemom_1",&truemom_1,"truemom_1[nMC_1]/D");
    tree->Branch("truept_1",&truept_1,"truept_1[nMC_1]/D");
    tree->Branch("truephi_1",&truephi_1,"truephi_1[nMC_1]/D");
    tree->Branch("truetheta_1",&truetheta_1,"truetheta_1[nMC_1]/D");
    
    tree->Branch("km_p4_x",&km_p4_x,"km_p4_x/D");
    tree->Branch("km_p4_y",&km_p4_y,"km_p4_y/D");
    tree->Branch("km_p4_z",&km_p4_z,"km_p4_z/D");
    tree->Branch("km_p4_t",&km_p4_t,"km_p4_t/D");
    
    tree->Branch("kp_p4_x",&kp_p4_x,"kp_p4_x/D");
    tree->Branch("kp_p4_y",&kp_p4_y,"kp_p4_y/D");
    tree->Branch("kp_p4_z",&kp_p4_z,"kp_p4_z/D");
    tree->Branch("kp_p4_t",&kp_p4_t,"kp_p4_t/D");
    
    tree->Branch("pi_p4_x",&pi_p4_x,"pi_p4_x/D");
    tree->Branch("pi_p4_y",&pi_p4_y,"pi_p4_y/D");
    tree->Branch("pi_p4_z",&pi_p4_z,"pi_p4_z/D");
    tree->Branch("pi_p4_t",&pi_p4_t,"pi_p4_t/D");
    
    tree->Branch("sigD_p4_x",&sigD_p4_x,"sigD_p4_x/D");
    tree->Branch("sigD_p4_y",&sigD_p4_y,"sigD_p4_y/D");
    tree->Branch("sigD_p4_z",&sigD_p4_z,"sigD_p4_z/D");
    tree->Branch("sigD_p4_t",&sigD_p4_t,"sigD_p4_t/D");
    
    tree->Branch("pi_charge_1",&pi_charge_1,"pi_charge_1/I");
    
    //loop the event
    for(int i=0;i<nevent;i++){
        t->GetEvent(i);
        flag1_1=flag1;
        int AA = (int) (flag1/1000000);
        int BB = (int) (flag1-AA*1000000)/1000;
        int CC = flag1-AA*1000000-BB*1000;
        
	indexmc_1=indexmc;
	for(int idxmc=0;idxmc<indexmc;idxmc++){
            motheridx_1[idxmc]=motheridx[idxmc];
            pdgid_1[idxmc]=pdgid[idxmc];
        }
	              nMC_1=nMC;
	              for(int idxmc=0;idxmc<nMC;idxmc++){
                     mother_1[idxmc]=mother[idxmc];
                     pid_1[idxmc]=pid[idxmc];
                     truemom_1[idxmc]=truemom[idxmc];
                     truept_1[idxmc]=truept[idxmc];
                     truephi_1[idxmc]=truephi[idxmc];
                     truetheta_1[idxmc]=truetheta[idxmc];
                }
        
        Double_t deltaE_min=9999.;
        Int_t n=0;
        for(int dE_idx=0;dE_idx<deltaE_index;dE_idx++){
            //add your event selection and other things here
            
                //cout<<deltaE[dE_idx]<<endl;  
                pi_charge_1 = pi_charge[dE_idx];
                dE_min=deltaE[dE_idx];
                deltaE_min=deltaE[dE_idx];
                mbc_1=mbc[dE_idx];
                km_p4_x=km_p4[dE_idx][0];
                km_p4_y=km_p4[dE_idx][1];
                km_p4_z=km_p4[dE_idx][2];
                km_p4_t=km_p4[dE_idx][3];
                
                kp_p4_x=kp_p4[dE_idx][0];
                kp_p4_y=kp_p4[dE_idx][1];
                kp_p4_z=kp_p4[dE_idx][2];
                kp_p4_t=kp_p4[dE_idx][3];
                E_phi  =km_p4_t+kp_p4_t;
                P_phi  =sqrt((km_p4_x+kp_p4_x)*(km_p4_x+kp_p4_x)+(km_p4_y+kp_p4_y)*(km_p4_y+kp_p4_y)+(km_p4_z+kp_p4_z)*(km_p4_z+kp_p4_z));
                M_phi  =sqrt(E_phi*E_phi-P_phi*P_phi);
                
                pi_p4_x=pi_p4[dE_idx][0];
                pi_p4_y=pi_p4[dE_idx][1];
                pi_p4_z=pi_p4[dE_idx][2];
                pi_p4_t=pi_p4[dE_idx][3];
                sigD_p4_x=sigD_p4[dE_idx][0];
                sigD_p4_y=sigD_p4[dE_idx][1];
                sigD_p4_z=sigD_p4[dE_idx][2];
                sigD_p4_t=sigD_p4[dE_idx][3];

         if(fabs(deltaE[dE_idx])>1) continue; 
                if(mbc[dE_idx]<1.80 || mbc[dE_idx]>1.90 || M_phi>2) continue;
                //if(deltaE[dE_idx]==deltaE[dE_idx+1]||deltaE[dE_idx]==deltaE[dE_idx+2]||deltaE[dE_idx]==deltaE[dE_idx+3]||deltaE[dE_idx]==deltaE[dE_idx+4]||deltaE[dE_idx]==deltaE[dE_idx+5]||deltaE[dE_idx]==deltaE[dE_idx+6]||deltaE[dE_idx]==deltaE[dE_idx+7]||deltaE[dE_idx]==deltaE[dE_idx+8]||deltaE[dE_idx]==deltaE[dE_idx+9]||deltaE[dE_idx]==deltaE[dE_idx+10]||deltaE[dE_idx]==deltaE[dE_idx+11]||deltaE[dE_idx]==deltaE[dE_idx+12]||deltaE[dE_idx]==deltaE[dE_idx+13]||deltaE[dE_idx]==deltaE[dE_idx+14]||deltaE[dE_idx]==deltaE[dE_idx+15]||deltaE[dE_idx]==deltaE[dE_idx+16]||deltaE[dE_idx]==deltaE[dE_idx+17]||deltaE[dE_idx]==deltaE[dE_idx+18]||deltaE[dE_idx]==deltaE[dE_idx+19]||deltaE[dE_idx]==deltaE[dE_idx+20]) continue; 
                n++;
                index_deltaE=n;        
         
        }
        
        tree->Fill();//fill the event to the new tree
    }
    tree->Write();//write to the new file
    f->Close();
}









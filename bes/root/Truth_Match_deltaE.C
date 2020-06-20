#include "TFile.h"
#include "TTree.h"
#include "TVector3.h"
#include "TBranch.h"

void Truth_Match_deltaE(){

		Int_t           flag1_1;
		Int_t           nMC_1;
		Int_t           pid_1[500];   //[indexmc]
		Int_t           mother_1[500];   //[indexmc]
		Double_t        truemom_1[500];   //[p4index]
		Double_t        truept_1[500];   //[p4index]
		Double_t        truephi_1[500];   //[p4index]
		Double_t        truetheta_1[500];   //[p4index]
		Double_t        kp_p4_x;   //[p4index]
		Double_t        kp_p4_y;   //[p4index]
		Double_t        kp_p4_z;   //[p4index]
		Double_t        km_p4_x;   //[p4index]
		Double_t        km_p4_y;   //[p4index]
		Double_t        km_p4_z;   //[p4index]
		Double_t        pi_p4_x;   //[p4index]
		Double_t        pi_p4_y;   //[p4index]
		Double_t        pi_p4_z;   //[p4index]
		Int_t           pi_charge_1;   //[p4index]
		Double_t        mbc_1;
    Double_t        M_phi; 
          
	  TFile *f = new TFile("cut_MC.root");
    TTree *tree =(TTree*)f->Get("TDphipi");	
    TBranch *b1 = tree->GetBranch("flag1_1");
		TBranch *b2 = tree->GetBranch("nMC_1");
		TBranch *b3 = tree->GetBranch("pid_1");
		TBranch *b4 = tree->GetBranch("mother_1");
		TBranch *b5 = tree->GetBranch("truemom_1");
		TBranch *b6 = tree->GetBranch("truept_1");
		TBranch *b7 = tree->GetBranch("truephi_1");
		TBranch *b8 = tree->GetBranch("truetheta_1");
		TBranch *b9 = tree->GetBranch("kp_p4_x");
		TBranch *b10 = tree->GetBranch("kp_p4_y");
		TBranch *b11 = tree->GetBranch("kp_p4_z");
		TBranch *b12 = tree->GetBranch("km_p4_x");
		TBranch *b13 = tree->GetBranch("km_p4_y");
		TBranch *b14 = tree->GetBranch("km_p4_z");
		TBranch *b15 = tree->GetBranch("pi_p4_x");
		TBranch *b16 = tree->GetBranch("pi_p4_y");
		TBranch *b17 = tree->GetBranch("pi_p4_z");
		TBranch *b18 = tree->GetBranch("mbc_1");
		//TBranch *b23 = tree->GetBranch("deltaE_index_1");
		TBranch *b19 = tree->GetBranch("pi_charge_1");
		TBranch *b20 = tree->GetBranch("M_phi");

    b1->SetAddress(&flag1_1);
    b2->SetAddress(&nMC_1);
    b3->SetAddress(&pid_1);
    b4->SetAddress(&mother_1);
    b5->SetAddress(&truemom_1);
    b6->SetAddress(&truept_1);
    b7->SetAddress(&truephi_1);
    b8->SetAddress(&truetheta_1);
    b9->SetAddress(&kp_p4_x);
                b10->SetAddress(&kp_p4_y);
                b11->SetAddress(&kp_p4_z);
                b12->SetAddress(&km_p4_x);
                b13->SetAddress(&km_p4_y);
                b14->SetAddress(&km_p4_z);
                b15->SetAddress(&pi_p4_x);
                b16->SetAddress(&pi_p4_y);
                b17->SetAddress(&pi_p4_z);
                b18->SetAddress(&mbc_1);
                //b23->SetAddress(&deltaE_index1);
                b19->SetAddress(&pi_charge_1);
                b20->SetAddress(&M_phi);

                double anglekplus;
                double anglekminus;
                double anglepion;
                double deltakplus;
                double deltakminus;
                double deltapion;
                //Int_t           flag11;
                //Int_t           mode1;
                //Int_t           mode2;
                //Int_t           mode3;
		            //Int_t           deltaE_index1;
                // Int_t           nMC1;
                //Int_t           pid1[500];   //[indexmc]
                //Int_t           mother1[500];   //[indexmc]
                //Double_t        truemom1[500];   //[p4index]
                //Double_t        truept1[500];   //[p4index]
                //Double_t        truephi1[500];   //[p4index]
                //Double_t        truetheta1[500];   //[p4index]
                //Double_t        km_p41[1000][4];   //[p4index]
                //Double_t        kp_p41[1000][4];   //[p4index]
                //Double_t        k_p41[1000][4];   //[p4index]
                //int             k_charge_1[1000];   //[p4index]
                double mbc;
                double Mphi;

                TFile *f2= new TFile("truth_match3.root","recreate");
                TTree *t1 = new TTree("tree","");
                t1->Branch("anglekplus",&anglekplus,"anglekplus/D"); 
                t1->Branch("anglekminus",&anglekminus,"anglekminus/D");
                t1->Branch("anglepion",&anglepion,"anglepion/D");
                t1->Branch("deltakplus",&deltakplus,"deltakplus/D");
                t1->Branch("deltakminus",&deltakminus,"deltakminus/D");
                t1->Branch("deltapion",&deltapion,"deltapion/D");
                //t1->Branch("flag11", &flag11,"flag11/I");
                //t1->Branch("mode1", &mode1,"mode1/I");
                //t1->Branch("mode2", &mode2,"mode2/I");
                //t1->Branch("mode3", &mode3,"mode3/I");
                //t1->Branch("nMC11", &nMC11,"nMC11/I");
                //t1->Branch("pid11", &pid11,"pid11[nMC11]/I");
                //t1->Branch("mother11", &mother11,"mother11[nMC11]/I");
                //t1->Branch("indexmc1", &indexmc1,"indexmc1/I");
               // t1->Branch("pdgid1", &pdgid1,"pdgid1[indexmc1]/I");
                //t1->Branch("motheridx1", &motheridx1,"motheridx1[indexmc1]/I");
                //t1->Branch("truemom11", &truemom11,"truemom11[nMC11]/D");
                //t1->Branch("truept11", &truept11,"truept11[nMC11]/D");
                //t1->Branch("truephi11", &truephi11,"truephi11[nMC11]/D");
                //t1->Branch("truetheta11", &truetheta11,"truetheta11[nMC11]/D");
                //t1->Branch("deltaE_index1", &deltaE_index1,"deltaE_index1/D");
                //t1->Branch("kp_p41", &kp_p41,"kp_p41[deltaE_index1][4]/D");
                //t1->Branch("km_p41", &km_p41,"km_p41[deltaE_index1][4]/D");
                //t1->Branch("k_p41", &k_p41,"k_p41[deltaE_index1][4]/D");
                //t1->Branch("k_charge_1", &k_charge_1,"k_charge_1[deltaE_index1]/I");
                t1->Branch("mbc_1",&mbc_1,"mbc_1/D");
                t1->Branch("M_phi",&M_phi,"M_phi/D");



		Long64_t nentries = tree ->GetEntries();
		for(Long64_t i=0; i< nentries; i++){
//cout<<3333333333<<"   "<<nMC<<"   "<<mother<<endl;
				tree->GetEntry(i);
                                //flag11=flag1_1;
                                int mode1 = (int) (flag1_1/1000000);
                                int mode2 = (int) (flag1_1-mode1*1000000)/1000;
                                int mode3 = flag1_1-mode1*1000000-mode2*1000;
//cout<<9999999999<<"   "<<mode1<<"   "<<mode2<<"   "<<mode3<<endl;
                               // indexmc1=indexmc;
                                //for(int idxmc=0;idxmc<indexmc;idxmc++){
                                  //motheridx1[idxmc]=motheridx[idxmc];
                                  //pdgid1[idxmc]=pdgid[idxmc];
       // }   

        //MCtruth infor
             if(pid_1[8]==321){//&&mode3!=61&&mode3!=69&&mode3!=70){
                 Double_t truemom_kp_px=truept_1[8]*cos(truephi_1[8]);
                 Double_t truemom_kp_py=truept_1[8]*sin(truephi_1[8]);
                 Double_t truemom_kp_pz=truemom_1[8]*truetheta_1[8];
                 TVector3 truthkplusp  (truemom_kp_px, truemom_kp_py, truemom_kp_pz);
               }  
               if(pid_1[9]==-321){ //(D+ -> phi pi+ -> K+K- pi+)'s K- 
                 Double_t truemom_km_px=truept_1[9]*cos(truephi_1[9]);
                 Double_t truemom_km_py=truept_1[9]*sin(truephi_1[9]);
                 Double_t truemom_km_pz=truemom_1[9]*truetheta_1[9];
                 TVector3 truthkminusp  (truemom_km_px, truemom_km_py, truemom_km_pz);
               }
               if(pid_1[7]==211){ //(D+ ->phi pi+ -> K+K- pi+)'s pi+
                 Double_t truemom_pi_px=truept_1[7]*cos(truephi_1[7]);
                 Double_t truemom_pi_py=truept_1[7]*sin(truephi_1[7]);
                 Double_t truemom_pi_pz=truemom_1[7]*truetheta_1[7];
                 TVector3 truthpion  (truemom_pi_px, truemom_pi_py, truemom_pi_pz);
               }
 
              //rec infor
              TVector3 reckplus, reckminus, recpion;
              TVector3 reckplus   (kp_p4_x, kp_p4_y, kp_p4_z);
              TVector3 reckminus   (km_p4_x, km_p4_y, km_p4_z);
              TVector3 recpion   (pi_p4_x,pi_p4_y, pi_p4_z);
						
                                                //charged tracks
						double anglekplus  = reckplus.Angle(truthkplusp); // put K+, K- inverse
						//double akplus2  = reckminus.Angle(truthkaonp);
						//anglekplus = akplus1 < akplus2 ? akplus1:akplus2;
						double anglekminus = reckminus.Angle(truthkminusp); 
						//double akaon2  = reckaonp.Angle(truthkplusp);
						//anglekaonp = akaon1 < akaon2 ? akaon1:akaon2;
						double anglepion = recpion.Angle(truthpion);

						//=====momentum difference======
						TVector3 dkplus;//dkplus2;	
						TVector3 dpion;//dkaon2;	
						TVector3 dkminus;	

						dkplus = reckplus - truthkplusp; //dkplus2 = reckminus-truthkaonp;
						dkminus  = reckminus - truthkminusp; //dkaon2 = reckaonp-truthkplusp;
						dpion = recpion - truthpion; 

            deltakplus = dkplus.Mag();
            deltakminus = dkminus.Mag();
            deltapion = dpion.Mag();
   
            //mbc = mbc_1;
            //Mphi = M_phi;
						//deltakplus = dkplus1.Mag()<dkplus2.Mag()? dkplus1.Mag():dkplus2.Mag();	
						//deltakaonp = dkaon1.Mag()<dkaon2.Mag()? dkaon1.Mag():dkaon2.Mag();	
						//deltakminus = dkminus.Mag(); 
						t1->Fill();

		}
		t1->Write();
		f2->Write();
		f2->Close();
}

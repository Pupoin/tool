#include "TRandom.h"
#include "TString.h"
void efficiency(){
     // ************* Input **************
     TString FILENAME_I_1 = "all.root";
     TFile *FILE_I_1 = new TFile(FILENAME_I_1);
     TString TREENAME_I_1 = "TDphipi";
     TTree *TREE_I_1 = (TTree*)FILE_I_1->Get(TREENAME_I_1);
     int ientries = (int)TREE_I_1->GetEntries();
     cout << "******!!!!!******  IEntries are: = " << ientries <<endl;  
     
     int flag1; //int deltaE_index; double mbc[1000];
     //load the tuples
     TBranch *branch1  = TREE_I_1->GetBranch("flag1");
     //TBranch *branch2  = TREE_I_1->GetBranch("mbc");     
     //TBranch *branch3  = TREE_I_1->GetBranch("deltaE_index");     
     branch1->SetAddress(&flag1);
     //branch2->SetAddress(&mbc);
     //branch3->SetAddress(&deltaE_index);
     
     // ************* Output *************
     TFile *FILE_O_1 = new TFile("flag1.root","recreate");
     TTree *TREE_O_1 = new TTree("TDphipi","");
     
     int flag1_tr; int AA; int BB; int CC; //double mbc_1;
     TREE_O_1->Branch("flag1_tr",&flag1_tr,"flag1_tr/I");
     TREE_O_1->Branch("AA",&AA,"AA/I");
     TREE_O_1->Branch("BB",&BB,"BB/I");
     TREE_O_1->Branch("CC",&CC,"CC/I");
     //TREE_O_1->Branch("mbc_1",&mbc_1,"mbc_1/D");
    
     for(int i=0;i<ientries;i++){
        TREE_I_1->GetEvent(i); 
        flag1_tr=flag1;
        int AA = (int) (flag1/1000000);
        int BB = (int) (flag1-AA*1000000)/1000;
        int CC = flag1-AA*1000000-BB*1000;
        //for(int dE_idx=0;dE_idx<deltaE_index;dE_idx++){
        //mbc_1=mbc[dE_idx];
        //}
        TREE_O_1->Fill();
     }
     int oentries = (int)TREE_O_1->GetEntries();
     cout << "!!!!!!!!!********!!!!!!!! OEntries are : " << oentries << endl; 
     TREE_O_1->Write();  // write to the new file
     FILE_I_1->Close();

}

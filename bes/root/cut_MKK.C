void cut_MKK(){

     TChain *chain =new TChain("TDphipi");
     chain->Add("/scratchfs/bes/lincx/6.6.4.p02/DptoPhiPi/job_ana/root/same_deltaE1.root");
     TCut cut = "M_phi>1.01&&M_phi<1.03&&mbc_1>1.86&&mbc_1<1.88&&pi_charge_1==1";
    
     TFile *file = new TFile("cut_MKK1.root","recreate");
     TTree *TDphipi = chain->CopyTree(cut);
     cout<<TDphipi->GetEntries()<<endl;
     
     TDphipi->Write();
     file->Close();

}

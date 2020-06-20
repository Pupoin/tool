void cut_index(){

     TChain *chain =new TChain("TDphipi");
     chain->Add("/scratchfs/bes/lincx/6.6.4.p02/DptoPhiPi/job_ana/root/same_deltaE.root");
     TCut cut = "index_deltaE>1";
    
     TFile *file = new TFile("cut_index2.root","recreate");
     TTree *TDphipi = chain->CopyTree(cut);
     cout<<TDphipi->GetEntries()<<endl;
     
     TDphipi->Write();
     file->Close();

}

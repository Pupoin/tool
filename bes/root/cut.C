void cut(){

     TChain *chain =new TChain("TDphipi");
     chain->Add("/scratchfs/bes/lincx/6.6.4.p02/DptoPhiPi/job_ana/root/all_deltaE.root");
     TCut cut = "dE_min>-0.02&&dE_min<0.019&&M_phi>0.987354&&M_phi<1.085&&mbc_1>1.83&&mbc_1<1.8865";
     
     TFile *file = new TFile("cut_MC.root","recreate");
     TTree *TDphipi = chain->CopyTree(cut);
     cout<<TDphipi->GetEntries()<<endl;

     TDphipi->Write();
     file->Close();

}

void hadd_all(){
	TChain *chain1 = new TChain ("TDphipi");
	TChain *chain2 = new TChain ("TDphipi_truth");
	chain1->Add("ana*.root");
	chain2->Add("ana*.root");
   
  TFile * file = new TFile("all.root","recreate");
	TTree *TDphipi = chain1->CopyTree("");
	TTree *TDphipi_truth = chain2->CopyTree("");
 
  TDphipi->Write();
  TDphipi_truth->Write();
  file->Close();
}

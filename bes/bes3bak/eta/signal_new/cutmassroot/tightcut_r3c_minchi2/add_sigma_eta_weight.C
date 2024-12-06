
void addSingleWeight(string inFileName);

void add_sigma_eta_weight() 
{
    string fileList[] = {
        "4600signal_Costheta_sigma.root", 
        "4612signal_Costheta_sigma.root", 
        "4620signal_Costheta_sigma.root", 
        "4640signal_Costheta_sigma.root", 
        "4660signal_Costheta_sigma.root", 
        "4680signal_Costheta_sigma.root", 
        "4700signal_Costheta_sigma.root"
        };

    for(int i_file=0; i_file<7; i_file++ )
    {
        addSingleWeight(fileList[i_file]);
    }
}




void addSingleWeight(string inFileName) {

    TFile f1("weight.root");
    auto weightA = f1.Get<TH1D>("modelA_norminal");
    auto weightB = f1.Get<TH1D>("modelB_norminal");

    // f.Close();

    TFile f(inFileName.c_str(), "update");
    Double_t Costheta_sigma, weightp, weightm;
    auto t3 = f.Get<TTree>("tree");
    t3->SetBranchAddress("Costheta_sigma", &Costheta_sigma);
    auto newBranchp = t3->Branch("weightp", &weightp, "weightp/D");
    auto newBranchm = t3->Branch("weightm", &weightm, "weightm/D");
    Long64_t nentries = t3->GetEntries(); // read the number of entries in the t3
 
    
    for (Long64_t i = 0; i < nentries; i++) 
    {
        t3->GetEntry(i);
        if( i %5000  ==  0 ) cout << i << " " ;

        int index = int(Costheta_sigma/0.002) + 501;
        weightp = weightA->GetBinContent(index);
        weightm = weightB->GetBinContent(index);
                
        newBranchp->Fill();
        newBranchm->Fill();

        // break;
    }
 
    // t3->Write("", TObject::kWriteDelete); // save only the new version of the tree
    // t3->Write("", TObject::kOverwrite); // save only the new version of the tree
    t3->Write(""); // save only the new version of the tree
}


// TFile f("4700signal.root", "UPDATE");
// // gDirectory->Delete("tree;4")    
// gDirectory->Delete("tree;3")    
// gDirectory->Delete("tree;2")    

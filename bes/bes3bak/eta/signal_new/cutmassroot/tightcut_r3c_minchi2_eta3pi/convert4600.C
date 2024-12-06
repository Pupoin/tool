
void convert4600() {
    TFile f("4600signal.root", "update");
 
    
    Double_t new_Ap_ptruth[200]={0.0}, new_Am_ptruth[200]={0.0}, Ap_ptruth[200][4], Am_ptruth[200][4];
    int ndaughterAm, ndaughterAp;

    auto t3 = f.Get<TTree>("tree");

    t3->SetBranchAddress("Ap_ptruth", &Ap_ptruth);
    t3->SetBranchAddress("Am_ptruth", &Am_ptruth);
    t3->SetBranchAddress("ndaughterAm", &ndaughterAm);
    t3->SetBranchAddress("ndaughterAp", &ndaughterAp);

    auto newBranchp = t3->Branch("new_Ap_ptruth", &new_Ap_ptruth, "new_Ap_ptruth[200]/D");
    auto newBranchm = t3->Branch("new_Am_ptruth", &new_Am_ptruth, "new_Am_ptruth[200]/D");
 
    Long64_t nentries = t3->GetEntries(); // read the number of entries in the t3
 
    
    for (Long64_t i = 0; i < nentries; i++) {
        t3->GetEntry(i);
        if( i %2000  ==  1 )
            cout << i << " " ;
        for (int aa = 0; aa < ndaughterAp; aa++)
        {
            for (int ll = 0; ll < 4; ll++)
            {
                new_Ap_ptruth[aa*4+ll] = Ap_ptruth[aa][ll];
                
                // cout << __LINE__ << "    " << new_Ap_ptruth[aa*4+ll] << " ";
            }
            // cout << __LINE__ << "    "  <<  ", " << Ap_ptruth[aa][0] << " " << Ap_ptruth[aa][1] << " "<< Ap_ptruth[aa][2] << " "<< Ap_ptruth[aa][3] << " "<< endl;

        }
        newBranchp->Fill();
    
        for (int aa = 0; aa < ndaughterAm; aa++)
        {
            for (int ll = 0; ll < 4; ll++)
            {
                new_Am_ptruth[aa*4+ll] = Am_ptruth[aa][ll];
                
                // cout << __LINE__ << "    " << new_Am_ptruth[aa*4+ll] << " ";
            }
            // cout << __LINE__ << "    "  <<  ", " << Am_ptruth[aa][0] << " " << Am_ptruth[aa][1] << " "<< Am_ptruth[aa][2] << " "<< Am_ptruth[aa][3] << " "<< endl;

        }
        newBranchm->Fill();
        
        memset(new_Ap_ptruth,0.0,sizeof(new_Ap_ptruth));
        memset(new_Am_ptruth,0.0,sizeof(new_Am_ptruth));
        // break;
    }
 
    // t3->Write("", TObject::kWriteDelete); // save only the new version of the tree
    // t3->Write("", TObject::kOverwrite); // save only the new version of the tree
    t3->Write(""); // save only the new version of the tree
}


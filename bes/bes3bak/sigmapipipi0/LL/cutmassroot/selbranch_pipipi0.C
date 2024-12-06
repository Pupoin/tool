// select branch
void selbranch_pipipi0()
{
    // ROOT::RDataFrame rdf("tree", "4700LL.root.root");
    TChain chain("tree");
    chain.Add("4700LL.root");

    TCut cut = "M_BC_r3c>2.25 && M_BC_r3c<2.35 && chi2_min_r3c<30 && ( (omegamr3c>0.68&&omegamr3c<0.72) || (omegamr3c>0.84&&omegamr3c<0.89) )";
    TTree *t=chain.CopyTree(cut);


    TFile f("4700LL_selB_topo.root", "recreate");
    t->Write();
    f.Close();


    // std::vector<std::string> branchList = 
    //         {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c",
    //         "signal","omegamr3c", "mode2", "mode3"
    //         }; 

    // rdf2.Snapshot("tree", "4700LL.root_selB_pipipi0.root", branchList );

}

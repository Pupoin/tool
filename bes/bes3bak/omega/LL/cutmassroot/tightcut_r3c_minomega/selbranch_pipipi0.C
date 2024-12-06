// select branch
void selbranch_pipipi0()
{
    // ROOT::RDataFrame rdf("tree", "AAA.root");
    TChain chain("tree");
    chain.Add("AAA.root");

    TCut cut = "M_BC_r3c>2.276 && M_BC_r3c<2.294 && np!=0 && npbar!=0 && chi2_min_r3c<30 && ( (etaprimemr3c>0.68&&etaprimemr3c<0.72) || (etaprimemr3c>0.84&&etaprimemr3c<0.89) )";
    TTree *t=chain.CopyTree(cut);


    TFile f("AAA_selB_pipipi0_topo.root", "recreate");
    t->Write();
    f.Close();


    // std::vector<std::string> branchList = 
    //         {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c",
    //         "signal","etaprimemr3c", "mode2", "mode3"
    //         }; 

    // rdf2.Snapshot("tree", "AAA_selB_pipipi0.root", branchList );

}

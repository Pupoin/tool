
// select branch
void addRandomBranch()
{
    ROOT::RDataFrame rdf("tree", "AAA_rmLc.root");

    auto  rdf2 = rdf.Filter("flag1!=96 && M_BC_r3c>2.2")
    .Filter("flag1!=96 && M_BC_r3c>2.2")
               
    ;


    std::vector<std::string> branchList = 
            {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c","flag1", "mode1", "mode2", "mode3"
             }; 

    rdf2.Snapshot("tree", "AAA_rmLc.root", branchList );
    //rdf2.Snapshot("tree", "AAA_rmLc.root");

}

// select branch
void selbranchnocut()
{
    ROOT::RDataFrame rdf("tree", "AAA.root");



    std::vector<std::string> branchList = 
            {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c", "etaprimemr3c"

            }; 

    rdf.Snapshot("tree", "AAA_selnocut.root", branchList );

}

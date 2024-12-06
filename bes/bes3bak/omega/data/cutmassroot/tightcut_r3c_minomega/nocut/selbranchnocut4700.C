// select branch
void selbranchnocut4700()
{
    ROOT::RDataFrame rdf("tree", "4700data.root");



    std::vector<std::string> branchList = 
            {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c", "etaprimemr3c"

            }; 

    rdf.Snapshot("tree", "4700data_selnocut.root", branchList );

}

// select branch
void selbranchnocut4640()
{
    ROOT::RDataFrame rdf("tree", "4640data.root");



    std::vector<std::string> branchList = 
            {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c", "etaprimemr3c"

            }; 

    rdf.Snapshot("tree", "4640data_selnocut.root", branchList );

}

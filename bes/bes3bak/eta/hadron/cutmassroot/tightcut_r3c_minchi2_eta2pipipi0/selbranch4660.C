// select branch
void selbranch4660()
{
    ROOT::RDataFrame rdf("tree", "4660hadron.root");

    auto  rdf2 = rdf.Filter("flag1!=96")
    ;


    std::vector<std::string> branchList = 
            {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c",
            "signal"
            }; 

    rdf2.Snapshot("tree", "4660hadron_selB.root", branchList );

}

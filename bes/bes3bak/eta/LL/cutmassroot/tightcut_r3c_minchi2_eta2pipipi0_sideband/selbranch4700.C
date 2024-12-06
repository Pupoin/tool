// select branch
void selbranch4700()
{
    ROOT::RDataFrame rdf("tree", "4700LL.root");

    auto  rdf2 = rdf.Filter("M_BC_r3c>2.2 && np!=0 && npbar!=0")
    ;


    std::vector<std::string> branchList = 
            {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c",
            "signal"
    ,"etam","pi0m"
            }; 

    rdf2.Snapshot("tree", "4700LL_selB.root", branchList );

}

// select branch
void selbranch4680()
{
    ROOT::RDataFrame rdf("tree", "4680LL.root");

    auto  rdf2 = rdf.Filter("M_BC_r3c>2.2 && np!=0 && npbar!=0")
    ;


    std::vector<std::string> branchList = 
            {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c",

            "signal","sigmam_r3c", "etam_r3c","pi0m_r3c",
            "etam","pi0m"
            }; 

    rdf2.Snapshot("tree", "4680LL_selB.root", branchList );

}

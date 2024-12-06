// select branch
void selbranch4680()
{
    ROOT::RDataFrame rdf("tree", "4680shape.root");

    auto  rdf2 = rdf.Filter("M_BC_r3c>2.2 && np!=0 && npbar!=0")
    ;


    std::vector<std::string> branchList = 
            {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c",

            }; 

    rdf2.Snapshot("tree", "4680shape_selB2.root", branchList );

}

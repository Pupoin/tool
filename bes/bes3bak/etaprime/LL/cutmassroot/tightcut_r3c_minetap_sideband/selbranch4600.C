// select branch
void selbranch4600()
{
    ROOT::RDataFrame rdf("tree", "4600LL.root");

//    auto  rdf2 = rdf.Filter("M_BC_r3c>2.2 && etaprimemr3c>0.946 && etaprimemr3c<0.968")
    auto  rdf2 = rdf.Filter("M_BC_r3c>2.2 && etaprimemr3c>0.91 && etaprimemr3c<1.")
    ;


    std::vector<std::string> branchList = 
            {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c",
            "signal","sigmamr3c", "etaprimemr3c","etamr3c","pi0mr3c",
            "sigmamr", "etaprimemr","etamr","pi0mr",
            }; 

    rdf2.Snapshot("tree", "4600LL_selB.root", branchList );

}

// select branch
void selbranch4680()
{
    ROOT::RDataFrame rdf("tree", "4680hadron.root");

    auto  rdf2 = rdf.Filter("M_BC_r3c>2.2 && np!=0 && npbar!=0 && flag1!=96 && etaprimemr3c>0.76 && etaprimemr3c<0.8")
    ;


    std::vector<std::string> branchList = 
            {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c","signal"
            
            }; 

    rdf2.Snapshot("tree", "4680hadron_selB.root", branchList );

}

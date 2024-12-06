// select branch
void selbranch_pipipi04660()
{
    ROOT::RDataFrame rdf("tree", "4660hadron.root");

    auto  rdf2 = rdf.Filter("M_BC_r3c>2.2 && np!=0 && npbar!=0 && flag1!=96")
    ;


    std::vector<std::string> branchList = 
            {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c","signal", "etaprimemr3c",  "mode2", "mode3"
            
            }; 

    rdf2.Snapshot("tree", "4660hadron_selB_pipipi0.root", branchList );

}

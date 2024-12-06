// select branch
void selbranch4680()
{
    ROOT::RDataFrame rdf("tree", "4680data.root");

    auto  rdf2 = rdf.Filter("M_BC_r3c>2.25")//&& ( (etaprimemr3c>0.71&&etaprimemr3c<0.73) || (etaprimemr3c>0.83&&etaprimemr3c<0.85) )")
                    // .Filter("(etaprimemr3c>0.71&&etaprimemr3c<0.73)")
                    // .Filter("(etaprimemr3c>0.83&&etaprimemr3c<0.85) ")
    ;


    std::vector<std::string> branchList = 
            {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c", "etaprimemr3c"

            }; 

    rdf2.Snapshot("tree", "4680data_selB2.root", branchList );

}

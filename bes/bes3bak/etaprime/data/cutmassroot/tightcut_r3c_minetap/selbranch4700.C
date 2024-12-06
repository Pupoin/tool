// select branch
void selbranch4700()
{
    ROOT::RDataFrame rdf("tree", "4700data.root");

    auto  rdf2 = rdf.Filter("M_BC_r3c>2.25")//&& ( (etaprimemr3c>0.91&&etaprimemr3c<0.93) || (etaprimemr3c>1.0&&etaprimemr3c<1.02) )")
                    // .Filter("(etaprimemr3c>1&&etaprimemr3c<1.03)")
    ;


    std::vector<std::string> branchList = 
            {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c", "etaprimemr3c"

            }; 

    rdf2.Snapshot("tree", "4700data_selB2.root", branchList );

}


// select branch
void selbranch4640()
{
    ROOT::RDataFrame rdf("tree", "4640data.root");

    auto  rdf2 = rdf.Filter("M_BC_r3c>2.2")
                    .Define("event_", "event")
                    .Define("run_", "run")
                    .Define("M_BC_r3c_", "M_BC_r3c")
                    .Define("np_", "np")
                    .Define("npbar_", "npbar")
                    .Define("chi2_min_r3c_", "chi2_min_r3c")
                    .Define("deltaE_min_r3c_", "deltaE_min_r3c")
                    .Define("gam1_r3c_", "gam1_r3c")     // (vector<double,ROOT::Detail::VecOps::RAdoptAllocator<double> >*)
                    .Define("gam2_r3c_", "gam2_r3c")
                    .Define("p_pipr_", "p_pipr")
                    .Define("p_pimr_", "p_pimr") 
                    .Define("etaprimemr_", "etaprimemr") 
               
    ;


    std::vector<std::string> branchList = 
            {"event_", "run_", "M_BC_r3c_", "np_", "npbar_", "chi2_min_r3c_", "deltaE_min_r3c_",
             "gam1_r3c_", "gam2_r3c_", "p_pipr_", "p_pimr_", "etaprimemr_" }; 

    rdf2.Snapshot("tree", "4640data_selB.root", branchList );

}
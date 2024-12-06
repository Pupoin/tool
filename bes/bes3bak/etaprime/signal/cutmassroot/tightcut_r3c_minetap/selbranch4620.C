// select branch
void selbranch4620()
{
    ROOT::RDataFrame rdf("tree", "4620signal.root");

    //////////////////////
    auto cal_p = [](
                    ROOT::VecOps::RVec<double> x1, 
                    ROOT::VecOps::RVec<double> x2
                ) 
    { 
        double px = x1[0] + x2[0];
        double py = x1[1] + x2[1];
        double pz = x1[2] + x2[2];
        double e  = x1[3] + x2[3];
        ROOT::Math::PxPyPzEVector tmp(px, py, pz, e);
        
        return  tmp.R(); 

    };
    //////////////////////
    auto addpi0weight = [](double x) 
    { 
        double weight = 1;

        if(x >= 0 && x<0.2)
            weight = 1 - 0.052;
        else if (x>=0.2 && x<0.4)
            weight = 1 - 0.026;
        else if (x>=0.4 && x<0.6)
            weight = 1 - 0.004;
        else if (x>=0.6 && x<0.8)
            weight = 1 - 0.004;
        else if (x>=0.8 && x<1.0)
            weight = 1 - 0.004;
        
        return weight;

    };
    //////////////////////



    auto  rdf2 = rdf.Filter("M_BC_r3c>2.2 && etaprimemr3c>0.946 && etaprimemr3c<0.968")
                    .Define("p_gam12", cal_p, {"gam1", "gam2"})
                    .Define("p_gam34", cal_p, {"gam3", "gam4"}) //   1,2 -> eta             3,4 -> pi  
                    .Define("pi0MassWeight", addpi0weight, {"p_gam34"})
                    .Define("etaMassWeight", addpi0weight, {"p_gam12"})
                    .Define("bothMassWeight", "pi0MassWeight * etaMassWeight")

    ;


    std::vector<std::string> branchList = 
            {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c", "signal",
            "p_gam12", "p_gam34", "pi0MassWeight", "etaMassWeight", "bothMassWeight"

            }; 

    rdf2.Snapshot("tree", "4620signal_selB.root", branchList );

}

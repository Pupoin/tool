
// select branch
void adddipim()
{
    ROOT::RDataFrame rdf("tree", "AAA.root");


    // auto caldipim = [](vector<double,ROOT::Detail::VecOps::RAdoptAllocator<double>> x1, 
    //                 vector<double,ROOT::Detail::VecOps::RAdoptAllocator<double>> x2, 
    //                 vector<double,ROOT::Detail::VecOps::RAdoptAllocator<double>> x3, 
    //                 vector<double,ROOT::Detail::VecOps::RAdoptAllocator<double>> x4
    //             ) 
    //////////////////////
    auto caldipim = [](
                    ROOT::VecOps::RVec<double> x1, 
                    ROOT::VecOps::RVec<double> x2, 
                    ROOT::VecOps::RVec<double> x3, 
                    ROOT::VecOps::RVec<double> x4
                ) 
    { 
        double px = x1[0] + x2[0] + x3[0] + x4[0];
        double py = x1[1] + x2[1] + x3[1] + x4[1];
        double pz = x1[2] + x2[2] + x3[2] + x4[2];
        double e  = x1[3] + x2[3] + x3[3] + x4[3];
        ROOT::Math::PxPyPzEVector tmp(px, py, pz, e);
        
        return  tmp.M(); 

    };

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

    auto  rdf2 = rdf//.Filter("M_BC_r3c>2.2")
                    .Define("dipim", caldipim, {"gam1", "gam2", "gam3", "gam4"})
                    .Define("p_gam12", cal_p, {"gam1", "gam2"})
                    .Define("p_gam34", cal_p, {"gam3", "gam4"}) //   1,2 -> eta             3,4 -> pi  
                    .Define("pi0MassWeight", addpi0weight, {"p_gam34"})
                    .Define("etaMassWeight", addpi0weight, {"p_gam12"})
                    .Define("bothMassWeight", "pi0MassWeight * etaMassWeight")
               
    ;


    std::vector<std::string> branchList = 
            {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c","flag1", "rightflag",
             "mode1", "mode2", "mode3", "dipim", "signal", "p_gam12", "p_gam34", "pi0MassWeight",
             "etaMassWeight", "bothMassWeight"
            }; 

    rdf2.Snapshot("tree", "AAA_adddipim.root", branchList );
    //rdf2.Snapshot("tree", "AAA_rmLc.root");

}

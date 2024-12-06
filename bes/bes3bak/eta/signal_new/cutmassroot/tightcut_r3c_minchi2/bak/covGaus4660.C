
// select branch
void covGaus4660()
{
    ROOT::RDataFrame rdf("tree", "4660signal.root");


    // auto caldipim = [](vector<double,ROOT::Detail::VecOps::RAdoptAllocator<double>> x1, 
    //                 vector<double,ROOT::Detail::VecOps::RAdoptAllocator<double>> x2, 
    //                 vector<double,ROOT::Detail::VecOps::RAdoptAllocator<double>> x3, 
    //                 vector<double,ROOT::Detail::VecOps::RAdoptAllocator<double>> x4
    //             ) 
    // auto caldipim = [](
    //                 ROOT::VecOps::RVec<double> x1, 
    //                 ROOT::VecOps::RVec<double> x2, 
    //                 ROOT::VecOps::RVec<double> x3, 
    //                 ROOT::VecOps::RVec<double> x4
    //             ) 
    // { 
    //     double px = x1[0] + x2[0] + x3[0] + x4[0];
    //     double py = x1[1] + x2[1] + x3[1] + x4[1];
    //     double pz = x1[2] + x2[2] + x3[2] + x4[2];
    //     double e  = x1[3] + x2[3] + x3[3] + x4[3];
    //     ROOT::Math::PxPyPzEVector tmp(px, py, pz, e);
        
    //     return  tmp.M(); 

    // };

    auto  rdf2 = rdf.Define("Gaus1", "gRandom->Gaus(-0.38,0.49)")
                    .Define("chi2CovGaus", "chi2_min_r3c + Gaus1" );
               
    
    std::vector<std::string> branchList = 
        {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c","flag1", 
            "mode1", "mode2", "mode3", "signal", "Gaus1", "chi2CovGaus"
        }; 



    rdf2.Snapshot("tree", "4660signal_covGaus.root", branchList);
    //rdf2.Snapshot("tree", "4660signal_rmLc.root");

}

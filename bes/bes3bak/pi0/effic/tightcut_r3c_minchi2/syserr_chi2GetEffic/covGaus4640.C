
// select branch
void covGaus4640()
{
    ROOT::RDataFrame rdf("tree", "../../baseRoot/4640signal_adddipim.root");


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

    auto  rdf2 = rdf.Define("Gaus1", "ToBeAdd")
                    .Define("chi2CovGaus", "chi2_min_r3c + Gaus1" );
               
    



    rdf2.Snapshot("tree", "4640signal_adddipim_covGaus.root" );
    //rdf2.Snapshot("tree", "4640signal_rmLc.root");

}

#include "Math/Vector4D.h"

void addetap1c4600()
{
    ROOT::RDataFrame rdf("tree", "4600data_selB.root");



    auto sqrtSum = [](vector<double,ROOT::Detail::VecOps::RAdoptAllocator<double>> x1, 
                      vector<double,ROOT::Detail::VecOps::RAdoptAllocator<double>> x2, 
                      vector<double,ROOT::Detail::VecOps::RAdoptAllocator<double>> x3, 
                      vector<double,ROOT::Detail::VecOps::RAdoptAllocator<double>> x4
                    ) 
        { 
            double px = x1[0] + x2[0] + x3[0] + x4[0];
            double py = x1[1] + x2[1] + x3[1] + x4[1];
            double pz = x1[2] + x2[2] + x3[2] + x4[2];
            double e  = x1[3] + x2[3] + x3[3] + x4[3];
            ROOT::Math::PxPyPzEVector tmp(px, py, pz, e);
            
            return  tmp.M(); 

        };


    auto rdf2 = rdf.Define("etaprimem_r1c_", sqrtSum, {"gam1_r3c_", "gam2_r3c_", "p_pimr_", "p_pipr_"});

    rdf2.Snapshot("tree", "4600data_selB_addetap1c.root");


}

// tree->Draw("p_pimr[0]"); tree->Draw("p_pim_r3c[0]", "", "same *H");
// tree->Draw("p_pimr[1]"); tree->Draw("p_pim_r3c[1]", "", "same *H");
// tree->Draw("p_pimr[2]"); tree->Draw("p_pim_r3c[2]", "", "same *H");
// tree->Draw("p_pimr[3]"); tree->Draw("p_pim_r3c[3]", "", "same *H");

// tree->Draw("p_pipr[0]"); tree->Draw("p_pip_r3c[0]", "", "same *H");
// tree->Draw("p_pipr[1]"); tree->Draw("p_pip_r3c[1]", "", "same *H");
// tree->Draw("p_pipr[2]"); tree->Draw("p_pip_r3c[2]", "", "same *H");
// tree->Draw("p_pipr[3]"); tree->Draw("p_pip_r3c[3]", "", "same *H");
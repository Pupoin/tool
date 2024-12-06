#include "/usr/include/root/TLorentzVector.h"
#include "/usr/include/root/TVector3.h"
#include "/usr/include/root/TMath.h"

void a()
{
    ROOT::RDataFrame rdf("tree_truth", "4600signal.root");


        auto Costheta_sigma = [](double p_px, double p_py, double p_pz, double p_e,
                                 double sigma_px, double sigma_py, double sigma_pz, double sigma_e, 
                                 double Lc_px, double Lc_py, double Lc_pz, double Lc_e) 
        { 

            TLorentzVector sigma(sigma_px, sigma_py, sigma_pz, sigma_e );
            TLorentzVector proton(p_px, p_py, p_pz, p_e );
            TLorentzVector Lc(Lc_px, Lc_py, Lc_pz, Lc_e );

            TVector3 bt_sigma = sigma.BoostVector();
            // TVector3 bt_proton = proton.BoostVector();
            TVector3 bt_Lc = Lc.BoostVector();

            proton.Boost(-bt_sigma);
            sigma.Boost(-bt_Lc);
            
            
            double costheta = -100;
            costheta =  TMath::Cos(sigma.Angle(proton.Vect()));
            
            return  costheta; 

        };

    auto rdf2 = rdf//.Filter("M_BC_r3c>2.25 && chi2_min_r3c<30 && np!=0 && npbar!=0 && etaprimemr3c>0.946 && etaprimemr3c<0.968")
                   .Filter("(ndaughterAp ==11 || ndaughterAm == 11)")
                   .Define("pm_px", "new_Am_ptruth[8]")
                   .Define("pm_py", "new_Am_ptruth[9]")
                   .Define("pm_pz", "new_Am_ptruth[10]")
                   .Define("pm_e",  "new_Am_ptruth[11]")

                   .Define("pp_px", "new_Ap_ptruth[8]")
                   .Define("pp_py", "new_Ap_ptruth[9]")
                   .Define("pp_pz", "new_Ap_ptruth[10]")
                   .Define("pp_e",  "new_Ap_ptruth[11]")

                   .Define("sigma_px", "new_Ap_ptruth[0]")
                   .Define("sigma_py", "new_Ap_ptruth[1]")
                   .Define("sigma_pz", "new_Ap_ptruth[2]")
                   .Define("sigma_e",  "new_Ap_ptruth[3]")

                   .Define("Lc_px", "new_Ap_ptruth[0] + new_Ap_ptruth[4]")
                   .Define("Lc_py", "new_Ap_ptruth[1] + new_Ap_ptruth[5]")
                   .Define("Lc_pz", "new_Ap_ptruth[2] + new_Ap_ptruth[6]")
                   .Define("Lc_e",  "new_Ap_ptruth[3] + new_Ap_ptruth[7]")


                   .Define("Costheta_sigma_m", Costheta_sigma, {"pm_px", "pm_py", "pm_pz", "pm_e", "sigma_px", "sigma_py","sigma_pz","sigma_e",  "Lc_px", "Lc_py", "Lc_pz", "Lc_e"})
                   .Define("Costheta_sigma_p", Costheta_sigma, {"pp_px", "pp_py", "pp_pz", "pp_e", "sigma_px", "sigma_py","sigma_pz","sigma_e", "Lc_px", "Lc_py", "Lc_pz", "Lc_e"})
                    
                        ;

    std::vector<std::string> branchList = 
            {"Costheta_sigma_p","Costheta_sigma_m",  "pm_px", "pm_py", "pm_pz", "pm_e", "sigma_px", "sigma_py","sigma_pz","sigma_e", 
            "pp_px", "pp_py", "pp_pz", "pp_e", "Lc_px", "Lc_py","Lc_pz","Lc_e", 
            }; 


    rdf2.Snapshot("tree_truth", "tmp.root", branchList);


}

// tree->Scan("sqrt(pow(Am_ptruth[2][3],2)-pow(Am_ptruth[2][0],2)-pow(Am_ptruth[2][1],2)-pow(Am_ptruth[2][2],2))", "signal == -1")
// tree->Draw("sqrt(sigma_e*sigma_e - sigma_px*sigma_px - sigma_py*sigma_py - sigma_pz*sigma_pz)")
// tree->Draw("sqrt(pp_e*pp_e - pp_px*pp_px - pp_py*pp_py - pp_pz*pp_pz)")
// tree->Draw("sqrt(Lc_e*Lc_e - Lc_px*Lc_px - Lc_py*Lc_py - Lc_pz*Lc_pz)")

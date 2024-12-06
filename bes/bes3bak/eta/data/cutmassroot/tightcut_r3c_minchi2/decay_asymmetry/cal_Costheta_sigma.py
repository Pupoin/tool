import ROOT
from ROOT import *
import time
import os

    
ROOT.gInterpreter.Declare("""
double Costheta_sigma(double p_px, double p_py, double p_pz, double p_e,
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

}
""")
def cal_Costheta_sigma(file):
    start = time.time()

    rdf=ROOT.RDataFrame("tree", file)
    #.Filter("M_BC_r3c>2.25 && chi2_min_r3c<17 && np!=0 && npbar!=0 
    rdf2 = rdf.Filter("M_BC_r3c>2.25  && chi2_min_r3c<17 && np!=0 && npbar!=0" ) \
                .Define("p_px", "pall_r3c[0]")\
                .Define("p_py", "pall_r3c[1]")\
                .Define("p_pz", "pall_r3c[2]")\
                .Define("p_e",  "pall_r3c[3]")\
                .Define("sigma_px", "pall_r3c[0]+gam3_r3c[0]+gam4_r3c[0]")\
                .Define("sigma_py", "pall_r3c[1]+gam3_r3c[1]+gam4_r3c[1]")\
                .Define("sigma_pz", "pall_r3c[2]+gam3_r3c[2]+gam4_r3c[2]")\
                .Define("sigma_e",  "pall_r3c[3]+gam3_r3c[3]+gam4_r3c[3]")\
                .Define("Lc_px", "sigma_px + gam1_r3c[0]+gam2_r3c[0] ")\
                .Define("Lc_py", "sigma_py + gam1_r3c[1]+gam2_r3c[1] ")\
                .Define("Lc_pz", "sigma_pz + gam1_r3c[2]+gam2_r3c[2] ")\
                .Define("Lc_e",  "sigma_e  + gam1_r3c[3]+gam2_r3c[3]  ")\
                .Define("Costheta_sigma", "Costheta_sigma(p_px, p_py, p_pz, p_e, sigma_px, sigma_py,sigma_pz,sigma_e, Lc_px, Lc_py, Lc_pz, Lc_e)")

    branchList = ROOT.std.vector("string")((
            "Costheta_sigma", "p_px", "p_py", "p_pz", "p_e", "sigma_px", "sigma_py","sigma_pz","sigma_e", 
            "Lc_px", "Lc_py","Lc_pz","Lc_e",
            "event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c",    ))

    # rdf2.Snapshot("tree", "tmp0.root", branchList)
    rdf2.Snapshot("tree", "{0}_Costheta_sigma.root".format(file.split('.')[0]), branchList)
    print time.time()- start


if __name__ == "__main__":

    fileList = ["4600data_removedouble.root", "4612data_removedouble.root", "4620data_removedouble.root", "4640data_removedouble.root", "4660data_removedouble.root", "4680data_removedouble.root", "4700data_removedouble.root"]
    # fileList = ["4600data_removedouble.root"]
    
    for inFileName in fileList:
        print "====== start {0} ======".format(inFileName)
        cal_Costheta_sigma(inFileName)


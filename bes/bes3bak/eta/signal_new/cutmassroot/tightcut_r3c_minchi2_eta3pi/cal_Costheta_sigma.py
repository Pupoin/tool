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
    #.Filter("M_BC_r3c>2.25 && chi2_min_r3c<30 && np!=0 && npbar!=0 && etaprimemr3c>0.946 && etaprimemr3c<0.968")
    rdf2 = rdf.Filter("M_BC_r3c>2.2").Filter("(ndaughterAp==11&&ndaughterAm!=11) || (ndaughterAp==11&&ndaughterAm==11 && rightflag==1)")\
                .Define("p_px", "new_Ap_ptruth[8]")\
                .Define("p_py", "new_Ap_ptruth[9]")\
                .Define("p_pz", "new_Ap_ptruth[10]")\
                .Define("p_e",  "new_Ap_ptruth[11]")\
                .Define("sigma_px", "new_Ap_ptruth[0]")\
                .Define("sigma_py", "new_Ap_ptruth[1]")\
                .Define("sigma_pz", "new_Ap_ptruth[2]")\
                .Define("sigma_e",  "new_Ap_ptruth[3]")\
                .Define("Lc_px", "new_Ap_ptruth[0] + new_Ap_ptruth[4]")\
                .Define("Lc_py", "new_Ap_ptruth[1] + new_Ap_ptruth[5]")\
                .Define("Lc_pz", "new_Ap_ptruth[2] + new_Ap_ptruth[6]")\
                .Define("Lc_e",  "new_Ap_ptruth[3] + new_Ap_ptruth[7]")\
                .Define("Costheta_sigma", "Costheta_sigma(p_px, p_py, p_pz, p_e, sigma_px, sigma_py,sigma_pz,sigma_e, Lc_px, Lc_py, Lc_pz, Lc_e)")

    branchList = ROOT.std.vector("string")((
            "Costheta_sigma", "p_px", "p_py", "p_pz", "p_e", "sigma_px", "sigma_py","sigma_pz","sigma_e", 
            "Lc_px", "Lc_py","Lc_pz","Lc_e",
            "event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c", "signal"    ))

    os.system("/bin/rm tmp.root tmp0.root tmp1.root")
    rdf2.Snapshot("tree", "tmp0.root", branchList)
    # rdf2.Snapshot("tree_truth", "tmp.root", {"Costheta_sigma", "p_px", "p_py", "p_pz", "p_e", "sigma_px", "sigma_py","sigma_pz","sigma_e", \
    #          "Lc_px", "Lc_py","Lc_pz","Lc_e"})


    #.Filter("M_BC_r3c>2.25 && chi2_min_r3c<30 && np!=0 && npbar!=0 && etaprimemr3c>0.946 && etaprimemr3c<0.968")
    rdf3 = rdf.Filter("M_BC_r3c>2.2").Filter("(ndaughterAm==11&&ndaughterAp!=11 ) || (ndaughterAp==11&&ndaughterAm==11 && rightflag==-1)")\
                .Define("p_px", "new_Am_ptruth[8]")\
                .Define("p_py", "new_Am_ptruth[9]")\
                .Define("p_pz", "new_Am_ptruth[10]")\
                .Define("p_e",  "new_Am_ptruth[11]")\
                .Define("sigma_px", "new_Am_ptruth[0]")\
                .Define("sigma_py", "new_Am_ptruth[1]")\
                .Define("sigma_pz", "new_Am_ptruth[2]")\
                .Define("sigma_e",  "new_Am_ptruth[3]")\
                .Define("Lc_px", "new_Am_ptruth[0] + new_Am_ptruth[4]")\
                .Define("Lc_py", "new_Am_ptruth[1] + new_Am_ptruth[5]")\
                .Define("Lc_pz", "new_Am_ptruth[2] + new_Am_ptruth[6]")\
                .Define("Lc_e",  "new_Am_ptruth[3] + new_Am_ptruth[7]")\
                .Define("Costheta_sigma", "Costheta_sigma(p_px, p_py, p_pz, p_e, sigma_px, sigma_py,sigma_pz,sigma_e, Lc_px, Lc_py, Lc_pz, Lc_e)")

    rdf3.Snapshot("tree", "tmp1.root", branchList)

    
    os.system("hadd tmp.root tmp0.root tmp1.root")
    os.system("mv tmp.root {0}_Costheta_sigma.root".format(file.split('.')[0]))
    os.system("/bin/rm tmp0.root tmp1.root")
    print time.time()- start


if __name__ == "__main__":

    fileList = ["4600signal.root", "4612signal.root", "4620signal.root", "4640signal.root", "4660signal.root", "4680signal.root", "4700signal.root"]
    # fileList = ["4600signal.root"]
    
    for inFileName in fileList:
        print "====== start {0} ======".format(inFileName)
        cal_Costheta_sigma(inFileName)


// double ppi0(double p_px, double p_py, double p_pz, double p_e,
//                             double sigma_px, double sigma_py, double sigma_pz, double sigma_e, 
//                             double Lc_px, double Lc_py, double Lc_pz, double Lc_e) 
// { 
//     TLorentzVector sigma(sigma_px, sigma_py, sigma_pz, sigma_e );
//     TLorentzVector proton(p_px, p_py, p_pz, p_e );
//     TLorentzVector Lc(Lc_px, Lc_py, Lc_pz, Lc_e );


    
//     return  mppi0; 

// }

double calM(double p_px, double p_py, double p_pz, double p_e) 
{ 
    // TLorentzVector sigma(sigma_px, sigma_py, sigma_pz, sigma_e );
    TLorentzVector proton(p_px, p_py, p_pz, p_e );
    // TLorentzVector Lc(Lc_px, Lc_py, Lc_pz, Lc_e );


    
    return  proton.M(); 

}

void plot()
{

    
    TCut cut_np = "(np !=0 && npbar != 0)";
// TCut cut = "(refm>=0.115&&refm<=0.15) && (refmORsigm1m>=0.115&&refmORsigm1m<=0.15) && (sigmam>=1.174 && sigmam<=1.2) && (dipim<0.48 || dipim>0.52)";
TCut cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919))";
// TCut cut_deltaE_ref = "((deltaE_min>-0.033) && (deltaE_min<0.022))";
// TCut cut_deltaE_sig = "((deltaE_min>-0.021) && (deltaE_min<0.015))";
// TCut cut_chi2 = "(chi2_min_r3c< 29)";
TCut cut_ref = (cut_mbc && "(chi2_min_r3c<17) && (dipim<0.44 || dipim>0.52)" && cut_np);
TCut cut_sig = (cut_mbc && "(chi2_min_r3c<17)" && cut_np);


    ROOT::RDataFrame rdf("tree", "data_allbranch.root");

    auto  rdf2 = rdf.Filter("chi2_min_r3c<17 && ((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919)) && (np !=0 && npbar != 0)")
                .Define("M_ppi0_px", "m_pall_r3c[0] + m_gam3_r3c[0] + m_gam4_r3c[0]")
                .Define("M_ppi0_py", "m_pall_r3c[1] + m_gam3_r3c[1] + m_gam4_r3c[1]")
                .Define("M_ppi0_pz", "m_pall_r3c[2] + m_gam3_r3c[2] + m_gam4_r3c[2]")
                .Define("M_ppi0_e",  "m_pall_r3c[3] + m_gam3_r3c[3] + m_gam4_r3c[3]")
                .Define("M_ppi0", "calM(M_ppi0_px,M_ppi0_py,M_ppi0_pz,M_ppi0_e)")

                .Define("M_etapi0_px", "m_gam3_r3c[0] + m_gam4_r3c[0] + m_gam2_r3c[0] + m_gam1_r3c[0]")
                .Define("M_etapi0_py", "m_gam3_r3c[1] + m_gam4_r3c[1] + m_gam2_r3c[1] + m_gam1_r3c[1]")
                .Define("M_etapi0_pz", "m_gam3_r3c[2] + m_gam4_r3c[2] + m_gam2_r3c[2] + m_gam1_r3c[2]")
                .Define("M_etapi0_e",  "m_gam3_r3c[3] + m_gam4_r3c[3] + m_gam2_r3c[3] + m_gam1_r3c[3]")
                .Define("M_etapi0", "calM(M_etapi0_px,M_etapi0_py,M_etapi0_pz,M_etapi0_e)")
    ;


    // std::vector<std::string> branchList = 
    //         {"event", "run", "M_BC_r3c", "np", "npbar", "chi2_min_r3c", "deltaE_min_r3c",
    //         "signal"
    //         }; 

    // rdf2.Snapshot("tree", "4620data_selB.root", branchList );

    TCanvas can("","",800, 600);
    // TChain c("tree");
    // TH1F h1("h1","h1", 20, 2.25, 2.3);
    // c.Add("data_allbranch.root");

    // c.Project("h1","M_BC_r3c", cut_sig);
    // h1.Draw();

    auto myHisto = rdf2.
        Histo1D({"M_ppi0", "M(p#pi^{0})", 20u, 1.174, 1.2}, "M_ppi0");
        // (("M_ppi0", "M(p#pi^{0})", 0, 1.2, 20), "M_ppi0");
        // Histo1D("M_ppi0"); // This books the (lazy) filling of a histogram
    myHisto->Draw(); 
    can.SaveAs("M_ppi0.png");

    myHisto = rdf2.
        Histo1D({"M_etapi0", "M(#eta#pi^{0})", 20u, 0.65, 1.34}, "M_etapi0");
        // (("M_ppi0", "M(p#pi^{0})", 0, 1.2, 20), "M_ppi0");
        // Histo1D("M_ppi0"); // This books the (lazy) filling of a histogram
    myHisto->Draw(); 
    can.SaveAs("M_etapi0.png");

}

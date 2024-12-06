


void plot()
{
    TChain *chain_inclusive = new TChain("tree");

    chain_inclusive->Add("LL_pipipi0.root");
    TH1D *hist_inclusive_bkg = new TH1D("hist_inclusive_bkg", "m_{BC} Distribution", 20, 2.25, 2.35);

    TCut cut_np = "(np!=0 && npbar != 0)";
    TCut cut_chi2 = "(chi2_min_r3c<30)";
    TCut cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.35))";
    TCut cut_sum1 = (cut_mbc && cut_chi2 && cut_np) && "( (etaprimemr3c>0.68&&etaprimemr3c<0.72) || (etaprimemr3c>0.84&&etaprimemr3c<0.89) )" ;

    TCut cut_inclusive_sig = "(signal==1 || signal == -1)";
    TCut cut_inclusive_bkg = !cut_inclusive_sig;

    chain_inclusive->Project("hist_inclusive_bkg", "M_BC_r3c", cut_inclusive_bkg && cut_sum1 );
    TCanvas c("", "", 800, 800);
    hist_inclusive_bkg->Draw();
    c.SaveAs("tmp.png");}
// TCut cut_np = "(np!=0 && npbar != 0)";
// TCut cut_chi2 = "(chi2_min_r3c<30)";
// TCut cut_mbc = "((M_BC_r3c>=2.276) && (M_BC_r3c<=2.294))";
// TCut cut_sum1 = (cut_mbc && cut_chi2 && cut_np) && "( (etaprimemr3c>0.68&&etaprimemr3c<0.72) || (etaprimemr3c>0.84&&etaprimemr3c<0.89) )";


// TChain chain("tree");
// chain.Add("4*LL.root");

// TTree *t=chain.CopyTree(cut_sum1);



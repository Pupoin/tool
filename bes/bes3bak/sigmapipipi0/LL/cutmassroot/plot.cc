


TCut cut_np = "(np!=0 && npbar != 0)";
TCut cut_chi2 = "(chi2_min_r3c<30)";
// TCut cut_chi2 = "(deltaE_min_r3c<0.02 && deltaE_min_r3c>-0.02)";
TCut cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.35))";
TCut cut_sigma = "((sigmamr3c>=1.174) && (sigmamr3c<=1.2))";
TCut cut_omega = "( (omegamr3c<0.72) || (omegamr3c>0.84) )";
// TCut cut_omega = "( (omegamr3c>0.76) && (omegamr3c<0.8) )";

TCut cut_sum1 = cut_mbc && cut_chi2 && cut_sigma && cut_omega ;

// double xmin=1.17, xmax=1.2, xbin=20;
double xmin=2.25, xmax=2.35, xbin=10;
// double xmin=2.27, xmax=2.3, xbin=5;
void plot()
{
    gStyle->SetOptStat(0);
    TCanvas c("", "", 800, 800);
    TChain *chain_inclusive = new TChain("tree");

    // chain_inclusive->Add("4700LL.root");
    chain_inclusive->Add("my_topo.root");

    TH1D *total = new TH1D("total", "m_{BC} Distribution", xbin, xmin, xmax);
    TH1D *total_min = new TH1D("total_min", "m_{BC} Distribution", xbin, xmin, xmax);

    TH1D *h0 = new TH1D("h0", "m_{BC} Distribution", xbin, xmin, xmax);
    TH1D *h1 = new TH1D("h1", "m_{BC} Distribution", xbin, xmin, xmax);
    TH1D *h2 = new TH1D("h2", "m_{BC} Distribution", xbin, xmin, xmax);
    TH1D *h3 = new TH1D("h3", "m_{BC} Distribution", xbin, xmin, xmax);
    TH1D *h4 = new TH1D("h4", "m_{BC} Distribution", xbin, xmin, xmax);
    TH1D *h5 = new TH1D("h5", "m_{BC} Distribution", xbin, xmin, xmax);
    TH1D *h6 = new TH1D("h6", "m_{BC} Distribution", xbin, xmin, xmax);
    TH1D *h7 = new TH1D("h7", "m_{BC} Distribution", xbin, xmin, xmax);
    TH1D *h8 = new TH1D("h8", "m_{BC} Distribution", xbin, xmin, xmax);
    TH1D *h9 = new TH1D("h9", "m_{BC} Distribution", xbin, xmin, xmax);
    TH1D *h10 = new TH1D("h10", "m_{BC} Distribution", xbin, xmin, xmax);
    TH1D *h11 = new TH1D("h11", "m_{BC} Distribution", xbin, xmin, xmax);
    TCut a = "iCascDcyBrP_ALambda0_0!=0 && iCascDcyBrP_ALambda0_0!=1 && iCascDcyBrP_K_S0_0!=0 && iCascDcyBrP_K_S0_0!=1";
    TCut b = "iProdBrP_kplus_0!=2 && iProdBrP_kplus_0!=0 && iProdBrP_kplus_0!=1";
    chain_inclusive->Project("total","M_BC_r3c", cut_sum1 &&  a && b && "iDcyIFSts>5 || iDcyIFSts>30");
    chain_inclusive->Project("total_min","M_BC_r3c", cut_sum1 &&  a && b && "iDcyIFSts<30");
    chain_inclusive->Project("h0", "M_BC_r3c",    cut_sum1 &&  "iCascDcyBrP_ALambda0_0==1" );
    chain_inclusive->Project("h1", "M_BC_r3c",    cut_sum1 && "iCascDcyBrP_ALambda0_0==0" );
    chain_inclusive->Project("h2", "M_BC_r3c",    cut_sum1 && "iCascDcyBrP_K_S0_0==0" );
    chain_inclusive->Project("h3", "M_BC_r3c",    cut_sum1 && "iCascDcyBrP_K_S0_0==1" );
    chain_inclusive->Project("h4", "M_BC_r3c",    cut_sum1 && "iCascDcyBrP_omega_0==0" );
    chain_inclusive->Project("h5", "M_BC_r3c",    cut_sum1 && (!b) );
    // chain_inclusive->Project("h6", "M_BC_r3c",    cut_sum1 && "iDcyIFSts==6" );
    // chain_inclusive->Project("h7", "M_BC_r3c",    cut_sum1 && "iDcyIFSts==23" );
    // chain_inclusive->Project("h8", "M_BC_r3c",    cut_sum1 && "iDcyIFSts==9" );
    // chain_inclusive->Project("h9", "M_BC_r3c",    cut_sum1 && "iDcyIFSts==31" );
    // chain_inclusive->Project("h10", "M_BC_r3c",    cut_sum1 && "iDcyIFSts==17" );
    chain_inclusive->Project("h11", "M_BC_r3c",    cut_sum1 && "iDcyIFSts<50" );


    total_min->Draw("same");
    total->Draw("same");
    total->SetMinimum(0);
    THStack *hStack = new THStack("his", "");
    hStack->Add(h1);
    hStack->Add(h2);
    // hStack->Add(h4);
    hStack->Add(h5);
    // hStack->Add(h7);
    // hStack->Add(h8);
    // hStack->Add(h9);
    // hStack->Add(h10);
    // hStack->Add(h11);
    // hStack->Add(h4);
    hStack->Add(h3);
    hStack->Add(h0);

    // hStack->Draw("HIST same");
    total->SetLineColor(2);
    total_min->SetLineColor(2);
    
    // total->Scale(0.025);
    // total->SetMaximum(130);
    h0->SetLineColor(3+0);
    h1->SetLineColor(3+1);
    h2->SetLineColor(3+2);
    h3->SetLineColor(2);
    h4->SetLineColor(3+4);
    h5->SetLineColor(3+5);
    h6->SetLineColor(3+6);
    h7->SetLineColor(4+7);
    h8->SetLineColor(4+8);
    h9->SetLineColor(4+9);
    h10->SetLineColor(4+10);
    h11->SetLineColor(4+11);
    
    // h3 -> Draw("same");
    // h0 -> Draw("same");
    // h1 -> Draw("same");
    // h2 -> Draw("same");
    // // h4 -> Draw("same");
    // h5 -> Draw("same");
    // h6 -> Draw("same");
    // h7 -> Draw("same");
    // h8 -> Draw("same");
    // h9 -> Draw("same");
    // h10 -> Draw("same");
    // h11 -> Draw("same");


    TLegend *legend = new TLegend(0.7, 0.58, 0.96, 0.84);
    // legend->SetHeader("all data");
    // legend->AddEntry("hist_data", "data", "le");
    legend->AddEntry("total", "total", "f");
    legend->AddEntry("h0", "Lambda0-> p pi", "f");
    legend->AddEntry("h1", "Lambda0-> n pi0", "f");
    legend->AddEntry("h2", "Ks -> pi+ pi-", "f");
    legend->AddEntry("h3", "Ks -> pi0 pi0", "f");
    legend->AddEntry("h4", "omega", "f");
    legend->AddEntry("h5", "K+", "f");
    // legend->AddEntry("h6", "h7", "f");
    // legend->AddEntry("h7", "h8", "f");
    // legend->AddEntry("h8", "h9", "f");
    // legend->AddEntry("h9", "h10", "f");
    // legend->AddEntry("h10", "h11", "f");
    // legend->AddEntry("h11", "h12", "f");
    legend->SetBorderSize(0);
    legend->SetFillColor(0);
    legend->Draw();

    c.SaveAs("tmp.png");

}
// TCut cut_np = "(np!=0 && npbar != 0)";
// TCut cut_chi2 = "(chi2_min_r3c<30)";
// TCut cut_mbc = "((M_BC_r3c>=2.276) && (M_BC_r3c<=2.294))";
// TCut cut_sum1 = (cut_mbc && cut_chi2 && cut_np) && "( (etaprimemr3c>0.68&&etaprimemr3c<0.72) || (etaprimemr3c>0.84&&etaprimemr3c<0.89) )";


// TChain chain("tree");
// chain.Add("4*LL.root");

// TTree *t=chain.CopyTree(cut_sum1);



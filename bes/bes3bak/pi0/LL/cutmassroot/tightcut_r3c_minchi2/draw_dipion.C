void draw_dipion()
{


    TChain *chain_inclusive = new TChain("tree");

    chain_inclusive->Add("4*LL_adddipim.root");


    // TCut cut_np = "(np!=0 && npbar != 0)";
    // TCut cut_chi2 = "(chi2_min_r3c<17)";
    // TCut cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919))";
    // TCut cut_sum1 = (cut_mbc && cut_chi2 && cut_np && "(dipim<0.48 || dipim>0.52) && (signal!=1 && signal!=-1)");

    // TTree *tr = chain_inclusive->CopyTree(cut_sum1,"",100000000000,0);


    // setStyle();
    // setPad();
    double factor[2] = {0.030, 0.045};

    // //********************plot the mBC distributions*********************//
    TCanvas *canv1 = new TCanvas("canv1", "mBC", 800, 600);
    canv1->SetFillColor(0);
    canv1->SetFrameFillColor(0);
    canv1->SetTopMargin(0.13);
    canv1->SetBottomMargin(0.13);
    canv1->SetLeftMargin(0.13);
    canv1->SetRightMargin(0.13);
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    double xmin =0.4, xmax = 0.6;
    Int_t xbins = (xmax-xmin)*1000/5 + 1;
    xmax = xmin+xbins*0.005;
    TH1::SetDefaultSumw2(1);
    TString a("Events/");
    char b[100];
    sprintf(b, "(%g", (xmax - xmin) / xbins * 1000);
    TString c(" MeV)");
    TString ytitle = a + b + c;

    TH1D *hits_signal = new TH1D("hits_signal", "m_{BC} Distribution", xbins, xmin, xmax);
    TH1D *hits_mode0 = new TH1D("hits_mode0", "m_{BC} Distribution", xbins, xmin, xmax);
    TH1D *hist_nosignal = new TH1D("hist_nosignal", "m_{BC} Distribution", xbins, xmin, xmax);
    TH1D *hist_mode0_signal = new TH1D("hist_mode0_signal", "m_{BC} Distribution", xbins, xmin, xmax);

    // TCut cut_deltaE = "((deltaE_min>-0.020) && (deltaE_min<0.015))";
    TCut cut_np = "(np!=0 && npbar != 0)";
    TCut cut_chi2 = "(chi2_min_r3c<50)";
    TCut cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919))";
    TCut cut_sum1 = (cut_mbc && cut_chi2 && cut_np ) ;//&& "(dipim<0.48 || dipim>0.52)");

    // TCut cut_inclusive_sig = (cut_inclusive_sigp || cut_inclusive_sigm);
    TCut cut_inclusive_sig = "(signal==1 || signal == -1)";
    TCut cut_inclusive_bkg = !cut_inclusive_sig;

    chain_inclusive->Project("hits_signal", "dipim", cut_inclusive_sig && cut_sum1);
    //TCut cut_mode = ("mode1==0 && mode2==0 && mode3==96");
    //chain_hardon->Project("hits_mode0", "M_BC_r3c", cut_sum1 && "indexmc==0");
    chain_inclusive->Project("hits_mode0", "dipim", "(mode2==0 || mode3==0 )" && cut_inclusive_bkg && cut_sum1);

    auto chain_mode0_signal = chain_inclusive;
    auto chain_nosignal = chain_inclusive;
    chain_mode0_signal->Project("hist_mode0_signal", "dipim", cut_sum1);
    // chain_nosignal->Project("hist_nosignal", "dipim", cut_inclusive_bkg && cut_sum1);

    hist_nosignal->SetLineColor(2);
    hits_signal->SetLineColor(3);
    hits_mode0->SetLineColor(4);

    hist_nosignal->SetLineWidth(3);

    hits_signal->SetFillColor(3);
    hits_mode0->SetFillColor(4);

    canv1->cd();
    THStack *hStack = new THStack("his", "");
    // hs->SetMaximum(2);
    hStack->Add(hits_signal);
    hStack->Add(hits_mode0);

    // hStack->Add(hist_mode0_signal);

    // double fac = 1;
    // hist_nosignal->Scale(factor[0] * fac);
    // hist_mode0_signal->Scale(factor[0] * fac);
    // hits_mode0->Scale(factor[1] * fac);

    hits_signal->Draw("e ");
    hStack->Draw("HIST");
    hist_mode0_signal->Draw("HIST same");

    hStack->GetYaxis()->SetTitle(ytitle);
    // hStack->GetYaxis()->SetTitleOffset(0.75);
    hStack->GetYaxis()->SetTitleSize(0.05);
    // hStack->GetYaxis()->SetRange(0, 100);
    hStack->SetMinimum(0.);
    // double hist_max = hStack->GetMaximum() > hits_signal->GetMaximum() ? hStack->GetMaximum():hits_signal->GetMaximum();
    hStack->SetMaximum(hStack->GetMaximum() > hits_signal->GetMaximum() ? 1.2*hStack->GetMaximum(): 1.2*hits_signal->GetMaximum());
    hStack->GetXaxis()->SetTitle("m(#pi^{0}#pi^{0}) (GeV)");
    // hStack->GetXaxis()->SetTitleOffset(1.0);
    hStack->GetXaxis()->SetTitleSize(0.05);

    TLegend *legend = new TLegend(0.66, 0.6, 0.85, 0.85);
    // legend->SetHeader("#sqrt{s}=a GeV");
    legend->AddEntry("hist_mode0_signal", "all", "f");
    legend->AddEntry("hits_signal", "p#pi^{0}", "f");
    // legend->AddEntry("hist_nosignal", "signal", "f");
    legend->AddEntry("hits_mode0", "pK_{S}", "f");
    legend->SetBorderSize(0);
    legend->SetFillColor(0);
    legend->Draw();

    canv1->Update();
    // canv1->SaveAs("stackall.pdf");
    canv1->SaveAs("stackall.png");
    return 0;


}
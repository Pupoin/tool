void plot()
{
    TCanvas can("","",800, 600);
    can.SetFillColor(0);
    can.SetFrameFillColor(0);
    can.SetTopMargin(0.1);
    can.SetBottomMargin(0.15);
    can.SetLeftMargin(0.15);
    can.SetRightMargin(0.05);
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    double xmin = 2.25, xmax = 2.3;
    double xbins = 35;
    TH1::SetDefaultSumw2(1);
    TString a("Events / ");
    char b[100];
    sprintf(b, "(%g", (xmax - xmin) / xbins * 1000);
    TString ccc("MeV/#font[12]{c^{2}})");
    TString ytitle = a + b + ccc;

    TChain c("tree");
    TH1F h1("h1","h1", xbins, xmin, xmax);
    c.Add("4*data.root");

    c.Project("h1","M_BC_r3c", "((sigmam_r3c>1.14&&sigmam_r3c<1.16) || (sigmam_r3c>1.21&&sigmam_r3c<1.23))  && M_BC_r3c>2.25 && chi2_min_r3c<17 && (np!=0 && npbar!=0)"); 
    
    
    h1.Draw("e");
    

    h1.GetYaxis()->SetTitle(ytitle);
    // h1.GetYaxis()->SetTitleOffset(1);
    // h1.GetYaxis()->SetTitleSize(0.05);
    h1.GetXaxis()->SetTitle(" M_{BC} (GeV/#font[12]{c^{2}})");
    // h1.GetXaxis()->SetTitleOffset(1.0);
    // h1.GetXaxis()->SetTitleSize(0.05);
    h1.SetTitleSize(0.06, "xy");
    h1.SetLabelSize(0.045, "xy");
    h1.GetYaxis()->SetMaxDigits(3); 
    h1.GetXaxis()->SetNdivisions(210); 
    // TLegend *legend = new TLegend(0.2, 0.65, 0.45, 0.8);
    // legend->SetHeader("#Lambda_{c} ");
    // legend->Draw();

    can.SaveAs("Mbc_sigmaSideband.png");

}

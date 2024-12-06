int plot()
{

    TChain c("tree");
    c.Add("4*data.root");
    int xbin=20;

    TCanvas *canv1 = new TCanvas("canv1", "mBC", 700, 600);
    canv1->SetFillColor(0);
    canv1->SetFrameFillColor(0);
    canv1->SetTopMargin(0.1);
    canv1->SetBottomMargin(0.15);
    canv1->SetLeftMargin(0.15);
    canv1->SetRightMargin(0.03);
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);
    
    TH1F *h1 = new TH1F("h1", "h1",xbin, 2.25,2.35);
    TH1F *h2 = new TH1F("h2", "h2",xbin, 2.25,2.35);


    // c.Project("h1", "M_BC_r3c", "M_BC_r3c>2.25 && chi2_min_r3c<10 && etaprimemr3c>0.946 && etaprimemr3c<0.968"); h1.Draw("HIST");
    // np!=0 && npbar!=0
    TCut cut="M_BC_r3c>2.25 && chi2_min_r3c<10 && etaprimemr3c>0.946 && etaprimemr3c<0.968";

    TCut cut2="M_BC_r3c>2.25 && (np !=0 && npbar != 0) && chi2_min_r3c<10 && etaprimemr3c>0.946 && etaprimemr3c<0.968";
    
    c.Project("h1", "M_BC_r3c", cut2); 
    // c.Project("h2", "M_BC_r3c", cut); 


    h1->Draw("HIST");
    // h2->Draw("HIST same");
    h1->GetXaxis()->SetTitle("M_{BC} (GeV/c^{2})");
    h1->SetTitle("");
    h1->GetYaxis()->SetTitle(TString::Format("Events(%.2fMeV/c^{2})", (2.35-2.25)/xbin*1000));

    h1->SetLineColor(2);
    h1->SetLineColor(3);

    // h1->GetYaxis()->SetTitle(ytitle);
    h1->GetYaxis()->SetTitleSize(0.06);
    h1->GetYaxis()->SetLabelSize(0.045);
    h1->GetXaxis()->SetLabelSize(0.045);
    h1->SetMinimum(0.);
    // h1->SetMaximum(50);
    // h1->GetXaxis()->SetTitle("m_{/BC} (GeV/c^{2})");
    h1->GetXaxis()->SetTitleSize(0.06);
    h1->SetNdivisions(205);


    TLegend *legend = new TLegend(0.5, 0.68, 0.94, 0.84);
    // legend->SetHeader("#sqrt{s}=4628 GeV");
    legend->AddEntry("h1", "not request proton\n recoiled", "l");
    legend->AddEntry("h2", "request proton recoiled", "l");
    legend->SetBorderSize(0);
    legend->SetFillColor(0);
    // legend->Draw();

    canv1->SaveAs("requestProtonVs.png");
    canv1->SaveAs("requestProtonVs.pdf");



    return 0;
}


void cos()
{
    // TCanvas canv1;
    
    TCanvas *canv1 = new TCanvas("canv1", "mBC", 700, 600);
    canv1->SetFillColor(0);
    canv1->SetFrameFillColor(0);
    canv1->SetTopMargin(0.1);
    canv1->SetBottomMargin(0.15);
    canv1->SetLeftMargin(0.15);
    canv1->SetRightMargin(0.05);
    gStyle->SetOptStat(0);
    gStyle->SetPadColor(0);
    gStyle->SetCanvasColor(0);

    canv1->SetLogy(1);
    // canv1->SetLogx(1);

    double alpha_sigmaeta = 0.78;
    double alpha_sigma = -0.982; // -0.982 +- 0.014
    
    TF1 *fa = new TF1("fa","1 + [0] * [1] * x", -1, 1);
    fa->SetParameters(alpha_sigmaeta, alpha_sigma);
    fa->SetNpx(1000);
    auto *ha = fa->GetHistogram(); ha->SetName("ha");
    // ha->SetMaximum(5);
    ha->Scale(100000/ ha-> Integral() );
    ha->SetLineColor(1);
    ha->SetXTitle("cos #theta(#Sigma^{+})");
    ha->SetYTitle("Events");
    ha->SetTitleSize(0.06, "xy");
    ha->SetLabelSize(0.045,"xy");
    ha->SetNdivisions(110);
    ha->SetTitle(" ");
    // ha->SetMinimum(5);

    ha->Draw("HIST");
    
    

    TF1 *fa1 = new TF1("fa1","1 + [0] * [1] * x", -1, 1);
    fa1->SetParameters(alpha_sigmaeta, alpha_sigma + 0.014);
    fa1->SetNpx(1000);
    auto *ha1 = fa1->GetHistogram();ha1->SetName("ha1");
    ha1->SetLineColor(3);
    ha1->Scale(100000/ ha1-> Integral() );
    ha1->Draw("HIST same");



    TF1 *fa2 = new TF1("fa2","1 + [0] * [1] * x", -1, 1);
    fa2->SetParameters(alpha_sigmaeta, alpha_sigma - 0.014);
    fa2->SetNpx(1000);
    auto *ha2 = fa2->GetHistogram(); ha2->SetName("ha2");
    ha2->SetLineColor(2);
    ha2->Scale(100000/ ha2-> Integral() );
    ha2->Draw("HIST same");


    TLegend *legend = new TLegend(0.66, 0.6, 0.91, 0.85);
    legend->SetHeader("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta'");
    legend->AddEntry("ha", "norminal", "l");
    legend->AddEntry("ha1", "modelA", "l");
    legend->AddEntry("ha2", "modelB", "l");
    legend->SetBorderSize(0);
    legend->SetFillColor(0);
    legend->Draw();

    canv1->SaveAs("cos.png");
    canv1->SaveAs("cos.pdf");


    //////////////////////////////////////////////////////////////////////////
    TCanvas *canv2 = new TCanvas("canv1", "mBC", 700, 600);
    canv2->SetFillColor(0);
    canv2->SetFrameFillColor(0);
    canv2->SetTopMargin(0.1);
    canv2->SetBottomMargin(0.15);
    canv2->SetLeftMargin(0.15);
    canv2->SetRightMargin(0.05);

    TH1F *h1 = (TH1F*)ha1->Clone("modelA_norminal");
    h1->Divide(ha);
    h1->Draw("HIST");
    h1->SetMinimum(0.935);
    h1->SetMaximum(1.1);
    h1->SetLineColor(4);

    h1->SetXTitle("cos #theta(#Sigma^{+})");
    h1->SetYTitle("weight");
    h1->SetTitleSize(0.06, "xy");
    h1->SetLabelSize(0.045,"xy");
    h1->SetNdivisions(110);
    h1->SetTitle(" ");


    TH1F *h2 = (TH1F*)ha2 ->Clone("modelB_norminal");
    h2->Divide(ha);
    h2->Draw("HIST same");
    h2->SetLineColor(2);

    TLegend *legend2 = new TLegend(0.49, 0.64, 0.94, 0.89);
    legend2->SetHeader("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta'");
    legend2->AddEntry("modelA_norminal", "modelA/norminal", "l");
    legend2->AddEntry("modelB_norminal", "modelB/norminal", "l");
    legend2->SetBorderSize(0);
    legend2->SetFillColor(0);
    legend2->Draw();


    canv2->SaveAs("cos2.png");
    canv2->SaveAs("cos2.pdf");



    TFile* file = new TFile("weight.root","RECREATE");
    h1->Write();
    h2->Write();
    file->Close();
    



cout <<  ha1->GetBinContent(1)/ha->GetBinContent(1)  << " " <<  ha1->GetBinContent(1) << " " <<  ha->GetBinContent(1) << " "  <<endl;
cout << h1->GetBinContent(1) << endl;
cout << h1->GetBinWidth(1) << " " << ha1->GetBinWidth(1) << endl;
cout << ha1->GetXaxis()->GetBinLowEdge(1) << " " << ha1->GetXaxis()->GetBinUpEdge(1) << endl;
cout << ha1->GetXaxis()->GetBinLowEdge(1000) << " " << ha1->GetXaxis()->GetBinUpEdge(1000) << endl;


cout <<  ha2->GetBinContent(2)/ha->GetBinContent(2)  << " " <<  ha2->GetBinContent(2) << " " <<  ha->GetBinContent(2) << " "  <<endl;
cout << h2->GetBinContent(2) << endl;
cout << h2->GetBinWidth(2) << " " << ha2->GetBinWidth(2) << endl;
  

    
}
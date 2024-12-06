int plot()
{
    TChain c("tree");
    c.Add("data.root");
    TH1F *h1 = new TH1F("h1", "h1",20, 2.25,2.35);

    // c.Project("h1", "M_BC_r3c_", "M_BC_r3c_>2.25 && chi2_min_r3c_<20 && np_!=0 && npbar_!=0 && etaprimem_r1c_>0.946 && etaprimem_r1c_<0.968"); h1->Draw("HIST");
    c.Project("h1", "M_BC_r3c_", "M_BC_r3c_>2.25 && chi2_min_r3c_<25 && np_!=0 && npbar_!=0 && etaprimemr_>0.91 && etaprimemr_<0.968"); h1->Draw("HIST");
    // c.Project("h1", "M_BC_r3c_", "M_BC_r3c_>2.25 && chi2_min_r3c_<15 && np_!=0 && npbar_!=0"); h1->Draw("HIST");

    return 0;
}

// void plot()
// {

//     ROOT::RDataFrame rdf("tree", "data.root"); // Interface to TTree and TChain
//     auto rdf2 = rdf.Filter("M_BC_r3c_>2.25 && np_!=0 && npbar_!=0 && etaprimem_r1c_>0.946 && etaprimem_r1c_<0.968 && chi2_min_r3c_<35");


//     // ROOT::RDF::TH1DModel *th1dm = new ROOT::RDF::TH1DModel("M_BC", "M_BC", 20, 2.25, 2.3);
//     auto myHisto = rdf2.Histo1D( {"M_BC", "M_BC", 20u, 2.25, 2.35}, "M_BC_r3c_"); // This books the (lazy) filling of a histogram
    
//     myHisto->Draw("ALP"); 
//     // myHisto->Write("a.png");
//     // return 0;
// }
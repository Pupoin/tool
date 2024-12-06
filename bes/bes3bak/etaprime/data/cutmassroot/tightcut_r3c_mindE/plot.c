void plot()
{
    TChain c("tree");
    c.Add("4700data_selbranch.root");
    TH1F h1("h1", "h1",20, 2.25,2.35);
    c.Project("h1", "M_BC_r3c", "M_BC_r3c>2.25 && chi2_min_r3c<22.0"); 
    h1.Draw("HIST");

}
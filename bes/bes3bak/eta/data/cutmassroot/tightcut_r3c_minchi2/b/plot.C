void plot()
{
    //TCanvas can("","",800, 600);
    TChain c("tree");
    TH1F h1("h1","h1", 20, 2.25, 2.3);
    c.Add("4600data_removedouble.root");

    c.Project("h1","M_BC_r3c", "M_BC_r3c>2.25 && chi2_min_r3c<20 && (np!=0 && npbar!=0)"); h1.Draw();

    // can.Update();

}

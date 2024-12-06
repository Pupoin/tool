void plot()
{
    TChain c("tree");
    TH1F h1("h1","h1", 20, 2.25, 2.3);

    c.Add("4600data_removedouble.root");
    c.Project("h1","M_BC_c", "M_BC_c>2.25 && deltaE_min_c<0.022 && deltaE_min_c >-0.032  && (np!=0 && npbar!=0)"); h1.Draw();



    
}

int plot()
{
    TChain c("tree");
    c.Add("data.root");
    TH1F h1("h1", "h1",20, 2.25,2.35);


    // c.Project("h1", "M_BC_1c", "M_BC_1c>2.25 && deltaE_min_1c >-0.03 && deltaE_min_1c< 0.03 && etaprimem1c>0.946 && etaprimem1c<0.968"); h1.Draw("HIST");
    c.Project("h1", "M_BC_1c", "M_BC_1c>2.25 && deltaE_min_1c >-0.03 && deltaE_min_1c< 0.03 && np!=0 && npbar!=0 && etaprimem1c>0.946 && etaprimem1c<0.968 "); h1.Draw("HIST");

    return 0;
}
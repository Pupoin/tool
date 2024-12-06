
void a()
{
    TChain c("tree");
    c.Add("data.root");

    TH1F h1("h1", "h1", 20, 2.25, 2.35);
    c.Project("h1", "M_BC_r3c", "M_BC_r3c>2.25 && np==npbar && deltaE_min>-0.02 && deltaE_min<0.015"); h1.Draw();

    c.Project("h1", "M_BC_r3c", "M_BC_r3c>2.25 && chi2_min_r3c<10"); h1.Draw();
    c.Project("h1", "M_BC_r3c", "M_BC_r3c>2.25 && && np!=0 && npbar!=0 && chi2_min_r3c<29"); h1.Draw();
}
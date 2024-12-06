
// select branch
void rm_sig()
{
    ROOT::RDataFrame rdf("tree", "LL.root");



    auto  rdf2 = rdf.Filter("signal!=1 && signal!=-1");



    rdf2.Snapshot("tree", "LL_rmsig.root");
    //rdf2.Snapshot("tree", "AAA_rmLc.root");

}


// select branch
void rm_sig()
{
    ROOT::RDataFrame rdf("tree", "LL_split.root");



    auto  rdf2 = rdf.Filter("signal!=1 && signal!=-1");



    rdf2.Snapshot("tree", "LL_split_rmsig.root");
    //rdf2.Snapshot("tree", "AAA_rmLc.root");

}

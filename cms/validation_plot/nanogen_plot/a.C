void a()
{
    TChain *chain_0j = new TChain("Events");
    TChain *chain_1j = new TChain("Events");
    TChain *chain_2j = new TChain("Events");
    TChain *chain_inclusive = new TChain("Events");

    chain_0j->Add("../root/0j_*root");
    chain_1j->Add("../root/1j_*root");
    chain_2j->Add("../root/2j_*root");
    chain_inclusive->Add("../root/012j_*root");

    cout << "inclusive, LHE_NpNLO==0 :  " << chain_inclusive->GetEntries("LHE_NpNLO==0") << endl;
    cout << "inclusive, LHE_NpNLO==1 :  " << chain_inclusive->GetEntries("LHE_NpNLO==1") << endl;
    cout << "inclusive, LHE_NpNLO==2 :  " << chain_inclusive->GetEntries("LHE_NpNLO==2") << endl;
    cout << "inclusive, LHE_NpNLO>2  :  " << chain_inclusive->GetEntries("LHE_NpNLO>2" ) << endl;
    cout << "inclusive, all:    " << chain_inclusive->GetEntries() << endl;


    cout << "inclusive, LHE_NpNLO==0 && genWeight>0 :   " << chain_inclusive->GetEntries("LHE_NpNLO==0 && genWeight>0") << "    <0:    " << chain_inclusive->GetEntries("LHE_NpNLO==0 && genWeight<0") <<  endl;
    cout << "inclusive, LHE_NpNLO==1 && genWeight>0 :   " << chain_inclusive->GetEntries("LHE_NpNLO==1 && genWeight>0") << "    <0:    " << chain_inclusive->GetEntries("LHE_NpNLO==1 && genWeight<0") <<  endl;
    cout << "inclusive, LHE_NpNLO==2 && genWeight>0 :   " << chain_inclusive->GetEntries("LHE_NpNLO==2 && genWeight>0") << "    <0:    " << chain_inclusive->GetEntries("LHE_NpNLO==2 && genWeight<0") <<  endl;






































}

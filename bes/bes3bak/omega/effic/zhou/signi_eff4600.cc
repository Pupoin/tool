void signi_eff4600()
{
    //double sb = -171., b = -165.696;
	double a = 50634.4;


	// caclu efficiency
	TChain *chain_data = new TChain("tree_truth");
 	chain_data->Add("../signal/4600signal.root");
	double all_1 = chain_data->GetEntries("(ndaughterAp == 11 && Ap_id[0] == 3222 && Ap_id[1] == 223 && Ap_id[2] == 2212 && Ap_id[3] == 111 && Ap_id[4] == -211 && Ap_id[5] == 211 && Ap_id[6] == 111 && Ap_id[7] == 22 && Ap_id[8] == 22 && Ap_id[9] == 22 && Ap_id[10] == 22)");
	double all_2 = chain_data->GetEntries("(ndaughterAm == 11 && Am_id[0] == -3222 && Am_id[1] == 223 && Am_id[2] == -2212 && Am_id[3] == 111 && Am_id[4] == -211 && Am_id[5] == 211 && Am_id[6] == 111 && Am_id[7] == 22 && Am_id[8] == 22 && Am_id[9] == 22 && Am_id[10] == 22)");
	double all = all_1 + all_2;	
	//double all = chain_data->GetEntries();	
	double eff = (1.0*a) / (1.0 * all);
	//cout << "a: " << a <<  " +: " << all_1 << " -: " << all_2 << endl;
	cout << "a: " << a <<  " all: " << all << endl;
	cout << "eff :" << eff << endl;

	// calcu significance
    //Double_t DeltaLL = 2 * fabs(sb - b);
    //Double_t prob = TMath::Prob(DeltaLL, 1);              
    //Double_t significance = sqrt(2) * TMath::ErfcInverse(prob); // ErfcInverse(x) = 1 - ErfInverse(x)
    //cout << " 2ln(L) = " << DeltaLL << endl;
    //cout << " significance : " << significance << endl;

}

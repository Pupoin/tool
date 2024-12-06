void signi_eff()
{
    double sb = -8141.12, b = -8104.87;
	// double a = 98552.2;


	// caclu efficiency
	//TChain *chain_data = new TChain("tree_truth");
 	//chain_data->Add("../root/signal.root");
	//double all_1 = chain_data->GetEntries("(ndaughterAp == 8 && Ap_id[0] == 3222 && Ap_id[1] == 221 && Ap_id[2] == 2212 && Ap_id[3] == 111 && Ap_id[4] == 22 && Ap_id[5] == 22 && Ap_id[6] == 22 && Ap_id[7] == 22)");
	//double all_2 = chain_data->GetEntries("(ndaughterAm == 8 && Am_id[0] == -3222 && Am_id[1] == 221 && Am_id[2] == -2212 && Am_id[3] == 111 && Am_id[4] == 22 && Am_id[5] == 22 && Am_id[6] == 22 && Am_id[7] == 22)");
	//double all = all_1 + all_2;	
	//double eff = (1.0*a) / (1.0 * all);
	//cout << "a: " << a <<  " +: " << all_1 << " -: " << all_2 << endl;
	//cout << "eff :" << eff << endl;

	// calcu significance
    Double_t DeltaLL = 2 * fabs(sb - b);
    Double_t prob = TMath::Prob(DeltaLL, 1);              
    Double_t significance = sqrt(2) * TMath::ErfcInverse(prob); // ErfcInverse(x) = 1 - ErfInverse(x)
    cout << " 2ln(L) = " << DeltaLL << endl;
    cout << " significance : " << significance << endl;

}

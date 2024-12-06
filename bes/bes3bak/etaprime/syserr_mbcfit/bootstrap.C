// #include "/afs/ihep.ac.cn/users/s/suyj/RootUtil.h"
// #include "/publicfs/ucas/user/suyj/data/Lambda_c/Sigma0_Kp/cut/cut_best_chi.h"

void bootstrap(int seed, string fileName)
{

    TCut cut_np = "(np !=0 && npbar != 0)";
    TCut cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919))";
    TCut cut_ref = (cut_mbc && "(chi2_min_r3c< 30)" && cut_np );
    TCut cut_sig = (cut_mbc && "(chi2_min_r3c< 30)" && cut_np );

    const int bootstrap_num = 1;

    gRandom -> SetSeed(seed);
    cout << __LINE__ << ", seed: " << seed << endl;

	Double_t xmin_4600 = 2.25, xmax_4600 = 2.299765;
	Double_t xmin_4612 = 2.25, xmax_4612 = 2.30579;
	Double_t xmin_4620 = 2.25, xmax_4620 = 2.31387;
	Double_t xmin_4640 = 2.25, xmax_4640 = 2.320255;
	Double_t xmin_4660 = 2.25, xmax_4660 = 2.33046;
	Double_t xmin_4680 = 2.25, xmax_4680 = 2.34079;
	Double_t xmin_4700 = 2.25, xmax_4700 = 2.34919;

    RooRealVar var_4600("M_BC_r3c","M_{BC}", xmin_4600, xmax_4600); 
    RooRealVar var_4612("M_BC_r3c","M_{BC}", xmin_4612, xmax_4612); 
    RooRealVar var_4620("M_BC_r3c","M_{BC}", xmin_4620, xmax_4620); 
    RooRealVar var_4640("M_BC_r3c","M_{BC}", xmin_4640, xmax_4640); 
    RooRealVar var_4660("M_BC_r3c","M_{BC}", xmin_4660, xmax_4660); 
    RooRealVar var_4680("M_BC_r3c","M_{BC}", xmin_4680, xmax_4680); 
    RooRealVar var_4700("M_BC_r3c","M_{BC}", xmin_4700, xmax_4700); 

    TChain *tc_eta_4600 = new TChain("tree");
    TChain *tc_eta_4612 = new TChain("tree");
    TChain *tc_eta_4620 = new TChain("tree");
    TChain *tc_eta_4640 = new TChain("tree");
    TChain *tc_eta_4660 = new TChain("tree");
    TChain *tc_eta_4680 = new TChain("tree");
    TChain *tc_eta_4700 = new TChain("tree");
    tc_eta_4600 -> Add("etaprime/4600data_selB.root");
    tc_eta_4612 -> Add("etaprime/4612data_selB.root");
    tc_eta_4620 -> Add("etaprime/4620data_selB.root");
    tc_eta_4640 -> Add("etaprime/4640data_selB.root");
    tc_eta_4660 -> Add("etaprime/4660data_selB.root");
    tc_eta_4680 -> Add("etaprime/4680data_selB.root");
    tc_eta_4700 -> Add("etaprime/4700data_selB.root");

    TChain *tc_pion_4600 = new TChain("tree");
    TChain *tc_pion_4612 = new TChain("tree");
    TChain *tc_pion_4620 = new TChain("tree");
    TChain *tc_pion_4640 = new TChain("tree");
    TChain *tc_pion_4660 = new TChain("tree");
    TChain *tc_pion_4680 = new TChain("tree");
    TChain *tc_pion_4700 = new TChain("tree");
    tc_pion_4600 -> Add("omega/4600data_selB.root");
    tc_pion_4612 -> Add("omega/4612data_selB.root");
    tc_pion_4620 -> Add("omega/4620data_selB.root");
    tc_pion_4640 -> Add("omega/4640data_selB.root");
    tc_pion_4660 -> Add("omega/4660data_selB.root");
    tc_pion_4680 -> Add("omega/4680data_selB.root");
    tc_pion_4700 -> Add("omega/4700data_selB.root");

    RooDataSet *data_eta_4600 = new RooDataSet("data_etaprime_4600", "", tc_eta_4600 -> CopyTree(cut_sig), RooArgSet(var_4600));
    RooDataSet *data_eta_4612 = new RooDataSet("data_etaprime_4612", "", tc_eta_4612 -> CopyTree(cut_sig), RooArgSet(var_4612));
    RooDataSet *data_eta_4620 = new RooDataSet("data_etaprime_4620", "", tc_eta_4620 -> CopyTree(cut_sig), RooArgSet(var_4620));
    RooDataSet *data_eta_4640 = new RooDataSet("data_etaprime_4640", "", tc_eta_4640 -> CopyTree(cut_sig), RooArgSet(var_4640));
    RooDataSet *data_eta_4660 = new RooDataSet("data_etaprime_4660", "", tc_eta_4660 -> CopyTree(cut_sig), RooArgSet(var_4660));
    RooDataSet *data_eta_4680 = new RooDataSet("data_etaprime_4680", "", tc_eta_4680 -> CopyTree(cut_sig), RooArgSet(var_4680));
    RooDataSet *data_eta_4700 = new RooDataSet("data_etaprime_4700", "", tc_eta_4700 -> CopyTree(cut_sig), RooArgSet(var_4700));
    
    RooDataSet *data_pion_4600 = new RooDataSet("data_omega_4600", "", tc_pion_4600 -> CopyTree(cut_ref), RooArgSet(var_4600));
    RooDataSet *data_pion_4612 = new RooDataSet("data_omega_4612", "", tc_pion_4612 -> CopyTree(cut_ref), RooArgSet(var_4612));
    RooDataSet *data_pion_4620 = new RooDataSet("data_omega_4620", "", tc_pion_4620 -> CopyTree(cut_ref), RooArgSet(var_4620));
    RooDataSet *data_pion_4640 = new RooDataSet("data_omega_4640", "", tc_pion_4640 -> CopyTree(cut_ref), RooArgSet(var_4640));
    RooDataSet *data_pion_4660 = new RooDataSet("data_omega_4660", "", tc_pion_4660 -> CopyTree(cut_ref), RooArgSet(var_4660));
    RooDataSet *data_pion_4680 = new RooDataSet("data_omega_4680", "", tc_pion_4680 -> CopyTree(cut_ref), RooArgSet(var_4680));
    RooDataSet *data_pion_4700 = new RooDataSet("data_omega_4700", "", tc_pion_4700 -> CopyTree(cut_ref), RooArgSet(var_4700));
    

    TFile *file = new TFile(fileName.c_str(), "recreate");
    RooRealVar var_bootstrap("M_BC_r3c","M_{BC}", 2.25, 2.34919); 
    RooArgSet arg_set("arg_for_bootstrap");
    arg_set.add(var_bootstrap);
	RooWorkspace *ws_bootstrap = new RooWorkspace("ws_bootstrap","workspace of Boot Strap MC");

    int entry_boot;
    double var_entry;
    TString bootstrap_mc_name;

    auto list_to_bootstrap = {
        data_eta_4600,
        data_eta_4612,
        data_eta_4620,
        data_eta_4640,
        data_eta_4660,
        data_eta_4680,
        data_eta_4700,

        data_pion_4600,
        data_pion_4612,
        data_pion_4620,
        data_pion_4640,
        data_pion_4660,
        data_pion_4680,
        data_pion_4700
    };

    for (int i = 0; i < bootstrap_num; ++i) 
    {
        for (auto data : list_to_bootstrap) 
        {
            int data_num = -1;
            bootstrap_mc_name.Form("%s_bootstrap", data -> GetName());
            RooArgSet arg_set_init( * ((data -> get()) -> find("M_BC_r3c")) );
            RooDataSet bootstrap_mc( bootstrap_mc_name, bootstrap_mc_name, arg_set_init);
            data_num = data -> numEntries();

            cout<<data -> GetName() << " "<<data_num<<endl;
            for (int bi = 0; bi < data_num; ++bi) 
            {
                entry_boot = gRandom -> Integer(data_num);
                // entry_boot = bi;
                var_entry = ((RooRealVar*)(data->get(entry_boot)->find("M_BC_r3c")))->getVal();
                var_bootstrap.setVal(var_entry);
                bootstrap_mc.add(arg_set);

            }

            ws_bootstrap -> import(bootstrap_mc);

        }

    }

    ws_bootstrap -> Print();
    ws_bootstrap -> Write();
    file -> Close();
}

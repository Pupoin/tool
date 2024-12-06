void selbranch4612()
{
  TChain c("tree");
  c.Add("4612LL.root");

  int run, event, np, npbar, signal; double M_BC_r3c, deltaE_min_r3c, chi2_min_r3c;
  c.SetBranchStatus("*", 0);
  c.SetBranchStatus("run", 1);
  c.SetBranchStatus("event", 1);
  c.SetBranchStatus("M_BC_r3c", 1);
  c.SetBranchStatus("deltaE_min_r3c", 1);
  c.SetBranchStatus("chi2_min_r3c", 1);

  c.SetBranchAddress("run", &run);
  c.SetBranchAddress("event", &event);
  c.SetBranchAddress("M_BC_r3c", &M_BC_r3c);
  c.SetBranchAddress("deltaE_min_r3c", &deltaE_min_r3c);
  c.SetBranchAddress("chi2_min_r3c", &chi2_min_r3c);
  c.SetBranchAddress("np", &np);
  c.SetBranchAddress("npbar", &npbar);
  c.SetBranchAddress("signal", &signal);

  int run1, event1, np1, npbar1; double M_BC_r3c1, deltaE_min_r3c1, chi2_min_r3c1;
  int run2, event2, np2, npbar2; double M_BC_r3c2, deltaE_min_r3c2, chi2_min_r3c2;



  TFile f("4612LL_selbranch.root", "recreate");
  TTree tree("tree", "tree");
  int m_run, m_event, m_np, m_npbar, m_signal; double m_M_BC_r3c, m_deltaE_min_r3c, m_chi2_min_r3c;
  tree.Branch("run", &m_run);
  tree.Branch("event", &m_event);
  tree.Branch("M_BC_r3c", &m_M_BC_r3c);
  tree.Branch("deltaE_min_r3c", &m_deltaE_min_r3c);
  tree.Branch("chi2_min_r3c", &m_chi2_min_r3c);
  tree.Branch("np", &m_np);
  tree.Branch("npbar", &m_npbar);
  tree.Branch("signal", &m_signal);

  for(int i = 0; i< c.GetEntries(); i++)
  {
    if (i%20000==0) cout << __LINE__ << " " << i << endl;;
    c.GetEntry(i);
    if(M_BC_r3c<2) continue;
    run1 = run; 
    event1 = event; 
    M_BC_r3c1=M_BC_r3c; 
    deltaE_min_r3c1=deltaE_min_r3c; 
    chi2_min_r3c1=chi2_min_r3c;
    np1 = np;
    npbar1 = npbar;

    m_run = run1; 
    m_event = event1; 
    m_M_BC_r3c = M_BC_r3c1; 
    m_deltaE_min_r3c = deltaE_min_r3c1; 
    m_chi2_min_r3c = chi2_min_r3c1;
    m_np = np1;
    m_npbar = npbar1;
    m_signal = signal;

    tree.Fill();
    // if (i>10) break;
  }

  tree.Write();
  f.Write();
  f.Close();   
}

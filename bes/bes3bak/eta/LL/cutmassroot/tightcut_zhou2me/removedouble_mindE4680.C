void removedouble_mindE4680()
{
  TChain c("tree");
  c.Add("4680LL.root");

  int run, event, np, npbar, signal; double M_BC_c, deltaE_min_c, chi2_min_c;
  c.SetBranchAddress("run", &run);
  c.SetBranchAddress("event", &event);
  c.SetBranchAddress("M_BC_c", &M_BC_c);
  c.SetBranchAddress("deltaE_min_c", &deltaE_min_c);
  // c.SetBranchAddress("chi2_min_c", &chi2_min_c);
  c.SetBranchAddress("np", &np);
  c.SetBranchAddress("npbar", &npbar);
  c.SetBranchAddress("signal", &signal);


  int run1, event1, np1, npbar1; double M_BC_c1, deltaE_min_c1, chi2_min_c1, signal1;
  int run2, event2, np2, npbar2; double M_BC_c2, deltaE_min_c2, chi2_min_c2, signal2;


  TFile f("4680LL_removedouble.root", "recreate");
  TTree tree("tree", "tree");
  int m_run, m_event, m_np, m_npbar; double m_M_BC_c, m_deltaE_min_c, m_chi2_min_c, m_signal;
  tree.Branch("run", &m_run);
  tree.Branch("event", &m_event);
  tree.Branch("M_BC_c", &m_M_BC_c);
  tree.Branch("deltaE_min_c", &m_deltaE_min_c);
  // tree.Branch("chi2_min_c", &m_chi2_min_c);
  tree.Branch("np", &m_np);
  tree.Branch("npbar", &m_npbar);
  tree.Branch("signal", &m_signal);


  for(int i = 0; i< c.GetEntries(); )
  {
    if (i%20000==0) cout << __LINE__ << " " << i << endl;;
    c.GetEntry(i);
    run1 = run; 
    event1 = event; 
    M_BC_c1=M_BC_c; 
    deltaE_min_c1=deltaE_min_c; 
    // chi2_min_c1=chi2_min_c;
    np1 = np;
    npbar1 = npbar;
    signal1 = signal;

    c.GetEntry(i+1);
    run2 = run; 
    event2 = event; 
    M_BC_c2=M_BC_c; 
    deltaE_min_c2=deltaE_min_c; 
    // chi2_min_c2=chi2_min_c;
    np2 = np;
    npbar2 = npbar; 
    signal2 = signal;
   

    if( run1==run2 && event1 == event2 )
    {
      i=i+2;
      if(fabs(deltaE_min_c1) < fabs(deltaE_min_c2) )
      {
        m_run = run1; 
        m_event = event1; 
        m_M_BC_c = M_BC_c1; 
        m_deltaE_min_c = deltaE_min_c1; 
        // m_chi2_min_c = chi2_min_c1;
        m_np = np1;
        m_npbar = npbar1;
        m_signal = signal1;
      }
      else
      {
        m_run = run2; 
        m_event = event2; 
        m_M_BC_c = M_BC_c2; 
        m_deltaE_min_c = deltaE_min_c2; 
        // m_chi2_min_c = chi2_min_c2;
        m_np = np2;
        m_npbar = npbar2;
        m_signal = signal2;
      }
      
    }
    else
    {
      i++;
      m_run = run1; 
      m_event = event1; 
      m_M_BC_c = M_BC_c1; 
      m_deltaE_min_c = deltaE_min_c1; 
      m_chi2_min_c = chi2_min_c1;
      m_np = np1;
      m_npbar = npbar1;
      m_signal = signal1;
    }

    tree.Fill();
    // if (i>10) break;
  }

  tree.Write();
  f.Write();
  f.Close();   
}

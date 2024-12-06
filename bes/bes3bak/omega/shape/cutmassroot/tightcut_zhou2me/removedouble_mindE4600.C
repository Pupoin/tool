void removedouble_mindE4600()
{
  TChain c("tree");
  c.Add("4600shape.root");

  int run, event, np, npbar; double M_BC, deltaE_min, chi2_min_c;
  c.SetBranchAddress("run", &run);
  c.SetBranchAddress("event", &event);
  c.SetBranchAddress("M_BC", &M_BC);
  c.SetBranchAddress("deltaE_min", &deltaE_min);
  // c.SetBranchAddress("chi2_min_c", &chi2_min_c);
  c.SetBranchAddress("np", &np);
  c.SetBranchAddress("npbar", &npbar);

  int run1, event1, np1, npbar1; double M_BC1, deltaE_min1, chi2_min_c1;
  int run2, event2, np2, npbar2; double M_BC2, deltaE_min2, chi2_min_c2;


  TFile f("4600shape_removedouble.root", "recreate");
  TTree tree("tree", "tree");
  int m_run, m_event, m_np, m_npbar; double m_M_BC, m_deltaE_min, m_chi2_min_c;
  tree.Branch("run", &m_run);
  tree.Branch("event", &m_event);
  tree.Branch("M_BC", &m_M_BC);
  tree.Branch("deltaE_min", &m_deltaE_min);
  // tree.Branch("chi2_min_c", &m_chi2_min_c);
  tree.Branch("np", &m_np);
  tree.Branch("npbar", &m_npbar);

  for(int i = 0; i< c.GetEntries(); )
  {
    if (i%20000==0) cout << __LINE__ << " " << i << endl;;
    c.GetEntry(i);
    run1 = run; 
    event1 = event; 
    M_BC1=M_BC; 
    deltaE_min1=deltaE_min; 
    // chi2_min_c1=chi2_min_c;
    np1 = np;
    npbar1 = npbar;
    // cout << __LINE__ <<  " " << run1 <<  " " << event1 << endl;

    c.GetEntry(i+1);
    run2 = run; 
    event2 = event; 
    M_BC2=M_BC; 
    deltaE_min2=deltaE_min; 
    // chi2_min_c2=chi2_min_c;
    np2 = np;
    npbar2 = npbar;    // cout << __LINE__ <<  " " << run2 <<  " " << event2 << endl;

    if( run1==run2 && event1 == event2 )
    {
      i=i+2;
      if(fabs(deltaE_min1) < fabs(deltaE_min2) )
      {
        m_run = run1; 
        m_event = event1; 
        m_M_BC = M_BC1; 
        m_deltaE_min = deltaE_min1; 
        // m_chi2_min_c = chi2_min_c1;
        m_np = np1;
        m_npbar = npbar1;
      }
      else
      {
        m_run = run2; 
        m_event = event2; 
        m_M_BC = M_BC2; 
        m_deltaE_min = deltaE_min2; 
        // m_chi2_min_c = chi2_min_c2;
        m_np = np2;
        m_npbar = npbar2;
      }
      
    }
    else
    {
      i++;
      m_run = run1; 
      m_event = event1; 
      m_M_BC = M_BC1; 
      m_deltaE_min = deltaE_min1; 
      m_chi2_min_c = chi2_min_c1;
      m_np = np1;
      m_npbar = npbar1;
    }

    tree.Fill();
    // if (i>10) break;
  }

  tree.Write();
  f.Write();
  f.Close();   
}

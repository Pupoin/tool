void removedouble_minchi24620()
{
  TChain c("tree");
  c.Add("../4620data.root");

  int run, event, np, npbar; double M_BC_r3c, deltaE_min_r3c, chi2_min_r3c, E_beam, pall_r3c[4], gam1_r3c[4], gam2_r3c[4], gam3_r3c[4], gam4_r3c[4];
  c.SetBranchAddress("run", &run);
  c.SetBranchAddress("event", &event);
  c.SetBranchAddress("M_BC_r3c", &M_BC_r3c);
  c.SetBranchAddress("deltaE_min_r3c", &deltaE_min_r3c);
  c.SetBranchAddress("chi2_min_r3c", &chi2_min_r3c);
  c.SetBranchAddress("np", &np);
  c.SetBranchAddress("npbar", &npbar);
  c.SetBranchAddress("E_beam", &E_beam);
  c.SetBranchAddress("pall_r3c", pall_r3c);
  c.SetBranchAddress("gam1_r3c", gam1_r3c);
  c.SetBranchAddress("gam2_r3c", gam2_r3c);
  c.SetBranchAddress("gam3_r3c", gam3_r3c);
  c.SetBranchAddress("gam4_r3c", gam4_r3c);
  

  int run1, event1, np1, npbar1; double M_BC_r3c1, deltaE_min_r3c1, chi2_min_r3c1, E_beam1, pall_r3c1[4], gam1_r3c1[4], gam2_r3c1[4], gam3_r3c1[4], gam4_r3c1[4];
  int run2, event2, np2, npbar2; double M_BC_r3c2, deltaE_min_r3c2, chi2_min_r3c2, E_beam2, pall_r3c2[4], gam1_r3c2[4], gam2_r3c2[4], gam3_r3c2[4], gam4_r3c2[4];


  TFile f("4620data_removedouble.root", "recreate");
  TTree tree("tree", "tree");
  int m_run, m_event, m_np, m_npbar; double m_M_BC_r3c, m_deltaE_min_r3c;
  Float_t m_chi2_min_r3c, m_E_beam, m_pall_r3c[4], m_gam1_r3c[4], m_gam2_r3c[4], m_gam3_r3c[4], m_gam4_r3c[4];
  tree.Branch("run", &m_run);
  tree.Branch("event", &m_event);
  tree.Branch("M_BC_r3c", &m_M_BC_r3c);
  tree.Branch("deltaE_min_r3c", &m_deltaE_min_r3c);
  tree.Branch("chi2_min_r3c", &m_chi2_min_r3c);
  tree.Branch("np", &m_np);
  tree.Branch("npbar", &m_npbar);
  tree.Branch("E_beam", &m_E_beam);
  tree.Branch("pall_r3c", m_pall_r3c, "pall_r3c[4]/F");
  tree.Branch("gam1_r3c", m_gam1_r3c, "gam1_r3c[4]/F");
  tree.Branch("gam2_r3c", m_gam2_r3c, "gam2_r3c[4]/F");
  tree.Branch("gam3_r3c", m_gam3_r3c, "gam3_r3c[4]/F");
  tree.Branch("gam4_r3c", m_gam4_r3c, "gam4_r3c[4]/F");


  for(int i = 0; i< c.GetEntries(); )
  {
    if (i%20000==0) cout << __LINE__ << " " << i << endl;;
    c.GetEntry(i);
    run1 = run; 
    event1 = event; 
    M_BC_r3c1=M_BC_r3c; 
    deltaE_min_r3c1=deltaE_min_r3c; 
    chi2_min_r3c1=chi2_min_r3c;
    np1 = np;
    npbar1 = npbar;
    E_beam1 = E_beam;
    for(int j =0;j<4;j++)  
    {
        pall_r3c1[j] = pall_r3c[j];
        gam1_r3c1[j] = gam1_r3c[j];
        gam2_r3c1[j] = gam2_r3c[j];
        gam3_r3c1[j] = gam3_r3c[j];
        gam4_r3c1[j] = gam4_r3c[j];
    }

    // cout << __LINE__ <<  " " << run1 <<  " " << event1 << endl;

    c.GetEntry(i+1);
    run2 = run; 
    event2 = event; 
    M_BC_r3c2=M_BC_r3c; 
    deltaE_min_r3c2=deltaE_min_r3c; 
    chi2_min_r3c2=chi2_min_r3c;
    np2 = np;
    npbar2 = npbar;    // cout << __LINE__ <<  " " << run2 <<  " " << event2 << endl;
    E_beam1 = E_beam;
    for(int j =0;j<4;j++)  
    {
        pall_r3c2[j] = pall_r3c[j];
        gam1_r3c2[j] = gam1_r3c[j];
        gam2_r3c2[j] = gam2_r3c[j];
        gam3_r3c2[j] = gam3_r3c[j];
        gam4_r3c2[j] = gam4_r3c[j];
    }

    if( run1==run2 && event1 == event2 )
    {
      i=i+2;
      if(chi2_min_r3c1 < chi2_min_r3c2 )
      {
        m_run = run1; 
        m_event = event1; 
        m_M_BC_r3c = M_BC_r3c1; 
        m_deltaE_min_r3c = deltaE_min_r3c1; 
        m_chi2_min_r3c = chi2_min_r3c1;
        m_np = np1;
        m_npbar = npbar1;
        m_E_beam = E_beam1;
        for(int j =0;j<4;j++)  
        {
            m_pall_r3c[j] = pall_r3c1[j];
            m_gam1_r3c[j] = gam1_r3c1[j];
            m_gam2_r3c[j] = gam2_r3c1[j];
            m_gam3_r3c[j] = gam3_r3c1[j];
            m_gam4_r3c[j] = gam4_r3c1[j];
        }
      }
      else
      {
        m_run = run2; 
        m_event = event2; 
        m_M_BC_r3c = M_BC_r3c2; 
        m_deltaE_min_r3c = deltaE_min_r3c2; 
        m_chi2_min_r3c = chi2_min_r3c2;
        m_np = np2;
        m_npbar = npbar2;
        m_E_beam = E_beam2;
        for(int j =0;j<4;j++)  
        {
            m_pall_r3c[j] = pall_r3c2[j];
            m_gam1_r3c[j] = gam1_r3c2[j];
            m_gam2_r3c[j] = gam2_r3c2[j];
            m_gam3_r3c[j] = gam3_r3c2[j];
            m_gam4_r3c[j] = gam4_r3c2[j];
        }
      }
      
    }
    else
    {
      i++;
      m_run = run1; 
      m_event = event1; 
      m_M_BC_r3c = M_BC_r3c1; 
      m_deltaE_min_r3c = deltaE_min_r3c1; 
      m_chi2_min_r3c = chi2_min_r3c1;
      m_np = np1;
      m_npbar = npbar1;
      m_E_beam = E_beam1;
      for(int j =0;j<4;j++)  
      {
          m_pall_r3c[j] = pall_r3c1[j];
          m_gam1_r3c[j] = gam1_r3c1[j];
          m_gam2_r3c[j] = gam2_r3c1[j];
          m_gam3_r3c[j] = gam3_r3c1[j];
          m_gam4_r3c[j] = gam4_r3c1[j];
      }
    }

    tree.Fill();
    // if (i>10) break;
  }

  tree.Write();
  f.Write();
  f.Close();   
}

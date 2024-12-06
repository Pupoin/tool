void removedouble_mindE()
{
  TChain c("tree");
  c.Add("4600shape.root");

  int run, event, np, npbar; double M_BC_c, deltaE_min_c, chi2_min_c, gam1_c[4], gam2_c[4], gam3_c[4], gam4_c[4] ;
  c.SetBranchAddress("run", &run);
  c.SetBranchAddress("event", &event);
  c.SetBranchAddress("M_BC_c", &M_BC_c);
  c.SetBranchAddress("deltaE_min_c", &deltaE_min_c);
  // c.SetBranchAddress("chi2_min_c", &chi2_min_c);
  c.SetBranchAddress("np", &np);
  c.SetBranchAddress("npbar", &npbar);
  c.SetBranchAddress("gam1_c", &gam1_c);
  c.SetBranchAddress("gam2_c", &gam2_c);
  c.SetBranchAddress("gam3_c", &gam3_c);
  c.SetBranchAddress("gam4_c", &gam4_c);

  int run1, event1, np1, npbar1; double M_BC_c1, deltaE_min_c1, chi2_min_c1, dipim1;
  int run2, event2, np2, npbar2; double M_BC_c2, deltaE_min_c2, chi2_min_c2, dipim2;
  int m_run, m_event, m_np, m_npbar; double m_M_BC_c, m_deltaE_min_c, m_chi2_min_c, m_dipim ;

  TFile f("4600shape_removedouble.root", "recreate");
  TTree tree("tree", "tree");
  tree.Branch("run", &m_run);
  tree.Branch("event", &m_event);
  tree.Branch("M_BC_c", &m_M_BC_c);
  tree.Branch("deltaE_min_c", &m_deltaE_min_c);
  // tree.Branch("chi2_min_c", &m_chi2_min_c);
  tree.Branch("np", &m_np);
  tree.Branch("npbar", &m_npbar);
  tree.Branch("dipim", &m_dipim);

  TLorentzVector tmp;
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
    tmp[0] = gam1_c[0]+gam2_c[0]+gam3_c[0]+gam4_c[0];
    tmp[1] = gam1_c[1]+gam2_c[1]+gam3_c[1]+gam4_c[1];
    tmp[2] = gam1_c[2]+gam2_c[2]+gam3_c[2]+gam4_c[2];
    tmp[3] = gam1_c[3]+gam2_c[3]+gam3_c[3]+gam4_c[3];
    dipim1 = tmp.M();

    c.GetEntry(i+1);
    run2 = run; 
    event2 = event; 
    M_BC_c2=M_BC_c; 
    deltaE_min_c2=deltaE_min_c; 
    // chi2_min_c2=chi2_min_c;
    np2 = np;
    npbar2 = npbar;    
    tmp[0] = gam1_c[0]+gam2_c[0]+gam3_c[0]+gam4_c[0];
    tmp[1] = gam1_c[1]+gam2_c[1]+gam3_c[1]+gam4_c[1];
    tmp[2] = gam1_c[2]+gam2_c[2]+gam3_c[2]+gam4_c[2];
    tmp[3] = gam1_c[3]+gam2_c[3]+gam3_c[3]+gam4_c[3];
    dipim2 = tmp.M();

    if( run1==run2 && event1 == event2 )
    {
      i=i+2;
      if(fabs(deltaE_min_c1) < fabs(deltaE_min_c2))
      {
        m_run = run1; 
        m_event = event1; 
        m_M_BC_c = M_BC_c1; 
        m_deltaE_min_c = deltaE_min_c1; 
        // m_chi2_min_c = chi2_min_c1;
        m_np = np1;
        m_npbar = npbar1;
        m_dipim = dipim1;
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
        m_dipim = dipim2;

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
      m_dipim = dipim1;
    }

    tree.Fill();
    // if (i>15) break;
  }

  tree.Write();
  f.Write();
  f.Close();   
}

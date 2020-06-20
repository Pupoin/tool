#include <iostream>
#include <string>
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
double track_PID_err(){

		TFile *datafile = new TFile("/scratchfs/bes/lincx/job_ana/root/cut_MC.root");
		TTree *datatree = (TTree*)datafile->Get("TDphipi");

		Double_t kp_p4_x, kp_p4_y, kp_p4_z;
		Double_t km_p4_x, km_p4_y, km_p4_z;
    Double_t pi_p4_x, pi_p4_y, pi_p4_z;
		datatree->SetBranchAddress("kp_p4_x",&kp_p4_x);//get branch
		datatree->SetBranchAddress("kp_p4_y",&kp_p4_y);//get branch
		datatree->SetBranchAddress("kp_p4_z",&kp_p4_z);//get branch
		datatree->SetBranchAddress("km_p4_x",&km_p4_x);//get branch
		datatree->SetBranchAddress("km_p4_y",&km_p4_y);//get branch
		datatree->SetBranchAddress("km_p4_z",&km_p4_z);//get branch
		datatree->SetBranchAddress("pi_p4_x",&pi_p4_x);//get branch
		datatree->SetBranchAddress("pi_p4_y",&pi_p4_y);//get branch
		datatree->SetBranchAddress("pi_p4_z",&pi_p4_z);//get branch

		double err = 0;
		double ti[6]={1,1,1,1,1,1};
		for(Int_t i=0;i<datatree->GetEntries();i++){
          datatree->GetEntry(i);
		      //std::cout<<__LINE__<<kp[0]<<std::endl;	
		      double pkp = sqrt(kp_p4_x*kp_p4_x+kp_p4_y*kp_p4_y+kp_p4_z*kp_p4_z);//k+ momentum
		      double pkm = sqrt(km_p4_x*km_p4_x+km_p4_y*km_p4_y+km_p4_z*km_p4_z);//k- momentum
		      double ppi = sqrt(pi_p4_x*pi_p4_x+pi_p4_y*pi_p4_y+pi_p4_z*pi_p4_z);//pi momentum

                      //K+ or K- PID error
		      if(pkp>=1.0) ti[0] = -0.0027;
		      if(pkp<1.0&&pkp>=0.9) ti[0] = -0.0037;		
          if(pkp<0.9&&pkp>=0.8) ti[0] = -0.0006;
		      if(pkp<0.8&&pkp>=0.7) ti[0] = -0.0001;
		      if(pkp<0.7&&pkp>=0.6) ti[0] = 0.0013;
		      if(pkp<0.6&&pkp>=0.5) ti[0] = 0.0002;
		      if(pkp<0.5&&pkp>=0.4) ti[0] = 0.0006;
		      if(pkp<0.4&&pkp>=0.3) ti[0] = -0.0026;
		      if(pkp<0.3&&pkp>=0.2) ti[0] = 0.0004;
		      if(pkp<0.2&&pkp>=0.1) ti[0] = -0.0104;
		      if(pkp<0.1) ti[0] = 7.0000;
		      
          if(pkm>=1.0) ti[1] = -0.0027;
		      if(pkm<1.0&&pkm>=0.9) ti[1] = -0.0037;
		      if(pkm<0.9&&pkm>=0.8) ti[1] = -0.0006;
		      if(pkm<0.8&&pkm>=0.7) ti[1] = -0.0001;
		      if(pkm<0.7&&pkm>=0.6) ti[1] = 0.0013;
		      if(pkm<0.6&&pkm>=0.5) ti[1] = 0.0002;
		      if(pkm<0.5&&pkm>=0.4) ti[1] = 0.0006;
	        if(pkm<0.4&&pkm>=0.3) ti[1] = -0.0026;
		      if(pkm<0.3&&pkm>=0.2) ti[1] = 0.0004;
		      if(pkm<0.2&&pkm>=0.1) ti[1] = -0.0104;
		      if(pkm<0.1) ti[1] = 7.0000;
                      
                      //K+ or K- Tracking error
		      if(pkp>=1.0) ti[2] = 0.0207;
		      if(pkp<1.0&&pkp>=0.9) ti[2] = 0.0020;
		      if(pkp<0.9&&pkp>=0.8) ti[2] = 0.0018;
		      if(pkp<0.8&&pkp>=0.7) ti[2] = 0.0017;
		      if(pkp<0.7&&pkp>=0.6) ti[2] = 0.0016;
		      if(pkp<0.6&&pkp>=0.5) ti[2] = 0.0023;
		      if(pkp<0.5&&pkp>=0.4) ti[2] = 0.0026;
		      if(pkp<0.4&&pkp>=0.3) ti[2] = 0.0029;
		      if(pkp<0.3&&pkp>=0.2) ti[2] = 0.0040;
		      if(pkp<0.2&&pkp>=0.1) ti[2] = 0.0061;
		      if(pkp<0.1) ti[2] = 0.0114;
					
          if(pkm>=1.0) ti[3] = 0.0207;
		      if(pkm<1.0&&pkm>=0.9) ti[3] = 0.0020;
		      if(pkm<0.9&&pkm>=0.8) ti[3] = 0.0018;
		      if(pkm<0.8&&pkm>=0.7) ti[3] = 0.0017;
		      if(pkm<0.7&&pkm>=0.6) ti[3] = 0.0016;
		      if(pkm<0.6&&pkm>=0.5) ti[3] = 0.0023;                                                              
		      if(pkm<0.5&&pkm>=0.4) ti[3] = 0.0026;
		      if(pkm<0.4&&pkm>=0.3) ti[3] = 0.0029;
		      if(pkm<0.3&&pkm>=0.2) ti[3] = 0.0040;
		      if(pkm<0.2&&pkm>=0.1) ti[3] = 0.0061;
		      if(pkm<0.1) ti[3] = 0.0114;
                      
                      //pi PID error
                      if(ppi>=1.0) ti[4] = -0.0163;
                      if(ppi<1.0&&ppi>=0.9) ti[4] = -0.0112;
                      if(ppi<0.9&&ppi>=0.8) ti[4] = -0.0119;
                      if(ppi<0.8&&ppi>=0.7) ti[4] = -0.0086;
                      if(ppi<0.7&&ppi>=0.6) ti[4] = -0.0060;
                      if(ppi<0.6&&ppi>=0.5) ti[4] = -0.0015;    
                      if(ppi<0.5&&ppi>=0.4) ti[4] = -0.0006;
                      if(ppi<0.4&&ppi>=0.3) ti[4] = -0.0008;
                      if(ppi<0.3&&ppi>=0.2) ti[4] = -0.0002;
                      if(ppi<0.2&&ppi>=0.1) ti[4] = -0.0010;
                      if(ppi<0.1) ti[4] = -0.0065; 

                      //pi Tracking error
                      if(ppi>=1.0) ti[5] = -0.0016;  
                      if(ppi<1.0&&ppi>=0.9) ti[5] = 0.0012;
                      if(ppi<0.9&&ppi>=0.8) ti[5] = 0.0024;
                      if(ppi<0.8&&ppi>=0.7) ti[5] = 0.0011;     
                      if(ppi<0.7&&ppi>=0.6) ti[5] = 0.0010;
                      if(ppi<0.6&&ppi>=0.5) ti[5] = 0.0017;    
                      if(ppi<0.5&&ppi>=0.4) ti[5] = -0.0002;
                      if(ppi<0.4&&ppi>=0.3) ti[5] = -0.0024;
                      if(ppi<0.3&&ppi>=0.2) ti[5] = -0.0007;
                      if(ppi<0.2&&ppi>=0.1) ti[5] = 0.0088; 
                      if(ppi<0.1) ti[5] = 0.0910; 

	        for (int j=0;j<6;j++){
			    if (ti[j]==1) continue;
		      }
		      err = err + (1+ti[0])*(1+ti[1])*(1+ti[2])*(1+ti[3])*(1+ti[4])*(1+ti[5]);
		}
                
                double a_err;       
                cout<<err<<endl;
                a_err = (err/76510)-1;//N_rec(sig)=76510		
		return a_err;

} 

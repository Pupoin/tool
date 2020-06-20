#include <iostream>
#include <string>
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
double Trk_PID_err(){

		TFile *datafile = new TFile("/scratchfs/bes/lincx/6.6.4.p02/DptoPhiPi/job_ana/root/cut_MC.root");
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

		double err_kp_pid_data = 0, err_kp_pid_MC = 0, err_km_pid_data = 0, err_km_pid_MC = 0, err_pip_pid_data = 0, err_pip_pid_MC = 0;
		double err_kp_trk_data = 0, err_kp_trk_MC = 0, err_km_trk_data = 0, err_km_trk_MC = 0, err_pip_trk_data = 0, err_pip_trk_MC = 0;
		double ti[6]={1,1,1,1,1,1};
    double eff_MC[6]={1,1,1,1,1,1};
    double eff_data[6]={1,1,1,1,1,1};

		for(Int_t i=0;i<datatree->GetEntries();i++){
          datatree->GetEntry(i);
		      //std::cout<<__LINE__<<kp[0]<<std::endl;	
		      double pkp = sqrt(kp_p4_x*kp_p4_x+kp_p4_y*kp_p4_y+kp_p4_z*kp_p4_z);//k+ momentum
		      double pkm = sqrt(km_p4_x*km_p4_x+km_p4_y*km_p4_y+km_p4_z*km_p4_z);//k- momentum
		      double ppi = sqrt(pi_p4_x*pi_p4_x+pi_p4_y*pi_p4_y+pi_p4_z*pi_p4_z);//pi momentum

          //K+ or K- PID error
		      if(pkp>=1.0)          {ti[0] = -0.0027; eff_MC[0]=0.9452; eff_data[0]=0.9427;}
		      if(pkp<1.0&&pkp>=0.9) {ti[0] = -0.0037;	eff_MC[0]=0.9563;	eff_data[0]=0.9528;}
          if(pkp<0.9&&pkp>=0.8) {ti[0] = -0.0006; eff_MC[0]=0.9659; eff_data[0]=0.9653;}
		      if(pkp<0.8&&pkp>=0.7) {ti[0] = -0.0001; eff_MC[0]=0.9765; eff_data[0]=0.9764;}
		      if(pkp<0.7&&pkp>=0.6) {ti[0] = 0.0013;  eff_MC[0]=0.9827; eff_data[0]=0.9840;}
		      if(pkp<0.6&&pkp>=0.5) {ti[0] = 0.0002;  eff_MC[0]=0.9879; eff_data[0]=0.9881;}
		      if(pkp<0.5&&pkp>=0.4) {ti[0] = 0.0006;  eff_MC[0]=0.9927; eff_data[0]=0.9933;}
		      if(pkp<0.4&&pkp>=0.3) {ti[0] = -0.0026; eff_MC[0]=0.9953; eff_data[0]=0.9928;}
		      if(pkp<0.3&&pkp>=0.2) {ti[0] = 0.0004;  eff_MC[0]=0.9929; eff_data[0]=0.9933;}
		      if(pkp<0.2&&pkp>=0.1) {ti[0] = -0.0104; eff_MC[0]=0.9824; eff_data[0]=0.9722;}
		      if(pkp<0.1)           {ti[0] = 7.0000;  eff_MC[0]=0.1250; eff_data[0]=1.0000;}
		      
          if(pkm>=1.0)          {ti[1] = -0.0027; eff_MC[1]=0.9452; eff_data[1]=0.9427;}
		      if(pkm<1.0&&pkm>=0.9) {ti[1] = -0.0037; eff_MC[1]=0.9563; eff_data[1]=0.9528;}
		      if(pkm<0.9&&pkm>=0.8) {ti[1] = -0.0006; eff_MC[1]=0.9659; eff_data[1]=0.9653;}
		      if(pkm<0.8&&pkm>=0.7) {ti[1] = -0.0001; eff_MC[1]=0.9765; eff_data[1]=0.9764;}
		      if(pkm<0.7&&pkm>=0.6) {ti[1] = 0.0013;  eff_MC[1]=0.9827; eff_data[1]=0.9840;}
		      if(pkm<0.6&&pkm>=0.5) {ti[1] = 0.0002;  eff_MC[1]=0.9879; eff_data[1]=0.9881;}
		      if(pkm<0.5&&pkm>=0.4) {ti[1] = 0.0006;  eff_MC[1]=0.9927; eff_data[1]=0.9933;}
	        if(pkm<0.4&&pkm>=0.3) {ti[1] = -0.0026; eff_MC[1]=0.9953; eff_data[1]=0.9928;}
		      if(pkm<0.3&&pkm>=0.2) {ti[1] = 0.0004;  eff_MC[1]=0.9929; eff_data[1]=0.9933;}
		      if(pkm<0.2&&pkm>=0.1) {ti[1] = -0.0104; eff_MC[1]=0.9824; eff_data[1]=0.9722;}
		      if(pkm<0.1)           {ti[1] = 7.0000;  eff_MC[1]=0.1250; eff_data[1]=1.0000;}
                      
          //K+ or K- Tracking error
		      if(pkp>=1.0)          {ti[2] = 0.0207; eff_MC[2]=0.9400; eff_data[2]=0.9779;}
		      if(pkp<1.0&&pkp>=0.9) {ti[2] = 0.0020; eff_MC[2]=0.9339; eff_data[2]=0.9355;}
		      if(pkp<0.9&&pkp>=0.8) {ti[2] = 0.0018; eff_MC[2]=0.9252; eff_data[2]=0.9281;}
		      if(pkp<0.8&&pkp>=0.7) {ti[2] = 0.0017; eff_MC[2]=0.9199; eff_data[2]=0.9228;}
		      if(pkp<0.7&&pkp>=0.6) {ti[2] = 0.0016; eff_MC[2]=0.9061; eff_data[2]=0.9125;}
		      if(pkp<0.6&&pkp>=0.5) {ti[2] = 0.0023; eff_MC[2]=0.8875; eff_data[2]=0.8998;}
		      if(pkp<0.5&&pkp>=0.4) {ti[2] = 0.0026; eff_MC[2]=0.8532; eff_data[2]=0.8671;}
		      if(pkp<0.4&&pkp>=0.3) {ti[2] = 0.0029; eff_MC[2]=0.8023; eff_data[2]=0.8176;}
		      if(pkp<0.3&&pkp>=0.2) {ti[2] = 0.0040; eff_MC[2]=0.7036; eff_data[2]=0.7305;}
		      if(pkp<0.2&&pkp>=0.1) {ti[2] = 0.0061; eff_MC[2]=0.4229; eff_data[2]=0.4369;}
		      if(pkp<0.1)           {ti[2] = 0.0114; eff_MC[2]=0.1482; eff_data[2]=0.1939;}
					
          if(pkm>=1.0)          {ti[3] = 0.0207; eff_MC[3]=0.9400; eff_data[3]=0.9779;}
		      if(pkm<1.0&&pkm>=0.9) {ti[3] = 0.0020; eff_MC[3]=0.9339; eff_data[3]=0.9355;}
		      if(pkm<0.9&&pkm>=0.8) {ti[3] = 0.0018; eff_MC[3]=0.9252; eff_data[3]=0.9281;}
		      if(pkm<0.8&&pkm>=0.7) {ti[3] = 0.0017; eff_MC[3]=0.9199; eff_data[3]=0.9228;}
		      if(pkm<0.7&&pkm>=0.6) {ti[3] = 0.0016; eff_MC[3]=0.9061; eff_data[3]=0.9125;}
		      if(pkm<0.6&&pkm>=0.5) {ti[3] = 0.0023; eff_MC[3]=0.8875; eff_data[3]=0.8998;}                       
		      if(pkm<0.5&&pkm>=0.4) {ti[3] = 0.0026; eff_MC[3]=0.8532; eff_data[3]=0.8671;}
		      if(pkm<0.4&&pkm>=0.3) {ti[3] = 0.0029; eff_MC[3]=0.8023; eff_data[3]=0.8176;}
		      if(pkm<0.3&&pkm>=0.2) {ti[3] = 0.0040; eff_MC[3]=0.7036; eff_data[3]=0.7305;}
		      if(pkm<0.2&&pkm>=0.1) {ti[3] = 0.0061; eff_MC[3]=0.4229; eff_data[3]=0.4369;}
		      if(pkm<0.1)           {ti[3] = 0.0114; eff_MC[3]=0.1482; eff_data[3]=0.1939;}
                      
          //pi PID error
          if(ppi>=1.0)          {ti[4] = -0.0163; eff_MC[4]=0.9074; eff_data[4]=0.8926;} 
          if(ppi<1.0&&ppi>=0.9) {ti[4] = -0.0112; eff_MC[4]=0.9287; eff_data[4]=0.9183;} 
          if(ppi<0.9&&ppi>=0.8) {ti[4] = -0.0119; eff_MC[4]=0.9538; eff_data[4]=0.9425;} 
          if(ppi<0.8&&ppi>=0.7) {ti[4] = -0.0086; eff_MC[4]=0.9739; eff_data[4]=0.9656;} 
          if(ppi<0.7&&ppi>=0.6) {ti[4] = -0.0060; eff_MC[4]=0.9865; eff_data[4]=0.9806;} 
          if(ppi<0.6&&ppi>=0.5) {ti[4] = -0.0015; eff_MC[4]=0.9934; eff_data[4]=0.9919;} 
          if(ppi<0.5&&ppi>=0.4) {ti[4] = -0.0006; eff_MC[4]=0.9973; eff_data[4]=0.9967;} 
          if(ppi<0.4&&ppi>=0.3) {ti[4] = -0.0008; eff_MC[4]=0.9987; eff_data[4]=0.9979;} 
          if(ppi<0.3&&ppi>=0.2) {ti[4] = -0.0002; eff_MC[4]=0.9996; eff_data[4]=0.9994;}
          if(ppi<0.2&&ppi>=0.1) {ti[4] = -0.0010; eff_MC[4]=0.9997; eff_data[4]=0.9986;} 
          if(ppi<0.1)           {ti[4] = -0.0065; eff_MC[4]=0.9909; eff_data[4]=0.9844;} 

          //pi Tracking error
          if(ppi>=1.0)          {ti[5] = -0.0016; eff_MC[5]=0.9895; eff_data[5]=0.9879;}
          if(ppi<1.0&&ppi>=0.9) {ti[5] = 0.0012;  eff_MC[5]=0.9864; eff_data[5]=0.9876;}
          if(ppi<0.9&&ppi>=0.8) {ti[5] = 0.0024;  eff_MC[5]=0.9830; eff_data[5]=0.9854;}
          if(ppi<0.8&&ppi>=0.7) {ti[5] = 0.0011;  eff_MC[5]=0.9831; eff_data[5]=0.9841;}    
          if(ppi<0.7&&ppi>=0.6) {ti[5] = 0.0010;  eff_MC[5]=0.9794; eff_data[5]=0.9804;}
          if(ppi<0.6&&ppi>=0.5) {ti[5] = 0.0017;  eff_MC[5]=0.9737; eff_data[5]=0.9754;}
          if(ppi<0.5&&ppi>=0.4) {ti[5] = -0.0002; eff_MC[5]=0.9618; eff_data[5]=0.9616;}
          if(ppi<0.4&&ppi>=0.3) {ti[5] = -0.0024; eff_MC[5]=0.9388; eff_data[5]=0.9365;}
          if(ppi<0.3&&ppi>=0.2) {ti[5] = -0.0007; eff_MC[5]=0.9028; eff_data[5]=0.9022;}
          if(ppi<0.2&&ppi>=0.1) {ti[5] = 0.0088;  eff_MC[5]=0.8590; eff_data[5]=0.8665;}
          if(ppi<0.1)           {ti[5] = 0.0910;  eff_MC[5]=0.5255; eff_data[5]=0.5733;}

	        for (int j=0;j<6;j++){
			    if (ti[j]==1) continue;
		      }
		      //err = err + (1+ti[0])*(1+ti[1])*(1+ti[2])*(1+ti[3])*(1+ti[4])*(1+ti[5]);
          err_kp_pid_data = err_kp_pid_data +1/eff_data[0]; //K+,K-,pi+  PID or Tracking
          err_kp_pid_MC = err_kp_pid_MC +1/eff_MC[0]; //K+,K-,pi+  PID or Tracking
          err_km_pid_data = err_km_pid_MC +1/eff_data[1]; //K+,K-,pi+  PID or Tracking
          err_km_pid_MC = err_km_pid_MC +1/eff_MC[1]; //K+,K-,pi+  PID or Tracking
 
          err_kp_trk_data = err_kp_trk_data +1/eff_data[2]; //K+,K-,pi+  PID or Tracking
          err_kp_trk_MC = err_kp_trk_MC +1/eff_MC[2]; //K+,K-,pi+  PID or Tracking
          err_km_trk_data = err_km_trk_MC +1/eff_data[3]; //K+,K-,pi+  PID or Tracking
          err_km_trk_MC = err_km_trk_MC +1/eff_MC[3]; //K+,K-,pi+  PID or Tracking
         
          err_pip_pid_data = err_pip_pid_data +1/eff_data[4]; //K+,K-,pi+  PID or Tracking
          err_pip_pid_MC = err_pip_pid_MC +1/eff_MC[4]; //K+,K-,pi+  PID or Tracking
          err_pip_trk_data = err_pip_trk_data +1/eff_data[5]; //K+,K-,pi+  PID or Tracking
          err_pip_trk_MC = err_pip_trk_MC +1/eff_MC[5]; //K+,K-,pi+  PID or Tracking
		}
                
          double err_kp_pid=0, err_kp_trk=0, err_km_pid=0, err_km_trk=0, err_pip_pid=0, err_pip_trk=0;        
          
          err_kp_pid=(err_kp_pid_data-err_kp_pid_MC)/err_kp_pid_MC;
          err_km_pid=(err_km_pid_data-err_km_pid_MC)/err_km_pid_MC;
          err_pip_pid=(err_pip_pid_data-err_pip_pid_MC)/err_pip_pid_MC;
           
          err_kp_trk=(err_kp_trk_data-err_kp_trk_MC)/err_kp_trk_MC;
          err_km_trk=(err_km_trk_data-err_km_trk_MC)/err_km_trk_MC;
          err_pip_trk=(err_pip_trk_data-err_pip_trk_MC)/err_pip_trk_MC;
                
          cout<<"PID error of K+: "<<err_kp_pid<<endl;
          cout<<"PID error of K-: "<<err_km_pid<<endl;
          cout<<"PID error of Pi+: "<<err_pip_pid<<endl;
          cout<<"Tracking error of K+: "<<err_kp_trk<<endl;
          cout<<"Tracking error of K-: "<<err_km_trk<<endl;
          cout<<"Tracking error of Pi+: "<<err_pip_trk<<endl;

} 

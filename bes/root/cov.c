double cov(){

TChain *chain=new TChain("tree");
chain->Add("/afs/ihep.ac.cn/users/l/lincx/scratchfs/6.6.4.p02/DptoPhiPi/job_ana/root/truth_match3.root");
TTree *tree=chain->CopyTree("anglekplus*180/3.14<10&&anglekminus*180/3.14<10&&anglepion*180/3.14<10");
int n = tree->GetEntries();
double ambc=0,smbc=0,vmbc=0,svmbc=0;
double amkk=0,smkk=0,vmkk=0,svmkk=0;
double cov=0;
double rho=-9999;
double mbc_1,M_phi;
tree->SetBranchAddress("mbc_1",&mbc_1);
tree->SetBranchAddress("M_phi",&M_phi);
for (int i=0;i<n;i++){
tree->GetEntry(i);
smbc=smbc+mbc_1;
smkk=smkk+M_phi;
}
ambc=smbc/n;
amkk=smkk/n;
for(int j=0;j<n;j++){
tree->GetEntry(j);
svmbc=svmbc+(mbc_1-ambc)*(mbc_1-ambc);
svmkk=svmkk+(M_phi-amkk)*(M_phi-amkk);
}
vmbc=svmbc/n;
vmkk=svmkk/n;
for(int k=0;k<n;k++){
tree->GetEntry(k);
cov=cov+(mbc_1-ambc)*(M_phi-amkk);
}
cov=cov/n;
rho=cov/(sqrt(vmbc)*sqrt(vmkk));
cout<<ambc<<endl;
cout<<amkk<<endl;
cout<<vmbc<<endl;
cout<<vmkk<<endl;
cout<<cov<<endl;
return rho;
}

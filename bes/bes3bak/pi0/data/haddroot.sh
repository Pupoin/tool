cd 4600/root/
/bin/rm -rvf  4600data.root  
hadd 4600data.root ana*root > o & 
cd -
ln -s 4600/root/4600data.root .

cd 4612/root/
/bin/rm -rvf  4612data.root  
hadd 4612data.root ana*root > o & 
cd -
ln -s 4612/root/4612data.root .

cd 462*/root/
/bin/rm -rvf  4620data.root  
hadd 4620data.root ana*root > o & 
cd -
ln -s 462*/root/4620data.root .

cd 4640/root/
/bin/rm -rvf 4640data.root  
hadd 4640data.root ana*root > o & 
cd -
ln -s 4640/root/4640data.root .

cd 4660/root/
/bin/rm -rvf 4660data.root  
hadd 4660data.root ana*root > o & 
cd -
ln -s 4660/root/4660data.root .

#cd 4680/root/
#/bin/rm -rvf 4680data.root  
#hadd 4680data.root ana*root > o & 
#cd -
#ln -s 4680/root/4680data.root .

cd 4700/root/
/bin/rm -rvf 4700data.root  
hadd 4700data.root ana*root > o & 
cd -
ln -s 4700/root/4700data.root .


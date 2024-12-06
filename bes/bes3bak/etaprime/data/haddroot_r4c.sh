cd 4600/root_r4c/
/bin/rm -rvf  4600data.root  
hadd 4600data.root ana*root > o & 
cd -
ln -s 4600/root_r4c/4600data.root .

cd 4612/root_r4c/
/bin/rm -rvf  4612data.root  
hadd 4612data.root ana*root > o & 
cd -
ln -s 4612/root_r4c/4612data.root .

cd 4620/root_r4c/
/bin/rm -rvf  4620data.root  
hadd 4620data.root ana*root > o & 
cd -
ln -s 4620/root_r4c/4620data.root .

cd 4640/root_r4c/
/bin/rm -rvf 4640data.root  
hadd 4640data.root ana*root > o & 
cd -
ln -s 4640/root_r4c/4640data.root .

cd 4660/root_r4c/
/bin/rm -rvf 4660data.root  
hadd 4660data.root ana*root > o & 
cd -
ln -s 4660/root_r4c/4660data.root .

#cd 4680/root_r4c/
#/bin/rm -rvf 4680data.root  
#hadd 4680data.root ana*root > o & 
#cd -
ln -s 4680/root_r4c/4680data.root .

cd 4700/root_r4c/
/bin/rm -rvf 4700data.root  
hadd 4700data.root ana*root > o & 
cd -
ln -s 4700/root_r4c/4700data.root .


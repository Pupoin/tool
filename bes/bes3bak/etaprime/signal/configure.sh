#mkdir -p 4600/ana
#mkdir -p 4612/ana
#mkdir -p 4620/ana
#mkdir -p 4640/ana
#mkdir -p 4660/ana
#mkdir -p 4680/ana
#mkdir -p 4700/ana
#cp -r /publicfs/ucas/user/yuanchy8/7.0.6/eta/data/template/4626/* 4620/ana/
#cp -r /publicfs/ucas/user/yuanchy8/7.0.6/eta/data/template/4640/* 4640/ana/
#cp -r /publicfs/ucas/user/yuanchy8/7.0.6/eta/data/template/4660/* 4660/ana/
#cp -r /publicfs/ucas/user/yuanchy8/7.0.6/eta/data/template/4680/* 4680/ana/
#cp -r /publicfs/ucas/user/yuanchy8/7.0.6/eta/data/template/4700/* 4700/ana/


cd 4600/ana
a=$(pwd)
/bin/ls ${a}/../dst/*signalrhoA_rec*dst > dst_rhoA 
. splitjobs_dstlist.sh dst_rhoA  20
cd ../../../

cd 4612/ana
a=$(pwd)
/bin/ls ${a}/../dst/*signalrhoA_rec*dst > dst_rhoA 
. splitjobs_dstlist.sh dst_rhoA  20
cd ../../../

cd 4620/ana
a=$(pwd)
/bin/ls ${a}/../dst/*signalrhoA_rec*dst > dst_rhoA 
. splitjobs_dstlist.sh dst_rhoA  20
cd ../../../

cd 4640/ana
a=$(pwd)
/bin/ls ${a}/../dst/*signalrhoA_rec*dst > dst_rhoA 
. splitjobs_dstlist.sh dst_rhoA  20
cd ../../../

cd 4660/ana
a=$(pwd)
/bin/ls ${a}/../dst/*signalrhoA_rec*dst > dst_rhoA 
. splitjobs_dstlist.sh dst_rhoA  20
cd ../../../

cd 4680/ana
a=$(pwd)
/bin/ls ${a}/../dst/*signalrhoA_rec*dst > dst_rhoA 
. splitjobs_dstlist.sh dst_rhoA  20
cd ../../../

cd 4700/ana
a=$(pwd)
/bin/ls ${a}/../dst/*signalrhoA_rec*dst > dst_rhoA 
. splitjobs_dstlist.sh dst_rhoA  20
cd ../../../



#mkdir -p 4600/ana
#mkdir -p 4612/ana
#mkdir -p 4620/ana
#mkdir -p 4640/ana
#mkdir -p 4660/ana
#mkdir -p 4680/ana
#mkdir -p 4700/ana
#cp -r ../data/data-template/4600/*.* 4600/ana/
#cp -r ../data/data-template/4612/*.* 4612/ana/
#cp -r ../data/data-template/4620/*.* 4620/ana/
#cp -r ../data/data-template/4640/*.* 4640/ana/
#cp -r ../data/data-template/4660/*.* 4660/ana/
#cp -r ../data/data-template/4680/*.* 4680/ana/
#cp -r ../data/data-template/4700/*.* 4700/ana/
#

energy=(4600 4612 4620 4640 4660 4680 4700)

# for i_e in ${energy[@]}
# do 
#     cd "${i_e}/joblist/"
#     . subjob > o &
#     cd ../../
# done

cd 4600/ana
a=$(pwd)
/bin/ls ${a}/../dst/*signal3pi*dst > dst_3pi
. splitjobs_dstlist.sh dst_3pi 20
cd ../../../

cd 4612/ana
a=$(pwd)
/bin/ls ${a}/../dst/*signal3pi*dst > dst_3pi
. splitjobs_dstlist.sh dst_3pi 20
cd ../../../

cd 4620/ana
a=$(pwd)
/bin/ls ${a}/../dst/*signal3pi*dst > dst_3pi
. splitjobs_dstlist.sh dst_3pi 20
cd ../../../

cd 4640/ana
a=$(pwd)
/bin/ls ${a}/../dst/*signal3pi*dst > dst_3pi
. splitjobs_dstlist.sh dst_3pi 20
cd ../../../

cd 4660/ana
a=$(pwd)
/bin/ls ${a}/../dst/*signal3pi*dst > dst_3pi
. splitjobs_dstlist.sh dst_3pi 20
cd ../../../

cd 4680/ana
a=$(pwd)
/bin/ls ${a}/../dst/*signal3pi*dst > dst_3pi
. splitjobs_dstlist.sh dst_3pi 20
cd ../../../

cd 4700/ana
a=$(pwd)
/bin/ls ${a}/../dst/*signal3pi*dst > dst_3pi
. splitjobs_dstlist.sh dst_3pi 20
cd ../../../



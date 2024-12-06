#cd 4620
#. splitjobs_dstlist.sh 4620datadst 500
#cd ../../
#
#cd 4640
#. splitjobs_dstlist.sh 4640datadst 500
#cd ../../
#
#cd 4660
#. splitjobs_dstlist.sh 4660datadst 500
#cd ../../
#
#cd 4680
#. splitjobs_dstlist.sh 4680datadst 1500
#cd ../../
#
#cd 4700
#. splitjobs_dstlist.sh 4700datadst 500
#cd ../../
#

cd 4620
findRunWrong 'sigma eta 1c, v10'
cd ../

cd 4640
findRunWrong 'sigma eta 1c, v10'
cd ../

cd 4660
findRunWrong 'sigma eta 1c, v10'
cd ../

cd 4680
findRunWrong 'sigma eta 1c, v10'
cd ../

cd 4700
findRunWrong 'sigma eta 1c, v10'
cd ../

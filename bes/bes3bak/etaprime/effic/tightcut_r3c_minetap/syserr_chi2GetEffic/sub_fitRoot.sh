#!/bin/bash
# seed=`date "+%s"`
# echo $seed
echo "start time is " `date`
#mkdir -p log_fit/
mkdir -p out_fit/

# . /publicfs/ucas/user/yuanchy8/root/root_v6.24.06/bin/thisroot.sh
. /workfs2/bes/yuanchy8/root/root_v6.24.06/bin/thisroot.sh

# export LD_LIBRARY_PATH="/usr/lib64/root/"

# n=0
# while [ $n -le 0 ]
# do


#     seed=$(( $RANDOM + ${2} ))
#     echo "seed is  : $seed"

#     bash fitRoot.sh ${2}


#     let n++    #或者写作n=$(( $n + 1 ))
# done

bash fitRoot.sh ${2}
 
echo "end time is " `date`
# root -l -b -q fit_comb.C 

# hep_sub -g physics -o ./out_fit/ -e ./out_fit/ sub_fitRoot.sh -argu "%{ClusterId} %{ProcId}"  -n 2
# hep_sub -wt short -g physics  -o ./out_fit/ -e ./out_fit/ sub_fitRoot.sh -argu "%{ClusterId} %{ProcId}"  -n 100

# 3427951.
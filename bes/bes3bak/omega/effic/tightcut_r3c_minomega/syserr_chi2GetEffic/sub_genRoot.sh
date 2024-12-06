#!/bin/bash
# seed=`date "+%s"`
# echo $seed
echo "start time is " `date`
# mkdir -p log/
# mkdir -p out/

# . /publicfs/ucas/user/yuanchy8/root/root_v6.24.06/bin/thisroot.sh
# export LD_LIBRARY_PATH="/usr/lib64/root/"

n=0
while [ $n -le 0 ]
do


    seed=$(( $RANDOM + ${2} ))
    # seed=$RANDOM
    echo "seed is  : $seed"

    python genRoot.py  --seed $seed --ProcId ${2}


    let n++    #或者写作n=$(( $n + 1 ))
done

# 49 56 83 84 87 88 93 96 98

 
echo "end time is " `date`
# root -l -b -q fit_comb.C 

# hep_sub -g physics -o ./out/ -e ./out/ sub_genRoot.sh  -n 1
# hep_sub -g physics -o ./out/ -e ./out/ sub_genRoot.sh -argu "%{ClusterId} %{ProcId}"  -n 2
# hep_sub -wt short -g physics  -o ./out/ -e ./out/ sub_genRoot.sh -argu "%{ClusterId} %{ProcId}"  -n 100

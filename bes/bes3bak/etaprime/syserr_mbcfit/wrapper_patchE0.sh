#!/bin/bash
# seed=`date "+%s"`
# echo $seed
echo "start time is " `date`
# mkdir -p log/
# mkdir -p out/

. /publicfs/ucas/user/yuanchy8/root/root_v6.24.08/bin/thisroot.sh
# export LD_LIBRARY_PATH="/usr/lib64/root/"

n=0
while [ $n -le 30 ]
do

    fileName="data_bootstrap_${1}_${2}_${n}.root"
    echo "out file name is $fileName"
    seed=$(( $RANDOM + ${2} ))
    echo "seed is  : $seed"
    c=$(( ${n} % 2 ))
    echo "run file is fit_${c}_patchE0.o"

    # generate the sample
    root -l -b -q "bootstrap.C(${seed}, \"$fileName\")" 
    # root -l -b -q "bootstrap_3pi.C(${seed}, \"3pi_$fileName\")" 
    # fit
    ./fit_${c}_patchE0.o "$fileName" $seed > "log/log.fit_${c}_patchE0-${1}_${2}_${n}"
    /bin/rm ${fileName}




    let n++    #或者写作n=$(( $n + 1 ))
done


 
echo "end time is " `date`
# root -l -b -q fit_comb.C 

# hep_sub -g physics wrapper_patchE0.sh -argu "%{ClusterId} %{ProcId}"  -n 2
# hep_sub -g physics -o ./out/ -e ./out/ wrapper_patchE0.sh -argu "%{ClusterId} %{ProcId}"  -n 40
# hep_sub -wt short -g physics  -o ./out/ -e ./out/ wrapper_patchE0.sh -argu "%{ClusterId} %{ProcId}"  -n 40

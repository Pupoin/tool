#!/bin/bash
# seed=`date "+%s"`
# echo $seed
echo "start time is " `date`
# mkdir -p log/
# mkdir -p out/

. /publicfs/ucas/user/yuanchy8/root/root_v6.24.06/bin/thisroot.sh
# export LD_LIBRARY_PATH="/usr/lib64/root/"

n=0
while [ $n -le 50 ]
do

    fileName="data_bootstrap_${1}_${2}_${n}.root"
    echo "out file name is $fileName"
    seed=$(( $RANDOM + ${2} ))
    echo "seed is  : $seed"
    c=$(( ${n} % 5 ))
    echo "run file is fit_${c}.o"

    # generate the sample
    root -l -b -q "bootstrap.C(${seed}, \"$fileName\")" 
    # fit
    ./fit_${c}.o "$fileName" > "log/log.fit_${c}-${1}_${2}_${n}"


    /bin/rm ${fileName}
    let n++    #或者写作n=$(( $n + 1 ))
done


 
echo "end time is " `date`
# root -l -b -q fit_comb.C 

# hep_sub -g physics wrapper.sh -argu "%{ClusterId} %{ProcId}"  -n 2
# hep_sub -g physics -o ./out/ -e ./out/ wrapper.sh -argu "%{ClusterId} %{ProcId}"  -n 2
# hep_sub -g physics -wt short -o ./out/ -e ./out/ wrapper.sh -argu "%{ClusterId} %{ProcId}"  -n 100

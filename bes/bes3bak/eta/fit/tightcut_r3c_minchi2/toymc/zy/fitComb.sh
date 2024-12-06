#!/bin/bash
echo "start time is " `date`



mkdir -p ./out
# . /publicfs/ucas/user/yuanchy8/root/root_v6.24.08/bin/thisroot.sh
# export LD_LIBRARY_PATH="/usr/lib64/root/"

# g++ fit_toymc_comb.C $(root-config --cflags --libs)   -lRooFitCore -lRooFit -o fit_toymc_comb.o

n=0
# printf "" > log.fit_comb.Br
dir="toymc_C920" && mkdir -p $dir
while [ $n -le 10 ] 
do
    cd ${dir}

    
    # exit
    ../fit_toymc_comb_mc.o "$RANDOM"  > log.fit_${1}_${2}_${n} 
    # ../fit_toymc_comb.o "$n"  > log.fit_${1}_${2}_${n} 

    break
    
    echo 
    cd ../
    let n++    #或者写作n=$(( $n + 1 ))
done


 
echo "end time is " `date`
# root -l -b -q fit_comb.C 

# hep_sub -g physics wrapper.sh -argu "%{ClusterId} %{ProcId}"  -n 2
# hep_sub -g physics -o ./out/ -e ./out/ wrapper.sh -argu "%{ClusterId} %{ProcId}"  -n 100
# hep_sub -wt short -g physics  -o ./out/ -e ./out/ fitComb.sh  -argu  "%{ClusterId} %{ProcId}"  -n 40
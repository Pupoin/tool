#!/bin/bash
waitForJobs()
{
    b=10
    # while [[ x"${a}" != x"[${all}]"*"Done"*"fitInclusive"* ]] && [ "x${a}" != "x" ]
    while [ ${b} -gt 0 ]
    do
        a=`jobs`
        b=`echo $a | grep -o  Running | wc -l `
        printf " $b"  
        sleep 2
    done 
    printf "\n"
}


# seed=`date "+%s"`
# echo $seed
echo "start time is " `date`


energy=(4600 4612 4620 4640 4660 4680 4700)

mkdir -p ./out
# . /publicfs/ucas/user/yuanchy8/root/root_v6.24.08/bin/thisroot.sh
# export LD_LIBRARY_PATH="/usr/lib64/root/"


## ------------------------- zzz   yyyy ------------------------
# g++ fit_toymc_comb.C $(root-config --cflags --libs)   -lRooFitCore -lRooFit -o fit_toymc_comb.o
# g++ fit_toymc_comb_mc.C $(root-config --cflags --libs)   -lRooFitCore -lRooFit -o fit_toymc_comb_mc.o

n=0
# printf "" > log.fit_comb.Br
dir="toymc_C920" && mkdir -p $dir
while [ $n -le 10 ] 
do
    # ref_dir="/publicfs/ucas/user/yuanchy8/7.0.6/omega/effic/tightcut_r3c_minomega/syserr_chi2GetEffic/${dir}"
    # echo "$dir ${ref_dir}"
    # pwd
    # outname="fit_toymc_comb_${1}_${2}_${n}.C"
    # cp fit_toymc_comb.C ${dir}/${outname}
    cd ${dir}
    # rnd=`bc -l <<< "scale=4 ; ${RANDOM}/32767"`
    # end=`bc -l <<< "scale=4 ; $rnd+0.5"`
    # sed -i "s|fit_toymc_comb|fit_toymc_comb_${n}|" ${outname}
    # sed -i "s|double seed=|double seed=$RANDOM|" ${outname}
    # sed -i "s|double times =.*|double times = ${end};|" ${outname}

    
    # exit
    ../fit_toymc_comb_mc.o "$RANDOM"  > log.fit_${1}_${2}_${n} 
    # ../fit_toymc_comb.o "$n"  > log.fit_${1}_${2}_${n} 

    # break
    
    echo 
    cd ../
    let n++    #或者写作n=$(( $n + 1 ))
done


 
echo "end time is " `date`
# root -l -b -q fit_comb.C 

# hep_sub -g physics wrapper.sh -argu "%{ClusterId} %{ProcId}"  -n 2
# hep_sub -g physics -o ./out/ -e ./out/ wrapper.sh -argu "%{ClusterId} %{ProcId}"  -n 100
# hep_sub -wt short -g physics  -o ./out/ -e ./out/ fitComb.sh  -argu  "%{ClusterId} %{ProcId}"  -n 40
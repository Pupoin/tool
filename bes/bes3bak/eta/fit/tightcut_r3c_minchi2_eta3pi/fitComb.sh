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
# . /publicfs/ucas/user/yuanchy8/root/root_v6.24.06/bin/thisroot.sh
# export LD_LIBRARY_PATH="/usr/lib64/root/"

n=0
# printf "" > log.fit_comb.Br
while [ $n -le 100 ]
do
    dir="toymc_C"
    # ref_dir="/publicfs/ucas/user/yuanchy8/7.0.6/omega/effic/tightcut_r3c_minomega/syserr_chi2GetEffic/${dir}"
    # echo "$dir ${ref_dir}"
    # pwd
    outname="fit_toymc_comb_${n}.C"
    cp fit_toymc_comb.C ${dir}/${outname}
    cd ${dir}
    rnd=`bc -l <<< "scale=4 ; ${RANDOM}/32767"`
    end=`bc -l <<< "scale=4 ; $rnd+0.5"`
    sed -i "s|fit_toymc_comb|fit_toymc_comb_${n}|" ${outname}
    sed -i "s|double times =.*|double times = ${end};|" ${outname}
    
    # exit
    root -l -b -q ${outname} > log.fit_${n} 

    # flag=0
    # for i_e in ${energy[@]}
    # do 
    #     effic_sig="$(grep ${i_e} log.effic | cut -d' ' -f6)"
    #     effic_ref="$(grep ${i_e} ${ref_dir}/log.effic | cut -d' ' -f6)"

    #     if [ "x${effic_sig}" == "x" ] ||  [ "x${effic_ref}" == "x" ]
    #     then
    #         flag=1
    #         break
    #     fi

    #     echo "$effic_sig $effic_ref"

    #     sed -i "s|effic_${i_e}_sig|${effic_sig}|" fit_comb_chi2.C 
    #     sed -i "s|effic_${i_e}_ref|${effic_ref}|" fit_comb_chi2.C 

    # done

    # if [ ${flag} -ne 0 ]
    # then 
    #     cd ../../
    #     let n++
    #     echo
    #     continue
    # else
    #     root -l -b -q fit_comb_chi2.C > log.fit_comb 
    # fi


    waitForJobs

    # printf "" > log.fit_comb.Br
    # # if fit wrongly, try again for severial times #    Status : MINIMIZE=0 HESSE=0
    isSucess=`grep -c "Status : MIGRAD=0 HESSE=0" log.fit_${n} `
    if [ "x${isSucess}" == "x1" ]
    then 
        # Bratiov="$(tail log.fit_comb -n 50 | grep "Br:" | cut -d' ' -f2)"
        # Bratioe="$(tail log.fit_comb -n 50 | grep "Br:" | cut -d' ' -f4)"
        Bratio="$(tail log.fit_${n} -n 50 | grep "Br:")"
        echo "---0----  ${isSucess}  $Bratio ------ "  
        echo "---0----  ${isSucess}  $Bratio ------ " >> log.fit_comb.Br
    else
            #   mean_all   -9.9217e-05   -3.3722e-05 +/-  1.79e-04  <none>              
        tries=0
        while [ $tries -le 3 ]
        do 
            meanv="$(grep "    mean_all" log.fit_${n}   | cut -d' ' -f21)"
            meane="$(grep "    mean_all" log.fit_${n}   | cut -d' ' -f24)"
            sigmav="$(grep "    sigma_all" log.fit_${n}  | cut -d' ' -f22)"
            sigmae="$(grep "    sigma_all" log.fit_${n}  | cut -d' ' -f25)"

            # echo " ${isSucess}  $effic $meanv $meane $sigmav $sigmae"
            echo " ${isSucess}    $meanv $meane $sigmav $sigmae"
            sed -i "s|RooRealVar sigma_all(.*$|RooRealVar sigma_all(\"sigma_all\", \"sigma_all\", $sigmav, 0, $sigmav+($sigmae*5));|" ${outname}
            sed -i "s|RooRealVar mean_all(.*$|RooRealVar mean_all(\"mean_all\", \"mean_all\", $meanv, $meanv-($meane*5), $meanv+($meane*5));|" ${outname}
            root -l -b -q ${outname} > log.fit_${n}

            isSucess=`grep -c "Status : MIGRAD=0 HESSE=0" log.fit_${n} `
            if [ "x${isSucess}" == "x1" ]
            then 
                Bratio="$(tail log.fit_${n} -n 50 | grep "Br:")"
                echo "---$(( $tries + 1 ))----  ${isSucess}  $Bratio ------ " 
                echo "---$(( $tries + 1 ))----  ${isSucess}  $Bratio ------ " >> log.fit_comb.Br
                break
            fi 
            let tries++
        done
    fi
    
    echo 
    cd ../
    let n++    #或者写作n=$(( $n + 1 ))
done


echo "end time is " `date`

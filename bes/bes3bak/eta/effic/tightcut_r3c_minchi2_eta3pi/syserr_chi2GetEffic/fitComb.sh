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
while [ $n -le 99 ]
do
    dir="new_root/${1}_${n}"
    ref_dir="/publicfs/ucas/user/yuanchy8/7.0.6/pi0/effic/tightcut_r3c_minchi2/syserr_chi2GetEffic/${dir}"
    echo "$dir ${ref_dir}"
    pwd
    cp fit_comb_chi2.C ${dir}
    cd ${dir}


    flag=0
    for i_e in ${energy[@]}
    do 
        effic_sig="$(grep ${i_e} log.effic | cut -d' ' -f6)"
        effic_ref="$(grep ${i_e} ${ref_dir}/log.effic | cut -d' ' -f6)"

        if [ "x${effic_sig}" == "x" ] ||  [ "x${effic_ref}" == "x" ]
        then
            flag=1
            break
        fi

        echo "$effic_sig $effic_ref"

        sed -i "s|effic_${i_e}_sig|${effic_sig}|" fit_comb_chi2.C 
        sed -i "s|effic_${i_e}_ref|${effic_ref}|" fit_comb_chi2.C 

    done

    if [ ${flag} -ne 0 ]
    then 
        cd ../../
        let n++
        echo
        continue
    else
        root -l -b -q fit_comb_chi2.C > log.fit_comb 
    fi


    # waitForJobs

    printf "" > log.fit_comb.Br
    # # if fit wrongly, try again for severial times #    Status : MINIMIZE=0 HESSE=0
    isSucess=`grep -c "Status : MIGRAD=0 HESSE=0" log.fit_comb `
    if [ "x${isSucess}" == "x1" ]
    then 
        # Bratiov="$(tail log.fit_comb -n 50 | grep "Br:" | cut -d' ' -f2)"
        # Bratioe="$(tail log.fit_comb -n 50 | grep "Br:" | cut -d' ' -f4)"
        Bratio="$(tail log.fit_comb -n 50 | grep "Br:")"
        echo "---0----  ${isSucess}  $Bratio ------ "  
        echo "---0----  ${isSucess}  $Bratio ------ " >> log.fit_comb.Br
    else
        tries=0
        while [ $tries -le 3 ]
        do 
            meanv="$(grep "mean:" log.fit_comb   | cut -d' ' -f2)"
            meane="$(grep "mean:" log.fit_comb   | cut -d' ' -f3)"
            sigmav="$(grep "sigma:" log.fit_comb  | cut -d' ' -f2)"
            sigmae="$(grep "sigma:" log.fit_comb  | cut -d' ' -f3)"

            echo " ${isSucess}  $effic $meanv $meane $sigmav $sigmae"
            sed -i "s|RooRealVar sigma_all.*$|RooRealVar sigma_all(\"sigma_all\", \"sigma_all\", $sigmav, 0, $sigmav+$sigmae*2);|" fit_comb_chi2.C 
            sed -i "s|RooRealVar mean_all.*$|RooRealVar mean_all(\"mean_all\", \"mean_all\", $meanv, $meanv-($meane*2), $meanv+$meane*2);|" fit_comb_chi2.C 
            root -l -b -q fit_comb_chi2.C > log.fit_comb  

            isSucess=`grep -c "Status : MIGRAD=0 HESSE=0" log.fit_comb `
            if [ "x${isSucess}" == "x1" ]
            then 
                Bratio="$(tail log.fit_comb -n 50 | grep "Br:")"
                echo "---$(( $tries + 1 ))  ----  ${isSucess}  $Bratio ------ " 
                echo "---$(( $tries + 1 ))  ----  ${isSucess}  $Bratio ------ " >> log.fit_comb.Br
                break
            fi 
            let tries++
        done
    fi
    
    echo 
    cd ../../
    let n++    #或者写作n=$(( $n + 1 ))
done


echo "end time is " `date`

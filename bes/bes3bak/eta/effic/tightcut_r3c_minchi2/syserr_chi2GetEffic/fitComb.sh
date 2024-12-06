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
mkdir -p "list_fitcomb"
n=0
while [ $n -le 39 ]
do
    sig_dir="/publicfs/ucas/user/yuanchy8/7.0.6/eta/effic/tightcut_r3c_minchi2/syserr_chi2GetEffic/list_effic/"
    sig3pi_dir="/publicfs/ucas/user/yuanchy8/7.0.6/eta/effic/tightcut_r3c_minchi2_eta3pi/syserr_chi2GetEffic/list_effic/"
    ref_dir="/publicfs/ucas/user/yuanchy8/7.0.6/pi0/effic/tightcut_r3c_minchi2/syserr_chi2GetEffic/list_effic"
    echo $sig_dir 
    echo $sig3pi_dir 
    echo ${ref_dir}
    cd "list_fitcomb"


    flag=0
    tmp=`expr $n + 40 \* ${1}`; 
    fitName="fit_comb_chi2_$tmp"
    cp ../fit_comb_chi2.C ${fitName}.C
    sed -i "s|fit_comb_chi2|${fitName}|" ${fitName}.C 

    logeffic="$tmp.effic"; 
    echo $logeffic; 
    for i_e in ${energy[@]}
    do 
        effic_sig="$(grep ${i_e} $sig_dir/$logeffic | cut -d' ' -f6)"
        effic3pi_sig="$(grep ${i_e} $sig3pi_dir/$logeffic | cut -d' ' -f6)"
        effic_ref="$(grep ${i_e} ${ref_dir}/$logeffic | cut -d' ' -f6)"

        if [ "x${effic_sig}" == "x" ] ||  [ "x${effic_ref}" == "x" ]
        then
            flag=1
            break
        fi

        echo "$effic_sig $effic3pi_sig $effic_ref"

        sed -i "s|effic_${i_e}_sig|${effic_sig}|" ${fitName}.C 
        sed -i "s|effic3pi_${i_e}_sig|${effic3pi_sig}|" ${fitName}.C 
        sed -i "s|effic_${i_e}_ref|${effic_ref}|" ${fitName}.C 

    done

    if [ ${flag} -ne 0 ]
    then 
        cd ../../
        let n++
        echo
        continue
    else
        root -l -b -q ${fitName}.C > log.${fitName} 
    fi


    # waitForJobs

    # printf "" > log.fit_comb.Br
    # # if fit wrongly, try again for severial times #    Status : MINIMIZE=0 HESSE=0
    isSucess=`grep -c "Status : MIGRAD=0 HESSE=0" log.${fitName} `
    if [ "x${isSucess}" == "x1" ]
    then 
        # Bratiov="$(tail log.fit_comb -n 50 | grep "Br:" | cut -d' ' -f2)"
        # Bratioe="$(tail log.fit_comb -n 50 | grep "Br:" | cut -d' ' -f4)"
        Bratio="$(tail log.${fitName} -n 50 | grep "Br:")"
        echo "---0----  ${isSucess}  $Bratio ------ "  
        echo "---0----  ${isSucess}  $Bratio ------ " >> log.fit_comb.Br
    else
        tries=0
        while [ $tries -le 3 ]
        do 
            meanv="$(grep "mean:" log.${fitName}   | cut -d' ' -f2)"
            meane="$(grep "mean:" log.${fitName}   | cut -d' ' -f3)"
            sigmav="$(grep "sigma:" log.${fitName}  | cut -d' ' -f2)"
            sigmae="$(grep "sigma:" log.${fitName}  | cut -d' ' -f3)"

            echo " ${isSucess}  $effic $meanv $meane $sigmav $sigmae"
            sed -i "s|RooRealVar sigma_all.*$|RooRealVar sigma_all(\"sigma_all\", \"sigma_all\", $sigmav, 0, $sigmav+$sigmae*2);|" ${fitName}.C 
            sed -i "s|RooRealVar mean_all.*$|RooRealVar mean_all(\"mean_all\", \"mean_all\", $meanv, $meanv-($meane*2), $meanv+$meane*2);|" ${fitName}.C 
            root -l -b -q ${fitName}.C > log.${fitName}  

            isSucess=`grep -c "Status : MIGRAD=0 HESSE=0" log.${fitName} `
            if [ "x${isSucess}" == "x1" ]
            then 
                Bratio="$(tail log.${fitName} -n 50 | grep "Br:")"
                echo "---$(( $tries + 1 ))  ----  ${isSucess}  $Bratio ------ " 
                echo "---$(( $tries + 1 ))  ----  ${isSucess}  $Bratio ------ " >> log.fit_comb.Br
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

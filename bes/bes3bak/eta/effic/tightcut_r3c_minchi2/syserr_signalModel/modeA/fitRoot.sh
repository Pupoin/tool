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
# while [ $n -le 0 ]
# do
    # dir="new_root/${1}_${n}"
    # echo "$dir"
    # cp fitInclusive4*.cc ${dir}
    # cd ${dir}

    for i_e in ${energy[@]}
    do 
        # sed -i "s|chain_data->Add.*$|chain_data->Add(\"${i_e}signal_covGaus.root\");|" fitInclusive${i_e}.cc
        sed -i "s|RooRealVar sigma.*$|RooRealVar sigma(\"sigma\", \"sigma\", 0.0001, 0, 0.001);|" fitInclusive${i_e}.cc
        sed -i "s|RooRealVar mean.*$|RooRealVar mean(\"mean\", \"mean\", 0, -0.001, 0.001);|" fitInclusive${i_e}.cc
        root -l -b -q fitInclusive${i_e}.cc > log.${i_e} &
    done

    waitForJobs

    printf "" > log.effic
    echo '---$(( $tries + 1 ))---- $i_e  ${isSucess}  $effic $trutheffic------ ' > log.effic
    # if fit wrongly, try again for severial times
    for i_e in ${energy[@]}
    do  
        isSucess=`grep -c "Status : MINIMIZE=0 HESSE=0" log.${i_e}`
        isSucess2=`grep -c "covariance matrix quality: Full, accurate covariance matrix" log.${i_e}`
        if [ "x${isSucess}" == "x1"  ]
        then 
            effic="$(grep "fit: efficiency" log.${i_e} | cut -d' ' -f4 )"
            trutheffic="$(grep "truth: efficiency" log.${i_e} | cut -d' ' -f4 )"
            echo "---$(( $tries + 1 ))---- $i_e  ${isSucess}  $effic $trutheffic------ " 
            echo "---$(( $tries + 1 ))---- $i_e  ${isSucess}  $effic  $trutheffic ------ " >> log.effic
            continue
        else
            tries=0
            while [ $tries -le 3 ]
            do 
                meanv="$(grep "mean:" log.${i_e}  | cut -d' ' -f2)"
                meane="$(grep "mean:" log.${i_e}  | cut -d' ' -f3)"
                sigmav="$(grep "sigma:" log.${i_e} | cut -d' ' -f2)"
                sigmae="$(grep "sigma:" log.${i_e} | cut -d' ' -f3)"

                echo "$i_e ${isSucess}  $effic $meanv $meane $sigmav $sigmae"
                sed -i "s|RooRealVar sigma.*$|RooRealVar sigma(\"sigma\", \"sigma\", $sigmav, 0, $sigmav+($sigmae*5));|" fitInclusive${i_e}.cc
                sed -i "s|RooRealVar mean.*$|RooRealVar mean(\"mean\", \"mean\", $meanv, $meanv-($meane*5), $meanv+($meane*5));|" fitInclusive${i_e}.cc                
                root -l -b -q fitInclusive${i_e}.cc > log.${i_e} 

                isSucess=`grep -c "Status : MINIMIZE=0 HESSE=0" log.${i_e}`
                if [ "x${isSucess}" == "x1" ]
                then 
                    effic="$(grep "fit: efficiency" log.${i_e} | cut -d' ' -f4 )"
                    trutheffic="$(grep "truth: efficiency" log.${i_e} | cut -d' ' -f4 )"
                    echo "---$(( $tries + 1 ))---- $i_e  ${isSucess}  $effic $trutheffic------ " 
                    echo "---$(( $tries + 1 ))---- $i_e  ${isSucess}  $effic  $trutheffic ------ " >> log.effic
                    break
                fi 
                let tries++
            done
        fi
    done
    echo 


#     cd ../../
#     let n++    #或者写作n=$(( $n + 1 ))
# done


 
echo "end time is " `date`

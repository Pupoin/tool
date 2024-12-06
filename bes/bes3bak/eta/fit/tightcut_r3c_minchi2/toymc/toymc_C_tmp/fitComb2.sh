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


# energy=(4600 4612 4620 4640 4660 4680 4700)
# energy=(0 1 2 3 4 5 6)
# . /publicfs/ucas/user/yuanchy8/root/root_v6.24.06/bin/thisroot.sh
# export LD_LIBRARY_PATH="/usr/lib64/root/"
# cutcut=(
# '"rndm>=0\&\& rndm<0.025"'
# '"rndm>=0.025\&\& rndm<0.05"'
# )

# n=0
# energy=()
# cutcut=()
# while [ $n -le 100 ]
# do
#     # energy+=(${n})

#     rnd=`bc -l <<< "scale=4 ; ${RANDOM}/32767"` 
#     end=`bc -l <<< "scale=4 ; $rnd+0.05"`
#     cutcut+=("\"rndm>=$rnd \&\& rndm<=$end\"")

#     let n++

# done 
# echo ${energy[@]}
# echo ${cutcut[@]}

n=1001
flagloop=0
let N=n+1000
echo `date` >> log.io_Br
while [ $n -le $N ]
do
    if [ $flagloop -eq 1 ]
    then
        break 
    fi 

    
    filenames=()
    for(( i=0;i<10;i++)) 
    do 
        # if  [ $n -eq 0 ] || [ $n -eq 3 ] || [ $n -eq 4 ] || [ $n -eq 6 ] || [ $n -eq 7 ] || [ $n -eq 8 ] || [ $n -eq 11 ] || [ $n -eq 12 ] || [ $n -eq 16 ] || [ $n -eq 17 ] || [ $n -eq 18 ] || [ $n -eq 19 ] || [ $n -eq 20 ] || [ $n -eq 22 ] || [ $n -eq 24 ] || [ $n -eq 26 ] || [ $n -eq 27 ] || [ $n -eq 28 ] || [ $n -eq 29 ] || [ $n -eq 30 ] || [ $n -eq 31 ] || [ $n -eq 32 ] || [ $n -eq 34 ] || [ $n -eq 35 ] || [ $n -eq 37 ] || [ $n -eq 38 ] || [ $n -eq 1 ] || [ $n -eq 2 ] || [ $n -eq 5 ] || [ $n -eq 9 ] || [ $n -eq 21 ] || [ $n -eq 23 ] || [ $n -eq 33 ] || [ $n -eq 39 ]  
        # then
        #     let n++
        #     continue 
        # fi 
        # echo "tututuu", $n
        if [ $n -ge $N ]
        then 
            flagloop=1;
            break
        fi

        prefix="fit_toymc_comb_${n}"
        rootoutname="fit_toymc_comb_${n}.C"
        cp ../fit_toymc_comb.C ${rootoutname}
        
        # rnd=`bc -l <<< "scale=4 ; ${RANDOM}/32767"`
        # end=`bc -l <<< "scale=4 ; $rnd+0.5"`
        a=${RANDOM}
        let seed=a+n
        sed -i "s|fit_toymc_comb|fit_toymc_comb_${n}|" ${rootoutname}
        sed -i "s|double seed=.*|double seed=${seed};|" ${rootoutname}
        sed "s|io.png|io_${n}.png|g" -i ${rootoutname}
        
        sed -i "s|RooRealVar sigma_all(.*$|RooRealVar sigma_all(\"sigma_all\", \"sigma_all\", 0.0001, 0, 0.001);|" ${rootoutname}
        sed -i "s|RooRealVar mean_all(.*$|RooRealVar mean_all(\"mean_all\", \"mean_all\", 0, -0.001, 0.001);|" ${rootoutname}

        root -l -b -q ${rootoutname} > "log.${prefix}" &
        filenames+=("${prefix}")
        let n++
    done

    waitForJobs


    echo "___________ start check"
    # # if fit wrongly, try again for severial times #    Status : MINIMIZE=0 HESSE=0
    for mName in ${filenames[@]}
    do  
        isSucess0=`grep -c "Status : MIGRAD=0 HESSE=0" log.${mName} `
        isSucess1=`grep -c "covariance matrix quality: Full, accurate covariance matrix" log.${mName} `
        let isSucess=isSucess0+isSucess1
        if [ "x${isSucess}" == "x2" ]
        then 
            # Bratiov="$(tail log.${mName} -n 50 | grep "Br:" | cut -d' ' -f2)"
            # Bratioe="$(tail log.${mName} -n 50 | grep "Br:" | cut -d' ' -f4)"
            Bratio="$(tail log.${mName} -n 50 | grep "Br:")"
            echo "---0----  ${isSucess}  $Bratio ------ $mName"  
            echo "---0----  ${isSucess}  $Bratio ------ $mName" >> log.io_Br
        # else
        #     tries=0
        #     while [ $tries -le 3 ]
        #     do 
        #         meanv="$(grep "mean:" log.${mName}   | cut -d' ' -f2)"
        #         meane="$(grep "mean:" log.${mName}   | cut -d' ' -f3)"
        #         sigmav="$(grep "sigma:" log.${mName}  | cut -d' ' -f2)"
        #         sigmae="$(grep "sigma:" log.${mName}  | cut -d' ' -f3)"

        #         echo "log.${mName} ${isSucess}  $effic $meanv $meane $sigmav $sigmae"
        #         sed -i "s|RooRealVar sigma_all(.*$|RooRealVar sigma_all(\"sigma_all\", \"sigma_all\", $sigmav, 0, $sigmav+$sigmae*2);|" log.${mName}
        #         sed -i "s|RooRealVar mean_all(.*$|RooRealVar mean_all(\"mean_all\", \"mean_all\", $meanv, $meanv-($meane*2), $meanv+$meane*2);|" log.${mName}
        #         root -l -b -q "${mName}.C" > log.${mName}  

        #         isSucess0=`grep -c "Status : MIGRAD=0 HESSE=0" log.${mName} `
        #         isSucess1=`grep -c "covariance matrix quality: Full, accurate covariance matrix" log.${mName} `
        #         let isSucess=isSucess0+isSucess1
        #         if [ "x${isSucess}" == "x2" ]
        #         then 
        #             Bratio="$(tail log.${mName} -n 50 | grep "Br:")"
        #             echo "---$(( $tries + 1 ))  ----  ${isSucess}  $Bratio ------ $mName" 
        #             echo "---$(( $tries + 1 ))  ----  ${isSucess}  $Bratio ------ $mName" >> log.io_Br
        #             break
        #         fi 
        #         let tries++
        #     done
        fi

        let n++
        
    done

    echo "_____________________________________"
    
#     let n++    #或者写作n=$(( $n + 1 ))
done


 
echo "end time is " `date`

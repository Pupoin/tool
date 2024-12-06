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

/bin/rm log.fit_io_*
/bin/rm io_ref_*png
/bin/rm io_sig_*png
/bin/rm io_sig3pi_*png
/bin/rm fit_io_*.C

# energy=(4600 4612 4620 4640 4660 4680 4700)
# energy=(0 1 2 3 4 5 6)
# . /publicfs/ucas/user/yuanchy8/root/root_v6.24.06/bin/thisroot.sh
# export LD_LIBRARY_PATH="/usr/lib64/root/"
cutcut=(
'"rndm>=0\&\& rndm<0.025"'
'"rndm>=0.025\&\& rndm<0.05"'
'"rndm>=0.05\&\& rndm<0.075"'
'"rndm>=0.075\&\& rndm<0.1"'
'"rndm>=0.1\&\& rndm<0.125"'
'"rndm>=0.125\&\& rndm<0.15"'
'"rndm>=0.15\&\& rndm<0.175"'
'"rndm>=0.175\&\& rndm<0.2"'
'"rndm>=0.2\&\& rndm<0.225"'
'"rndm>=0.225\&\& rndm<0.25"'
'"rndm>=0.25\&\& rndm<0.275"'
'"rndm>=0.275\&\& rndm<0.3"'
'"rndm>=0.3\&\& rndm<0.325"'
'"rndm>=0.325\&\& rndm<0.35"'
'"rndm>=0.35\&\& rndm<0.375"'
'"rndm>=0.375\&\& rndm<0.4"'
'"rndm>=0.4\&\& rndm<0.425"'
'"rndm>=0.425\&\& rndm<0.45"'
'"rndm>=0.45\&\& rndm<0.475"'
'"rndm>=0.475\&\& rndm<0.5"'
'"rndm>=0.5\&\& rndm<0.525"'
'"rndm>=0.525\&\& rndm<0.55"'
'"rndm>=0.55\&\& rndm<0.575"'
'"rndm>=0.575\&\& rndm<0.6"'
'"rndm>=0.6\&\& rndm<0.625"'
'"rndm>=0.625\&\& rndm<0.65"'
'"rndm>=0.65\&\& rndm<0.675"'
'"rndm>=0.675\&\& rndm<0.7"'
'"rndm>=0.7\&\& rndm<0.725"'
'"rndm>=0.725\&\& rndm<0.75"'
'"rndm>=0.75\&\& rndm<0.775"'
'"rndm>=0.775\&\& rndm<0.8"'
'"rndm>=0.8\&\& rndm<0.825"'
'"rndm>=0.825\&\& rndm<0.85"'
'"rndm>=0.85\&\& rndm<0.875"'
'"rndm>=0.875\&\& rndm<0.9"'
'"rndm>=0.9\&\& rndm<0.925"'
'"rndm>=0.925\&\& rndm<0.95"'
'"rndm>=0.95\&\& rndm<0.975"'
'"rndm>=0.975\&\& rndm<1"'
)

# n=0
# energy=()
# cutcut=()
# while [ $n -le 100 ]
# do
#     # energy+=(${n})

    # rnd=`bc -l <<< "scale=4 ; ${RANDOM}/32767"` 
    # end=`bc -l <<< "scale=4 ; $rnd+0.05"`
#     cutcut+=("\"rndm>=$rnd \&\& rndm<=$end\"")

#     let n++

# done 
# echo ${energy[@]}
echo ${cutcut[@]}

n=0
flagloop=0
filenames=()
echo `date`>> log.io_Br
while [ $n -le ${#cutcut[@]} ]
do
    if [ $flagloop -eq 1 ]
    then
        break 
    fi 

    filenames=()
    for(( i=0;i<10;i++)) 
    do 
        # if [ $n -eq 1  ] || [ $n -eq 2 ] || [ $n -eq 3 ] || [ $n -eq 4 ] || [ $n -eq 5 ] || [ $n -eq 6 ] || [ $n -eq 8 ] || [ $n -eq 9 ] || [ $n -eq 14 ] || [ $n -eq 17 ] || [ $n -eq 19 ] || [ $n -eq 21 ] || [ $n -eq 22 ] || [ $n -eq 23 ] || [ $n -eq 24 ] || [ $n -eq 26 ] || [ $n -eq 27 ] || [ $n -eq 28 ] || [ $n -eq 31 ] || [ $n -eq 32 ] || [ $n -eq 35 ] || [ $n -eq 36 ] || [ $n -eq 37 ] || [ $n -eq 38 ] 
        # then
        #     let n++
        #     continue 
        # fi 
        echo "tututuu", $n
            # echo  "ck" ${filenames[@]}

        if [ $n -ge ${#cutcut[@]} ]
        then 
            flagloop=1;
            # echo  "c" ${filenames[@]}
            break
        fi

        fileName="fit_io_${n}"
        cp fit_ioBase.C "${fileName}.C"
        sed "s|fit_ioBase|${fileName}|g" -i "${fileName}.C"

        rnd=`bc -l <<< "scale=4 ; ${RANDOM}/32767"` 
        end=`bc -l <<< "scale=4 ; $rnd+0.025"`
        range="rndm>=$rnd\&\& rndm<$end"
        sed "s|auto cutcut_io.*|auto cutcut_io = \"$range\";|g" -i "${fileName}.C"
        # sed "s|auto cutcut_io.*|auto cutcut_io = ${cutcut[${n}]};|g" -i "${fileName}.C"
        sed "s|io_sig.png|io_sig_${n}.png|g" -i "${fileName}.C"
        sed "s|io_sig3pi.png|io_sig3pi_${n}.png|g" -i "${fileName}.C"
        sed "s|io_ref.png|io_ref_${n}.png|g" -i "${fileName}.C"
        
        # sed -i "s|chain_data->Add.*$|chain_data->Add(\"${i_e}signal_covGaus.root\");|" "${fileName}.C"
        sed -i "s|RooRealVar sigma_all.*$|RooRealVar sigma_all(\"sigma_all\", \"sigma_all\", 0.0001, 0, 0.001);|" "${fileName}.C"
        sed -i "s|RooRealVar mean_all.*$|RooRealVar mean_all(\"mean_all\", \"mean_all\", 0, -0.001, 0.001);|" "${fileName}.C"
        # echo ${fileName}
        root -l -b -q "${fileName}.C" > "log.${fileName}" 2>&1  &
        filenames+=("${fileName}")
        # echo ${filenames[@]}
        let n++
    done
    waitForJobs
    # jobs
    # echo "afsd" $n

    
    echo " start check" ${#filenames[@]}
    # if fit wrongly, try again for severial times #    Status : MINIMIZE=0 HESSE=0
    for mName in ${filenames[@]}
    do  
        isSucess0=`grep -c "Status : MIGRAD=0 HESSE=0" log.${mName} `
        isSucess1=`grep -c "covariance matrix quality: Full, accurate covariance matrix" log.${mName} `
        # let isSucess=isSucess0+isSucess1
        let isSucess=isSucess0 
        if [ "x${isSucess}" == "x1" ]
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

        #         echo "log.${mName} ${isSucess}  $meanv $meane $sigmav $sigmae"
        #         sed -i "s|RooRealVar sigma_all.*$|RooRealVar sigma_all(\"sigma_all\", \"sigma_all\", $sigmav, 0, $sigmav+$sigmae*2);|" log.${mName}
        #         sed -i "s|RooRealVar mean_all.*$|RooRealVar mean_all(\"mean_all\", \"mean_all\", $meanv, $meanv-($meane*2), $meanv+$meane*2);|" log.${mName}
        #         root -l -b -q "${mName}.C" > log.${mName} 2>&1 

        #         isSucess0=`grep -c "Status : MIGRAD=0 HESSE=0" log.${mName} `
        #         isSucess1=`grep -c "covariance matrix quality: Full, accurate covariance matrix" log.${mName} `
        #         # let isSucess=isSucess0+isSucess1
        #         let isSucess=isSucess0 
        #         if [ "x${isSucess}" == "x1" ]
        #         then 
        #             Bratio="$(tail log.${mName} -n 50 | grep "Br:")"
        #             echo "---$(( $tries + 1 ))  ----  ${isSucess}  $Bratio ------ " 
        #             echo "---$(( $tries + 1 ))  ----  ${isSucess}  $Bratio ------ " >> log.io_Br
        #             break
        #         fi 
        #         let tries++
        #     done
        fi
    done
    let n++
    # echo "asdadfadsf" $n

#     cd ../../
#     let n++    #或者写作n=$(( $n + 1 ))
done


 
echo "end time is " `date`

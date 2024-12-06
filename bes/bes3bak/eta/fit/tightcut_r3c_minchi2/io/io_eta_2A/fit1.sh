#!/bin/bash


fileName=${1}

root -l -b -q "${fileName}.C" > "log.${fileName}" 

# fileName="fit_io_${n}"
isSucess=`grep -c "Status : MIGRAD=0 HESSE=0" log.${fileName} `
if [ "x${isSucess}" == "x1" ]
then 
    # Bratiov="$(tail log.${fileName} -n 50 | grep "Br:" | cut -d' ' -f2)"
    # Bratioe="$(tail log.${fileName} -n 50 | grep "Br:" | cut -d' ' -f4)"
    Bratio="$(tail log.${fileName} -n 50 | grep "Br:")"
    echo "---0----  ${isSucess}  $Bratio ------ $fileName"  
    # echo "---0----  ${isSucess}  $Bratio ------ $fileName" >> log.io_Br
else
    tries=0
    while [ $tries -le 3 ]
    do 
        meanv="$(grep "    mean_all" log.$fileName   | cut -d' ' -f22)"
        meane="$(grep "    mean_all" log.$fileName   | cut -d' ' -f25)"
        sigmav="$(grep "    sigma_all" log.$fileName  | cut -d' ' -f22)"
        sigmae="$(grep "    sigma_all" log.$fileName  | cut -d' ' -f25)"
        echo "${isSucess}  $meanv $meane, $sigmav $sigmae"

        sed -i "s|RooRealVar sigma_all.*$|RooRealVar sigma_all(\"sigma_all\", \"sigma_all\", $sigmav, 0, $sigmav+$sigmae*2);|" log.${fileName}
        sed -i "s|RooRealVar mean_all.*$|RooRealVar mean_all(\"mean_all\", \"mean_all\", $meanv, $meanv-($meane*2), $meanv+$meane*2);|" log.${fileName}
        root -l -b -q "${fileName}.C" > log.${fileName}  

        isSucess=`grep -c "Status : MIGRAD=0 HESSE=0" log.${fileName} `
        if [ "x${isSucess}" == "x1" ]
        then 
            Bratio="$(tail log.${fileName} -n 50 | grep "Br:")"
            echo "---$(( $tries + 1 ))  ----  ${isSucess}  $Bratio ------ $fileName" 
            # echo "---$(( $tries + 1 ))  ----  ${isSucess}  $Bratio ------ " >> log.io_Br
            break
        fi 
        let tries++
    done
fi
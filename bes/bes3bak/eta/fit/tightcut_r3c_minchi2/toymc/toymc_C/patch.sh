


for f in `ls log.fit_*`
do 
    isSucess=`grep -c "Status : MIGRAD=0 HESSE=0" ${f} `
    isSucess2=`grep -c "covariance matrix quality: Full, accurate covariance matrix" ${f} `


    if [ ${isSucess} -eq  1 ]  && [ ${isSucess2} -eq  1 ]
    then 
        # Bratiov="$(tail log.fit_comb -n 50 | grep "Br:" | cut -d' ' -f2)"
        # Bratioe="$(tail log.fit_comb -n 50 | grep "Br:" | cut -d' ' -f4)"
        Bratio="$(tail ${f} -n 50 | grep "Br:")"
        # echo "---0----  ${isSucess}  $Bratio ------ "  
        echo "---0----  ${isSucess}  $Bratio ------ " >> log.fit_comb.Br.patch
    fi

done 




printf "" > log.fit_comb.Br.patch
for f in `ls log.fit_io_[1-9]*`
do 
    isSucess=`grep -c "Status : MIGRAD=0 HESSE=0" ${f} `
    isSucess2=`grep -c "covariance matrix quality: Full, accurate covariance matrix" ${f} `


    if [ ${isSucess} -eq  1 ]  && [ ${isSucess2} -eq  1 ]
    # if [ ${isSucess} -eq  1 ]   
    then 
        # Bratiov="$(tail log.fit_comb -n 50 | grep "Br:" | cut -d' ' -f2)"
        # Bratioe="$(tail log.fit_comb -n 50 | grep "Br:" | cut -d' ' -f4)"
        Bratio="$(tail ${f} -n 50 | grep "Br:")"
        echo "---0----  ${isSucess}${isSucess2}  $Bratio ------ $f"  
        echo "---0----  ${isSucess}${isSucess2}  $Bratio ------ $f" >> log.fit_comb.Br.patch
    fi

done 


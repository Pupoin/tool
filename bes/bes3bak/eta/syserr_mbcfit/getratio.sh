

dir="./log/"
outfile="log.Bratio"


printf "" > ${outfile}
for i in `ls -v ${dir}/`
do
    f="${dir}/${i}"
    
    isSuccess=`grep -c "Status : MIGRAD=0 HESSE=0" ${f}`
    isSuccess1=`grep -c "covariance matrix quality: Full, accurate covariance matrix" ${f} `

    if [ "x${isSuccess}" == "x1" -a "x${isSuccess1}" == "x1" ]
    then 
        ratio=`grep "Bratio.* <none>" ${f}`
        echo "${f}  ${isSuccess} ${ratio}" >>  ${outfile}
    fi

done

# b=${ratio%%+*}

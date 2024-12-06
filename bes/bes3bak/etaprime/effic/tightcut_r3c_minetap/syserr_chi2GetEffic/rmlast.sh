
i=0
while [ $i -le 99 ]
do
    # a="x"
    echo ${i}
    n=0
    while [ $n -le 99 ]
    do
        dir="new_root/${i}_${n}"
        cd ${dir}
        # echo "$dir"
        # cp fitInclusive4*.cc ${dir}
        a="x"
        if [ -f  log.fit_comb.Br ]
        then 
            a=`ll log.fit_comb.Br |awk '{print  $6 "-" $7}' `
        fi
        
        # echo ${a}

        if [ "$a" != "Oct-26" ]
        then 
            echo $a, `pwd`
            /bin/rm -f log.fit_comb.Br
            # echo "aa"
        fi
        cd ../../
        let n++
    done
    let i++
done
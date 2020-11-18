
ht=(40to70 70to100 100to200 200to400 400to600 600to800 800to1200 1200to2500 2500toInf inclusive)
factor=""

for I in ${ht[*]}
do 
    echo 'python3 getx.py ' ${I}
    a=$(python3 getx.py ${I})
    #a="afdijfosdfijfas err: fadsi afd +- aisfdj pb"
    b=${a#*err:}
    c=${b%+-*}

    printf "$a\n"
    #echo $b
    #echo $c

    factor="${factor},${c}"
    #echo ${factor}

    echo 
done

echo 
echo "  double factor[${#ht[@]}] = {${factor#, }};" 
echo 

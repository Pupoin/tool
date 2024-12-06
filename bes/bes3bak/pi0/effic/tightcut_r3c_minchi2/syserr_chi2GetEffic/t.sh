

b=10
a="[14]   DoneDone     Done    Running  Running "
b=`echo $a | grep -o  Running | wc -l `
    echo "-----------  $a ----- $b"

if [ ${b} -ge 1 ]
then

    echo "aaa"
fi


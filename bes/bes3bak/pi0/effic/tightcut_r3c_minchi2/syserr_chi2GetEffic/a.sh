

i=0
j=99

while [ $i -le 99 ]
do
    # while [ $j -le 99 ]
    # do
        cd "new_root/${i}_${j}"
        cp ../../all_covGaus.sh .
        
        bash all_covGaus.sh
        cd ../../
        # let j++
    # done 
    let i++
done 

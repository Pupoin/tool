

energy=(4600 4612 4620 4640 4660 4680 4700)
#energy=(4600 4612 4620 4640 4660 4680 )

for i_e in ${energy[@]}
do 
    cd "${i_e}/joblist/"
    . subjob > o &
    cd ../../
done


# cd 4740/joblist/
# . subjob > o &
# cd ../../

# cd 4750/joblist/
# . subjob > o &
# cd ../../

# cd 4780/joblist/
# . subjob > o &
# cd ../../

# cd 4840/joblist/
# . subjob > o &
# cd ../../

# cd 4914/joblist/
# . subjob > o &
# cd ../../

# cd 4946/joblist/
# . subjob > o &
# cd ../../


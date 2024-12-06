
energy=(4600 4612 4620 4640 4660 4680 4700)
# energy=( 4612 )

for i_e in ${energy[@]}
do 
    cd "${i_e}/"
    bash gensimrec.sh  "pi0${i_e}signal" 100 &
    cd ../ 
done

# grep decay */sim*/*head*
# ll */decay*
# ll */joblist/*99.txt
# ll */joblist/o

# ll */sim*/*head*


# grep "Lambda_c-.*PHOTOS PHSP"  decay.dec 
# ll decay.dec


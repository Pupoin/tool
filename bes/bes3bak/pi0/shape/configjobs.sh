
energy=(4600 4612 4620 4640 4660 4680 4700)
# energy=( 4612 )

for i_e in ${energy[@]}
do 
    cd "${i_e}/"
    bash gensimrec.sh  "pi0${i_e}shape" 100 &
    cd ../ 
done







# cd 4740/
# . gensimrec.sh  4740signalomega 100
# cd ../../

# cd 4750/
# . gensimrec.sh  4750signalomega 100
# cd ../../

# cd 4780/
# . gensimrec.sh  4780signalomega 100
# cd ../../

# cd 4840/
# . gensimrec.sh  4840signalomega 100
# cd ../../

# cd 4914/
# . gensimrec.sh  4914signalomega 100
# cd ../../

# cd 4946/
# . gensimrec.sh  4946signalomega 100
# cd ../../


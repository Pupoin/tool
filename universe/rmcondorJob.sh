#!/bin/bash  
# remove condor jobs

read -p "Enter starting number: " sstart  
read -p "Enter ending number: " eend 


#sstart=5000
#eend=9999
while [[ $sstart -le $eend ]];  
do  
    echo 'condor_rm 12976799.'$sstart
    condor_rm "12976799.$sstart"
    ((sstart++))  
done  



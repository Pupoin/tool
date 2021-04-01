#!/bin/bash

#array length is 2 for two version comparison
xs=(0.03294 1.308e-02 8.537e-03)
histo_name=("4la_NLO.root" "zlla_NLO.root" "zlla_LO.root")
names=("4la_NLO" "zlla_NLO" "zlla_LO")

#array length is larger than 2 for inclusive vs stitched, e.g.:
# xs=(6383. 5156. 913. 348.6)
# histo_name=("DYm50_012j_nlo_ewparams_cp5.root" "DYm50_0j_nlo_ewparams_cp5.root" "DYm50_1j_nlo_ewparams_cp5.root" "DYm50_2j_nlo_ewparams_cp5.root")
# names=("MGinc" "MG0j" "MG1j" "MG2j")

inDIR="./"
outDIR="./pic"
mkdir -p $outDIR

xs_=""
histo_name_=""
names_=""
for var in ${xs[@]};do
  xs_="$xs_ $var"
done
xs_="--xs ${xs_}"
for var1 in ${histo_name[@]};do
  histo_name_="$histo_name_ $var1"
done
histo_name_="--histo ${histo_name_}"
for var2 in ${names[@]};do
  names_="$names_ $var2"
done
names_="--name ${names_}"

while getopts "m:" opt;do
  case "$opt" in
    m) MODE=$OPTARG
	;;
  esac
done

if [ -z "MODE" ]; then
  #TWOVERSION means comparison between two versions, e.g., MG265 inclusive vs MG273 inclusive
  #INCVSSTIT means comparison between inclusive vs summed stitched
  echo "plot.sh -m <TWOVERSION/INCVSSTIT>" 
fi

case $MODE in
  TWOVERSION)
    echo "two version comparison mode--->>>"
    if [ ${#xs[*]} -ne 2 ] || [ ${#histo_name[*]} -ne 2 ]; then
	echo "ERROR! Only two cross section value and two histograms should be provided!!"
	break
    fi
#    python plot.py --xs ${xs[0]} ${xs[1]} --inputdir $inDIR --histo ${histo_name[0]} ${histo_name[1]} --name ${names[0]} ${names[1]}
    python plot.py ${xs_}  --inputdir $inDIR ${histo_name_} ${names_} --outputdir $outDIR
	;;

  INCVSSTIT)
    echo "inclusive vs stitched mode--->>>"
    if [ ${#xs[*]} -lt 3 ] || [ ${#histo_name[*]} -lt 3 ]; then
	echo "ERROR! Only two cross section value and two histograms is provided, need mode!!!"
	break
    fi
    python plot.py ${xs_} --inputdir $inDIR ${histo_name_} ${names_} --outputdir $outDIR
	;;
esac

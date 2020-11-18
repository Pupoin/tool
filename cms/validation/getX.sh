
# /bin/bash
# calculate the After matching cross section from .err file
# root files need in the folder ./root, log files need in th floder ./log
# $1 is 70to100, or 100to200, or ... or inclusive
# more information in file ${1}.xsection
# run such as:  . getX.sh inclusive

sumcross=0
sumerror=0
nRunOk=0
nRunerror=0

echo -e "rootFile \t logFile \t cross+-error \t cross2+-error2" | column -t > ${1}.xsection
rootFolderName="roottmp"
logFolderName="log"

for i in `ls -v ./${rootFolderName}/${1}_*.root`
do 
  doterrfile_tmp=${i/_/.err_}
  doterrfile_tmp2=${doterrfile_tmp/.root/}
  doterrfile_tmp3=${doterrfile_tmp2/${rootFolderName}/${logFolderName}}
  doterrfile_head=${doterrfile_tmp3%_*}
  doterrfile_tail=${doterrfile_tmp3##*_}
  doterrfile=${doterrfile_head}-${doterrfile_tail}
  string=$(grep -sin "After matching: total cross section = " ${doterrfile})

  allcross=${string#*=}
  # echo ${allcross}

  cross=${allcross%+-*}
  # echo  ${cross}
  cross2=`printf "%f" ${cross}`
  # echo ${cross2}

  errorpb=${allcross#*+-}
  error=${errorpb%pb*}
  error2=`printf "%f" ${error}`

  sumcross=$(awk 'BEGIN{printf "%f\n",('$cross2'+'${sumcross}')}')
  sumerror=$(awk 'BEGIN{printf "%f\n",('$error2'+'${sumerror}')}')

  if [ "x${cross}" != "x" ]
  then 
    let "nRunOk=${nRunOk}+1"
    echo -e  "${i}\t${doterrfile}\t${cross}+-${error}\t${cross2}+-${error2}" >> ${1}.xsection
  else
    let "nRunerror=${nRunerror}+1"
    echo -e  "wrong ${i}\t${doterrfile}\t${cross}+-${error}\t${cross2}+-${error2}" >> ${1}.xsection

    mkdir -p ./${rootFolderName}/wrong
    mkdir -p ./${logFolderName}/wrong
    mv ${doterrfile} ./${logFolderName}/wrong/
    mv ${i} ./${rootFolderName}/wrong/
  fi
done

echo >> ${1}.xsection
echo >> ${1}.xsection

unitcross=0
uniterror=0

unitcross=$(awk 'BEGIN{printf "%f\n",('$sumcross'/'$nRunOk')}')
uniterror=$(awk 'BEGIN{printf "%f\n",('$sumerror'/'$nRunOk')}')

# save to the file
echo "nRunOk number: "${nRunOk}  >> ${1}.xsection
echo "nRunerror number: "${nRunerror}  >> ${1}.xsection
echo -e "sumcross  +- sumerror:   ${sumcross}  +- ${sumerror}"  | column -t >> ${1}.xsection
echo -e "unitcross +- uniterror:  ${unitcross} +- ${uniterror}" | column -t >> ${1}.xsection

echo "out file in ${1}.xsection"
echo "rootFloler: ${rootFolderName}"
echo "logFloler: ${logFolderName}"
echo
echo "nRunOk number: "${nRunOk}
echo "nRunerror number: "${nRunerror}
echo -e "sumcross  +- sumerror:   ${sumcross}  +- ${sumerror}"  | column -t
echo -e "unitcross +- uniterror:  ${unitcross} +- ${uniterror}" | column -t

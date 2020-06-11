# /bin/bash
inputRootFolderName="root"
outputRootFolderName="outputRoot"

printf "" > paralleljobs

for i in `ls -v ../${inputRootFolderName}/inclusive_12863937*.root`
do 
  echo "bash run22.sh ${i}" >> paralleljobs

done

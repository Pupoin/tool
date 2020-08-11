# /bin/bash
inputRootPath="../root"
outputRootPath="./outputRoot"

mkdir -p ${outputRootPath}

printf "" > paralleljobs

for i in `ls -v ${inputRootPath}/inclusive_12894116*.root`
do
  outputRootFile_tmp=${i##*/}   # inclusive_12863937*.root
  outputRootFile=${outputRootFile_tmp/.root/_ana.root}

  echo "bash run22.sh ${i} ${outputRootPath}/${outputRootFile}" >> paralleljobs

done

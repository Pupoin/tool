# /bin/bash

inputRootFile=${1##*/}         # inclusive_12863937*.root

# echo ${inputRootFile}
# echo ${1}
# echo ${2}

anaName=ana_${inputRootFile}.py

wget --no-check-certificate "http://stash.osgconnect.net/+zhyuan/anaCondor/ana.py" -O ${anaName}

sed -i "s#inputRootFile.root#${1}#" -i ${anaName}
sed -i "s#outputRootFile.root#${2}#" -i ${anaName}

echo start ${anaName}
python ${anaName}
#echo ${outputRootFile}
echo end ${1} ${2} success
/bin/rm -rf ${anaName}

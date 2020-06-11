inputRootFolderName="root"
outputRootFolderName="outputRoot"

inputRootFile=${1##*/}
outputRootFile_tmp=${1##*/}
outputRootFile=${outputRootFile_tmp/.root/_ana.root}

wget --no-check-certificate "http://stash.osgconnect.net/+zhyuan/anaCondor/ana.py" -O ana_${inputRootFile}.py 

sed -i "s#inputRootFile.root#../${inputRootFolderName}/${inputRootFile}#" -i ana_${inputRootFile}.py
sed -i "s#outputRootFile.root#./${outputRootFolderName}/${outputRootFile}#" -i ana_${inputRootFile}.py

echo start ana_${inputRootFile}
python ana_${inputRootFile}.py

echo end ../${inputRootFolderName}/${inputRootFile} ./${outputRootFolderName}/${outputRootFile} success
# /bin/rm -rf ana_${inputRootFile}.py

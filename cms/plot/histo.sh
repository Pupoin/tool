#!/bin/bash

while getopts "q:" opt; do
 case "$opt" in
   q) WHAT=$OPTARG
	;;
 esac
done

if [ -z "$WHAT" ]; then
 echo "histo.sh -q <LOCAL/SUBMIT/PARALLEL>";
fi


name="histo"
inDIR="/lo/"
suffix="v265"   # version of MG

case $WHAT in

 LOCAL)
   PWD=`pwd`
   outDIR=${PWD}${inDIR}"Output"
   mkdir -p $outDIR
   
   for f in ${PWD}${inDIR}*.root;do
    tmp=${f##*/}
    outname=${name}_${tmp%.*}_$suffix
    python histo.py -i $f -o ${outname}
    mv $outname".root" $outDIR
   done
   ;;

 PARALLEL)
   PWD=`pwd`
   echo "prepare parallel file--->>>"

   subDIR=${PWD}${inDIR}"Parallel"
   mkdir -p $subDIR
   outDIR=${PWD}${inDIR}"Output"
   mkdir -p $outDIR
   paralleljobs="jobs.parallel"
   if [ -f "$paralleljobs" ]; then
      echo "$paralleljobs already exist, remove it"
      /bin/rm $paralleljobs
   fi

   for f in $(/bin/ls -v ${PWD}${inDIR} | grep .root);do
      temp=$f
      temp1=${temp%.root}
      read -r -a prename <<< "$temp1"
      exefile=$subDIR\/$prename.sh
      echo "#!/bin/bash">$exefile
      outname="$outDIR/${name}_${prename}_${suffix}"
      echo "python ${PWD}/histo.py -i ${PWD}${inDIR}$f -o ${outname}">>$exefile
      echo "sh ${exefile}" >>  $paralleljobs
   done
   nohup parallel -j 15 < ${paralleljobs} --joblog ./log.parallel &
   ;;

 SUBMIT)
   PWD=`pwd`
   queue="tomorrow"
   echo "prepare condor file--->>>"
   OpSysAndVer=`cat /etc/redhat-release`
   if [[ "$OpSysAndVer" == *"SLC"* ]]; then
     OpSysAndVer="SLCern6"
   else
     OpSysAndVer="CentOS7"
   fi

   subDIR=${PWD}${inDIR}"CondorSub"
   mkdir -p $subDIR
   outDIR=${PWD}${inDIR}"Output"
   mkdir -p $outDIR
   subfile=condor.sub
   if [ -f "$subfile" ]; then
      echo "$subfile already exist, remove it"
      rm $subfile
   fi
   echo "executable = $subDIR/\$(cfgFile).sh">$subfile
   echo "universe = vanilla" >>$subfile
   echo "output = $subDIR/output.out">>$subfile
   echo "error = $subDIR/output.err">>$subfile
   echo "log = $subDIR/output.log">>$subfile
   echo "requirements = (OpSysAndVer =?= \""$OpSysAndVer"\")">>$subfile
   echo "+JobFlavour = "$queue"">>$subfile
  
   for f in $(/bin/ls -v ${PWD}${inDIR} | grep .root);do
      temp=$f
      temp1=${temp%.root}
      read -r -a prename <<< "$temp1"
      echo "cfgFile=${prename}">>$subfile
      echo "queue 1">>$subfile
      exefile=$subDIR\/$prename.sh
      echo "#!/bin/bash">$exefile
      echo "WORKDIR=\`pwd\`">>$exefile
      echo "echo \"Working directory is \$WORKDIR\"">>$exefile
      echo "python ${PWD}/histo.py -i ${PWD}${inDIR}$f -o ${name}_${prename}_$suffix">>$exefile
      echo "mv -v \$WORKDIR/${name}_${prename}_$suffix.root $outDIR">>$exefile
   done
   condor_submit $subfile
   ;;
esac

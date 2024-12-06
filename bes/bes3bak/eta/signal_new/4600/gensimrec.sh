#!/bin/bash
#
#set +x
date=`date +%N`
test $# -lt 2 && echo $0 '<prefix_jobname> <job_num>' && exit 0
name=$1
num=$2
test $num -lt 1 && echo $2 less than 1 && exit 0
test -f sim_ini/run_template_head.txt || exit 0 
test -f sim_ini/run_template_tail.txt || exit 0 
test -f rec_ini/run_template_head.txt || exit 0 
test -f rec_ini/run_template_tail.txt || exit 0 

ANA_DIR=`pwd`
echo Current dir: $ANA_DIR
DST_DIR=${ANA_DIR}/dst
RTRAW_DIR=${ANA_DIR}/rtraw
#RTRAW_DIR=` echo ${RTRAW_DIR} |sed 's/\/$//'`
JOB_DIR=${ANA_DIR}/joblist

mkdir -p  ${RTRAW_DIR} ${JOB_DIR} ${DST_DIR} 
cd  ${JOB_DIR}
rm -f *txt* list*
i_num=0
while [ $i_num -lt $num ]
do 
  fake_num=`printf "%04d\n" ${i_num}`
  SIM_JOB_FILE=${name}_sim_${fake_num}.txt
  echo $SIM_JOB_FILE
  cat ${ANA_DIR}/sim_ini/run_template_head.txt>${SIM_JOB_FILE}
	cat ${ANA_DIR}/sim_ini/run_template_tail.txt | sed "s#NAME#${RTRAW_DIR}/${name}_sim_${fake_num}#g" | sed "s#LIPR#$date#g" >> ${SIM_JOB_FILE}
	echo boss.condor ${SIM_JOB_FILE}>>list_sim

  REC_JOB_FILE=${name}_rec_${fake_num}.txt
  echo $REC_JOB_FILE
  cat ${ANA_DIR}/rec_ini/run_template_head.txt>${REC_JOB_FILE}
	cat ${ANA_DIR}/rec_ini/run_template_tail.txt |sed "s#NAMEA#${RTRAW_DIR}/${name}_sim_${fake_num}#g"| sed "s#NAMEB#${DST_DIR}/${name}_rec_${fake_num}#g" | sed "s#LIPR#$date#g" >> ${REC_JOB_FILE}
	echo boss.condor ${REC_JOB_FILE}>>list_rec

  i_num=`expr ${i_num} + 1`
  date=`expr ${date} + 1`

done

JobExe=${name}_sim_rec.condor
CmdJobId="grep GlobalJobId \$_CONDOR_JOB_AD | cut -d'#' -f2"
CmdJobSlot="grep RemoteHost \$_CONDOR_JOB_AD"

echo "#!/bin/tcsh -f" > ${JobExe}
echo "cd ${JOB_DIR}" >> ${JobExe}

echo "set procid=\$1" >> ${JobExe} 
echo "set sub_name_number=\`expr \$procid\`" >> ${JobExe}
echo "set sub_name=\`printf \"%04d\n\" \$sub_name_number\`" >> ${JobExe}

echo "echo -n \"Job \`${CmdJobId}\` on \" > ${name}_sim_\${sub_name}.txt.bosslog" >> ${JobExe}
echo "${CmdJobSlot} >> ${name}_sim_\${sub_name}.txt.bosslog" >> ${JobExe}
echo "((time boss.exe ${name}_sim_\${sub_name}.txt) >> ${name}_sim_\${sub_name}.txt.bosslog) >& ${name}_sim_\${sub_name}.txt.bosserr" >> ${JobExe}
echo "sleep 3" >> ${JobExe}

echo "echo -n \"Job ${CmdJobId} on \" > ${name}_rec_\${sub_name}.txt.bosslog" >> ${JobExe}
echo "${CmdJobSlot} >> ${name}_rec_\${sub_name}.txt.bosslog" >> ${JobExe}
echo "((time boss.exe ${name}_rec_\${sub_name}.txt) >> ${name}_rec_\${sub_name}.txt.bosslog) >& ${name}_rec_\${sub_name}.txt.bosserr" >> ${JobExe}
echo "sleep 3" >> ${JobExe}
#echo "rm -f ${JobExe}" >> ${JobExe}

chmod u+x ${JobExe}

echo "hep_sub -g physics -o /dev/null -e /dev/null ${JobExe} -argu \"%{ProcId}\" -n $num" > subjob

echo !!!!!DONE!!!!! 

#!/bin/bash
#
#set +x
date=`date +%s`
test $# -lt 1 && echo $0 '<job_num>' && exit 0
num=`expr $1 `
test $num -lt 1 && echo $num less than 1 && exit 0
test -f run_template_head.txt || exit 0 
test -f run_template_tail.txt || exit 0 

ANA_DIR=`pwd`
echo Current dir: $ANA_DIR
DEST_DIR=${ANA_DIR}/rtraw
JOB_DIR=${ANA_DIR}/joblist

mkdir -p  ${DEST_DIR} ${JOB_DIR}
cd  ${JOB_DIR}
rm -f sim_* list

offset=1000
i_num=$offset
while [ `expr $i_num - $offset` -lt $num ]
do 
  JOB_FILE=sim_${i_num}.txt
  echo $JOB_FILE
  cat ${ANA_DIR}/run_template_head.txt>${JOB_FILE}
        # seed=$i_num
        seed=`expr $date`
	cat ${ANA_DIR}/run_template_tail.txt | sed "s#NAME#${DEST_DIR}/sim_${i_num}#g" | sed "s#LIPR#$seed#g" >> ${JOB_FILE}
	echo boss.condor ${JOB_FILE}>>list
  i_num=`expr ${i_num} + 1`
  date=`expr ${date} + 1`
done
chmod +x list
echo !!!!!DONE!!!!! 

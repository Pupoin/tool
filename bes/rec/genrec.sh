#!/bin/bash
#
#set +x
date=`date +%s`
test $# -lt 2 && echo $0 '<rtraw_path> <job_num>' && exit 0
#DATA_DIR=$1
DATA_DIR=` echo $1 |sed 's/\/$//'`
#echo $DATA_DIR
test -d ${DATA_DIR} || exit 0

offset=1000
num=`expr $2 + $offset`
test $num -lt `expr $offset + 1` && echo $num less than 1 && exit 0
test -f run_template_head.txt || exit 0 
test -f run_template_tail.txt || exit 0 

ANA_DIR=`pwd`
echo Current dir: $ANA_DIR
DEST_DIR=${ANA_DIR}/dst
JOB_DIR=${ANA_DIR}/joblist

mkdir -p  ${DEST_DIR} ${JOB_DIR}
cd  ${JOB_DIR}
rm -f rec_* list
i_num=$offset
while [ $i_num -lt $num ]
do 
  JOB_FILE=rec_${i_num}.txt
  echo $JOB_FILE
  cat ${ANA_DIR}/run_template_head.txt>${JOB_FILE}
	cat ${ANA_DIR}/run_template_tail.txt |sed "s#NAMEA#${DATA_DIR}/sim_${i_num}#g"| sed "s#NAMEB#${DEST_DIR}/rec_${i_num}#g" | sed "s#LIPR#$date#g" >> ${JOB_FILE}
	#bossq -pbs ${JOB_FILE}
	echo boss.condor ${JOB_FILE}>>list
  i_num=`expr ${i_num} + 1`
done
chmod +x list
echo !!!!!DONE!!!!! 

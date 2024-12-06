#!/bin/bash
#
#set +x
test $# -lt 2 && echo $0 '<list_of_dst_files> <job_num> '&& exit 0
list_files=$1
num=$2
name=ana

test $num -lt 1 && echo $num less than 1 && exit 0
test -f $list_files || exit 0 
test -f run_mc_template_head.txt || exit 0 
test -f run_mc_template_tail.txt || exit 0 

ANA_DIR=`pwd`
echo Current dir: $ANA_DIR
DEST_DIR=${ANA_DIR}/root_zhou2me
WRK_DIR=${ANA_DIR}/joblist_zhou2me
echo $DEST_DIR 
echo $WRK_DIR

mkdir -p  ${DEST_DIR} ${WRK_DIR}
#cp -f ${ANA_DIR}/src/* ${WRK_DIR}/
cp ${list_files} ${WRK_DIR}/TMP.list
cd  ${WRK_DIR}
rm -f ${name}_* list
line_num=`wc -l TMP.list | cut -d" " -f1`
test ${line_num} -eq 0 && exit 0 
step=`expr $line_num /  $num `
test `expr $line_num % $num` -gt 0 && step=`expr $step + 1`
echo total: $line_num lines in $num jobs, step is $step line

offset=1000
num=`expr $num + $offset `
i_num=$offset
while [ $i_num -lt $num ]
do 
  JOB_FILE=${name}_${i_num}.txt
	Line=`expr ${i_num} - $offset`
  line_up=`expr ${Line} \* ${step} + 1`
  line_end=`expr ${line_up} + ${step} - 1`
  test $line_up -gt $line_num && break
  test $line_end -gt $line_num  && line_end=$line_num
  echo ${i_num} of $num : lines from $line_up to $line_end
  length=`expr ${line_end} - ${line_up} + 1`
  cat TMP.list | head -${line_end} | tail -${length} > TMP.list${i_num}
  cat TMP.list${i_num} | awk '{print ",\"" $1 "\""}' | sed '1 s/,//' > TMP.list${i_num}.2
  cat ${ANA_DIR}/run_mc_template_head.txt TMP.list${i_num}.2 ${ANA_DIR}/run_mc_template_tail.txt | sed "s#NAME#${DEST_DIR}/${name}_${i_num}#g" > ${JOB_FILE}
	#bossoffline -q ${JOB_FILE}
	#echo boss -q ${JOB_FILE}>>list
	echo boss.condor ${JOB_FILE}>>list
  i_num=`expr ${i_num} + 1`
done
chmod +x list
/bin/rm -f TMP*

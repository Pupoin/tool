#!/bin/bash
#
#set +x

# given the path
# eg: /scratchfs/bes/yuanchy8/7.0.3/Lambda_c_2_sigmap_eta-etaPrime/signgl_tag_mc/ana/dst/

dir=$1
if [ x"${dir}" == x"" ]
then
    unset dir
    dir=$(cd $(dirname $(readlink -f "${BASH_SOURCE[0]}")) && pwd)/../rec/dst

fi

list_dir="$( cd -P $dir && pwd )"
echo -e "path is : ${list_dir}"

ls -v $list_dir/*.dst > list_ini

num=`find ${list_dir} -name "*.dst" | wc -l`
echo -e "dst num is: $num"

echo -e "\033[01;31mTo be continue ？[y/n] \033[0m" 
read confirm  
if [ $confirm == 'n' ] || [ $confirm == 'N' ];then
    exit 1
fi
./splitjobs_dstlist.sh list_ini ${num}

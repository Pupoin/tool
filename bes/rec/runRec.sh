#!/bin/bash
#
#set +x

# given the path
# eg: /scratchfs/bes/yuanchy8/7.0.3/Lambda_c_2_sigmap_eta-etaPrime/signgl_tag_mc/ana/dst/

dir=$1
if [ x"${dir}" == x"" ]
then
    unset dir
    dir=$(cd $(dirname $(readlink -f "${BASH_SOURCE[0]}")) && pwd)/../sim/rtraw
fi

list_dir="$( cd -P $dir && pwd )"
echo -e "path is : ${list_dir}"

num=`find ${list_dir} -name "*.rtraw" | wc -l`
echo -e "rtraw num is: $num"

echo -e "\033[01;31mTo be continue ？[y/n] \033[0m" 
read confirm  
if [ $confirm == 'y' ] || [ $confirm == 'Y' ];then
    ./genrec.sh $list_dir ${num}
    exit 0
else
    echo have canceled it!
fi


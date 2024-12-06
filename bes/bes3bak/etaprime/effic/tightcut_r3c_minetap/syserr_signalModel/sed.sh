file=("fitInclusive4600.cc" "fitInclusive4612.cc" "fitInclusive4620.cc" "fitInclusive4640.cc" "fitInclusive4660.cc" "fitInclusive4680.cc" "fitInclusive4700.cc")

for i_e in ${file[@]}
do 
    if [ -d "$i_e/ana" ]; then
        cd $i_e/ana/
    else 
        cd $i_e/
    fi
    echo "______________  $i_e ______________"
    a=`tail $dir/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong $dir

    if [ -d "../ana" ]; then
        cd ../../
    else 
        cd ../
    fi
done
mycheckrun3()
{
	if [ x"${1}" == x"" ]
	then 
		echo "error ~! please run like: checkrun \"******\" "
		return 1
	fi
    mtxt=${1}
    
    cd 462*/ana
    echo "462*______________________________________________________________"
    a=`tail joblist/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong
    cd ../../
    
    cd 4640/ana
    echo "4640____________________________________________________________"
    a=`tail joblist/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong
    cd ../../
    
    cd 4660/ana
    echo "4660____________________________________________________________"
    a=`tail joblist/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong
    cd ../../
    
    cd 4680/ana 
    echo "4680____________________________________________________________"
    a=`tail joblist/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong
    cd ../../
    
    cd 4700/ana 
    echo "4700____________________________________________________________"
    a=`tail joblist/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong
    cd ../../
} 


mycheckrun2()
{
	if [ x"${1}" == x"" ]
	then 
		echo "error ~! please run like: checkrun \"******\" "
		return 1
	fi
    mtxt=${1}
    
    cd 462*/
    echo "462*______________________________________________________________"
    a=`tail joblist/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong
    cd ../
    
    cd 4640/
    echo "4640____________________________________________________________"
    a=`tail joblist/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong
    cd ../
    
    cd 4660/
    echo "4660____________________________________________________________"
    a=`tail joblist/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong
    cd ../
    
    cd 4680 
    echo "4680____________________________________________________________"
    a=`tail joblist/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong
    cd ../
    
    cd 4700 
    echo "4700____________________________________________________________"
    a=`tail joblist/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong
    cd ../
} 


mycheckrun()
{
	if [ x"${1}" == x"" ]
	then 
		echo "error ~! please run like: checkrun \"******\" "
		return 1
	fi
    mtxt=${1}
    
    cd LL/
    echo "LL______________________________________________________________"
    a=`tail joblist/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong
    cd ../
    
    cd data/
    echo "data____________________________________________________________"
    a=`tail joblist/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong
    cd ../
    
    cd hadron/
    echo "hadron____________________________________________________________"
    a=`tail joblist/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong
    cd ../
    
    cd signal/ana/
    echo "signal____________________________________________________________"
    a=`tail joblist/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong
    cd ../../
    
    cd shape/ana/
    echo "shape____________________________________________________________"
    a=`tail joblist/*log | grep -c "${mtxt}"`
    printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
    findRunWrong
    cd ../../
} 



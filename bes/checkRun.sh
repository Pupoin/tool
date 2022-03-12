# isRunSuccess()
# {

#     echo "path is:" $(pwd)
#     dir="./joblist"
#     numAna=`ls $dir | grep -c txt$`
#     echo number of \*.txt is: $numAna

#     numLog=`ls $dir | grep -c bosslog`
#     echo number of bosslog is: $numLog

#     numStopSuccess=`tail $dir/*bosslog | grep -c "Application Manager Stopped successfully" `
#     echo number of stopped successfully is: $numStopSuccess

#     numFinalizeSuccess=`tail $dir/*bosslog | grep -c "Application Manager Finalized successfully" `
#     echo number of finalized successfully is: $numFinalizeSuccess

#     numTerminateSuccess=`tail $dir/*bosslog | grep -c "Application Manager Terminated successfully" `
#     echo number of terminated successfully is: $numTerminateSuccess

#     echo
#     echo done ~!
# }

findRunWrong()
{
    
    dir=${1}
    if [ "x$dir" == "x" ] 
    then
        dir="./joblist"
    fi
    echo "path is:" $(pwd)/${dir}

    numAna=`ls $dir | grep -c txt$`
    printf "number of *.txt is:\033[31m $numAna \033[0m \n"
    numLog=`ls $dir | grep -c bosslog`
    printf "number of bosslog is:\033[31m $numLog \033[0m \n"

    # cd $dir
    printf "" > submitWrong
    tmp=""
    n=0
    for i in `/bin/ls $dir/*bosslog`
    do
        #echo ${i}
        tmp=$(tail ${i} | grep -c "INFO Application Manager Finalized successfully")
        #echo ${tmp}

        if [ "x${tmp}" == "x0" ]
        then
            echo "boss.condor "  ${i/.bosslog/}  >> submitWrong
            let n=n+1
            #printf "${i}"
        fi

        printf "\r${i}"
    done

    printf "\r                                                   "
    printf "\rwrong:\033[31m ${n} \033[0m\n"
    echo 'resubmit using: source submitWrong'
    echo 
    #cat submitWrong

}

energy=(4600 4612 4620 4640 4660 4680 4700)
#energy=(4740 4750 4780 4840 4914 4946)  # ${energy[0]}

mycheckrun2()
{   
    dir=${1}
    if [ "x$dir" == "x" ] 
    then
        dir="./joblist"
    fi

	if [ x"${2}" == x"" ]
	then 
		echo "error ~! please run like: checkrun \"******\" "
		return 1
	fi
    mtxt=${2}
    
    for i_e in ${energy[@]}
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
} 


mycheckrun()
{
    proc=(LL data hadron signal shape )  # ${proc[0]}

    dir=${1}
    if [ "x$dir" == "x" ] 
    then
        dir="./joblist"
    fi

	if [ x"${2}" == x"" ]
	then 
		echo "error ~! please run like: checkrun \"******\" "
		return 1
	fi
    mtxt=${2}
        

    for i_e in ${proc[@]}
    do 
        if [ ! -d "$i_e/ana/" ]; then
            cd $i_e/ana/
        else 
            cd $i_e/
        fi
        echo "______________  $i_e ______________"
        a=`tail $dir/*log | grep -c "${mtxt}"`
        printf "num of ${mtxt}:\033[31m ${a} \033[0m \n"
        findRunWrong $dir

        if [ -d "$i_e/ana/" ]; then
            cd ../../
        else 
            cd ../
        fi
    done
} 



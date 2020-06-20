
isRunSuccess()
{

    echo "path is:" $(pwd)
    dir="./joblist"
    numAna=`ls $dir | grep -c txt$`
    echo number of \*.txt is: $numAna

    numLog=`ls $dir | grep -c bosslog`
    echo number of bosslog is: $numLog

    numStopSuccess=`tail $dir/*bosslog | grep -c "Application Manager Stopped successfully" `
    echo number of stopped successfully is: $numStopSuccess

    numFinalizeSuccess=`tail $dir/*bosslog | grep -c "Application Manager Finalized successfully" `
    echo number of finalized successfully is: $numFinalizeSuccess

    numTerminateSuccess=`tail $dir/*bosslog | grep -c "Application Manager Terminated successfully" `
    echo number of terminated successfully is: $numTerminateSuccess

    echo 
    echo done ~!
}

findRunWrong()
{
    echo "path is:" $(pwd)
    dir="./joblist"

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
        fi

        printf "\r${i}" 
    done 

    printf "\r                                                   "
    printf "\rwrong: ${n} \n"
    echo 'resubmit using: source submitWrong'

}



## check effic num == 7 in "new_root" fold 
n=0
mkdir -p "list_effic"
for list in `/bin/ls new_root/ `
do 
    echo $list
    file="new_root/$list/log.effic"
    num="$(wc -l $file  | cut -d' ' -f1)"
    if [ "x$num" == "x7" ]
    then 
        cp  $file list_effic/$n.effic
        let n=n+1
    fi
    # break 
done 
starttime=`date +'%Y-%m-%d %H:%M:%S'`


parallel -j 10 < paralleljobs --joblog ./parallel.log 
#bash run22.sh ../root/inclusive_12863937_0.root ./outputRoot
#bash run22.sh ../root/inclusive_12863937_1.root ./outputRoot

endtime=`date +'%Y-%m-%d %H:%M:%S'`
start_seconds=$(date --date="$starttime" +%s);
end_seconds=$(date --date="$endtime" +%s);
echo "run time: "$((end_seconds-start_seconds))"s"

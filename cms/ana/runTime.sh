starttime=`date +'%Y-%m-%d %H:%M:%S'`


parallel -j 396 < paralleljobs --joblog ./parallel.log > parallel.out
#bash run22.sh ../root/inclusive_12863937_0.root
#bash run22.sh ../root/inclusive_12863937_1.root

endtime=`date +'%Y-%m-%d %H:%M:%S'`
start_seconds=$(date --date="$starttime" +%s);
end_seconds=$(date --date="$endtime" +%s);
echo "run time: "$((end_seconds-start_seconds))"s"

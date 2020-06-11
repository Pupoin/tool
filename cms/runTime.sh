starttime=`date +'%Y-%m-%d %H:%M:%S'`


sleep 5

endtime=`date +'%Y-%m-%d %H:%M:%S'`
start_seconds=$(date --date="$starttime" +%s);
end_seconds=$(date --date="$endtime" +%s);
echo "run time: "$((end_seconds-start_seconds))"s"

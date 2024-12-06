 n=0
 a=100
 while [ $n -le 39 ]
 do  
 tmp=`expr $n + 40 \* $a`; 
 logeffic="$tmp.effic"; 
 echo $logeffic; 
 let n=n+1
 done
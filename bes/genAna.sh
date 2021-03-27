# /bin/bash
Path="ana*txt"

printf "" > paralleljobs

for i in `ls -v ${Path}`
do
  echo "boss.exe ${i} > ${i}.bosslog 2>${i}.bosserr " >> paralleljobs
done

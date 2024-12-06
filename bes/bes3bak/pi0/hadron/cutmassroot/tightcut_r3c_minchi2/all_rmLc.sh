cp rmLc.C  rmLc4600.C
sed -i "s|rmLc()|rmLc4600()|" -i rmLc4600.C
sed -i "s|AAA|4600hadron|" -i rmLc4600.C
root -l -b -q rmLc4600.C &

cp rmLc.C  rmLc4612.C
sed -i "s|rmLc()|rmLc4612()|" -i rmLc4612.C
sed -i "s|AAA|4612hadron|" -i rmLc4612.C
root -l -b -q rmLc4612.C &

cp rmLc.C  rmLc4620.C
sed -i "s|rmLc()|rmLc4620()|" -i rmLc4620.C
sed -i "s|AAA|4620hadron|" -i rmLc4620.C
root -l -b -q rmLc4620.C &

cp rmLc.C  rmLc4640.C
sed -i "s|rmLc()|rmLc4640()|" -i rmLc4640.C
sed -i "s|AAA|4640hadron|" -i rmLc4640.C
root -l -b -q rmLc4640.C &


cp rmLc.C  rmLc4660.C
sed -i "s|rmLc()|rmLc4660()|" -i rmLc4660.C
sed -i "s|AAA|4660hadron|" -i rmLc4660.C
root -l -b -q rmLc4660.C &



cp rmLc.C  rmLc4680.C
sed -i "s|rmLc()|rmLc4680()|" -i rmLc4680.C
sed -i "s|AAA|4680hadron|" -i rmLc4680.C
root -l -b -q rmLc4680.C &


cp rmLc.C  rmLc4700.C
sed -i "s|rmLc()|rmLc4700()|" -i rmLc4700.C
sed -i "s|AAA|4700hadron|" -i rmLc4700.C
root -l -b -q rmLc4700.C &


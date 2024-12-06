cp split.C  split4600.C
sed -i "s|split()|split4600()|" -i split4600.C
sed -i "s|AAA|4600LL|" -i split4600.C
root -l -b -q split4600.C &

cp split.C  split4612.C
sed -i "s|split()|split4612()|" -i split4612.C
sed -i "s|AAA|4612LL|" -i split4612.C
root -l -b -q split4612.C &

cp split.C  split4620.C
sed -i "s|split()|split4620()|" -i split4620.C
sed -i "s|AAA|4620LL|" -i split4620.C
root -l -b -q split4620.C &

cp split.C  split4640.C
sed -i "s|split()|split4640()|" -i split4640.C
sed -i "s|AAA|4640LL|" -i split4640.C
root -l -b -q split4640.C &


cp split.C  split4660.C
sed -i "s|split()|split4660()|" -i split4660.C
sed -i "s|AAA|4660LL|" -i split4660.C
root -l -b -q split4660.C &



cp split.C  split4680.C
sed -i "s|split()|split4680()|" -i split4680.C
sed -i "s|AAA|4680LL|" -i split4680.C
root -l -b -q split4680.C &


cp split.C  split4700.C
sed -i "s|split()|split4700()|" -i split4700.C
sed -i "s|AAA|4700LL|" -i split4700.C
root -l -b -q split4700.C &


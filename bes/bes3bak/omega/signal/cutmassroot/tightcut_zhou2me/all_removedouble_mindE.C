cp removedouble_mindE.C  removedouble_mindE4600.C
sed -i "s|removedouble_mindE()|removedouble_mindE4600()|" -i removedouble_mindE4600.C
sed -i "s|AAA|4600signal|" -i removedouble_mindE4600.C
root -l -b -q removedouble_mindE4600.C &

cp removedouble_mindE.C  removedouble_mindE4612.C
sed -i "s|removedouble_mindE()|removedouble_mindE4612()|" -i removedouble_mindE4612.C
sed -i "s|AAA|4612signal|" -i removedouble_mindE4612.C
root -l -b -q removedouble_mindE4612.C &

cp removedouble_mindE.C  removedouble_mindE4620.C
sed -i "s|removedouble_mindE()|removedouble_mindE4620()|" -i removedouble_mindE4620.C
sed -i "s|AAA|4620signal|" -i removedouble_mindE4620.C
root -l -b -q removedouble_mindE4620.C &

cp removedouble_mindE.C  removedouble_mindE4640.C
sed -i "s|removedouble_mindE()|removedouble_mindE4640()|" -i removedouble_mindE4640.C
sed -i "s|AAA|4640signal|" -i removedouble_mindE4640.C
root -l -b -q removedouble_mindE4640.C &


cp removedouble_mindE.C  removedouble_mindE4660.C
sed -i "s|removedouble_mindE()|removedouble_mindE4660()|" -i removedouble_mindE4660.C
sed -i "s|AAA|4660signal|" -i removedouble_mindE4660.C
root -l -b -q removedouble_mindE4660.C &



cp removedouble_mindE.C  removedouble_mindE4680.C
sed -i "s|removedouble_mindE()|removedouble_mindE4680()|" -i removedouble_mindE4680.C
sed -i "s|AAA|4680signal|" -i removedouble_mindE4680.C
root -l -b -q removedouble_mindE4680.C &


cp removedouble_mindE.C  removedouble_mindE4700.C
sed -i "s|removedouble_mindE()|removedouble_mindE4700()|" -i removedouble_mindE4700.C
sed -i "s|AAA|4700signal|" -i removedouble_mindE4700.C
root -l -b -q removedouble_mindE4700.C &


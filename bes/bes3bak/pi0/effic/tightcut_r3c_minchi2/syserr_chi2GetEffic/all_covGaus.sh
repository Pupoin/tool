cp covGaus.C  covGaus4600.C
sed -i "s|covGaus()|covGaus4600()|" -i covGaus4600.C
sed -i "s|AAA|4600signal|" -i covGaus4600.C
root -l -b -q covGaus4600.C &

cp covGaus.C  covGaus4612.C
sed -i "s|covGaus()|covGaus4612()|" -i covGaus4612.C
sed -i "s|AAA|4612signal|" -i covGaus4612.C
root -l -b -q covGaus4612.C &

cp covGaus.C  covGaus4620.C
sed -i "s|covGaus()|covGaus4620()|" -i covGaus4620.C
sed -i "s|AAA|4620signal|" -i covGaus4620.C
root -l -b -q covGaus4620.C &

cp covGaus.C  covGaus4640.C
sed -i "s|covGaus()|covGaus4640()|" -i covGaus4640.C
sed -i "s|AAA|4640signal|" -i covGaus4640.C
root -l -b -q covGaus4640.C &


cp covGaus.C  covGaus4660.C
sed -i "s|covGaus()|covGaus4660()|" -i covGaus4660.C
sed -i "s|AAA|4660signal|" -i covGaus4660.C
root -l -b -q covGaus4660.C &



cp covGaus.C  covGaus4700.C
sed -i "s|covGaus()|covGaus4700()|" -i covGaus4700.C
sed -i "s|AAA|4700signal|" -i covGaus4700.C
root -l -b -q covGaus4700.C &

cp covGaus.C  covGaus4680.C
sed -i "s|covGaus()|covGaus4680()|" -i covGaus4680.C
sed -i "s|AAA|4680signal|" -i covGaus4680.C
root -l -b -q covGaus4680.C 



cp covGausEtapMass.C  covGausEtapMass4600.C
sed -i "s|covGausEtapMass()|covGausEtapMass4600()|" -i covGausEtapMass4600.C
sed -i "s|AAA|4600signal|" -i covGausEtapMass4600.C
root -l -b -q covGausEtapMass4600.C &

cp covGausEtapMass.C  covGausEtapMass4612.C
sed -i "s|covGausEtapMass()|covGausEtapMass4612()|" -i covGausEtapMass4612.C
sed -i "s|AAA|4612signal|" -i covGausEtapMass4612.C
root -l -b -q covGausEtapMass4612.C &

cp covGausEtapMass.C  covGausEtapMass4620.C
sed -i "s|covGausEtapMass()|covGausEtapMass4620()|" -i covGausEtapMass4620.C
sed -i "s|AAA|4620signal|" -i covGausEtapMass4620.C
root -l -b -q covGausEtapMass4620.C &

cp covGausEtapMass.C  covGausEtapMass4640.C
sed -i "s|covGausEtapMass()|covGausEtapMass4640()|" -i covGausEtapMass4640.C
sed -i "s|AAA|4640signal|" -i covGausEtapMass4640.C
root -l -b -q covGausEtapMass4640.C &


cp covGausEtapMass.C  covGausEtapMass4660.C
sed -i "s|covGausEtapMass()|covGausEtapMass4660()|" -i covGausEtapMass4660.C
sed -i "s|AAA|4660signal|" -i covGausEtapMass4660.C
root -l -b -q covGausEtapMass4660.C &



cp covGausEtapMass.C  covGausEtapMass4680.C
sed -i "s|covGausEtapMass()|covGausEtapMass4680()|" -i covGausEtapMass4680.C
sed -i "s|AAA|4680signal|" -i covGausEtapMass4680.C
root -l -b -q covGausEtapMass4680.C &


cp covGausEtapMass.C  covGausEtapMass4700.C
sed -i "s|covGausEtapMass()|covGausEtapMass4700()|" -i covGausEtapMass4700.C
sed -i "s|AAA|4700signal|" -i covGausEtapMass4700.C
root -l -b -q covGausEtapMass4700.C &


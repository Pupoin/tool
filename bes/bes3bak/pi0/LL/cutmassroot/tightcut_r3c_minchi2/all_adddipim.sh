cp adddipim.C  adddipim4600.C
sed -i "s|adddipim()|adddipim4600()|" -i adddipim4600.C
sed -i "s|AAA|4600LL|" -i adddipim4600.C
root -l -b -q adddipim4600.C &

cp adddipim.C  adddipim4612.C
sed -i "s|adddipim()|adddipim4612()|" -i adddipim4612.C
sed -i "s|AAA|4612LL|" -i adddipim4612.C
root -l -b -q adddipim4612.C &

cp adddipim.C  adddipim4620.C
sed -i "s|adddipim()|adddipim4620()|" -i adddipim4620.C
sed -i "s|AAA|4620LL|" -i adddipim4620.C
root -l -b -q adddipim4620.C &

cp adddipim.C  adddipim4640.C
sed -i "s|adddipim()|adddipim4640()|" -i adddipim4640.C
sed -i "s|AAA|4640LL|" -i adddipim4640.C
root -l -b -q adddipim4640.C &


cp adddipim.C  adddipim4660.C
sed -i "s|adddipim()|adddipim4660()|" -i adddipim4660.C
sed -i "s|AAA|4660LL|" -i adddipim4660.C
root -l -b -q adddipim4660.C &



cp adddipim.C  adddipim4680.C
sed -i "s|adddipim()|adddipim4680()|" -i adddipim4680.C
sed -i "s|AAA|4680LL|" -i adddipim4680.C
root -l -b -q adddipim4680.C &


cp adddipim.C  adddipim4700.C
sed -i "s|adddipim()|adddipim4700()|" -i adddipim4700.C
sed -i "s|AAA|4700LL|" -i adddipim4700.C
root -l -b -q adddipim4700.C &


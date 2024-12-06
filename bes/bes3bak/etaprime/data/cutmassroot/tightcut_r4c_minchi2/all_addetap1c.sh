cp addetap1c.C  addetap1c4600.C
sed -i "s|addetap1c()|addetap1c4600()|" -i addetap1c4600.C
sed -i "s|AAA|4600data|" -i addetap1c4600.C
root -l -b -q addetap1c4600.C &

cp addetap1c.C  addetap1c4612.C
sed -i "s|addetap1c()|addetap1c4612()|" -i addetap1c4612.C
sed -i "s|AAA|4612data|" -i addetap1c4612.C
root -l -b -q addetap1c4612.C &

cp addetap1c.C  addetap1c4620.C
sed -i "s|addetap1c()|addetap1c4620()|" -i addetap1c4620.C
sed -i "s|AAA|4620data|" -i addetap1c4620.C
root -l -b -q addetap1c4620.C &

cp addetap1c.C  addetap1c4640.C
sed -i "s|addetap1c()|addetap1c4640()|" -i addetap1c4640.C
sed -i "s|AAA|4640data|" -i addetap1c4640.C
root -l -b -q addetap1c4640.C &


cp addetap1c.C  addetap1c4660.C
sed -i "s|addetap1c()|addetap1c4660()|" -i addetap1c4660.C
sed -i "s|AAA|4660data|" -i addetap1c4660.C
root -l -b -q addetap1c4660.C &



cp addetap1c.C  addetap1c4680.C
sed -i "s|addetap1c()|addetap1c4680()|" -i addetap1c4680.C
sed -i "s|AAA|4680data|" -i addetap1c4680.C
root -l -b -q addetap1c4680.C &


cp addetap1c.C  addetap1c4700.C
sed -i "s|addetap1c()|addetap1c4700()|" -i addetap1c4700.C
sed -i "s|AAA|4700data|" -i addetap1c4700.C
root -l -b -q addetap1c4700.C &


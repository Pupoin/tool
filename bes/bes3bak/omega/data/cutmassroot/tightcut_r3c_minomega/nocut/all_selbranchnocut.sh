cp selbranchnocut.C  selbranchnocut4600.C
sed -i "s|selbranchnocut()|selbranchnocut4600()|" -i selbranchnocut4600.C
sed -i "s|AAA|4600data|" -i selbranchnocut4600.C
root -l -b -q selbranchnocut4600.C &

cp selbranchnocut.C  selbranchnocut4612.C
sed -i "s|selbranchnocut()|selbranchnocut4612()|" -i selbranchnocut4612.C
sed -i "s|AAA|4612data|" -i selbranchnocut4612.C
root -l -b -q selbranchnocut4612.C &

cp selbranchnocut.C  selbranchnocut4620.C
sed -i "s|selbranchnocut()|selbranchnocut4620()|" -i selbranchnocut4620.C
sed -i "s|AAA|4620data|" -i selbranchnocut4620.C
root -l -b -q selbranchnocut4620.C &

cp selbranchnocut.C  selbranchnocut4640.C
sed -i "s|selbranchnocut()|selbranchnocut4640()|" -i selbranchnocut4640.C
sed -i "s|AAA|4640data|" -i selbranchnocut4640.C
root -l -b -q selbranchnocut4640.C &


cp selbranchnocut.C  selbranchnocut4660.C
sed -i "s|selbranchnocut()|selbranchnocut4660()|" -i selbranchnocut4660.C
sed -i "s|AAA|4660data|" -i selbranchnocut4660.C
root -l -b -q selbranchnocut4660.C &



cp selbranchnocut.C  selbranchnocut4680.C
sed -i "s|selbranchnocut()|selbranchnocut4680()|" -i selbranchnocut4680.C
sed -i "s|AAA|4680data|" -i selbranchnocut4680.C
root -l -b -q selbranchnocut4680.C &


cp selbranchnocut.C  selbranchnocut4700.C
sed -i "s|selbranchnocut()|selbranchnocut4700()|" -i selbranchnocut4700.C
sed -i "s|AAA|4700data|" -i selbranchnocut4700.C
root -l -b -q selbranchnocut4700.C &


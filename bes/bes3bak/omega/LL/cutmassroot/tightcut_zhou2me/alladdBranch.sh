cp addBranch.C  addBranch4600.C
sed -i "s|addBranch4600()|addBranch4600()|" -i addBranch4600.C
sed -i "s|AAA|4600LL|" -i addBranch4600.C
root -l -b -q addBranch4600.C &

cp addBranch.C  addBranch4612.C
sed -i "s|addBranch4600()|addBranch4612()|" -i addBranch4612.C
sed -i "s|AAA|4612LL|" -i addBranch4612.C
root -l -b -q addBranch4612.C &

cp addBranch.C  addBranch4620.C
sed -i "s|addBranch4600()|addBranch4620()|" -i addBranch4620.C
sed -i "s|AAA|4620LL|" -i addBranch4620.C
root -l -b -q addBranch4620.C &

cp addBranch.C  addBranch4640.C
sed -i "s|addBranch4600()|addBranch4640()|" -i addBranch4640.C
sed -i "s|AAA|4640LL|" -i addBranch4640.C
root -l -b -q addBranch4640.C &

cp addBranch.C  addBranch4660.C
sed -i "s|addBranch4600()|addBranch4660()|" -i addBranch4660.C
sed -i "s|AAA|4660LL|" -i addBranch4660.C
root -l -b -q addBranch4660.C &

cp addBranch.C  addBranch4680.C
sed -i "s|addBranch4600()|addBranch4680()|" -i addBranch4680.C
sed -i "s|AAA|4680LL|" -i addBranch4680.C
root -l -b -q addBranch4680.C &

cp addBranch.C  addBranch4700.C
sed -i "s|addBranch4600()|addBranch4700()|" -i addBranch4700.C
sed -i "s|AAA|4700LL|" -i addBranch4700.C
root -l -b -q addBranch4700.C &


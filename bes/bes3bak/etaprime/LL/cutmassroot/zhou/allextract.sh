cp extract.C  extract4600.C
sed -i "s|extract()|extract4600()|" -i extract4600.C
sed -i "s|shape|4600LL|" -i extract4600.C
root -l -b -q extract4600.C

cp extract.C  extract4612.C
sed -i "s|extract()|extract4612()|" -i extract4612.C
sed -i "s|shape|4612LL|" -i extract4612.C
root -l -b -q extract4612.C

cp extract.C  extract4620.C
sed -i "s|extract()|extract4620()|" -i extract4620.C
sed -i "s|shape|4620LL|" -i extract4620.C
root -l -b -q extract4620.C

cp extract.C  extract4640.C
sed -i "s|extract()|extract4640()|" -i extract4640.C
sed -i "s|shape|4640LL|" -i extract4640.C
root -l -b -q extract4640.C


cp extract.C  extract4660.C
sed -i "s|extract()|extract4660()|" -i extract4660.C
sed -i "s|shape|4660LL|" -i extract4660.C
root -l -b -q extract4660.C



cp extract.C  extract4680.C
sed -i "s|extract()|extract4680()|" -i extract4680.C
sed -i "s|shape|4680LL|" -i extract4680.C
root -l -b -q extract4680.C


cp extract.C  extract4700.C
sed -i "s|extract()|extract4700()|" -i extract4700.C
sed -i "s|shape|4700LL|" -i extract4700.C
root -l -b -q extract4700.C


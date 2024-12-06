cp extract.C  extract4600-1.C
sed -i "s|extract()|extract4600-1()|" -i extract4600-1.C
sed -i "s|shape|4600data-1|" -i extract4600-1.C
root -l -b -q extract4600-1.C

cp extract.C  extract4600-2.C
sed -i "s|extract()|extract4600-2()|" -i extract4600-2.C
sed -i "s|shape|4600data-2|" -i extract4600-2.C
root -l -b -q extract4600-2.C

cp extract.C  extract4612.C
sed -i "s|extract()|extract4612()|" -i extract4612.C
sed -i "s|shape|4612data|" -i extract4612.C
root -l -b -q extract4612.C

cp extract.C  extract4620.C
sed -i "s|extract()|extract4620()|" -i extract4620.C
sed -i "s|shape|4620data|" -i extract4620.C
root -l -b -q extract4620.C

cp extract.C  extract4640.C
sed -i "s|extract()|extract4640()|" -i extract4640.C
sed -i "s|shape|4640data|" -i extract4640.C
root -l -b -q extract4640.C


cp extract.C  extract4660.C
sed -i "s|extract()|extract4660()|" -i extract4660.C
sed -i "s|shape|4660data|" -i extract4660.C
root -l -b -q extract4660.C



cp extract.C  extract4680.C
sed -i "s|extract()|extract4680()|" -i extract4680.C
sed -i "s|shape|4680data|" -i extract4680.C
root -l -b -q extract4680.C


cp extract.C  extract4700.C
sed -i "s|extract()|extract4700()|" -i extract4700.C
sed -i "s|shape|4700data|" -i extract4700.C
root -l -b -q extract4700.C


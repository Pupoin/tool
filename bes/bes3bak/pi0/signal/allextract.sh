cp extract.C  extract4620.C
sed -i "s|extract()|extract4620()|" -i extract4620.C
sed -i "s|shape|4620signal|" -i extract4620.C
root -l -b -q extract4620.C

cp extract.C  extract4640.C
sed -i "s|extract()|extract4640()|" -i extract4640.C
sed -i "s|shape|4640signal|" -i extract4640.C
root -l -b -q extract4640.C


cp extract.C  extract4660.C
sed -i "s|extract()|extract4660()|" -i extract4660.C
sed -i "s|shape|4660signal|" -i extract4660.C
root -l -b -q extract4660.C



cp extract.C  extract4680.C
sed -i "s|extract()|extract4680()|" -i extract4680.C
sed -i "s|shape|4680signal|" -i extract4680.C
root -l -b -q extract4680.C


cp extract.C  extract4700.C
sed -i "s|extract()|extract4700()|" -i extract4700.C
sed -i "s|shape|4700signal|" -i extract4700.C
root -l -b -q extract4700.C


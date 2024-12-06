cp extract_dipi.C  extract_dipi4600.C
sed -i "s|extract_dipi()|extract_dipi4600()|" -i extract_dipi4600.C
sed -i "s|shape|4600hadron|" -i extract_dipi4600.C
root -l -b -q extract_dipi4600.C

cp extract_dipi.C  extract_dipi4612.C
sed -i "s|extract_dipi()|extract_dipi4612()|" -i extract_dipi4612.C
sed -i "s|shape|4612hadron|" -i extract_dipi4612.C
root -l -b -q extract_dipi4612.C

cp extract_dipi.C  extract_dipi4620.C
sed -i "s|extract_dipi()|extract_dipi4620()|" -i extract_dipi4620.C
sed -i "s|shape|4620hadron|" -i extract_dipi4620.C
root -l -b -q extract_dipi4620.C

cp extract_dipi.C  extract_dipi4640.C
sed -i "s|extract_dipi()|extract_dipi4640()|" -i extract_dipi4640.C
sed -i "s|shape|4640hadron|" -i extract_dipi4640.C
root -l -b -q extract_dipi4640.C


cp extract_dipi.C  extract_dipi4660.C
sed -i "s|extract_dipi()|extract_dipi4660()|" -i extract_dipi4660.C
sed -i "s|shape|4660hadron|" -i extract_dipi4660.C
root -l -b -q extract_dipi4660.C



cp extract_dipi.C  extract_dipi4680.C
sed -i "s|extract_dipi()|extract_dipi4680()|" -i extract_dipi4680.C
sed -i "s|shape|4680hadron|" -i extract_dipi4680.C
root -l -b -q extract_dipi4680.C


cp extract_dipi.C  extract_dipi4700.C
sed -i "s|extract_dipi()|extract_dipi4700()|" -i extract_dipi4700.C
sed -i "s|shape|4700hadron|" -i extract_dipi4700.C
root -l -b -q extract_dipi4700.C


cp rmmode.C  rmmode4600.C
sed -i "s|rmmode()|rmmode4600()|" -i rmmode4600.C
sed -i "s|shape|4600hadron|" -i rmmode4600.C
root -l -b -q rmmode4600.C  &

cp rmmode.C  rmmode4612.C
sed -i "s|rmmode()|rmmode4612()|" -i rmmode4612.C
sed -i "s|shape|4612hadron|" -i rmmode4612.C
root -l -b -q rmmode4612.C &

cp rmmode.C  rmmode4620.C
sed -i "s|rmmode()|rmmode4620()|" -i rmmode4620.C
sed -i "s|shape|4620hadron|" -i rmmode4620.C
root -l -b -q rmmode4620.C &

cp rmmode.C  rmmode4640.C
sed -i "s|rmmode()|rmmode4640()|" -i rmmode4640.C
sed -i "s|shape|4640hadron|" -i rmmode4640.C
root -l -b -q rmmode4640.C &


cp rmmode.C  rmmode4660.C
sed -i "s|rmmode()|rmmode4660()|" -i rmmode4660.C
sed -i "s|shape|4660hadron|" -i rmmode4660.C
root -l -b -q rmmode4660.C &



cp rmmode.C  rmmode4680.C
sed -i "s|rmmode()|rmmode4680()|" -i rmmode4680.C
sed -i "s|shape|4680hadron|" -i rmmode4680.C
root -l -b -q rmmode4680.C &


cp rmmode.C  rmmode4700.C
sed -i "s|rmmode()|rmmode4700()|" -i rmmode4700.C
sed -i "s|shape|4700hadron|" -i rmmode4700.C
root -l -b -q rmmode4700.C &

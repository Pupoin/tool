cp template/fitInclusive4620.cc fitInclusive4600.cc
cp template/signi_eff4620.cc  signi_eff4600.cc
sed -i  's/4620/4600/' -i signi_eff4600.cc
sed -i  's/4620/4600/' -i fitInclusive4600.cc
sed -i 's/E=4.626/E=4.600/' -i fitInclusive4600.cc
sed -i 's/2.31387/2.299765/' fitInclusive4600.cc
#root -l fitInclusive4600.cc

cp template/fitInclusive4620.cc fitInclusive4612.cc
cp template/signi_eff4620.cc  signi_eff4612.cc
sed -i  's/4620/4612/' -i signi_eff4612.cc
sed -i  's/4620/4612/' -i fitInclusive4612.cc
sed -i 's/E=4.626/E=4.612/' -i fitInclusive4612.cc
sed -i 's/2.31387/2.30579/' fitInclusive4612.cc
#root -l fitInclusive4612.cc

cp template/fitInclusive4620.cc fitInclusive4640.cc
cp template/signi_eff4620.cc  signi_eff4640.cc
sed -i  's/4620/4640/' -i signi_eff4640.cc
sed -i  's/4620/4640/' -i fitInclusive4640.cc
sed -i 's/E=4.626/E=4.640/' -i fitInclusive4640.cc
sed -i 's/2.31387/2.320255/' fitInclusive4640.cc
#root -l fitInclusive4640.cc

cp template/fitInclusive4620.cc fitInclusive4660.cc
cp template/signi_eff4620.cc  signi_eff4660.cc
sed -i  's/4620/4660/' -i signi_eff4660.cc
sed -i  's/4620/4660/' -i fitInclusive4660.cc
sed -i 's/E=4.626/E=4.660/' -i fitInclusive4660.cc
sed -i 's/2.31387/2.33046/' fitInclusive4660.cc
#root -l fitInclusive4660.cc

cp template/fitInclusive4620.cc fitInclusive4680.cc
cp template/signi_eff4620.cc  signi_eff4680.cc
sed -i  's/4620/4680/' -i signi_eff4680.cc
sed -i  's/4620/4680/' -i fitInclusive4680.cc
sed -i 's/E=4.626/E=4.680/' -i fitInclusive4680.cc
sed -i 's/2.31387/2.34079/' fitInclusive4680.cc
#root -l fitInclusive4680.cc

cp template/fitInclusive4620.cc fitInclusive4700.cc
cp template/signi_eff4620.cc  signi_eff4700.cc
sed -i  's/4620/4700/' -i signi_eff4700.cc
sed -i  's/4620/4700/' -i fitInclusive4700.cc
sed -i 's/E=4.626/E=4.700/' -i fitInclusive4700.cc
sed -i 's/2.31387/2.34919/' fitInclusive4700.cc
#root -l fitInclusive4700.cc


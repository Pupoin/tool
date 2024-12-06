cp selbranch.C  selbranch4600.C
sed -i "s|selbranch()|selbranch4600()|" -i selbranch4600.C
sed -i "s|AAA|4600signal|" -i selbranch4600.C
root -l -b -q selbranch4600.C &

cp selbranch.C  selbranch4612.C
sed -i "s|selbranch()|selbranch4612()|" -i selbranch4612.C
sed -i "s|AAA|4612signal|" -i selbranch4612.C
root -l -b -q selbranch4612.C &

cp selbranch.C  selbranch4620.C
sed -i "s|selbranch()|selbranch4620()|" -i selbranch4620.C
sed -i "s|AAA|4620signal|" -i selbranch4620.C
root -l -b -q selbranch4620.C &

cp selbranch.C  selbranch4640.C
sed -i "s|selbranch()|selbranch4640()|" -i selbranch4640.C
sed -i "s|AAA|4640signal|" -i selbranch4640.C
root -l -b -q selbranch4640.C &


cp selbranch.C  selbranch4660.C
sed -i "s|selbranch()|selbranch4660()|" -i selbranch4660.C
sed -i "s|AAA|4660signal|" -i selbranch4660.C
root -l -b -q selbranch4660.C &



cp selbranch.C  selbranch4680.C
sed -i "s|selbranch()|selbranch4680()|" -i selbranch4680.C
sed -i "s|AAA|4680signal|" -i selbranch4680.C
root -l -b -q selbranch4680.C &


cp selbranch.C  selbranch4700.C
sed -i "s|selbranch()|selbranch4700()|" -i selbranch4700.C
sed -i "s|AAA|4700signal|" -i selbranch4700.C
root -l -b -q selbranch4700.C &


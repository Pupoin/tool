cp rm_sig.C  rm_sig4600.C
sed -i "s|rm_sig()|rm_sig4600()|" -i rm_sig4600.C
sed -i "s|AAA|4600LL|" -i rm_sig4600.C
root -l -b -q rm_sig4600.C &

cp rm_sig.C  rm_sig4612.C
sed -i "s|rm_sig()|rm_sig4612()|" -i rm_sig4612.C
sed -i "s|AAA|4612LL|" -i rm_sig4612.C
root -l -b -q rm_sig4612.C &

cp rm_sig.C  rm_sig4620.C
sed -i "s|rm_sig()|rm_sig4620()|" -i rm_sig4620.C
sed -i "s|AAA|4620LL|" -i rm_sig4620.C
root -l -b -q rm_sig4620.C &

cp rm_sig.C  rm_sig4640.C
sed -i "s|rm_sig()|rm_sig4640()|" -i rm_sig4640.C
sed -i "s|AAA|4640LL|" -i rm_sig4640.C
root -l -b -q rm_sig4640.C &


cp rm_sig.C  rm_sig4660.C
sed -i "s|rm_sig()|rm_sig4660()|" -i rm_sig4660.C
sed -i "s|AAA|4660LL|" -i rm_sig4660.C
root -l -b -q rm_sig4660.C &



cp rm_sig.C  rm_sig4680.C
sed -i "s|rm_sig()|rm_sig4680()|" -i rm_sig4680.C
sed -i "s|AAA|4680LL|" -i rm_sig4680.C
root -l -b -q rm_sig4680.C &


cp rm_sig.C  rm_sig4700.C
sed -i "s|rm_sig()|rm_sig4700()|" -i rm_sig4700.C
sed -i "s|AAA|4700LL|" -i rm_sig4700.C
root -l -b -q rm_sig4700.C &


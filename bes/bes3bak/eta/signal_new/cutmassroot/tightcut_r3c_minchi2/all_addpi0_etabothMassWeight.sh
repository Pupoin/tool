

energy=(4600 4612 4620 4640 4660 4680 4700)
for i_e in ${energy[@]}
do 
    cp addpi0_etabothMassWeight.C  "addpi0_etabothMassWeight${i_e}.C"
    sed -i "s|addpi0_etabothMassWeight()|addpi0_etabothMassWeight${i_e}()|" -i "addpi0_etabothMassWeight${i_e}.C"
    sed -i "s|AAA|${i_e}signal|" -i "addpi0_etabothMassWeight${i_e}.C"
    root -l -b -q "addpi0_etabothMassWeight${i_e}".C &

done




# cp adddipim.C  adddipim4600.C
# sed -i "s|adddipim()|adddipim4600()|" -i adddipim4600.C
# sed -i "s|AAA|4600signal|" -i adddipim4600.C
# root -l -b -q adddipim4600.C &

# cp adddipim.C  adddipim4612.C
# sed -i "s|adddipim()|adddipim4612()|" -i adddipim4612.C
# sed -i "s|AAA|4612signal|" -i adddipim4612.C
# root -l -b -q adddipim4612.C &

# cp adddipim.C  adddipim4620.C
# sed -i "s|adddipim()|adddipim4620()|" -i adddipim4620.C
# sed -i "s|AAA|4620signal|" -i adddipim4620.C
# root -l -b -q adddipim4620.C &

# cp adddipim.C  adddipim4640.C
# sed -i "s|adddipim()|adddipim4640()|" -i adddipim4640.C
# sed -i "s|AAA|4640signal|" -i adddipim4640.C
# root -l -b -q adddipim4640.C &


# cp adddipim.C  adddipim4660.C
# sed -i "s|adddipim()|adddipim4660()|" -i adddipim4660.C
# sed -i "s|AAA|4660signal|" -i adddipim4660.C
# root -l -b -q adddipim4660.C &



# cp adddipim.C  adddipim4680.C
# sed -i "s|adddipim()|adddipim4680()|" -i adddipim4680.C
# sed -i "s|AAA|4680signal|" -i adddipim4680.C
# root -l -b -q adddipim4680.C &


# cp adddipim.C  adddipim4700.C
# sed -i "s|adddipim()|adddipim4700()|" -i adddipim4700.C
# sed -i "s|AAA|4700signal|" -i adddipim4700.C
# root -l -b -q adddipim4700.C &



energy=(4600 4612 4620 4640 4660 4680 4700)
#energy=(4600 4612 4620 4640 4660 4680)


# convert Ap_ptruth[][4]/Am_ptruth to new_Ap_ptruth/new_Am_ptruth[200]
for i_e in ${energy[@]}
do 

    cp convert.C  convert${i_e}.C
    sed -i "s|convert()|convert${i_e}()|" -i convert${i_e}.C
    sed -i "s|AAA|${i_e}signal|" -i convert${i_e}.C
    root -l -b -q convert${i_e}.C &
done



# TFile f1("4612signal.root", "UPDATE");
# gDirectory->Delete("tree;3")    
# gDirectory->Delete("tree;2")  

# TFile f2("4620signal.root", "UPDATE");
# gDirectory->Delete("tree;3")    
# gDirectory->Delete("tree;2") 

# TFile f3("4640signal.root", "UPDATE");
# gDirectory->Delete("tree;3")    
# gDirectory->Delete("tree;2")  

# TFile f4("4660signal.root", "UPDATE");
# gDirectory->Delete("tree;3")    
# gDirectory->Delete("tree;2")  

# TFile f5("4680signal.root", "UPDATE");
# gDirectory->Delete("tree;3")    
# gDirectory->Delete("tree;2")  

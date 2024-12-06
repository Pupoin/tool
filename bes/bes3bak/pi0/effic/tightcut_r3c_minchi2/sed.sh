
files=(fitInclusive4600.cc
fitInclusive4612.cc
fitInclusive4620.cc
fitInclusive4640.cc
fitInclusive4660.cc
fitInclusive4680.cc
fitInclusive4700.cc)

energy=(4600 4612 4620 4640 4660 4680 4700)
endpoint=(2.299765 2.30579  2.31387 2.320255 2.33046  2.34079 2.34919 )

fitBase()
{
    for(( i=0;i<${#files[@]};i++))
    do
        # echo ${files[i]};
        #cp fitBase.cc ${files[i]}
       # sed "s|_endpoint_|${endpoint[i]}|g" -i ${files[i]}
       # sed "s|_energy_|${energy[i]}|g" -i ${files[i]}
		sed "s|c^{2}|#font[12]{c^{2}}|g" -i ${files[i]}
    done


    # for i_e in ${energy[@]}
    # do 
    #     cp fitBase.cc ${i_e}
    #     sed "s|endpoint|" -i ${i_e}

    # done 
}

fitBase

# for i_e in ${energy[@]}
# do 
#     sed -i 's|using namespace RooFit;|\
# using namespace RooFit;\n\
# TCanvas *canv1 = new TCanvas("canv1", "mBC", 700, 600); \
# canv1->SetFillColor(0);\
# canv1->SetFrameFillColor(0);\
# canv1->SetTopMargin(0.15);\
# canv1->SetBottomMargin(0.15);\
# canv1->SetLeftMargin(0.15);\
# canv1->SetRightMargin(0.03);\
# gStyle->SetOptStat(0);\
# gStyle->SetPadColor(0);\
# gStyle->SetCanvasColor(0);|g' -i ${i_e}

# sed -i "s|TCanvas \*c1.*||g" -i ${i_e}
# sed -i "s|c1->SetMargin.*||g" -i ${i_e}
# sed -i "s|c1|canv1|g" -i ${i_e}


# done
# 


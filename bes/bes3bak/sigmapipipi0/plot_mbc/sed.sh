
files=(
plot_mbc4600.cc
plot_mbc4612.cc
plot_mbc4620.cc
plot_mbc4640.cc
plot_mbc4660.cc
plot_mbc4680.cc
plot_mbc4700.cc
# plot_mbcall.cc
)

energy=(4600 4612 4620 4640 4660 4680 4700)
endpoint=(2.299765 2.30579  2.31387 2.320255 2.33046  2.34079 2.34919 )

factor=(
'double factor[2] = {0.0190, 0.0250};'
'double factor[2] = {0.030, 0.0250};'
'double factor[2] = {0.0220, 0.02250};'
'double factor[2] = {0.0250, 0.0250};'
'double factor[2] = {0.02250, 0.02250};'
'double factor[2] = {0.025, 0.03};'
'double factor[2] = {0.0250, 0.0250};'
)

fitBase()
{
    for(( i=0;i<${#files[@]};i++))
    do
        # echo ${files[i]};
        cp plot_mbcBase.cc ${files[i]}
        sed "s|_endpoint_|${endpoint[i]}|g" -i ${files[i]}
        sed "s|_energy_|${energy[i]}|g" -i ${files[i]}
        sed "s|double factor.*|${factor[i]}|g" -i ${files[i]}

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


# root -l -b -q cos.C
# bash all_convert.sh 
python cal_Costheta_sigma.py 
root -l -b -q add_sigma_eta_weight.C


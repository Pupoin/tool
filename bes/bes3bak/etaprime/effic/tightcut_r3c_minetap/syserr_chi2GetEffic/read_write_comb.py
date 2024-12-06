import ROOT
from ROOT import TBranch, TTree, TFile
import argparse
import os
import os.path
import importlib
import shutil
from array import array
import time
 
import numpy as np
# import re
start=time.time()
# os.system("bash getratio.sh")

effic_4600 = []
# effic_4612 = []
# effic_4620 = []
# effic_4640 = []
# effic_4660 = []
# effic_4680 = []
# effic_4700 = []
for i in range(0, 100):
    print "---- ", i,  " ---- "
    for j in  range(0,100):

        fileName = "new_root/{0}_{1}/log.fit_comb.Br".format(i,j)
        if not os.path.isfile(fileName):
            continue
        f=open(fileName)
        count = 0
        for line in f:
            count = count + 1

        f=open(fileName)
        if count != 1:
            print "fit wrongly in ", fileName
        if count == 1:
            for line in f:
                txt = line.split()
                if(len(txt) == 7 and txt[1]=='1' and  txt[2]=='Br:' ):    
                    effic_4600.append(float(txt[3]))
                # if(len(txt) == 5 and txt[1]=='4612' and  txt[2]=='1' ):    effic_4612.append(float(txt[3]))
                # if(len(txt) == 5 and txt[1]=='4620' and  txt[2]=='1' ):    effic_4620.append(float(txt[3]))
                # if(len(txt) == 5 and txt[1]=='4640' and  txt[2]=='1' ):    effic_4640.append(float(txt[3]))
                # if(len(txt) == 5 and txt[1]=='4660' and  txt[2]=='1' ):    effic_4660.append(float(txt[3]))
                # if(len(txt) == 5 and txt[1]=='4680' and  txt[2]=='1' ):    effic_4680.append(float(txt[3]))
                # if(len(txt) == 5 and txt[1]=='4700' and  txt[2]=='1' ):    effic_4700.append(float(txt[3]))
        f.close()

# print effic_4600
# print effic_4612
# print effic_4620
# print effic_4640
# print effic_4660
# print effic_4680
# print effic_4700


# # print effic_4612

# write ratio to root file 
rf = ROOT.TFile("Br.root", "RECREATE")
tree = ROOT.TTree("tree", "ratio")

x_effic_4600 = array('d',[0])
# x_effic_4612 = array('d',[0])
# x_effic_4620 = array('d',[0])
# x_effic_4640 = array('d',[0])
# x_effic_4660 = array('d',[0])
# x_effic_4680 = array('d',[0])
# x_effic_4700 = array('d',[0])

tree.Branch("Br", x_effic_4600, "Br/D")
# tree.Branch("effic_4612", x_effic_4612, "effic_4612/D")
# tree.Branch("effic_4620", x_effic_4620, "effic_4620/D")
# tree.Branch("effic_4640", x_effic_4640, "effic_4640/D")
# tree.Branch("effic_4660", x_effic_4660, "effic_4660/D")
# tree.Branch("effic_4680", x_effic_4680, "effic_4680/D")
# tree.Branch("effic_4700", x_effic_4700, "effic_4700/D")


for i  in range(len(effic_4600)) :
    x_effic_4600[0] = effic_4600[i]
    # x_effic_4612[0] = effic_4612[i]
    # x_effic_4620[0] = effic_4620[i]
    # x_effic_4640[0] = effic_4640[i]
    # x_effic_4660[0] = effic_4660[i]
    # x_effic_4680[0] = effic_4680[i]
    # x_effic_4700[0] = effic_4700[i]
    tree.Fill()

tree.Write("", ROOT.TObject.kOverwrite)
rf.Close()

print "time", time.time()- start
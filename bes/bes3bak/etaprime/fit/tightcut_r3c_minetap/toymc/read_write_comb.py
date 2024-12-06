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

branch = []
brancherr = []
fileName = "toymc_C/log.io_Br"
# fileName = "toymc_C/old_xx/log.io_Br"
if not os.path.isfile(fileName):
    exit

f=open(fileName)
for line in f:
    # if count != 1:
    #     print "fit wrongly in ", fileName
    # if count == 1:
    print line 
    txt = line.split()
    if(len(txt) == 8 and txt[1]=='2' and  txt[2]=='Br:' ):    
        branch.append(float(txt[3]))
        brancherr.append(float(txt[5]))
        print txt[3], txt[5]
f.close()

# print branch

# write ratio to root file 
rf = ROOT.TFile("Br.root", "RECREATE")
tree = ROOT.TTree("tree", "ratio")

x_branch = array('d',[0])
x_brancherr = array('d',[0])
pull = array('d',[0])
tree.Branch("Br", x_branch, "Br/D")
tree.Branch("Brerr", x_brancherr, "Brerr/D")
tree.Branch("pull", pull, "pull/D")
 


for i  in range(len(branch)) :
    # if brancherr[i] <0.04 or brancherr[i] >0.2: 
    if brancherr[i] > 0.2 : # or fTree.Brerr < 0.03 :
        continue

    x_branch[0] = branch[i]
    x_brancherr[0] = brancherr[i]
    pull[0] = 1.0* (branch[i] - 0.335808)/(brancherr[i])
    # print x_branch[0] , x_brancherr[0], pull
    
 
    tree.Fill()

tree.Write("", ROOT.TObject.kOverwrite)
rf.Close()

print "time", time.time()- start
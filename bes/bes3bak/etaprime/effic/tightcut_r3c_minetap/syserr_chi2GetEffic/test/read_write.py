import ROOT
from ROOT import TBranch, TTree, TFile
import argparse
import os
import importlib
import shutil
from array import array

 
import numpy as np
# import re

# os.system("bash getratio.sh")

f=open("o")
line = f.readline()
list_ratio = []
# list_error = []

while line:
    # txt = line.split()
    # if(len(txt) > 4):
        # print(line, " === ", txt[4], txt[6])
    list_ratio.append(float(line))
        # list_error.append(float(txt[6]))
        
    line = f.readline()

f.close()

# print list_error

## write ratio to root file 
rf = ROOT.TFile("ratio.root", "RECREATE")
tree = ROOT.TTree("tree", "ratio")

x_ratio = array('d',[0])
# x_error = array('d',[0])
# x_pull = array('d',[0])
tree.Branch("ratio", x_ratio, "ratio/D")
# tree.Branch("error", x_error, "error/D")
# tree.Branch("pull", x_pull, "pull/D")


for i  in range(len(list_ratio)) :
    x_ratio[0] = list_ratio[i]
    # x_error[0] = list_error[i]
    # x_pull[0] = (list_ratio[i] - 0.301613)/list_error[i]
    tree.Fill()

tree.Write("", ROOT.TObject.kOverwrite)
rf.Close()

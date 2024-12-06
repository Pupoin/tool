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

f=open("log.Bratio")
line = f.readline()
list_ratio = []
list_error = []
list_kind = []


while line:
    txt = line.split()
    if(len(txt) > 4):
        a=txt[0].split('-')[0].split('/')[-1]
        b=a.split("_")[-1]
        print(a, b)
        list_kind.append(float(b))
        list_ratio.append(float(txt[4]))
        list_error.append(float(txt[6]))
        
    line = f.readline()

f.close()

# print list_error

## write ratio to root file 
rf = ROOT.TFile("ratio.root", "RECREATE")
tree = ROOT.TTree("tree", "ratio")

k_kind = array('d',[0])
x_ratio = array('d',[0])
x_error = array('d',[0])
x_pull = array('d',[0])
tree.Branch("ratio", x_ratio, "ratio/D")
tree.Branch("error", x_error, "error/D")
tree.Branch("pull", x_pull, "pull/D")
tree.Branch("kind", k_kind, "kind/D")


for i  in range(len(list_ratio)) :
    x_ratio[0] = list_ratio[i]
    k_kind[0] = list_kind[i]
    x_error[0] = list_error[i]
    x_pull[0] = (list_ratio[i] - 0.335808)/list_error[i]
    tree.Fill()

tree.Write("", ROOT.TObject.kOverwrite)
rf.Close()

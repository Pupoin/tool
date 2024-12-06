import ROOT
from ROOT import TBranch, TTree, TFile
import argparse
import os
import importlib
import shutil
from array import array
import time


import numpy as np
# import re
start = time.time()
# os.system("bash getratio.sh")

rf = ROOT.TFile("effic.root", "RECREATE")
tree = ROOT.TTree("tree", "ratio")

x_effic_4600 = array('d',[0])
x_effic_4612 = array('d',[0])
x_effic_4620 = array('d',[0])
x_effic_4640 = array('d',[0])
x_effic_4660 = array('d',[0])
x_effic_4680 = array('d',[0])
x_effic_4700 = array('d',[0])

tree.Branch("effic_4600", x_effic_4600, "effic_4600/D")
tree.Branch("effic_4612", x_effic_4612, "effic_4612/D")
tree.Branch("effic_4620", x_effic_4620, "effic_4620/D")
tree.Branch("effic_4640", x_effic_4640, "effic_4640/D")
tree.Branch("effic_4660", x_effic_4660, "effic_4660/D")
tree.Branch("effic_4680", x_effic_4680, "effic_4680/D")
tree.Branch("effic_4700", x_effic_4700, "effic_4700/D")


for i in range(0, 100):
    print "---- ", i,  " ---- "
    for j in  range(0,100):

        fileName = "new_root/{0}_{1}/log.effic".format(i,j)

        f=open(fileName)
        count = 0
        for line in f:
            count = count + 1

        f=open(fileName)
        if count != 7:
            print "fit wrongly in ", fileName
        if count == 7:
            for line in f:
                txt = line.split()
                if(len(txt) == 5 and txt[1]=='4600' and  txt[2]=='1' ):    x_effic_4600 = float(txt[3])
                if(len(txt) == 5 and txt[1]=='4612' and  txt[2]=='1' ):    x_effic_4612 = float(txt[3])
                if(len(txt) == 5 and txt[1]=='4620' and  txt[2]=='1' ):    x_effic_4620 = float(txt[3])
                if(len(txt) == 5 and txt[1]=='4640' and  txt[2]=='1' ):    x_effic_4640 = float(txt[3])
                if(len(txt) == 5 and txt[1]=='4660' and  txt[2]=='1' ):    x_effic_4660 = float(txt[3])
                if(len(txt) == 5 and txt[1]=='4680' and  txt[2]=='1' ):    x_effic_4680 = float(txt[3])
                if(len(txt) == 5 and txt[1]=='4700' and  txt[2]=='1' ):    x_effic_4700 = float(txt[3])
                tree.Fill() 
        f.close()


tree.Write("", ROOT.TObject.kOverwrite)
rf.Close()

print "time", time.time()- start
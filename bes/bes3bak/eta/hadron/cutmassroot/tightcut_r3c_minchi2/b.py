import ROOT
from ROOT import * 

f=[ "4600hadron_mode.root", "4600hadron_removedouble_mode.root", 
    "4612hadron_mode.root", "4612hadron_removedouble_mode.root", 
    "4620hadron_mode.root", "4620hadron_removedouble_mode.root", 
    "4640hadron_mode.root", "4640hadron_removedouble_mode.root",
    "4660hadron_mode.root", "4660hadron_removedouble_mode.root",
    "4680hadron_mode.root", "4680hadron_removedouble_mode.root",
    "4700hadron_mode.root", "4700hadron_removedouble_mode.root" ]

c=TChain ("tree")

for i in range(len(f)):
    c.Add(f[i])
    print f[i], c.GetEntries()
    c.Reset()




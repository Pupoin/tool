import ROOT
from ROOT import * 

f=["4600data.root", "4600data_removedouble.root", 
    "4612data.root", "4612data_removedouble.root", 
    "4620data.root", "4620data_removedouble.root", 
    "4640data.root", "4640data_removedouble.root",
    "4660data.root","4660data_removedouble.root",
    "4680data.root","4680data_removedouble.root",
    "4700data.root","4700data_removedouble.root" ]

c=TChain ("tree")

for i in range(len(f)):
    c.Add(f[i])
    print f[i], c.GetEntries()
    c.Reset()




import ROOT
from ROOT import * 

f=["4600LL.root",  
    "4612LL.root", 
    "4620LL.root", 
    "4640LL.root",
    "4660LL.root",
    "4680LL.root",
    "4700LL.root"]

c=TChain ("tree_truth")

for i in range(len(f)):
    c.Add(f[i])
    al=c.GetEntries()
    sig=c.GetEntries("mode2==48 || mode3==48")
    print f[i], sig, al, 1.0*sig/al/2.0
    c.Reset()




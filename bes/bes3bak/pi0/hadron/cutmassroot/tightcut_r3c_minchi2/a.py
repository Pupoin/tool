import ROOT
from ROOT import * 

f=[ "4600hadron.root",  
    "4612hadron.root", 
    "4620hadron.root", 
    "4640hadron.root",
    "4660hadron.root",
    "4680hadron.root",
    "4700hadron.root"]

c=TChain ("tree_truth")

sum=0
sum_total=0
for i in range(len(f)):
    c.Add(f[i])
    # al=c.GetEntries("signal==1 || signal==-1")
    # al=c.GetEntries("mode2==35 || mode3==35")
    # al=c.GetEntries("mode2==12 || mode3==12")    
    al_t=c.GetEntries()   
    sum_total = sum_total+  al_t
    print f[i], al_t
    # sum = sum+al
    c.Reset()
print "sum", sum, sum_total



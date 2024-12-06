import ROOT
from ROOT import * 

f=[ "4600hadron_selB.root",  
    "4612hadron_selB.root", 
    "4620hadron_selB.root", 
    "4640hadron_selB.root",
    "4660hadron_selB.root",
    "4680hadron_selB.root",
    "4700hadron_selB.root"]

c=TChain ("tree")

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



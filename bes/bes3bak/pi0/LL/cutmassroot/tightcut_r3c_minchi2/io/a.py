import ROOT
from ROOT import * 

f=[ "../4600LL.root",  
    "../4612LL.root", 
    "../4620LL.root", 
    "../4640LL.root",
    "../4660LL.root",
    "../4680LL.root",
    "../4700LL.root"]

c=TChain ("tree_truth")

sum=0
sum_total=0
for i in range(len(f)):
    c.Add(f[i])
    # al=c.GetEntries("signal==1 || signal==-1")
    # al=c.GetEntries("mode2==35 || mode3==35")
    al=c.GetEntries("mode2==12 || mode3==12")    
    al_t=c.GetEntries()   
    sum_total = sum_total+  al_t
    print f[i], al, al_t
    sum = sum+al
    c.Reset()
print "sum", sum, sum_total



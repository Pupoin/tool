import ROOT
from ROOT import * 

f=[ "4600LL.root",  
    "4612LL.root", 
    "4620LL.root", 
    "4640LL.root",
    "4660LL.root",
    "4680LL.root",
    "4700LL.root"]

# ch=TChain ("tree_truth")

# sum_a=0
# sum_b=0
# sum_c=0
# a=0
# for i in range(len(f)):
#     ch.Add(f[i])
#     # a=ch.GetEntries("signal==1 || signal==-1")
#     # b=ch.GetEntries("mode2==35 || mode3==35")
#     b=ch.GetEntries("mode2==12 || mode3==12")    
#     c=ch.GetEntries()   
#     sum_c = sum_c +  c
#     sum_a = sum_a+a
#     sum_b = sum_b+b
#     print f[i], "a, b, c, a/c, b/c",  a, b, c, a*1.0/c, b*1.0/c
#     ch.Reset()
# print " sum_a, sum_b, sum_c,sum_a/sum_c, sum_b/sum_c ", sum_a, sum_b, sum_c, sum_a*1.0/sum_c, sum_b*1.0/sum_c


import ROOT
from ROOT import * 

f=[ "4600LL.root",  
    "4612LL.root", 
    "4620LL.root", 
    "4640LL.root",
    "4660LL.root",
    "4680LL.root",
    "4700LL.root"]

# ch=TChain ("tree_truth")

# sum_a=0
# sum_b=0
# sum_c=0
# a=0
# for i in range(len(f)):
#     ch.Add(f[i])
#     # a=ch.GetEntries("signal==1 || signal==-1")
#     b=ch.GetEntries("mode2==35 || mode3==35")
#     # al=c.GetEntries("mode2==12 || mode3==12")    
#     c=ch.GetEntries()   
#     sum_c = sum_c +  c
#     sum_a = sum_a+a
#     sum_b = sum_b+b
#     print f[i], "a, b, c, a/c, b/c",  a, b, c, a*1.0/c, b*1.0/c
#     ch.Reset()
# print " sum_a, sum_b, sum_c,sum_a/sum_c, sum_b/sum_c ", sum_a, sum_b, sum_c, sum_a*1.0/sum_c, sum_b*1.0/sum_c


ch=TChain ("tree")
sum_a=0
sum_b=0
sum_c=0
a=0
for i in range(len(f)):
    ch.Add(f[i])
    a=ch.GetEntries("signal==1 || signal==-1")
    # b=ch.GetEntries("mode2==35 || mode3==35")
    b=ch.GetEntries("mode2==12 || mode3==12")    
    c=ch.GetEntries()   
    sum_c = sum_c +  c
    sum_a = sum_a+a
    sum_b = sum_b+b
    print f[i], "a, b, c, a/c, b/c",  a, b, c, a*1.0/c, b*1.0/c
    ch.Reset()
print " sum_a, sum_b, sum_c,sum_a/sum_c, sum_b/sum_c ", sum_a, sum_b, sum_c, sum_a*1.0/sum_c, sum_b*1.0/sum_c



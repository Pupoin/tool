import ROOT
import sys
from DataFormats.FWLite import Events, Handle, Runs

from math import hypot, pi

events = Events (['./nomadspin.root'])
runs = Runs (['./nomadspin.root'])

file_out = open('fail.txt','w')

geninfo,geninfoLabel = Handle("GenEventInfoProduct"), "generator"
lheinfo,lheinfoLabel = Handle("LHEEventProduct"), "externalLHEProducer"
lheruninfo,lheruninfoLabel = Handle("LHERunInfoProduct"), "externalLHEProducer"
handlePruned  = Handle ("std::vector<reco::GenParticle>")
labelPruned = ("prunedGenParticles")

# loop over events
count= 0
countweighted = 0

count = count+1
runs.getByLabel(lheruninfoLabel,lheruninfo)
lherun = lheruninfo.product()
iiter = lherun.headers_begin()
print len(iiter.lines())
for ii in range(0,lherun.headers_size()-1):
    if ii<57: continue
#    if 'initrwgt' not in iiter.tag(): continue
    print 'tag:', iiter.tag()
    for iline in range(0,iiter.lines().size()):
       print iiter.lines()[iline]
    iiter = iiter+1

th1f_ele1_pt = ROOT.TH1F("ele1 pt","",11,25,300)
th1f_ele11_pt = ROOT.TH1F("ele11 pt","",11,25,300)
th1f_ele12_pt = ROOT.TH1F("ele12 pt","",11,25,300)
th1f_ele13_pt = ROOT.TH1F("ele13 pt","",11,25,300)
th1f_ele14_pt = ROOT.TH1F("ele14 pt","",11,25,300)
th1f_ele15_pt = ROOT.TH1F("ele15 pt","",11,25,300)
th1f_ele16_pt = ROOT.TH1F("ele16 pt","",11,25,300)
th1f_ele17_pt = ROOT.TH1F("ele17 pt","",11,25,300)
th1f_ele18_pt = ROOT.TH1F("ele18 pt","",11,25,300)
th1f_ele1_atgc1_pt = ROOT.TH1F("ele1 atgc1 pt","",11,25,300)
th1f_ele1_atgc124_pt = ROOT.TH1F("ele1 atgc124 pt","",11,25,300)
fail_count=0

for event in events:

    if count>0: break
    count = count+1
    if count % 10000 == 0:
        print "count = " + str(count)

    event.getByLabel(labelPruned, handlePruned)

    pruned = handlePruned.product()

    event.getByLabel(geninfoLabel,geninfo)
    event.getByLabel(lheinfoLabel,lheinfo)

#    gen = geninfo.product()
#    print 'Gen weights number:',gen.weights().size()
#    for i in range(0,gen.weights().size()):
#        print 'Gen weights:', gen.weights()[i]

    lhe = lheinfo.product() 
    if lhe.weights().size() !=236:
	file_out.write(str(lhe.weights().size()))
	file_out.write('\n')
	fail_count = fail_count+1
	continue
#    print 'originalXWGTUP:',lhe.originalXWGTUP()
#    print 'LHE weights number:',lhe.weights().size()
#    for i in range(0,lhe.weights().size()):
#        print 'LHE weights:', lhe.weights()[i].wgt
    weight_central= lhe.weights()[0].wgt
    weight_scale1 = lhe.weights()[1].wgt
    weight_scale2 = lhe.weights()[2].wgt
    weight_scale3 = lhe.weights()[3].wgt
    weight_scale4 = lhe.weights()[4].wgt
    weight_scale5 = lhe.weights()[5].wgt
    weight_scale6 = lhe.weights()[6].wgt
    weight_scale7 = lhe.weights()[7].wgt
    weight_scale8 = lhe.weights()[8].wgt
    weight_aTGC1 = lhe.weights()[112].wgt/lhe.weights()[173].wgt*weight_central
    weight_aTGC124 = lhe.weights()[235].wgt/lhe.weights()[173].wgt*weight_central

    ele1_pt = 0
    for p in pruned :
        if abs(p.pdgId()) == 11 and p.pt() > 25 and abs(p.eta()) < 2.5 and (p.statusFlags().isPrompt()) and p.status() == 1  :
	    if p.pt>ele1_pt: ele1_pt = p.pt()
    th1f_ele1_pt.Fill(ele1_pt, weight_central)
    th1f_ele11_pt.Fill(ele1_pt, weight_scale1)
    th1f_ele12_pt.Fill(ele1_pt, weight_scale2)
    th1f_ele13_pt.Fill(ele1_pt, weight_scale3)
    th1f_ele14_pt.Fill(ele1_pt, weight_scale4)
    th1f_ele15_pt.Fill(ele1_pt, weight_scale5)
    th1f_ele16_pt.Fill(ele1_pt, weight_scale6)
    th1f_ele17_pt.Fill(ele1_pt, weight_scale7)
    th1f_ele18_pt.Fill(ele1_pt, weight_scale8)
    th1f_ele1_atgc1_pt.Fill(ele1_pt, weight_aTGC1)
    th1f_ele1_atgc124_pt.Fill(ele1_pt, weight_aTGC124)

print 'fail count,', fail_count
f=ROOT.TFile.Open('out.root','RECREATE')
f.cd()
th1f_ele1_pt.Write()
th1f_ele11_pt.Write()
th1f_ele12_pt.Write()
th1f_ele13_pt.Write()
th1f_ele14_pt.Write()
th1f_ele15_pt.Write()
th1f_ele16_pt.Write()
th1f_ele17_pt.Write()
th1f_ele18_pt.Write()
th1f_ele1_atgc1_pt.Write()
th1f_ele1_atgc124_pt.Write()
f.Close()
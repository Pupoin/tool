import ROOT;
from root_numpy import root2array
import numpy as np
import sys, os
import pickle
# from matplotlib import pyplot as plt
from ROOT import TFile, TTree, AddressOf
import sys
from DataFormats.FWLite import Events, Handle
from array import array
from math import hypot, pi
import codecs
ROOT.gSystem.Load("libFWCoreFWLite.so")
ROOT.gSystem.Load("libDataFormatsFWLite.so")
ROOT.gSystem.Load("libDataFormatsPatCandidates.so")

out = TFile( 'outputRootFile.root', 'RECREATE' )
tree = TTree('test','a test tree')
t1_px = array('d',[0])
t1_py = array('d',[0])
t1_pz = array('d',[0])
t1_e = array('d',[0])
t2_px = array('d',[0])
t2_py = array('d',[0])
t2_pz = array('d',[0])
t2_e = array('d',[0])
mtt = array('d',[0])
ht = array('d',[0])
wpt=array('d',[0])
pid=array('d',[0])
wpt_r=array('d',[0])
lx_r=array('d',[0])
nuy_r=array('d',[0])
ly_r=array('d',[0])
nux_r=array('d',[0])


tree.Branch('t1_px',t1_px,'t1_px/D')
tree.Branch('t1_py',t1_py,'t1_py/D')
tree.Branch('t1_pz',t1_pz,'t1_pz/D')
tree.Branch('t1_e',t1_e,'t1_e/D')
tree.Branch('t2_px',t2_px,'t2_px/D')
tree.Branch('t2_py',t2_py,'t2_py/D')
tree.Branch('t2_pz',t2_pz,'t2_pz/D')
tree.Branch('t2_e',t2_e,'t2_e/D')
tree.Branch('mtt',mtt,'mtt/D')
tree.Branch('ht',ht,'ht/D')
tree.Branch('wpt',wpt,'wpt/D')
tree.Branch('pid',pid,'pid/D')
tree.Branch('lx_r',lx_r,'lx_r/D')
tree.Branch('nuy_r',nuy_r,'nuy_r/D')
tree.Branch('wpt_r',wpt_r,'wpt_r/D')
tree.Branch('ly_r',lx_r,'lx_r/D')
tree.Branch('nux_r',nux_r,'nux_r/D')

count = 0
string = []
string.append("inputRootFile.root")

events_test = Events(string)
geninfo,geninfoLabel = Handle("GenEventInfoProduct"), "generator"
handlePruned  = Handle ("std::vector<reco::GenParticle>")
            #labelPruned = ("genParticles")
labelPruned = ("genParticles")


for event in events_test:
    #if count > 101:
    #    break
    if count % 2500 == 0:
        print "count = " + str(count)
    count +=1

    event.getByLabel (labelPruned, handlePruned)
    pruned = handlePruned.product()

    event.getByLabel(geninfoLabel,geninfo)
    gen = geninfo.product()
    
    t1_px[0] = 0.0
    t1_py[0] = 0.0
    t1_pz[0] = 0.0
    t1_e[0] = 0.0

    t2_px[0] = 0.0
    t2_py[0] = 0.0
    t2_pz[0] = 0.0
    t2_e[0] = 0.0
    mtt[0] = 0.0
    num_t=0
    ht[0]=0.0
    wpt[0]=0.0
    pid[0]=0.0
    lx_r[0]=0.0
    nuy_r[0]=0.0
    wpt_r[0]=0.0
    ly_r[0]=0.0
    nux_r[0]=0.0
    for p in pruned :
        if (abs(p.pdgId())<6 or abs(p.pdgId())==21) and p.status()==23 and abs(p.mother().pdgId()) != 6 and abs(p.mother().pdgId()) != 24 and abs(p.mother().pdgId()) != 25 and abs(p.mother().pdgId()) !=23:
            ht[0] = ht[0] + p.pt()
#            print ht[0]
        if abs(p.pdgId())== 24 and abs(pruned.at(p.daughterRef(0).index()).pdgId())!=24  and abs(pruned.at(p.daughterRef(1).index()).pdgId())!=24:#numberOfDaughters() != 1:
            wpt[0]= p.pt()
            lx_r[0]=pruned.at(p.daughterRef(0).index()).px()
            ly_r[0]=pruned.at(p.daughterRef(0).index()).py()
            nux_r[0]=pruned.at(p.daughterRef(1).index()).px()
            nuy_r[0]=pruned.at(p.daughterRef(1).index()).py()
            wpt_r[0] = ((lx_r[0]+nux_r[0])*(lx_r[0]+nux_r[0]) +(ly_r[0]+nuy_r[0])*(ly_r[0]+nuy_r[0]))**0.5
    tree.Fill()

out.cd()
out.Write()
out.Close()

import os
import sys
import optparse
import ROOT
import math
import collections


from ROOT import TH1F, TFile, TTree, TLorentzVector, TVectorD
from optparse import OptionParser
from math import cos, sin, sinh
MW_=80.379
Z_mass = 91.1876

class extend_p4:
  p4_vector=ROOT.TLorentzVector()
  pdgid=11
  def __init__(self, ltvector, pid):
    self.p4_vector=ltvector
    self.pdgid = pid

def mll(lep):
  zp4_tmp = collections.OrderedDict()
  zp4 = collections.OrderedDict()
  z1p4 = ROOT.TLorentzVector()
  z2p4 = ROOT.TLorentzVector()
  for i in range(len(lep)):
    for j in range(i+1, len(lep)):
      if (lep[i].pdgid + lep[j].pdgid) == 0:
        zp4_tmp[str(i) + str(j)] = lep[i].p4_vector + lep[j].p4_vector
  for key in list(zp4_tmp.keys()):
    for key2 in list(zp4_tmp.keys()):
      if (len(set(key)&set(key2)) == 0):
        zp4[key] = zp4_tmp[key]
        zp4[key2] = zp4_tmp[key2]
        del zp4_tmp[key]
        del zp4_tmp[key2]
  #end the group(1st, 2nd), group(3rd, 4th), of zp4
  
  list_zp4=list(zp4.values())
  if len(zp4) == 2:
      list_zp4.sort(key=lambda x: x.Pt(),reverse=True)
      z1p4 = list_zp4[0]
      z2p4 = list_zp4[1]
  if len(zp4) == 4:
    a = (list_zp4[0].M() - Z_mass)**2 + (list_zp4[1].M() - Z_mass)**2
    b = (list_zp4[2].M() - Z_mass)**2 + (list_zp4[3].M() - Z_mass)**2
    if a < b:
      c = [list_zp4[0], list_zp4[1]]
      c.sort(key=lambda x: x.Pt(),reverse=True)
      z1p4 = c[0]
      z2p4 = c[1]
    else:
      c = [list_zp4[2], list_zp4[3]]
      c.sort(key=lambda x: x.Pt(),reverse=True)
      z1p4 = c[0]
      z2p4 = c[1]
    #--end
  return z1p4, z2p4


# def mll(lep):
#
#  zp4_tmp = dict()
#  zp4 = dict()
#
#  for i in range(len(lep)):
#    for j in range(i+1, len(lep)):
#      if (lep[i].pdgid + lep[j].pdgid) == 0:
#        zp4_tmp[str(i) + str(j)] = lep[i].p4_vector + lep[j].p4_vector
#
#  minz_key = min(zp4_tmp, key=lambda k: abs((zp4_tmp[k]).M() - Z_mass))
#  minz_p4 = zp4_tmp[minz_key]
#  zp4[minz_key] = minz_p4
#
#  for key in zp4_tmp.keys():
#    if (len(set(key)&set(minz_key)) == 0):
#        zp4[key] = zp4_tmp[key]
#        return zp4[minz_key], zp4[key]
#        break

def wreco(lepp4, metpt, metphi):
  nu4=TLorentzVector()
  px=metpt*cos(metphi)
  py=metpt*sin(metphi)
  pz=0.
  pxl=lepp4.Px()
  pyl=lepp4.Py()
  pzl=lepp4.Pz()
  El=lepp4.E()
  a=MW_*MW_ + 2.*pxl*px + 2.*pyl*py
  A=4.*(El*El - pzl*pzl)
  B=-4.*a*pzl
  C=4.*El*El*(px*px+py*py)-a*a
  tmproot=B*B - 4.*A*C

  if tmproot<0:
    pz=-1.*B/(2*A)
  else:
    tmpsol1 = (-B + math.sqrt(tmproot))/(2.0*A)
    tmpsol2 = (-B - math.sqrt(tmproot))/(2.0*A)
    if abs(tmpsol2-pzl)<abs(tmpsol1-pzl):
      pz=tmpsol2
    else:
      pz=tmpsol1
  if abs(pz)>300:
    if abs(tmpsol1)<abs(tmpsol2):
      pz=tmpsol1
    else:
      pz=tmpsol2
  nu4.SetPxPyPzE(px,py,pz,math.sqrt(px*px+py*py+pz*pz))
  wp4=lepp4+nu4
  return wp4

def main():
  usage = 'usage: %prog [options]'
  parser = optparse.OptionParser(usage)
  parser.add_option('-i', '--in', dest='inputfiles', help='name of input files', default=None, type='string')
  parser.add_option('-o', '--out', dest='outputfiles', help='name output files', default=None, type='string')
  (opt, args) = parser.parse_args()

  h_weight = TH1F('weight','weight',2,-1,1)
  ####################  histos #########################################
  h_lep1pt_LHE = TH1F('lep1pt_LHE', 'lep1pt_LHE', 75, 0, 150)
  h_lep1eta_LHE = TH1F('lep1eta_LHE', 'lep1eta_LHE', 60, -3, 3)
  h_lep1phi_LHE = TH1F('lep1phi_LHE', 'lep1phi_LHE', 80, -4, 4)
  h_lep2pt_LHE = TH1F('lep2pt_LHE', 'lep2pt_LHE', 75, 0, 150)
  h_lep2eta_LHE = TH1F('lep2eta_LHE', 'lep2eta_LHE', 60, -3, 3)
  h_lep2phi_LHE = TH1F('lep2phi_LHE', 'lep2phi_LHE', 80, -4, 4)
  h_lep3pt_LHE = TH1F('lep3pt_LHE', 'lep3pt_LHE', 75, 0, 150)
  h_lep3eta_LHE = TH1F('lep3eta_LHE', 'lep3eta_LHE', 60, -3, 3)
  h_lep3phi_LHE = TH1F('lep3phi_LHE', 'lep3phi_LHE', 80, -4, 4)
  h_lep4pt_LHE = TH1F('lep4pt_LHE', 'lep4pt_LHE', 75, 0, 150)
  h_lep4eta_LHE = TH1F('lep4eta_LHE', 'lep4eta_LHE', 60, -3, 3)
  h_lep4phi_LHE = TH1F('lep4phi_LHE', 'lep4phi_LHE', 80, -4, 4)
  h_apt_LHE = TH1F('apt_LHE', 'apt_LHE', 75, 0, 50)
  h_aeta_LHE = TH1F('aeta_LHE', 'aeta_LHE', 60, -3, 6)
  h_aphi_LHE = TH1F('aphi_LHE', 'aphi_LHE', 80, -4, 4)

  h_Z1mass_LHE = TH1F('Z1mass_LHE', 'Z1mass_LHE', 80, 0, 130)
  h_Z1pt_LHE = TH1F('Z1pt_LHE', 'Z1pt_LHE', 100, 0, 200)
  h_Z1eta_LHE = TH1F('Z1eta_LHE', 'Z1eta_LHE', 100, -5, 5)
  h_Z1phi_LHE = TH1F('Z1phi_LHE', 'Z1phi_LHE', 80, -4, 4)
  h_Z2mass_LHE = TH1F('Z2mass_LHE', 'Z2mass_LHE', 80, 0, 130)
  h_Z2pt_LHE = TH1F('Z2pt_LHE', 'Z2pt_LHE', 100, 0, 200)
  h_Z2eta_LHE = TH1F('Z2eta_LHE', 'Z2eta_LHE', 100, -5, 5)
  h_Z2phi_LHE = TH1F('Z2phi_LHE', 'Z2phi_LHE', 80, -4, 4)

  h_Vpt_LHE = TH1F('Vpt_LHE', 'Vpt_LHE', 75, 0, 150)
  
  h_Dressedlep1pt_GEN = TH1F('Dressedlep1pt_GEN', 'Dressedlep1pt_GEN', 75, 0, 150)
  h_Dressedlep1eta_GEN = TH1F('Dressedlep1eta_GEN', 'Dressedlep1eta_GEN', 60, -3, 3)
  h_Dressedlep1phi_GEN = TH1F('Dressedlep1phi_GEN', 'Dressedlep1phi_GEN', 80, -4, 4)
  h_Dressedlep2pt_GEN = TH1F('Dressedlep2pt_GEN', 'Dressedlep2pt_GEN', 75, 0, 150)
  h_Dressedlep2eta_GEN = TH1F('Dressedlep2eta_GEN', 'Dressedlep2eta_GEN', 60, -3, 3)
  h_Dressedlep2phi_GEN = TH1F('Dressedlep2phi_GEN', 'Dressedlep2phi_GEN', 80, -4, 4)
  h_Dressedlep3pt_GEN = TH1F('Dressedlep3pt_GEN', 'Dressedlep3pt_GEN', 75, 0, 150)
  h_Dressedlep3eta_GEN = TH1F('Dressedlep3eta_GEN', 'Dressedlep3eta_GEN', 60, -3, 3)
  h_Dressedlep3phi_GEN = TH1F('Dressedlep3phi_GEN', 'Dressedlep3phi_GEN', 80, -4, 4)
  h_Dressedlep4pt_GEN = TH1F('Dressedlep4pt_GEN', 'Dressedlep4pt_GEN', 75, 0, 150)
  h_Dressedlep4eta_GEN = TH1F('Dressedlep4eta_GEN', 'Dressedlep4eta_GEN', 60, -3, 3)
  h_Dressedlep4phi_GEN = TH1F('Dressedlep4phi_GEN', 'Dressedlep4phi_GEN', 80, -4, 4)
  
  h_apt_GEN = TH1F('apt_GEN', 'apt_GEN', 75, 0, 50)
  h_aeta_GEN = TH1F('aeta_GEN', 'aeta_GEN', 60, -3, 3)
  h_aphi_GEN = TH1F('aphi_GEN', 'aphi_GEN', 80, -4, 4)

  h_Z1mass_GEN = TH1F('Z1mass_GEN', 'Z1mass_GEN', 80, 0, 130)
  h_Z1pt_GEN = TH1F('Z1pt_GEN', 'Z1pt_GEN', 100, 0, 200)
  h_Z1eta_GEN = TH1F('Z1eta_GEN', 'Z1eta_GEN', 100, -5, 5)
  h_Z1phi_GEN = TH1F('Z1phi_GEN', 'Z1phi_GEN', 80, -4, 4)
  h_Z2mass_GEN = TH1F('Z2mass_GEN', 'Z2mass_GEN', 80, 0, 130)
  h_Z2pt_GEN = TH1F('Z2pt_GEN', 'Z2pt_GEN', 100, 0, 200)
  h_Z2eta_GEN = TH1F('Z2eta_GEN', 'Z2eta_GEN', 100, -5, 5)
  h_Z2phi_GEN = TH1F('Z2phi_GEN', 'Z2phi_GEN', 80, -4, 4)

  
  h_drl1l2_GEN = TH1F('drl1l2_GEN', 'drl1l2_GEN', 60, 0, 3)
  h_drl1l3_GEN = TH1F('drl1l3_GEN', 'drl1l3_GEN', 60, 0, 3)
  h_drl1l4_GEN = TH1F('drl1l4_GEN', 'drl1l4_GEN', 60, 0, 3)
  h_drl2l3_GEN = TH1F('drl2l3_GEN', 'drl2l3_GEN', 60, 0, 3)
  h_drl2l4_GEN = TH1F('drl2l4_GEN', 'drl2l4_GEN', 60, 0, 3)
  h_drl3l4_GEN = TH1F('drl3l4_GEN', 'drl3l4_GEN', 60, 0, 3)
  h_drl1a_GEN = TH1F('drl1a_GEN', 'drl1a_GEN', 60, 0, 3)
  h_drl2a_GEN = TH1F('drl2a_GEN', 'drl2a_GEN', 60, 0, 3)
  h_drl3a_GEN = TH1F('drl3a_GEN', 'drl3a_GEN', 60, 0, 3)
  h_drl4a_GEN = TH1F('drl4a_GEN', 'drl4a_GEN', 60, 0, 3)
  h_drz1a_GEN = TH1F('drz1a_GEN', 'drz1a_GEN', 60, 0, 6)
  h_drz2a_GEN = TH1F('drz2a_GEN', 'drz2a_GEN', 60, 0, 6)
  h_drz1z2_GEN = TH1F('drz1z2_GEN', 'drz1z2_GEN', 60, 0, 6)

  h_Vistaupt_GEN = TH1F('Vistaupt_GEN', 'Vistaupt_GEN', 100, 0, 200)
  h_Vistaueta_GEN = TH1F('Vistaueta_GEN', 'Vistaueta_GEN', 60, -3, 3)
  h_Vistauphi_GEN = TH1F('Vistauphi_GEN', 'Vistauphi_GEN', 80, -4, 4)
  h_METpt_GEN = TH1F('METpt_GEN', 'METpt_GEN', 50, 0, 100)
  h_METphi_GEN = TH1F('METphi_GEN', 'METphi_GEN', 80, -4, 4)
  h_mzz_GEN = TH1F('mzz_GEN', 'mzz_GEN', 100, 0, 300)
  
  #######################  add histos dictionary ##############################
  histo_array = {}
  histo_array['h_weight']=h_weight
  histo_array['h_lep1pt_LHE']=h_lep1pt_LHE
  histo_array['h_lep1eta_LHE']=h_lep1eta_LHE
  histo_array['h_lep1phi_LHE']=h_lep1phi_LHE
  histo_array['h_lep2pt_LHE']=h_lep2pt_LHE
  histo_array['h_lep2eta_LHE']=h_lep2eta_LHE
  histo_array['h_lep2phi_LHE'] = h_lep2phi_LHE
  histo_array['h_lep3pt_LHE']=h_lep3pt_LHE
  histo_array['h_lep3eta_LHE']=h_lep3eta_LHE
  histo_array['h_lep3phi_LHE'] = h_lep3phi_LHE
  histo_array['h_lep4pt_LHE']=h_lep4pt_LHE
  histo_array['h_lep4eta_LHE']=h_lep4eta_LHE
  histo_array['h_lep4phi_LHE'] = h_lep4phi_LHE
  histo_array['h_Vpt_LHE'] = h_Vpt_LHE
  
  histo_array['h_Z1mass_LHE']=h_Z1mass_LHE
  histo_array['h_Z1pt_LHE']=h_Z1pt_LHE
  histo_array['h_Z1eta_LHE']=h_Z1eta_LHE
  histo_array['h_Z1phi_LHE']=h_Z1phi_LHE
  histo_array['h_Z2mass_LHE']=h_Z2mass_LHE
  histo_array['h_Z2pt_LHE']=h_Z2pt_LHE
  histo_array['h_Z2eta_LHE']=h_Z2eta_LHE
  histo_array['h_Z2phi_LHE']=h_Z2phi_LHE

  histo_array['h_apt_LHE'] = h_apt_LHE
  histo_array['h_aeta_LHE'] = h_aeta_LHE
  histo_array['h_aphi_LHE'] = h_aphi_LHE


  histo_array['h_Dressedlep1pt_GEN']=h_Dressedlep1pt_GEN
  histo_array['h_Dressedlep1eta_GEN']=h_Dressedlep1eta_GEN
  histo_array['h_Dressedlep1phi_GEN']=h_Dressedlep1phi_GEN
  histo_array['h_Dressedlep2pt_GEN']=h_Dressedlep2pt_GEN
  histo_array['h_Dressedlep2eta_GEN']=h_Dressedlep2eta_GEN
  histo_array['h_Dressedlep2phi_GEN'] = h_Dressedlep2phi_GEN
  histo_array['h_Dressedlep3pt_GEN']=h_Dressedlep3pt_GEN
  histo_array['h_Dressedlep3eta_GEN']=h_Dressedlep3eta_GEN
  histo_array['h_Dressedlep3phi_GEN'] = h_Dressedlep3phi_GEN
  histo_array['h_Dressedlep4pt_GEN']=h_Dressedlep4pt_GEN
  histo_array['h_Dressedlep4eta_GEN']=h_Dressedlep4eta_GEN
  histo_array['h_Dressedlep4phi_GEN'] = h_Dressedlep4phi_GEN
  histo_array['h_apt_GEN']=h_apt_GEN
  histo_array['h_aeta_GEN']=h_aeta_GEN
  histo_array['h_aphi_GEN'] = h_aphi_GEN

  histo_array['h_Z1mass_GEN']=h_Z1mass_GEN
  histo_array['h_Z1pt_GEN']=h_Z1pt_GEN
  histo_array['h_Z1eta_GEN']=h_Z1eta_GEN
  histo_array['h_Z1phi_GEN']=h_Z1phi_GEN
  histo_array['h_Z2mass_GEN']=h_Z2mass_GEN
  histo_array['h_Z2pt_GEN']=h_Z2pt_GEN
  histo_array['h_Z2eta_GEN']=h_Z2eta_GEN
  histo_array['h_Z2phi_GEN']=h_Z2phi_GEN
  
  histo_array['h_drl1l2_GEN'] = h_drl1l2_GEN
  histo_array['h_drl1l3_GEN'] = h_drl1l3_GEN
  histo_array['h_drl1l4_GEN'] = h_drl1l4_GEN
  histo_array['h_drl2l3_GEN'] = h_drl2l3_GEN
  histo_array['h_drl2l4_GEN'] = h_drl2l4_GEN
  histo_array['h_drl3l4_GEN'] = h_drl3l4_GEN
  histo_array['h_drl1a_GEN'] = h_drl1a_GEN
  histo_array['h_drl2a_GEN'] = h_drl2a_GEN
  histo_array['h_drl3a_GEN'] = h_drl3a_GEN
  histo_array['h_drl4a_GEN'] = h_drl4a_GEN

  histo_array['h_drz1a_GEN'] = h_drz1a_GEN
  histo_array['h_drz2a_GEN'] = h_drz2a_GEN
  histo_array['h_drz1z2_GEN'] = h_drz1z2_GEN

  histo_array['h_Vistaupt_GEN']=h_Vistaupt_GEN
  histo_array['h_Vistaueta_GEN']=h_Vistaueta_GEN
  histo_array['h_Vistauphi_GEN']=h_Vistauphi_GEN
  histo_array['h_METpt_GEN']=h_METpt_GEN
  histo_array['h_METphi_GEN'] = h_METphi_GEN
  histo_array['h_mzz_GEN'] = h_mzz_GEN
  

  for key in histo_array:
    histo_array[key].SetStats(0)
    histo_array[key].Sumw2()
    histo_array[key].GetYaxis().SetTitle("a.u.")
    histo_array[key].GetYaxis().SetTitleSize(0.05)
    histo_array[key].GetYaxis().SetTitleOffset(0.75)
    histo_array[key].GetXaxis().SetTitle(key)
    histo_array[key].SetMinimum(0)

  if not os.path.isfile(opt.inputfiles):
    print 'inputfile does not exist!!'
  filein=TFile.Open(opt.inputfiles)
  treein=filein.Get('Events')
  npos=treein.GetEntries('genWeight>0')
  nneg=treein.GetEntries('genWeight<0')
  h_weight.SetBinContent(1,nneg)
  h_weight.SetBinContent(2,npos)

  for entry in range(0,treein.GetEntries()):
    p4temp = TLorentzVector()
    wp4temp=TLorentzVector()
    zp4 = TLorentzVector()
    LHElep = []
    LHEjet = []
    LHEa = []
    treein.GetEntry(entry)
    weight=(treein.genWeight)/(abs(treein.genWeight))

    # LHE info
    #histo_array['h_Vpt_LHE'].Fill(treein.LHE_Vpt, weight)
    #histo_array['h_Njets_LHE'].Fill(ord(treein.LHE_Njets), weight)
    #histo_array['h_HT_LHE'].Fill(treein.LHE_HT, weight)

    for iLHE in range(2,treein.nLHEPart):
      # LHE leptons
      if (abs(treein.LHEPart_pdgId[iLHE])==11 or abs(treein.LHEPart_pdgId[iLHE])==13):
        p4temp.SetPtEtaPhiM(treein.LHEPart_pt[iLHE], treein.LHEPart_eta[iLHE], treein.LHEPart_phi[iLHE], treein.LHEPart_mass[iLHE])
        LHElep.append(extend_p4(p4temp.Clone(), treein.LHEPart_pdgId[iLHE]))
      # LHE jets
      if treein.LHEPart_status[iLHE] == 1 and (abs(treein.LHEPart_pdgId[iLHE]) == 1 or abs(treein.LHEPart_pdgId[iLHE]) == 2 or
                                               abs(treein.LHEPart_pdgId[iLHE]) == 3 or abs(treein.LHEPart_pdgId[iLHE]) == 4 or
                                               abs(treein.LHEPart_pdgId[iLHE]) == 5 or abs(treein.LHEPart_pdgId[iLHE]) == 21):
        p4temp.SetPtEtaPhiM(treein.LHEPart_pt[iLHE], treein.LHEPart_eta[iLHE], treein.LHEPart_phi[iLHE], treein.LHEPart_mass[iLHE])
        LHEjet.append(p4temp.Clone())
      if treein.LHEPart_pdgId[iLHE] == 22:
        p4temp.SetPtEtaPhiM(treein.LHEPart_pt[iLHE], treein.LHEPart_eta[iLHE], treein.LHEPart_phi[iLHE], treein.LHEPart_mass[iLHE])
        LHEa.append(p4temp.Clone())
    #--end loop LHEpart

    if len(LHElep) > 0: LHElep.sort(key=lambda x: x.p4_vector.Pt())  # sort the lep by pt
    if len(LHElep) == 4  and len(LHEa) == 1:
      histo_array['h_lep1pt_LHE'].Fill(LHElep[0].p4_vector.Pt(), weight)
      histo_array['h_lep2pt_LHE'].Fill(LHElep[1].p4_vector.Pt(), weight)
      histo_array['h_lep3pt_LHE'].Fill(LHElep[2].p4_vector.Pt(), weight)
      histo_array['h_lep4pt_LHE'].Fill(LHElep[3].p4_vector.Pt(), weight)
      histo_array['h_lep1eta_LHE'].Fill(LHElep[0].p4_vector.Eta(), weight)
      histo_array['h_lep2eta_LHE'].Fill(LHElep[1].p4_vector.Eta(), weight)
      histo_array['h_lep3eta_LHE'].Fill(LHElep[2].p4_vector.Eta(), weight)
      histo_array['h_lep4eta_LHE'].Fill(LHElep[3].p4_vector.Eta(), weight)
      histo_array['h_lep1phi_LHE'].Fill(LHElep[0].p4_vector.Phi(), weight)
      histo_array['h_lep2phi_LHE'].Fill(LHElep[1].p4_vector.Phi(), weight)
      histo_array['h_lep3phi_LHE'].Fill(LHElep[2].p4_vector.Phi(), weight)
      histo_array['h_lep4phi_LHE'].Fill(LHElep[3].p4_vector.Phi(), weight)

      histo_array['h_apt_LHE'].Fill(LHEa[0].Pt(), weight)
      histo_array['h_aphi_LHE'].Fill(LHEa[0].Phi(), weight)
      histo_array['h_aeta_LHE'].Fill(LHEa[0].Eta(), weight)


      minZ_lhe, otherZ_lhe = mll(LHElep)
      histo_array['h_Z1mass_LHE'].Fill(minZ_lhe.M(), weight)
      histo_array['h_Z1pt_LHE'].Fill(minZ_lhe.Pt(), weight)
      histo_array['h_Z1phi_LHE'].Fill(minZ_lhe.Phi(), weight)
      histo_array['h_Z1eta_LHE'].Fill(minZ_lhe.Eta(), weight)
      histo_array['h_Z2mass_LHE'].Fill(otherZ_lhe.M(), weight)
      histo_array['h_Z2pt_LHE'].Fill(otherZ_lhe.Pt(), weight)
      histo_array['h_Z2phi_LHE'].Fill(otherZ_lhe.Phi(), weight)
      histo_array['h_Z2eta_LHE'].Fill(otherZ_lhe.Eta(), weight)
    ##--end lhe info

    GENjet = []
    GENDressLep = []
    GENgamma_tmp = []
    GENgamma = []
    Gena = TLorentzVector()
    HT_GEN = 0.
    ##-GEN info
    if treein.nGenDressedLepton>0:
      for idressedlep in range(0, treein.nGenDressedLepton):
        if treein.GenDressedLepton_hasTauAnc[idressedlep]: continue
        p4temp.SetPtEtaPhiM(treein.GenDressedLepton_pt[idressedlep],treein.GenDressedLepton_eta[idressedlep],treein.GenDressedLepton_phi[idressedlep],treein.GenDressedLepton_mass[idressedlep])
        GENDressLep.append(extend_p4(p4temp.Clone(), treein.GenDressedLepton_pdgId[idressedlep]))
      #-sort by pt
      GENDressLep.sort(key=lambda x: x.p4_vector.Pt())
      if len(GENDressLep)==4:
        if GENDressLep[0].p4_vector.Pt() < 10:
          continue
        histo_array['h_Dressedlep1pt_GEN'].Fill(GENDressLep[0].p4_vector.Pt(), weight)
        histo_array['h_Dressedlep1eta_GEN'].Fill(GENDressLep[0].p4_vector.Eta(), weight)
        histo_array['h_Dressedlep1phi_GEN'].Fill(GENDressLep[0].p4_vector.Phi(), weight)
        histo_array['h_Dressedlep2pt_GEN'].Fill(GENDressLep[1].p4_vector.Pt(), weight)
        histo_array['h_Dressedlep2eta_GEN'].Fill(GENDressLep[1].p4_vector.Eta(), weight)
        histo_array['h_Dressedlep2phi_GEN'].Fill(GENDressLep[1].p4_vector.Phi(), weight)
        histo_array['h_Dressedlep3pt_GEN'].Fill(GENDressLep[2].p4_vector.Pt(), weight)
        histo_array['h_Dressedlep3eta_GEN'].Fill(GENDressLep[2].p4_vector.Eta(), weight)
        histo_array['h_Dressedlep3phi_GEN'].Fill(GENDressLep[2].p4_vector.Phi(), weight)
        histo_array['h_Dressedlep4pt_GEN'].Fill(GENDressLep[3].p4_vector.Pt(), weight)
        histo_array['h_Dressedlep4eta_GEN'].Fill(GENDressLep[3].p4_vector.Eta(), weight)
        histo_array['h_Dressedlep4phi_GEN'].Fill(GENDressLep[3].p4_vector.Phi(), weight)
      
        histo_array['h_drl1l2_GEN'].Fill(GENDressLep[0].p4_vector.DeltaR(GENDressLep[1].p4_vector), weight)
        histo_array['h_drl1l3_GEN'].Fill(GENDressLep[0].p4_vector.DeltaR(GENDressLep[2].p4_vector), weight)
        histo_array['h_drl1l4_GEN'].Fill(GENDressLep[0].p4_vector.DeltaR(GENDressLep[3].p4_vector), weight)
        histo_array['h_drl2l3_GEN'].Fill(GENDressLep[1].p4_vector.DeltaR(GENDressLep[2].p4_vector), weight)
        histo_array['h_drl2l4_GEN'].Fill(GENDressLep[1].p4_vector.DeltaR(GENDressLep[3].p4_vector), weight)
        histo_array['h_drl3l4_GEN'].Fill(GENDressLep[2].p4_vector.DeltaR(GENDressLep[3].p4_vector), weight)
      
        minZ_gen, otherZ_gen = mll(GENDressLep)
        histo_array['h_Z1mass_GEN'].Fill(minZ_gen.M(), weight)
        histo_array['h_Z1pt_GEN'].Fill(minZ_gen.Pt(), weight)
        histo_array['h_Z1phi_GEN'].Fill(minZ_gen.Phi(), weight)
        histo_array['h_Z1eta_GEN'].Fill(minZ_gen.Eta(), weight)
        histo_array['h_Z2mass_GEN'].Fill(otherZ_gen.M(), weight)
        histo_array['h_Z2pt_GEN'].Fill(otherZ_gen.Pt(), weight)
        histo_array['h_Z2phi_GEN'].Fill(otherZ_gen.Phi(), weight)
        histo_array['h_Z2eta_GEN'].Fill(otherZ_gen.Eta(), weight)
        histo_array['h_drz1z2_GEN'].Fill(otherZ_gen.DeltaR(minZ_gen), weight)
        histo_array['h_mzz_GEN'].Fill((minZ_gen + otherZ_gen).M(), weight)
        
    #--end nGenDressedLepton
    if len(GENDressLep)==4 and treein.nGenPart>0:
      for iGenPart in range(0, treein.nGenPart):
        if treein.GenPart_pdgId[iGenPart]==22: # and treein.GenPart_statusFlags[iGenPart] == 0
          p4temp.SetPtEtaPhiM(treein.GenPart_pt[iGenPart],treein.GenPart_eta[iGenPart],treein.GenPart_phi[iGenPart],treein.GenPart_mass[iGenPart])
          GENgamma_tmp.append(p4temp.Clone())
      for iGENgamma_tmp in range(0, len(GENgamma_tmp)):
        if GENDressLep[0].p4_vector.DeltaR(GENgamma_tmp[iGENgamma_tmp])>0.5 and GENDressLep[1].p4_vector.DeltaR(GENgamma_tmp[iGENgamma_tmp])>0.5 and GENDressLep[2].p4_vector.DeltaR(GENgamma_tmp[iGENgamma_tmp])>0.5 and GENDressLep[3].p4_vector.DeltaR(GENgamma_tmp[iGENgamma_tmp])>0.5:
          GENgamma.append(GENgamma_tmp[iGENgamma_tmp].Clone())
      GENgamma.sort(key=lambda x: x.Pt(), reverse=True)
      if len(GENgamma) == 0: continue
      Gena = GENgamma[0]
      # finished selecting gamma
      histo_array['h_apt_GEN'].Fill(Gena.Pt())
      histo_array['h_aeta_GEN'].Fill(Gena.Eta())
      histo_array['h_aphi_GEN'].Fill(Gena.Phi())
      histo_array['h_drl1a_GEN'].Fill(Gena.DeltaR(GENDressLep[0].p4_vector))
      histo_array['h_drl2a_GEN'].Fill(Gena.DeltaR(GENDressLep[1].p4_vector))
      histo_array['h_drl3a_GEN'].Fill(Gena.DeltaR(GENDressLep[2].p4_vector))
      histo_array['h_drl4a_GEN'].Fill(Gena.DeltaR(GENDressLep[3].p4_vector))
      histo_array['h_drz1a_GEN'].Fill(Gena.DeltaR(minZ_gen))
      histo_array['h_drz2a_GEN'].Fill(Gena.DeltaR(otherZ_gen))
    if treein.nGenVisTau>0:
      histo_array['h_Vistaupt_GEN'].Fill(treein.GenVisTau_pt[0], weight)
      histo_array['h_Vistaueta_GEN'].Fill(treein.GenVisTau_eta[0], weight)
      histo_array['h_Vistauphi_GEN'].Fill(treein.GenVisTau_phi[0], weight)
    histo_array['h_METpt_GEN'].Fill(treein.GenMET_pt, weight)
    histo_array['h_METphi_GEN'].Fill(treein.GenMET_phi, weight)

    #if entry > 10:
    #  break

  fileout=TFile.Open(opt.outputfiles+'.root','RECREATE')
  # fileout=TFile.Open(opt.outputfiles+'.root','UPDATE')
  fileout.cd()
  #print histo_array.keys()
  for key in histo_array:
    histo_array[key].Write()
  fileout.Close()

if __name__ == "__main__":
  sys.exit(main())

import ROOT
from ROOT import TCanvas
import time, sys
import os, hlt, mcInfo
from hlt import *
from mcInfo import *
import math
from math import sqrt
import plot_ZZregion





ROOT.gInterpreter.Declare("""
auto cal_ZZ(float Z1_pt, float Z1_eta, float Z1_phi, float Z1_mass,
                    float Z2_pt, float Z2_eta, float Z2_phi, float Z2_mass) 
{
    ROOT::Math::PtEtaPhiMVector Z1(Z1_pt,  Z1_eta,  Z1_phi,  Z1_mass);
    ROOT::Math::PtEtaPhiMVector Z2(Z2_pt,  Z2_eta,  Z2_phi,  Z2_mass);
    ROOT::Math::PtEtaPhiMVector ZZp4 = Z1+ Z2;
    ROOT::VecOps::RVec<float> ZZ;
    ZZ.emplace_back(ZZp4.Pt());
    ZZ.emplace_back(ZZp4.Eta());
    ZZ.emplace_back(ZZp4.Phi());
    ZZ.emplace_back(ZZp4.M());
    return  ZZ;
}
""")

a=ROOT.RDataFrame("tree", "MCroot/4600LL_mass.root").Range(10)
b=a.Define("ZZ","cal_ZZ(Z1_pt,  Z1_eta,  Z1_phi,  Z1_mass,  Z2_pt,  Z2_eta,  Z2_phi,  Z2_mass)")
b.Snapshot("Events","tmp.root")
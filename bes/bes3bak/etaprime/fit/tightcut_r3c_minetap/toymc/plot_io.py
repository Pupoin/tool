import ROOT
from ROOT import TH1F, TGraphErrors, TCanvas, TLine, TPaveText, TFile
import os
from array import array

import numpy as np

ROOT.gROOT.SetBatch(1)

# filepath="log.io_Br"
# f=open(filepath)


brv=array("f")
bre=array("f")
x=array("f")
ex=array("f")
i=1
# for line in f:
#     txt=line.split()
#     brv.append(float(txt[3]))
#     bre.append(float(txt[5]))
#     x.append(i)
#     i=i+1
#     ex.append(0)


fFile = TFile("Br.root", "READ")
fTree = fFile.Get("tree")
nEntries = fTree.GetEntries()
for i in range(0, nEntries):
    fTree.GetEntry(i)
    # if fTree.Brerr > 0.4:
    #  continue
    brv.append(fTree.Br)
    bre.append(fTree.Brerr)
    x.append(i)
    i=i+1
    ex.append(0)


# print bre
# print brv
c4 = TCanvas("c4","c4",700, 600)
c4.SetMargin(0.15, 0.03, 0.15, 0.1)


ge = TGraphErrors(len(brv), x, brv, ex, bre)
ge.SetMarkerStyle(20)
ge.SetTitle("")
# ge.SetTitle("Releative Branching Ratio", "y")
ge.SetMinimum(0)
ge.SetMaximum(1)
ge.GetXaxis().SetTitle("Times")
ge.GetXaxis().SetTitleSize(0.06)
ge.GetXaxis().SetLabelSize(0.045)

ge.GetYaxis().SetTitle("Relative BF")
ge.GetYaxis().SetTitleSize(0.06)
ge.GetYaxis().SetLabelSize(0.045)
ge.Draw("ap")

y=0.335808
print np.mean(brv), y
tline = TLine(0.6,y,len(brv),y) 
tline.SetLineWidth(2) 
tline.SetLineColor(2) 
tline.Draw()

tline2 = TLine(0.6,np.mean(brv) ,len(brv), np.mean(brv)) 
tline2.SetLineWidth(2) 
tline2.SetLineColor(3) 
tline2.Draw()

pt =  TPaveText(0.4, 0.67, 0.64, 0.87, "brNDC")
pt.SetBorderSize(0)
pt.SetFillColor(0)
#pt.SetLineColor(5)
#pt.SetTextColor(5)
pt.InsertText("#Lambda_{c}^{+} #rightarrow #Sigma^{+} #eta'")
# pt.InsertText(TString::Format("effic = %.2f %%", ISIG/all*100.))
pt.SetTextAlign(12)
pt.SetTextSize(0.06)
pt.Draw()

c4.SaveAs("toyio_etaprime.png")
c4.SaveAs("toyio_etaprime.pdf")
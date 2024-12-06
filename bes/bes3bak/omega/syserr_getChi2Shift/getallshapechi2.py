import ROOT
from ROOT import  TCanvas, TFile, TChain, TH1F, TTree, TCut, RooArgSet
from ROOT import  RooRealVar, RooDataSet, RooKeysPdf, RooWorkspace, RooPlot
from ROOT import *
from ROOT.RooFit import *
gROOT.SetBatch(kTRUE) # same to root -b

energy = [4600, 4612, 4620, 4640, 4660, 4680, 4700]

xmin = 2.25
xmax = 2.34919
xbins = 25
mbcmin = 2.25
mbcmax = 2.34919

cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919))"
# cut_deltaE_sig = "((deltaE_min>-0.03) && (deltaE_min<0.02))"
# cut_deltaE_ref = "((deltaE_min>-0.03) && (deltaE_min<0.02))"
cut_deltaE_sig = "( np!=0 && npbar !=0 )"
cut_deltaE_ref = "( np!=0 && npbar !=0 )"
cut_sig = (cut_mbc + " && "+  cut_deltaE_sig)
# cut_ref = (cut_mbc  + " && "+  cut_deltaE_ref)

chi2_min_r3c = RooRealVar("chi2_min_r3c", "chi2_min_r3c", 0, 100)

can = TCanvas("can", "pdf", 800, 600) 
# can.Divide(2, 7)
sig_fileDirPath="/publicfs/ucas/user/yuanchy8/7.0.6/omega/shape/cutmassroot/tightcut_r3c_minomega/"
# ref_fileDirPath="/publicfs/ucas/user/yuanchy8/7.0.6/pi0/shape_new/cutmassroot/tightcut_r3c_minchi2/"
#%% __ sig __

chain = TChain("tree")
for i in range(0, len(energy)):
    fff = sig_fileDirPath + "{0}shape_selB.root".format(energy[i])
    print fff
    chain.Add(fff)

# chain.Add("/publicfs/ucas/user/yuanchy8/7.0.6/eta/shape_new/cutmassroot/tightcut_r3c_minchi2/4600shape.root")   

tr_shape = chain.CopyTree(cut_sig, "")
shape = RooDataSet("shape", "#Chi^{2}", tr_shape, RooArgSet(chi2_min_r3c))

shapepdf = RooKeysPdf("modelPdf", "", chi2_min_r3c, shape, RooKeysPdf.NoMirror, 1 )  
wspace = RooWorkspace("wspace", "wspace title")
# wspace.Import(shapepdf) 
getattr(wspace,'import')(shapepdf)
wspace.writeToFile("allchi2_shapepdf.root")

frame = chi2_min_r3c.frame(ROOT.RooFit.Title("eta chi2 shape"))
shape.plotOn(frame)
shapepdf.plotOn(frame, ROOT.RooFit.LineStyle(kDashed), ROOT.RooFit.LineColor(2)) 

can.cd()
frame.Draw()
can.SaveAs("allchi2_shapepdf.png")


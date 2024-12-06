import ROOT
from ROOT import  TCanvas, TFile, TChain, TH1F, TTree, TCut, RooArgSet
from ROOT import  RooRealVar, RooDataSet, RooKeysPdf, RooWorkspace, RooPlot
from ROOT import *
from ROOT.RooFit import *
gROOT.SetBatch(1)

energy = [4600, 4612, 4620, 4640, 4660, 4680, 4700]

xmin = 2.25
xmax = 2.34919
xbins = 25
mbcmin = 2.25
mbcmax = 2.34919
cut_mbc = "((M_BC_r3c>=2.25) && (M_BC_r3c<=2.34919))"
# cut_deltaE_sig = "((deltaE_min>-0.03) && (deltaE_min<0.02))"
# cut_deltaE_ref = "((deltaE_min>-0.03) && (deltaE_min<0.02))"
cut_deltaE_sig = "(chi2_min_r3c<30 && np!=0 && npbar !=0 )"
cut_deltaE_ref = "(chi2_min_r3c<30 && np!=0 && npbar !=0 )"
cut_sig = (cut_mbc + " && "+  cut_deltaE_sig)
cut_ref = (cut_mbc  + " && "+  cut_deltaE_ref + " && "+ "(etaprimemr3c>0.6&&etaprimemr3c<0.92)")
# M_BC_r3c = RooRealVar("M_BC_r3c", "M_BC_r3c", mbcmin, mbcmax)

xmin = 2.25 
xmax_4600 = 2.299765
xmax_4612 = 2.30579
xmax_4620 = 2.31387
xmax_4640 = 2.320255
xmax_4660 = 2.33046
xmax_4680 = 2.34079
xmax_4700 = 2.34919

var_4600 = RooRealVar("etaprimemr3c","M_{BC}", 0.67, 0.9) 
var_4612 = RooRealVar("M_BC_r3c","M_{BC}", xmin, xmax_4612) 
var_4620 = RooRealVar("M_BC_r3c","M_{BC}", xmin, xmax_4620) 
var_4640 = RooRealVar("M_BC_r3c","M_{BC}", xmin, xmax_4640) 
var_4660 = RooRealVar("M_BC_r3c","M_{BC}", xmin, xmax_4660) 
var_4680 = RooRealVar("M_BC_r3c","M_{BC}", xmin, xmax_4680) 
var_4700 = RooRealVar("M_BC_r3c","M_{BC}", xmin, xmax_4700) 

var=[ var_4600, var_4612, var_4620, var_4640, var_4660, var_4680, var_4700]
name=["4600", "4612", "4620", "4640", "4660", "4680", "4700"]

can = TCanvas("can", "pdf", 700, 600) 
can.Divide(2, 7)
sig_fileDirPath="/publicfs/ucas/user/yuanchy8/7.0.6/etaprime/shape/cutmassroot/tightcut_r3c_minetap/"
ref_fileDirPath="/publicfs/ucas/user/yuanchy8/7.0.6/omega/shape/cutmassroot/tightcut_r3c_minomega/"
#%% __ sig __
# sig_filepath = []
# sig_filepath.append(sig_fileDirPath + "4600shape_selB.root")
# sig_filepath.append(sig_fileDirPath + "4612shape_selB.root")
# sig_filepath.append(sig_fileDirPath + "4620shape_selB.root")
# sig_filepath.append(sig_fileDirPath + "4640shape_selB.root")
# sig_filepath.append(sig_fileDirPath + "4660shape_selB.root")
# sig_filepath.append(sig_fileDirPath + "4680shape_selB.root")
# sig_filepath.append(sig_fileDirPath + "4700shape_selB.root")
#%% __ ref __

chain = TChain("tree")
chain.Add(ref_fileDirPath + "4600shape.root")
chain.Add(ref_fileDirPath + "4612shape.root")
chain.Add(ref_fileDirPath + "4620shape.root")
chain.Add(ref_fileDirPath + "4640shape.root")
chain.Add(ref_fileDirPath + "4660shape.root")
chain.Add(ref_fileDirPath + "4680shape.root")
chain.Add(ref_fileDirPath + "4700shape.root")

tr_shape = chain.CopyTree(cut_ref, "")
shape = RooDataSet("shape", "mBC(GeV)", tr_shape, RooArgSet( var[0]))
shapepdf = RooKeysPdf("modelPdf", "",  var[0], shape, RooKeysPdf.NoMirror) 

wspace_ref = RooWorkspace("wspace", "wspace_ref title")
# wspace_ref.import(shapepdf) 
getattr(wspace_ref,'import')(shapepdf)    
wspace_ref.writeToFile("omegashape.root")
    
frame = var[0].frame(ROOT.RooFit.Title("{} omega".format(str(energy[0]))), ROOT.RooFit.Bins(25))
shapepdf.plotOn(frame, ROOT.RooFit.LineStyle(kDashed), ROOT.RooFit.LineColor(2)) 
# can.cd(i+8) 
frame.Draw()

can.SaveAs("omegashape.png")


